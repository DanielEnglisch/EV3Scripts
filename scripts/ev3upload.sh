#!/bin/bash
if [ $# -ne 2 ]
then
	echo "Error! Usage: uploadev3 <ip>"
	exit
fi
echo "=== EV3 Upload Script v.0.8 by Xer0 and peerfunk ==="
echo "Copying binary..."
scp $1 robot@$2:/home/robot/EV3Scripts
echo "Executing binary..."
ssh robot@$2 ./EV3Scripts
echo "=== Done ==="
