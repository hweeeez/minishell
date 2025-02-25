#!/bin/bash

# Define high-contrast colors
ERROR_COLOR='\033[1;91m'   # Bright Red (Errors)
COMMAND_COLOR='\033[1;93m' # Bright Yellow (Commands)
OUTPUT_COLOR='\033[1;96m'  # Cyan (Output)
DIVIDER_COLOR='\033[1;95m' # Bright Magenta (Dividers)
NC='\033[0m'               # No color (Reset)

# Define the commands to be tested
commands=(
  "/bin/echo \"This is a test\""
  "/bin/echo 'Another test with single quotes'"
  "/bin/echo \"Mixing 'quotes' inside double quotes\""
  "/bin/echo 'Mixing \"quotes\" inside single quotes'"
  "/bin/echo \"\nNewline inside double quotes\""
  "/bin/echo -n \"No newline at the end\""
  "/bin/echo \"Special chars: !@#\$%^&*()_+\""
  "/bin/echo \"\$USER, your home is \$HOME\""
  "/bin/echo \"Escaping \\\"double quotes\\\" inside quotes\""
  "/bin/echo \"Escaping \\'single quotes\\' inside quotes\""
  "/bin/echo \"\$? shows the exit status\""
  "/bin/echo \"Hello && echo Chained command\""
  "/bin/echo \"echo inside \$(echo subcommand)\""
  "/bin/echo \"Echoing to a file\" > output.txt"
  "/bin/echo \"Appending to a file\" >> output.txt"
  "/bin/echo \"hello\" | /bin/cat"
  "/bin/echo \"\$(/bin/echo nested command)\""
  "/bin/echo \"Wildcards * ? [a-z]\""
  "/bin/echo \$RANDOM"
  "/bin/echo \"Combining \$USER, \$PWD, \$SHELL\""
  "/bin/echo \"\"0\"\""
  "/bin/echo 0\"42\""
  "/bin/echo ''0''\"42\""
  "/bin/echo '\"$USER\"'"
  "/bin/echo \"'$USER'\""
  "/bin/echo \"\"'$USER'\"\""
  "/bin/echo '\"'$USER'\"'"
  "/bin/echo \"''$USER''\""
  "/bin/echo \"'\"'$USER'\"'\""
  "/bin/echo '\"'\"$USER\"'\"'"
  "/bin/echo \$HOME\$USER"
  "/bin/echo \"exit_code ->0 user ->$USER home -> $HOME\""
  "/bin/echo \$HOME"
  "/bin/echo \"\$ \""
  "/bin/echo hi >./outfile01 | /bin/echo bye"
  "/bin/echo <123 <456 hi | /bin/echo 42"
  "/bin/echo \"totally logical\""
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
