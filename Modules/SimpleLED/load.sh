#!/bin/sh

/sbin/insmod ./driver.ko $* || exit 1

driver_major=`cat /proc/devices | awk "\\$2==\"led\" {print \\$1}"`

rm -f /dev/led
mknod /dev/led c $driver_major 129
