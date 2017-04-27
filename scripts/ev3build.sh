#!/bin/bash
echo "=== EV3 Build Script v.1.0 by Xer0 and peerfunk ==="
#BUILDING CURRENT DIRECTORY
FILES=`find . -type f -name "*.cpp" | tr -d ' '`
echo "Compiling files: $FILES"
arm-linux-gnueabi-g++ -o EV3Scripts $FILES -lev3dev -L./ -std=c++14 -static -fpermissive
echo "Done compiling and linking!"
if [ $# -eq 1 ]
then
	#UPLOADING
	echo "Copying binary..."
	scp ./EV3Scripts robot@$1:/home/robot/EV3Scripts
	echo "Executing binary..."
	ssh robot@$1 ./EV3Scripts
	echo "=== Done ==="
fi
