#!/bin/bash

# Define high-contrast colors
ERROR_COLOR='\033[1;91m'   # Bright Red (Errors)
COMMAND_COLOR='\033[1;93m' # Bright Yellow (Commands)
OUTPUT_COLOR='\033[1;96m'  # Cyan (Output)
DIVIDER_COLOR='\033[1;95m' # Bright Magenta (Dividers)
NC='\033[0m'               # No color (Reset)

# Define the commands to be tested
commands=(
  ### BASIC INPUT REDIRECTION ###
  "grep hi < ./test_files/infile"
  "grep hi < ./test_files/infile_big < ./test_files/infile"
  "cat < './test_files/file name with spaces'"
  "cat < ./test_files/infile_big ./test_files/infile"
  "echo < ./test_files/infile_big | cat < ./test_files/infile"
  "echo hi | cat < ./test_files/infile"
  "cat < ./test_files/infile | grep hello"
  
  ### EDGE CASES FOR INPUT REDIRECTION ###
  "cat < missing"  # Missing file test
  "cat < missing | cat"  # Piping missing file
  "cat < missing | echo oi"  # Piping with an invalid input file
  "cat < missing | cat < ./test_files/infile"  # Missing input before a valid input
  "echo <123 <456 hi | echo 42"  # Multiple input redirections

  ### BASIC OUTPUT REDIRECTION ###
  "ls > ./outfiles/outfile01"
  "ls > ./outfiles/outfile01 > ./outfiles/outfile02"
  "ls > './outfiles/outfile with spaces'"
  "ls > ./outfiles/outfile01 > ./test_files/invalid_permission"  # Permission error
  "echo hi > ./test_files/invalid_permission"  # Permission error
  
  ### PIPE + REDIRECTION COMBINED ###
  "echo hi > ./outfiles/outfile01 | echo bye"
  "echo hi > ./outfiles/outfile01 > ./outfiles/outfile02 | echo bye"
  "cat < ./test_files/infile | grep hello > ./outfiles/outfile01"
  "cat < ./test_files/infile | wc -l > ./outfiles/outfile02"
  "ls | tee ./outfiles/outfile01 | wc -l"
  
  ### APPEND REDIRECTION (>>) ###
  "ls >> ./outfiles/outfile01"
  "echo hi >> ./outfiles/outfile01"
  "echo hi >> ./test_files/invalid_permission"  # Permission error
  "ls > ./outfiles/outfile01 >> ./outfiles/outfile01"
  
  ### EDGE CASES FOR OUTPUT REDIRECTION ###
  "cat < missing > ./outfiles/outfile01"  # Missing input file
  "cat < missing > ./test_files/invalid_permission"  # Missing input, invalid permission
  
  ### INVALID SYNTAX CASES ###
  "| ls"  # Syntax error: Pipe without left command
  "ls |"  # Syntax error: Pipe without right command
  "ls | | wc -l"  # Syntax error: Consecutive pipes
  "echo < missing > ./outfiles/outfile01"  # Invalid file handling
  "ls > ./test_files/invalid_permission >> ./outfiles/outfile01"  # Mixed permissions

  ### HEREDOC TESTS (SIMULATED WITH ECHO) ###
  "echo 'hello minishell' | tr a-z A-Z"
  "echo 'HELLO' | cat"  
  "echo 'multi-line\ninput test' | cat"

  ### DEV NULL TESTS ###
  "cat < /dev/null"
  "/bin/echo 42 > /dev/null"
  "/bin/echo 42 >> /dev/null"
  "/bin/echo 1 > /dev/null | /usr/bin/grep 1"
  "/bin/echo 1 > /dev/null | /bin/echo 2"

  ### PERMISSION DENIED TESTS ###
  "touch tmp_redir_out_file1"
  "chmod -r tmp_redir_out_file1"
  "/bin/echo 1 > tmp_redir_out tmp_redir_out_file1"

  ### OVERWRITE & APPEND COMPLEX CASES ###
  "/bin/echo 42 > /dev/null > /dev/null > /dev/null > /dev/null > tmp_redir_out"
  "cat tmp_redir_out"
  "rm tmp_redir_out"
  "/bin/echo 42 > tmp_redir_out > tmp_redir_out1 > tmp_redir_out2 > tmp_redir_out3"
  "/bin/echo 0"
  "cat tmp_redir_out"
  "/bin/echo 1"
  "cat tmp_redir_out1"
  "/bin/echo 2"
  "cat tmp_redir_out2"
  "/bin/echo 3"
  "cat tmp_redir_out3"
  "rm tmp_redir_out tmp_redir_out1 tmp_redir_out2 tmp_redir_out3"
  
  ### CLEANUP COMMANDS ###
  "> out"
  "/bin/rm -f out"
  "< out"
  "/bin/rm -f out"
  ">> out"
  "/bin/rm -f out"
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
