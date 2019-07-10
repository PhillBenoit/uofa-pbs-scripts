#!/bin/bash

### $1 = program to watch
### $2 = log output file
### $3 = delay

### get GPU name
gpu_name=`nvidia-smi --format=csv,noheader --query-gpu=gpu_name | head -n 1 | sed -e 's/ /_/g'`

### append gpu name to log name
log="$2.$gpu_name"

### column header
echo date time gpu_index cpu mem > $log

nvidia-smi --format=csv,noheader --query-gpu=timestamp,index,utilization.gpu,utilization.memory --loop=$3 >> $log
