#!/bin/bash

# Define high-contrast colors
ERROR_COLOR='\033[1;91m'   # Bright Red (Errors)
COMMAND_COLOR='\033[1;93m' # Bright Yellow (Commands)
OUTPUT_COLOR='\033[1;96m'  # Cyan (Output)
DIVIDER_COLOR='\033[1;95m' # Bright Magenta (Dividers)
NC='\033[0m'               # No color (Reset)

# Define the commands to be tested
commands=(
  "echo \"hello world\""
  "echo \"\$USER\""
  "echo 'Literal \$USER'"
  "echo \"\"\"\$USER\"\"\""
  "echo -n \"no newline\""
  "echo \"exit_code ->\$? user ->\$USER home -> \$HOME\""
  "echo \$HOME"
  "echo \\$USER"
  "echo \"multiple   spaces\""
  "echo \"hello > file\" > testfile"
  "echo \"piping test\" | cat"
  "echo \"text\" \"more text\" \"even more\""
  "echo \"quotes test\" '\"inside single\"'"
  "echo word1   word2   word3"                      # Multiple spaces
  "echo    spaced    out    "                       # Leading & trailing spaces
  "echo 'single quotes test'"                       # Single quotes (literal)
  "echo \"double quotes test\""                     # Double quotes (expands variables)
  "echo '  multiple     spaces  inside  '"          # Preserves spaces inside single quotes
  "echo \"  multiple     spaces  inside  \""        # Preserves spaces inside double quotes
  "echo text\"more text\"even more"                 # No spaces between
  "echo \"text\" \"more text\" \"even more\""       # Words split inside quotes
  "echo \"this    is   a test\" 'with    spaces'"   # Mixing quotes with spaces
  "echo \$USER spaced out"                           # Expands `$USER` normally
  "echo \"\$USER     spaced out\""                  # Expands `$USER`, keeps spaces
  "echo \$USER\$HOME"                                # Expands two variables, no space
  "echo \$USER \$HOME"                               # Expands two variables, keeps space
  "echo \$USER' '$HOME"                             # Expands `$USER`, space, `$HOME`
  "echo \$USER'   '$HOME"                           # Expands `$USER`, multiple spaces, `$HOME`
  "echo \"\$USER \$HOME \$PWD\""                     # Expands all, spaces inside double quotes
  "echo \$USER\$HOME\$PWD"                          # Expands all, no spaces
  "echo \$USER   \"\$HOME   \$PWD\""                 # Expands `$USER`, `$HOME` and `$PWD`
  "echo \"This is   a  test\" | cat"                # Pipe output with spaces
  "echo \"\$?   -> Exit Code\""                     # `$?` with extra spacing
  "echo \"Concatenated\"text"                       # No space between
  "echo \"Concatenated\" \"text\""                  # Space between
  "echo -n \"this  is  a  test\""                   # No newline, keeps spaces
  "echo -n \"\$USER spaced\""                        # No newline, variable expands
  "echo '       whitespace inside       '"         # Preserves all whitespace
  "echo \"       whitespace inside       \""        # Preserves all whitespace
  "echo \$USER\$HOME text \$PWD"                    # Expands variables with text in between
  "echo \"\$USER    \$HOME    \$PWD\""               # Expands variables, keeps spacing
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
