
#!/bin/bash
echo "=== EV3 Build Script v.1.1 by Xer0 ==="
#BUILDING CURRENT DIRECTORY
FILES=`find . -type f -name "*.cpp" | tr -d ' '`
#FILES="$FILES `find . -type f -name "*.h" | tr -d ' '`"

printf "Linking and Compiling files:\n"
echo $FILES
#sleep 3
arm-linux-gnueabi-g++-5 -o EV3Scripts $FILES -lev3dev -L./ -std=c++14 -static -fpermissive
	echo "=== Building Done ==="
if [ $# -eq 1 ]
then
	#UPLOADING
	echo "Copying binary..."
	sshpass -p 'Cisco0' scp ./EV3Scripts robot@$1:/home/robot/EV3Scripts
	if [ $? -eq 1 ]
	then
		echo "!!! -> Upload failed!"
		exit
	fi
	echo "=== Uploading Done ==="
	echo "Executing binary..."
	sshpass -p 'Cisco0' ssh robot@$1 ./EV3Scripts
	echo "=== Script Done ==="
fi
