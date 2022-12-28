#!/bin/bash
RAMTOTAL="$(free | grep Mem | awk '{print $2}')"
RAMUSED="$(free | grep Mem | awk '{print $3}')"
RAMFREE="$(free | grep Mem | awk '{print $4}')"
SPACEROOT="$(df -hm / | grep / | awk '{print $2}')"
SPACEROOTU="$(df -hm / | grep / | awk '{print $3}')"
SPACEROOTF="$(df -hm / | grep / | awk '{print $4}')"

function getdata {
HOSTNAME=$(echo "HOSTNAME = "$(hostname)"")
TIMEZONE=$(echo "TIMEZONE = "$(timedatectl | grep "Time zone" | awk '{print $3 $4 $5}')"")
USER=$(echo "USER = "$(whoami)"")
OS=$(echo "OS = "$(cat /etc/issue)"")
DATE=$(echo "DATE = "$(date)"")
UPTIME=$(echo "UPTIME = "$(uptime -p)"")
UPTIME_SEC=$(echo "UPTIME_SEC = "$(awk '{print $1}' /proc/uptime)"")
IP=$(echo "IP = "$(ip a | grep inet | awk '{print $2}')"")
NETMASK=$(echo "NETMASK = "$(/sbin/ifconfig | grep netmask | awk '{print $4}')"")
GATEWAY=$(echo "GATEWAY = "$(ip -4 r show default)"")
RAMTOTAL=$(printf "RAM_TOTAL = %.3f" $((10**3 * $RAMTOTAL/1000000))e-3)
RAMUSED=$(printf "RAM_USED = %.3f" $((10**3 * $RAMUSED/1000000))e-3)
RAMFREE=$(printf "RAM_FREE = %.3f" $((10**3 * $RAMFREE/1000000))e-3)
SPACEROOT=$(printf "SPACE_ROOT = %.2f" $((10**2 * $SPACEROOT*1000/1024))e-2)
SPACEROOTU=$(printf "SPACE_USED = %.2f" $((10**2 * $SPACEROOTU*1000/1024))e-2)
SPACEROOTF=$(printf "SPACE_FREE = %.2f" $((10**2 * $SPACEROOTF*1000/1024))e-2)
TESTARR=("$HOSTNAME" "$TIMEZONE" "$USER" "$OS" "$DATE" "$UPTIME" "$UPTIME_SEC" "$IP" "$NETMASK" "$GATEWAY" "$RAMTOTAL" "$RAMUSED" "$RAMFREE" "$SPACEROOT" "$SPACEROOTU" "$SPACEROOTF")
}

