#!/bin/sh

while true
do
	raspistill -o out.jpg -n -w 1920 -h 1080  -t 1 && ./reader out.jpg
	echo "++++++++++++++++++++++++++++++++++++++++"
done
