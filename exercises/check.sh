#!/bin/bash

if [ -z "$1" ]; then
echo "usage: $0 filename"
fi

if [ -f "$1" ]; then
echo "file $1 exists."
else 
echo "file $1 does not exist."
fi
