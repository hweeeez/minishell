#!/bin/bash

# Define high-contrast colors
ERROR_COLOR='\033[1;91m'   # Bright Red (Errors)
COMMAND_COLOR='\033[1;93m' # Bright Yellow (Commands)
OUTPUT_COLOR='\033[1;96m'  # Cyan (Output)
DIVIDER_COLOR='\033[1;95m' # Bright Magenta (Dividers)
NC='\033[0m'               # No color (Reset)

# Define exit tests (piping exit into minishell)
commands=(
  "echo \"exit 0\" | ./minishell"
  "echo \"exit 1\" | ./minishell"
  "echo \"exit 42\" | ./minishell"
  "echo \"exit -1\" | ./minishell"
  "echo \"exit 255\" | ./minishell"
  "echo \"exit \\\"1\\\"\" | ./minishell"
  "echo \"exit \\\"+10\\\"\" | ./minishell"
  "echo \"exit \\\"-10\\\"\" | ./minishell"
  "echo \"exit 9223372036854775807\" | ./minishell"
  "echo \"exit -9223372036854775808\" | ./minishell"
  "echo \"exit \\\"hello\\\" \" | ./minishell"
  "echo \"exit \\\"\\\"\" | ./minishell"
  "echo \"exit 0 0 \" | ./minishell"
  "echo \"exit 10000000000000000000 \" | ./minishell"
)

# Check if minishell executable exists
if [ ! -f "./minishell" ]; then
    echo -e "${ERROR_COLOR}Error: ./minishell executable not found${NC}"
    exit 1
fi

# Function to run a test and capture exit code
run_test() {
    local cmd="$1"

    echo -e "${DIVIDER_COLOR}======================================${NC}"
    echo -e "${COMMAND_COLOR}Executing in minishell: $cmd${NC}"
    echo -e "${DIVIDER_COLOR}--------------------------------------${NC}"
    
    # Execute the command and capture the exit status
    eval "$cmd" 2>/dev/null
    exit_code=$?

    # Display the exit code captured in Bash
    echo -e "${OUTPUT_COLOR}Exit Code: $exit_code${NC}"
    
    echo -e "${DIVIDER_COLOR}--------------------------------------${NC}"
}

# Run a single test if provided as an argument
if [ "$1" != "" ]; then
    run_test "$1"
    exit 0
fi

# Loop through each test command
for cmd in "${commands[@]}"; do
    run_test "$cmd"
done
