
#!/bin/bash
echo "=== EV3 Build Script v.2.0 by Xer0, peerfunk ==="
#BUILDING CURRENT DIRECTORY
FILES=`find . -type f -name "*.cpp" | tr -d ' '`
#FILES="$FILES `find . -type f -name "*.h" | tr -d ' '`"

printf "Linking and Compiling files:\n"
echo $FILES
#sleep 3
arm-linux-gnueabi-g++ -o EV3Scripts $FILES -lev3dev -L./ -std=c++14 -static -fpermissive
if [ $? -eq 1 ]
	then
		echo "!!! -> Build failed!"
		exit
	fi
echo "=== Building Done (size: $(($(stat -c%s 'EV3Scripts')/1024)) kB) ==="
if [ $# -eq 1 ]
then
	#UPLOADING
	echo "Copying binary..."
	sshpass -p 'Cisco0' scp ./EV3Scripts root@192.168.10.223:/home/robot/Gruppe1/Latest
	#nc $1 1222 < ./EV3Scripts
	if [ $? -eq 1 ]
	then
		echo "!!! -> Upload failed!"
		exit
	fi
	echo "=== Uploading Done ==="
	echo "Executing binary..."
	# $1
	sshpass -p 'Cisco0' ssh root@192.168.10.223 /home/robot/Gruppe1/Latest
	echo "=== Script Done ==="
fi
