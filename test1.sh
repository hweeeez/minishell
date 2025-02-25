#!/bin/bash

# Define the commands to be tested
commands=(
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
  "/bin/echo $\"HOME\"$USER"
  "/bin/echo $\"HOM\"E$USER"
  "/bin/echo \"exit_code ->0 user ->$USER home -> $HOME\""
  "/bin/echo $\"HOME\""
  "/bin/echo $\"42$\""
  "/bin/echo \"$ \""
  "/bin/echo hi >./outfile01 | /bin/echo bye"
  "/bin/echo <123 <456 hi | /bin/echo 42"
  "/bin/echo '$=''"
  "/bin/echo '$ '"
  "/bin/echo \"0\""
  "/bin/echo '$?''"
  "/bin/echo \"'0'\""
  "/bin/echo \\$USER"
  "/bin/echo \\\\$USER"
  "/bin/echo \\\\\\$USER"
  "/bin/echo \\\\\\\\$USER"
  "/bin/echo \\\\\\\\\\$USER"
  "/bin/echo \\\\\\\\\\\\\\\\$USER"
  "/bin/echo \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\$USER \\$PATH \\\\$PWD"
  "/bin/echo \"cat lol.c | cat > lol.c\""
  "/bin/echo \"cat lol.c '|' cat > lol.c\""
  "/bin/echo '$USER' \"$USER\" \"text ' text\""
  "/bin/echo $USER =intergalaktikus miaf*szomez"
  "/bin/echo -n\"-n\" bonjour"
  "/bin/echo \"'$USER'\""
  "/bin/echo \" '$USER' \""
  "/bin/echo text\"$USER\""
  "/bin/echo text\"'$USER'\" ' $USER '"
  "/bin/echo \"text\" \"$USER\" \"$USER\""
  "/bin/echo ' $USER '"
  "/bin/echo ''''''''''$USER'''''''''''"
  "/bin/echo \"\"\"\"\"\"\"\"$USER\"\"\"\"\"\"\"\""
  "/bin/echo '\"\"\"\"\"\"\"\"$USER\"\"\"\"\"\"\"\"'"
  "/bin/echo \"\"'\"\"\"\"\"\"$USER\"\"\"\"\"\"'\"\"" 
  "/bin/echo \"\"\"\"\"\"\"\"'$USER'\"\"\"\"\"\"\"\""
  "/bin/echo \"\"\"\"\"\"\"'\"$USER\"'\"\"\"\"\"\"\"" 
  "/bin/echo \"\"\"\"\"\"'\"\"$USER\"\"'\"\"\"\"\"\"" 
  "/bin/echo \"\"'\"\"'\"\"\"\"$USER\"\"\"\"'\"\"'\"\"" 
  "/bin/echo '\"\"'\"\"'\"\"\"\"$USER\"\"\"\"'\"\"'\"\"'" 
  "/bin/echo $USER'$USER'text oui oui oui oui $USER oui $USER ''"
  "/bin/echo \"text\" \"text$USER\" ... \"$USER\""
  "/bin/echo"
  "/bin/echo ''"
  "/bin/echo \"\""
  "/bin/echo '' \"\""
  "/bin/echo /bin/echo"
  "/bin/echo test1"
  "/bin/echo 'test1'"
  "/bin/echo \"/bin/echo hallo\""
  "/bin/echo /bin/echo\"1\""
  "/bin/echo \"test1 test2\""
  "/bin/echo \"test1 test2\" test3"
  "/bin/echo \" test1 test2 \" 'test3 '"
  "/bin/echo test1 test2"
  "/bin/echo $USER$TESTNOTFOUND$HOME$"
  "/bin/echo $USER$TESTNOTFOUND$HOME$WTF$PWD"
  "/bin/echo -n test1"
  "/bin/echo -n \"test1 test2\""
  "/bin/echo -n \"test1 test2\" test3"
  "/bin/echo -n \" test1 test2 \" 'test3 '"
  "/bin/echo -n test1 test2"
  "/bin/echo test1 -n"
  "/bin/echo \"test1 -n\""
  "/bin/echo -n -n test1"
  "/bin/echo -n -n -n -n -n test1"
  "/bin/echo \" -nn \""
  "/bin/echo \"-n test1 -n test2\""
  "/bin/echo \"test1 -n test2\""
  "/bin/echo ~42"
  "/bin/echo -n -n -nasd"
  "/bin/echo -n -n -n-nnnnn"
  "/bin/echo -n -nnnnnnn -n -nnn -nnnnn -n-n"
  "/bin/echo -n -nnnnnnn -n -nnn -nnnnn -n feel my pain"
  "/bin/echo -n -n -n-n"
  "/bin/echo \"'totally logical'\""
  "/bin/echo 'totally logical'"
  "/bin/echo ''totally logical''"
  "/bin/echo \"\"'totally logical'\"\""
)

# Check if minishell executable exists
if [ ! -f "./minishell" ]; then
    echo "Error: ./minishell executable not found"
    exit 1
fi

# Function to run a command in minishell
run_command() {
    local cmd="$1"

    echo "======================================"    
    echo "Command: $cmd"
    echo "---------------------------------------"
    
    # Create a file with the command and exit
    echo "$cmd\n" > cmd_file.tmp
    #echo "exit" >> cmd_file.tmp
    
    # Run minishell with the command file
    ./minishell < cmd_file.tmp
    
    echo "---------------------------------------"
    echo "======================================="
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