#!/bin/bash

# ==========================================
# Automated Log Analysis Script
# ==========================================

# Check if a directory argument was provided
if [ $# -eq 0 ]; then
    echo "Usage: $0 <log_directory>"
    exit 1
fi

LOG_DIR=$1

# Verify the directory exists
if [ ! -d "$LOG_DIR" ]; then
    echo "Error: Directory $LOG_DIR does not exist."
    exit 1
fi

echo "=========================================="
echo "Starting Log Analysis in: $LOG_DIR"
echo "=========================================="

# TODO 1: Use `find` to get all files ending in .log inside $LOG_DIR
# Assign the output to the LOG_FILES variable.
# Example: LOG_FILES=$(find ...)
LOG_FILES=$(find "$LOG_DIR" -type f -name "*.log")

# Loop through each found log file
for FILE in $LOG_FILES; do
    echo ""
    echo "Analyzing $FILE..."
    
    # TODO 2: Use `wc -l` to count total lines in $FILE
    # Assign to TOTAL_LINES
    TOTAL_LINES=$(wc -l < "$FILE")
    echo "Total lines: $TOTAL_LINES"

    # TODO 3: Use `grep` (case-insensitive) to find "404" or "error" or "fail", then `wc -l` to count them.
    # Assign to ERROR_COUNT
    ERROR_COUNT=$(grep -iE "404|error|fail" "$FILE" | wc -l)
    echo "Potential Errors/404s found: $ERROR_COUNT"

    # TODO 4: Use `awk` to extract the 1st column (IP address), 
    # then `sort | uniq -c | sort -nr | head -n 3` to find the top 3 IPs.
    echo "Top 3 IP Addresses:"
    # Put your pipeline here:
    awk '{print $1}' "$FILE" | sort | uniq -c | sort -nr | head -n 3

    echo "------------------------------------------"
done

echo "Analysis Complete."
