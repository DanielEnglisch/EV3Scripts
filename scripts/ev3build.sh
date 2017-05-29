
#!/bin/bash
echo "=== EV3 Build Script v.1.2 by Xer0, peerfunk ==="
#BUILDING CURRENT DIRECTORY
FILES=`find . -type f -name "*.cpp" | tr -d ' '`
#FILES="$FILES `find . -type f -name "*.h" | tr -d ' '`"

printf "Linking and Compiling files:\n"
echo $FILES
#sleep 3
arm-linux-gnueabi-g++ -o EV3Scripts $FILES -lev3dev -L./ -std=c++14 -static -fpermissive
	echo "=== Building Done ==="
if [ $# -eq 1 ]
then
	#UPLOADING
	echo "Copying binary..."
	sshpass -p 'Cisco0' scp ./EV3Scripts robot@192.168.1.101:/home/robot/EV3Scripts
	if [ $? -eq 1 ]
	then
		echo "!!! -> Upload failed!"
		exit
	fi
	echo "=== Uploading Done ==="
	echo "Executing binary..."
	# $1
	sshpass -p 'Cisco0' ssh robot@192.168.1.101 ./EV3Scripts
	echo "=== Script Done ==="
fi
