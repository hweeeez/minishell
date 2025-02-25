#!/bin/bash

# Define high-contrast colors
ERROR_COLOR='\033[1;91m'   # Bright Red (Errors)
COMMAND_COLOR='\033[1;93m' # Bright Yellow (Commands)
OUTPUT_COLOR='\033[1;96m'  # Cyan (Output)
DIVIDER_COLOR='\033[1;95m' # Bright Magenta (Dividers)
NC='\033[0m'               # No color (Reset)

# Define the commands to be tested
commands=(
  # Basic Pipe Tests
  "echo 'Hello, World!' | cat"
  "ls | wc -l"
  "whoami | rev"
  "date | awk '{print \$1}'"
  
  # Multiple Pipes
  "ls -l | grep 'minishell' | wc -l"
  "cat /etc/passwd | cut -d':' -f1 | sort | uniq | wc -l"
  "ps aux | grep bash | awk '{print \$2}'"

  # Many Pipes (Stress Test)
  "ls | ls | ls | ls | ls | ls | ls | ls | ls | ls"
  "echo 'test' | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat"

  # Order of Execution Check
  "echo '1' | echo '2' | echo '3' | echo '4'"

  # Redirections with Pipes
  "echo 'Hello, World!' | tee output.txt"
  "ls | tee list.txt | wc -l"
  "cat < /etc/hostname | tr a-z A-Z"
  
  # Edge Cases
  "ls | nonexistentcommand | wc -l"
  "echo 'test' | | cat"  # Syntax Error Expected
  "export TEST_VAR='42' | echo \$TEST_VAR"
  "cd .. | pwd"
  "unset TEST_VAR | env | grep TEST_VAR"

  # Subshells in Pipes
  "(echo 'Hello') | cat"
  "(ls -l) | wc -l"

  # No Spaces Around Pipes
  "echo 'Hello'|cat|wc -l"

  # Performance & Stress Tests
  "yes 'minishell' | head -n 100 | tail -n 50 | sort | uniq | wc -l"
  "cat /dev/urandom | base64 | head -n 100"

  # Error Handling
  "ls | cat nonexistentfile"
  "| ls"  # Syntax Error Expected
  "ls |"  # Syntax Error Expected
  "yes 'test' | head -n 5"

# Here Document with Pipes
  "echo 'hello minishell' | tr a-z A-Z"
  "echo 'try cat << EOF | tr a-z A-Z'"
)

# Check if minishell executable exists
if [ ! -f "./minishell" ]; then
    echo -e "${ERROR_COLOR}Error: ./minishell executable not found${NC}"
    exit 1
fi

# Function to run a command in minishell
run_command() {
    local cmd="$1"

    echo -e "${DIVIDER_COLOR}======================================${NC}"
    echo -e "${COMMAND_COLOR}Executing: $cmd${NC}"
    echo -e "${DIVIDER_COLOR}--------------------------------------${NC}"
    
    # Create a file with the command
    echo "$cmd" > cmd_file.tmp
    
    # Run minishell, filter out the extra prompt
    output=$(./minishell < cmd_file.tmp | sed '/weneedtherapy%/d')

    # Display output without prompt
    echo -e "${OUTPUT_COLOR}$output${NC}"
    
    echo -e "${DIVIDER_COLOR}--------------------------------------${NC}"
}

# Run a single command if provided as an argument
if [ "$1" != "" ]; then
    run_command "$1"
    rm -f cmd_file.tmp
    exit 0
fi

# Loop through each command
for cmd in "${commands[@]}"; do
    run_command "$cmd"
done

# Clean up
rm -f cmd_file.tmp
