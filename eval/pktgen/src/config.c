#include <getopt.h>
#include <inttypes.h>
#include <rte_common.h>
#include <rte_ethdev.h>
#include <stdio.h>
#include <stdlib.h>

#include "pktgen.h"

#define CMD_OPT_HELP "help"
#define CMD_OPT_TOTAL_FLOWS "total-flows"
#define CMD_OPT_TX_PORT "tx"
#define CMD_OPT_RX_PORT "rx"
#define CMD_OPT_NUM_TX_CORES "tx-cores"
#define CMD_OPT_NUM_RX_CORES "rx-cores"
#define CMD_OPT_EXP_TIME "exp-time"

struct config_t config;

enum {
  /* long options mapped to short options: first long only option value must
   * be >= 256, so that it does not conflict with short options.
   */
  CMD_OPT_HELP_NUM = 256,
  CMD_OPT_TOTAL_FLOWS_NUM,
  CMD_OPT_TX_PORT_NUM,
  CMD_OPT_RX_PORT_NUM,
  CMD_OPT_NUM_TX_CORES_NUM,
  CMD_OPT_NUM_RX_CORES_NUM,
  CMD_OPT_EXP_TIME_NUM,
};

/* if we ever need short options, add to this string */
static const char short_options[] = "";

static const struct option long_options[] = {
    {CMD_OPT_HELP, no_argument, NULL, CMD_OPT_HELP_NUM},
    {CMD_OPT_TOTAL_FLOWS, required_argument, NULL, CMD_OPT_TOTAL_FLOWS_NUM},
    {CMD_OPT_TX_PORT, required_argument, NULL, CMD_OPT_TX_PORT_NUM},
    {CMD_OPT_RX_PORT, required_argument, NULL, CMD_OPT_RX_PORT_NUM},
    {CMD_OPT_NUM_TX_CORES, required_argument, NULL, CMD_OPT_NUM_TX_CORES_NUM},
    {CMD_OPT_NUM_RX_CORES, required_argument, NULL, CMD_OPT_NUM_RX_CORES_NUM},
    {CMD_OPT_EXP_TIME, required_argument, NULL, CMD_OPT_EXP_TIME_NUM},
    {NULL, 0, NULL, 0}};

void config_print_usage(char **argv) {
  printf(
      "Usage:\n"
      "%s [EAL options] --\n"
      "\t[--help]: Show this help and exit\n"
      "\t --" CMD_OPT_TOTAL_FLOWS
      " <#flows>: Total number of flows\n"
      "\t --" CMD_OPT_TX_PORT
      " <port>: TX port\n"
      "\t --" CMD_OPT_RX_PORT
      " <port>: RX port\n"
      "\t --" CMD_OPT_NUM_TX_CORES
      " <#cores>: Number of TX cores\n"
      "\t --" CMD_OPT_NUM_RX_CORES
      " <#cores>: Number of RX cores\n"
      "\t --" CMD_OPT_EXP_TIME " <time>: Flow expiration time (in us)\n",
      argv[0]);
}

static uintmax_t parse_int(const char *str, const char *name) {
  char *temp;
  intmax_t result = strtoimax(str, &temp, 10);

  // There's also a weird failure case with overflows, but let's not care
  if (temp == str || *temp != '\0') {
    rte_exit(EXIT_FAILURE, "Error while parsing '%s': %s\n", name, str);
  }

  return result;
}

#define PARSER_ASSERT(cond, fmt, ...) \
  if (!(cond)) rte_exit(EXIT_FAILURE, fmt, ##__VA_ARGS__);

void config_init(int argc, char **argv) {
  // Default configuration values
  config.flows = 0;
  config.exp_time = 0;
  config.rx.port = 0;
  config.rx.cores = 0;
  config.tx.port = 0;
  config.tx.cores = 0;

  // Setup runtime configuration
  config.runtime.running = false;
  config.runtime.update_cnt = 0;
  config.runtime.rate = 0;

  unsigned nb_devices = rte_eth_dev_count_avail();
  unsigned nb_cores = rte_lcore_count();

  if (nb_devices < 2) {
    rte_exit(EXIT_FAILURE,
             "Insufficient number of available devices (%" PRIu16
             " detected, but we require at least 2).\n",
             nb_devices);
  }

  int opt;
  while ((opt = getopt_long(argc, argv, short_options, long_options, NULL)) !=
         EOF) {
    switch (opt) {
      case CMD_OPT_HELP_NUM: {
        config_print_usage(argv);
        exit(0);
      } break;
      case CMD_OPT_TOTAL_FLOWS_NUM: {
        config.flows = parse_int(optarg, CMD_OPT_TOTAL_FLOWS);
        PARSER_ASSERT(config.flows > 0,
                      "Number of flows must be positive (requested %" PRIu64
                      ").\n",
                      config.flows);
      } break;
      case CMD_OPT_TX_PORT_NUM: {
        config.tx.port = parse_int(optarg, CMD_OPT_TX_PORT);
        PARSER_ASSERT(config.tx.port < nb_devices,
                      "Invalid TX device: requested %" PRIu16
                      " but only %" PRIu16 " available.\n",
                      config.tx.port, nb_devices);
      } break;
      case CMD_OPT_RX_PORT_NUM: {
        config.rx.port = parse_int(optarg, CMD_OPT_RX_PORT);
        PARSER_ASSERT(config.rx.port < nb_devices,
                      "Invalid RX device: requested %" PRIu16
                      " but only %" PRIu16 " available.\n",
                      config.rx.port, nb_devices);
      } break;
      case CMD_OPT_NUM_TX_CORES_NUM: {
        config.tx.cores = parse_int(optarg, CMD_OPT_NUM_TX_CORES);
        PARSER_ASSERT(config.tx.cores > 0,
                      "Number of TX cores must be positive (requested %" PRIu16
                      ").\n",
                      config.tx.cores);
      } break;
      case CMD_OPT_NUM_RX_CORES_NUM: {
        config.rx.cores = parse_int(optarg, CMD_OPT_NUM_TX_CORES);
        PARSER_ASSERT(config.rx.cores > 0,
                      "Number of RX cores must be positive (requested %" PRIu16
                      ").\n",
                      config.rx.cores);
      } break;
      case CMD_OPT_EXP_TIME_NUM: {
        time_us_t exp_time = parse_int(optarg, CMD_OPT_EXP_TIME);
        config.exp_time = 1000 * exp_time;
      } break;
      default:
        rte_exit(EXIT_FAILURE, "Unknown option %c\n", opt);
    }
  }

  PARSER_ASSERT(config.tx.cores + config.rx.cores <= nb_cores,
                "Invalid number of cores (tx=%" PRIu16 ", rx=%" PRIu16
                ", available=%" PRIu16 ").\n",
                config.tx.cores, config.rx.cores, nb_cores);

  config.min_positive_churn = (60.0 * config.flows);
  config.max_churn = ((double)(60.0 * config.flows)) /
                     NS_TO_S(MIN_CHURN_ACTION_TIME_MULTIPLER * config.exp_time);

  PARSER_ASSERT(config.min_positive_churn < config.max_churn,
                "Invalid combination of expiration time and number of flows: "
                "min churn = %" PRIu64 " fpm, max churn = %" PRIu64 " fpm.\n",
                config.min_positive_churn, config.max_churn);

  // Reset getopt
  optind = 1;
}

void config_print(void) {
  printf("\n----- Config -----\n");

  printf("TX port:         %" PRIu16 "\n", config.tx.port);
  printf("RX port:         %" PRIu16 "\n", config.rx.port);
  printf("TX cores:        %" PRIu16 "\n", config.tx.cores);
  printf("RX cores:        %" PRIu16 "\n", config.rx.cores);
  printf("Flows:           %" PRIu64 "\n", config.flows);
  printf("Expiration time: %" PRIu64 " us\n", config.exp_time / 1000);
  printf("Min churn:       %" PRIu64 " fpm\n", config.min_positive_churn);
  printf("Max churn:       %" PRIu64 " fpm\n", config.max_churn);

  printf("------------------\n");
}
