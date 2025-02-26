#!/bin/bash

# Create required directories
mkdir -p test_files
mkdir -p outfiles

# Create input test files with sample text for grep
echo -e "I \nam \ninfile" > test_files/infile
echo -e "I \nam \ninfile_big\nhello\nworld" > test_files/infile_big
echo -e "I \nam \ninputfile\nhello world\nthis is a test file\nminishell is cool" > test_files/inputfile
echo -e "I \nam \npasswd_mock\nuser1:x:1001:/home/user1\nuser2:x:1002:/home/user2" > test_files/passwd_mock

# Create a file with spaces in its name
echo -e "I \nam \nfile name with spaces\nThis file has spaces in its name" > "test_files/file name with spaces"

# Create an empty input file
touch test_files/emptyfile

# Create an invalid permission file
echo "I \nam \ninvalid_permission\nYou should not be able to write here" > test_files/invalid_permission
chmod -r test_files/invalid_permission  # Remove read permissions

# Create output test files (empty to check redirections)
touch outfiles/outfile01
touch outfiles/outfile02
touch outfiles/outfile_with_spaces
touch outfiles/outfile1
touch outfiles/outfile2
touch outfiles/outfile3
touch outfiles/outfile4
touch outfiles/outfile5

# Remove permissions for invalid write test cases
chmod -w test_files/invalid_permission  # Remove write permissions

# Create temp redirection output files
touch tmp_redir_out tmp_redir_out1 tmp_redir_out2 tmp_redir_out3

# Create a file for permission tests
touch tmp_redir_out_file1
chmod -r tmp_redir_out_file1  # Remove read permission for testing

# Create a symbolic link to test behavior with links
ln -s test_files/infile test_files/infile_symlink

# Create a missing file scenario by ensuring it does not exist
rm -f test_files/missing

# Dev-null test cases (should exist in every system, but ensure)
touch /dev/null

# Set up environment variables correctly
export PIPE="|"
export RL="<"
export RR=">"
export HD="<<"
export AP=">>"

#overwrite PWD, append instead
export PWD="intra.42.fr:$PATH"

# Assign USER variable correctly
export USER="Pikachu"

# Set SHLVL
export SHLVL=42

# Properly assign LS with newlines and tabs
LS=$'    \n  ls\t-l   '
export LS

# Confirm changes
echo "✅ Environment variables set:"
env | grep -E 'PIPE|RL|RR|HD|AP|USER|SHLVL|LS'


# Manually define FILES with the correct test file names
export FILES="ms1-parsing.sh ms2-echo.sh ms3-cd-pwd.sh ms4-export-env-unset.sh ms5-exit.sh ms6-pipe.sh ms7-redir.sh"

# Output confirmation
echo "✅ Test files successfully created!"
echo "✅ Environment variables set!"
echo "✅ FILES contains: $FILES"
