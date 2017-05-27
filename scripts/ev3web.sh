
#!/bin/bash
echo "=== EV3 Web-upload Script v.1.2 by Xer0, peerfunk ==="

#Bundeling files
cd ../web
tar -czvf upload_web.tar  *

echo "=== Compress done ==="


#uploading files
echo "Copying files..."
	
sshpass -p 'Cisco0' scp ../web/upload_web.tar robot@$1:/home/robot/
	if [ $? -eq 1 ]
	then
		echo "!!! -> Upload failed!"
		exit
	fi
	echo "=== Uploading Done ==="
	
	echo "Configuring_webspace"
	sshpass -p 'Cisco0' ssh robot@$1 /var/www/configure.sh

	echo "=== Script Done ==="
