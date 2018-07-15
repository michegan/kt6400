#!/bin/sh

#tslib
export TSLIB_TSDEVICE=/dev/input/event1
export TSLIB_CONFFILE=/usr/local/tslib/etc/ts.conf
export TSLIB_PLUGINDIR=/usr/local/tslib/lib/ts
export TSLIB_CALIBFILE=/etc/pointercal

#run
/usr/local/tslib/bin/ts_calibrate