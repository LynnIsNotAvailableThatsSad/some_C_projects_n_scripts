#!/bin/bash
RAMTOTAL="$(free | grep Mem | awk '{print $2}')"
RAMUSED="$(free | grep Mem | awk '{print $3}')"
RAMFREE="$(free | grep Mem | awk '{print $4}')"
SPACEROOT="$(df -hm / | grep / | awk '{print $2}')"
SPACEROOTU="$(df -hm / | grep / | awk '{print $3}')"
SPACEROOTF="$(df -hm / | grep / | awk '{print $4}')"

function getdata {
HOSTNAME=$(echo "$(hostname)")
TIMEZONE=$(echo "$(timedatectl | grep "Time zone" | awk '{print $3 $4 $5}')")
USER=$(echo "$(whoami)")
OS=$(echo "$(cat /etc/issue | awk '{print $1" "$2" "$3}')")
DATE=$(echo "$(date)")
UPTIME=$(echo "$(uptime -p)")
UPTIME_SEC=$(echo "$(awk '{print $1}' /proc/uptime)")
IP=$(echo "$(ip a | grep inet | awk '{print $2}')")
NETMASK=$(echo "$(/sbin/ifconfig | grep netmask | awk '{print $4}')")
GATEWAY=$(echo ""$(ip -4 r show default)"")
RAMTOTAL=$(printf "%.3f" $((10**3 * $RAMTOTAL/1000000))e-3)
RAMUSED=$(printf "%.3f" $((10**3 * $RAMUSED/1000000))e-3)
RAMFREE=$(printf "%.3f" $((10**3 * $RAMFREE/1000000))e-3)
SPACEROOT=$(printf "%.2f" $((10**2 * $SPACEROOT*1000/1024))e-2)
SPACEROOTU=$(printf "%.2f" $((10**2 * $SPACEROOTU*1000/1024))e-2)
SPACEROOTF=$(printf "%.2f" $((10**2 * $SPACEROOTF*1000/1024))e-2)
VALUE=("$HOSTNAME" "$TIMEZONE" "$USER" "$OS" "$DATE" "$UPTIME" "$UPTIME_SEC" "$IP" "$NETMASK" "$GATEWAY" "$RAMTOTAL" "$RAMUSED" "$RAMFREE" "$SPACEROOT" "$SPACEROOTU" "$SPACEROOTF")
NAME=("HOSTNAME" "TIMEZONE" "USER" "OS" "DATE" "UPTIME" "UPTIME_SEC" "IP" "NETMASK" "GATEWAY" "RAM_TOTAL" "RAM_USED" "RAM_FREE" "SPACE_ROOT" "SPACE_USED" "SPACE_FREE")
}

