#!/bin/sh

cd /kt6400

#tslib
export TSLIB_TSDEVICE=/dev/input/event1
export TSLIB_CONFFILE=/usr/local/tslib/etc/ts.conf
export TSLIB_PLUGINDIR=/usr/local/tslib/lib/ts
export TSLIB_CALIBFILE=/etc/pointercal

#qt
export QTDIR=/opt/qt-4.8.4
export QT_QWS_FONTDIR=$QTDIR/lib/fonts
export QWS_MOUSE_PROTO="tslib:/dev/input/event1"

#other
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./lib
export QWS_DISPLAY="LinuxFb:mmWidth100:mmHeight130:0" 

#prepare
rm /tmp/qtembedded-0/ -rf

mknod /dev/int_device c 310 0
insmod ./ko/kt6400_dev.ko

#run
killall app

chmod +x app
./app -qws &