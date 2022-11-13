#!/bin/sh

/sbin/rmmod ./driver.ko $* || exit 1

rm -f /dev/led
