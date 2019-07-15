#!/bin/bash

# default unknown
host_cluster="unknown"

# use gateway to determine host cluster

if (( `route -n | grep 10.140.116.0 | wc -l` > 0 ))
then
host_cluster="ocelote"
fi

if (( `route -n | grep 10.140.86.0 | wc -l` > 0 ))
then
host_cluster="elgato"
fi

echo $host_cluster
