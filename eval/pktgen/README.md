# SyNAPSE traffic generator

```
$ sudo ./build/bin/pktgen --no-huge --no-shconf --vdev "net_tap0,iface=test_rx" --vdev "net_tap1,iface=test_tx" -- --total-flows 1 --tx 1 --rx 0 --tx-cores 4 --rx-cores 4
```