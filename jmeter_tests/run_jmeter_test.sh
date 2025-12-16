#!/bin/bash

# Directories for logs and results
LOG_DIR=".jmeter_logs"
RESULT_DIR=".jmeter_results"
mkdir -p "$LOG_DIR" "$RESULT_DIR"

# Single timestamp for both log and result files
TIMESTAMP=$(date +"%Y-%m-%d_%H-%M-%S")

LOG_FILE="$LOG_DIR/jmeter_$TIMESTAMP.log"
RESULT_FILE="$RESULT_DIR/results_$TIMESTAMP.jtl"

# Run JMeter in non-GUI mode
jmeter -n -t "Test_API_Kuznechik.jmx" -q "user.properties" -l "$RESULT_FILE" -j "$LOG_FILE"

echo "Test completed. Results: $RESULT_FILE, Logs: $LOG_FILE"
