#!/bin/sh

if [ $# -eq 0 ];then
    echo "NO argument found !"
    echo "usage: ./set_ip interface [ip]"
    exit
fi


echo "interface: "$1
echo "ip: "$2

uci set network.$1.ipaddr=$2
uci commit network
/etc/init.d/network restart
