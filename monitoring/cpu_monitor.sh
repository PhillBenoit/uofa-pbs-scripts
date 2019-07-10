#!/bin/bash

### $1 = program to watch
### $2 = log output file
### $3 = delay

### machine memory info for log file
memory=`free -m | grep Mem | awk '{print $2}'`

### column headers
### memory is in megabytes
echo date time node process_time process_id cpu memory > $2

### Run foever
while true
do

### Get date
date=`date "+%D %T"`

### This will only work if the columns from top are in the expected order
### please use the propper '.toprc'
top -bn1 -u $USER | awk -v program="$1" -v host="$HOSTNAME" -v date="$date" \
-v memory="$memory" '{if($10 == program){print date, host, $1, $2, $4, $5*memory}}'\
>> $2

### Delay
sleep $3

### End loop
done
