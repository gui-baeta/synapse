#ifndef PKTGEN_SRC_PKTGEN_H_
#define PKTGEN_SRC_PKTGEN_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#define MIN_FLOWS_NUM 2

// To induce churn, flows are changed from time to time, alternating between an
// old and a new value. Naturally, alternating between these flows so fast that
// the time between alternation becomes smaller than the expiration time
// completely nullifies the churn. To really make sure that flows are expired,
// we only perform flow swapping after at least EPOCH_TIME *
// MIN_CHURN_ACTION_TIME_MULTIPLER time elapsed from the last swap.
#define MIN_CHURN_ACTION_TIME_MULTIPLER 3

// Maximum time (in seconds) to perform a flow swap, counting from the last
// performed swap.
#define MAX_CHURN_ACTION_TIME 1

typedef uint64_t byte_t;

typedef uint64_t time_us_t;
typedef uint64_t time_ns_t;

#define NS_TO_S(T) (((double)(T)) / 1e9)

typedef uint64_t churn_fpm_t;

typedef uint64_t rate_gbps_t;

struct config_t {
  uint64_t flows;
  time_ns_t exp_time;

  churn_fpm_t min_positive_churn; // non-zero
  churn_fpm_t max_churn;

  struct {
    uint16_t port;
    uint16_t cores;
  } tx;

  struct {
    uint16_t port;
    uint16_t cores;
  } rx;

  struct {
    bool running;
    uint64_t update_cnt;
    rate_gbps_t rate;
  } runtime;
};

extern struct config_t config;

void config_init(int argc, char **argv);
void config_print(void);
void config_print_usage(char **argv);

void pktgen_cmdline();
void pktgen_stats_display();

#ifdef __cplusplus
}
#endif

#endif  // PKTGEN_SRC_PKTGEN_H_
