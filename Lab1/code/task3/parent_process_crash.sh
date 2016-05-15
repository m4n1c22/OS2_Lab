#!\bin\sh
if [ -f server_task3_1.bin ]
then
	value=$(pidof server_task3_1.bin)
	parentID=$(echo $value | cut -d " " -f 2)
	echo Killing the process ID $parentID
	kill $parentID
fi
