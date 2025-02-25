#!/bin/bash

echo "🧹 Cleaning up test files and resetting permissions..."

# Remove test files and directories
rm -rf test_files
rm -rf outfiles
rm -f tmp_redir_out tmp_redir_out1 tmp_redir_out2 tmp_redir_out3
rm -f tmp_redir_out_file1
rm -f test_files/missing
rm -f test_files/infile_symlink

# Restore permission for invalid permission test (if exists)
if [ -e test_files/invalid_permission ]; then
    chmod +r test_files/invalid_permission
    chmod +w test_files/invalid_permission
fi

# Output
echo "✅ Cleanup complete! All test files and directories have been removed."
