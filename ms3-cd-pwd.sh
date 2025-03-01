#!/bin/bash

# Define high-contrast colors
ERROR_COLOR='\033[1;91m'   # Bright Red (Errors)
COMMAND_COLOR='\033[1;93m' # Bright Yellow (Commands)
OUTPUT_COLOR='\033[1;96m'  # Cyan (Output)
DIVIDER_COLOR='\033[1;95m' # Bright Magenta (Dividers)
NC='\033[0m'               # No color (Reset)

# Define test groups for CD
tests=(
  # Basic Navigation
  "pwd
cd ..
pwd"

  "pwd
cd /
pwd"

  "pwd
cd ~
pwd"

  "pwd
cd .
pwd"

  # Special Cases
  "pwd
cd '$PWD'
pwd"

  "pwd
cd ''
pwd"

  "pwd
cd -
pwd"

  "pwd
cd ////// 
pwd"

  "pwd
cd ./././
pwd"

  # Environment Variables
  "pwd
cd \$HOME
pwd"

  "pwd
cd \$OLDPWD
pwd"

  # Absolute and Relative Paths
  "pwd
cd /tmp
pwd"

  "pwd
cd ../../
pwd"

  "pwd
cd ../
pwd"

  # Invalid Paths (Should Fail)
  "pwd
cd does_not_exist
pwd"

  "pwd
cd /root #2>/dev/null
pwd"

  "pwd
cd + #2>/dev/null
pwd"

  "pwd
cd -invalid #2>/dev/null
pwd"

  "pwd
cd 'bad dir' #2>/dev/null
pwd"

  # Edge Cases
  "pwd
cd \"'/////\"
pwd"

  "pwd
cd \$HOME/../
pwd"

  "pwd
cd /var
pwd"

  "pwd
cd \$PWD
pwd"

  "pwd"
  
  "\"pwd\""
  
  "pwd test42"
  
  "pwd 42 42 42"
  
  "pwd pwd"
  
  "pwd pwd pwd"
)

# Check if minishell executable exists
if [ ! -f "./minishell" ]; then
    echo -e "${ERROR_COLOR}Error: ./minishell executable not found${NC}"
    exit 1
fi

# Function to run a test group in minishell
run_test_group() {
    local group="$1"

    echo -e "${DIVIDER_COLOR}======================================${NC}"
    echo -e "${COMMAND_COLOR}Executing test group:${NC}"
    echo -e "${COMMAND_COLOR}${group}${NC}"
    echo -e "${DIVIDER_COLOR}--------------------------------------${NC}"
    
    # Write the group of commands into a temporary file
    echo -e "${group}" > cmd_file.tmp
    
    # Run minishell with the command file, filtering out any unwanted prompt lines
    output=$(./minishell < cmd_file.tmp | sed '/weneedtherapy%/d')

    # Display the combined output
    echo -e "${OUTPUT_COLOR}$output${NC}"
    
    echo -e "${DIVIDER_COLOR}--------------------------------------${NC}"
}

# Run a single test group if provided as an argument
if [ "$1" != "" ]; then
    run_test_group "$1"
    rm -f cmd_file.tmp
    exit 0
fi

# Loop through each test group
for group in "${tests[@]}"; do
    run_test_group "$group"
done

# Clean up
rm -f cmd_file.tmp
