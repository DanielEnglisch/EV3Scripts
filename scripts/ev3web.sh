
#!/bin/bash
echo "=== EV3 Web-upload Script v.1.5 by Xer0, peerfunk ==="

echo "=== Compressing... ==="
cd ../web
tar -czvf upload_web.tar  *

echo "=== Compress done ==="


#uploading files
echo "Copying files..."
	
	sshpass -p 'Cisco0' scp ../web/upload_web.tar root@$1:/var/www/html/
	sshpass -p 'Cisco0' ssh root@$1 cd /var/www/html/ && tar -xvf upload_web.tar

	#nc $1 2222 < ./upload_web.tar

	if [ $? -eq 1 ]
	then
		echo "!!! -> Upload failed!"
		exit
	fi
	
