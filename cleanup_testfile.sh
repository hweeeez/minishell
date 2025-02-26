#!/bin/bash

echo "🧹 Cleaning up test files, environment variables, and resetting permissions..."

# Remove test files and directories
rm -rf test_files
rm -rf outfiles
rm -f tmp_redir_out tmp_redir_out1 tmp_redir_out2 tmp_redir_out3
rm -f tmp_redir_out_file1
rm -f test_files/missing
rm -f test_files/infile_symlink

# Restore permissions before removing invalid permission test file
if [ -e test_files/invalid_permission ]; then
    chmod +r test_files/invalid_permission
    chmod +w test_files/invalid_permission
    rm -f test_files/invalid_permission
fi

# Restore permission to temp files if they exist
if [ -e tmp_redir_out_file1 ]; then
    chmod +r tmp_redir_out_file1
    chmod +w tmp_redir_out_file1
    rm -f tmp_redir_out_file1
fi

# Unset environment variables used during testing
unset PIPE
unset RL
unset RR
unset HD
unset AP
unset LS
unset FILES

# Output confirmation
echo "✅ Cleanup complete! All test files, scripts, and environment variables have been removed."
