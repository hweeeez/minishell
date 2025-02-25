#!/bin/bash

# Define high-contrast colors
ERROR_COLOR='\033[1;91m'   # Bright Red (Errors)
COMMAND_COLOR='\033[1;93m' # Bright Yellow (Commands)
OUTPUT_COLOR='\033[1;96m'  # Cyan (Output)
DIVIDER_COLOR='\033[1;95m' # Bright Magenta (Dividers)
NC='\033[0m'               # No color (Reset)

# Define the commands to be tested
commands=(
  # ✅ ENV Tests
  "env | grep HOME"
  "env | grep USER"
  "env | wc -l"
  "env | grep DOESNT_EXIST"

  # ✅ EXPORT Tests
  "export TEST=hello"
  "echo \$TEST"
  "export EMPTY="
  "echo \$EMPTY"
  "export VAR=\"a value\""
  "export \"TEST2=hello world\""
  "export _TEST=123"
  "export TEST_42=\"value42\""
  "export INVALID-VAR=invalid 2>/dev/null"
  "env | grep TEST"
  "export TEST"
  "export \"\""
  "export \"=\""
  "export TES.T=123"
  "export TES+T=123"
  "export =123"
  "export \"hello there\""

  # ✅ UNSET Tests
  "export TEST=100"
  "echo \$TEST"
  "unset TEST"
  "echo \$TEST"
  "export VAR1=1 VAR2=2"
  "unset VAR1"
  "echo \$VAR1"
  "unset VAR2"
  "echo \$VAR2"
  "unset \"invalid var name\" 2>/dev/null"

  # ✅ Edge Case: PIPE as Variable
  "export PIPE=\"|\" | ls \$PIPE cat"
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
