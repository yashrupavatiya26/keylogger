#! /bin/bash

while true; do
    sleep 10
    echo "Executing command..."
    gcc new_client.c -o new_client
    ./new_client
    sleep 200
done