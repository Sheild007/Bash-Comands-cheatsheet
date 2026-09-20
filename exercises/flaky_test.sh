#!/usr/bin/env bash

# Check if a command was provided
if [ $# -eq 0 ]; then
    echo "Usage: $0 <command to run>"
    exit 1
fi

count=0
while true; do
    "$@" &> out.log
    if [[ $? -ne 0 ]]; then
        cat out.log
        echo "Failed after $count runs"
        break
    fi
    ((count++))
done
