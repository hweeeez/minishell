#!/usr/bin/bash

MINISHELL="./minishell"
BASH="/usr/bin/bash"
TEST_DIR="test_results"

# Create test directory
mkdir -p "$TEST_DIR"

# Define test cases
declare -a TESTS=(
    "echo hello world"
    "ls -l"
    "pwd"
    "whoami"
    "echo \$HOME"
    "export TEST_VAR=123 && echo \$TEST_VAR"
    "cd /tmp && pwd"
    "echo test > file.txt && cat file.txt && rm file.txt"
    "ls | wc -l"
    "echo hello | grep h"
    "echo 'hello' && echo 'world'"
    "echo 'This is a test' | cat > testfile && cat testfile && rm testfile"
    "echo 'test' | tee output.txt | cat && rm output.txt"
    "sleep 1 && echo done"
)

# Run tests
for TEST in "${TESTS[@]}"; do
    echo "Running test: $TEST"

    # Run in minishell
    echo "$TEST" | $MINISHELL > "$TEST_DIR/minishell_output.txt" 2>&1
    EXIT_MINISHELL=$?

    # Run in bash
    echo "$TEST" | $BASH > "$TEST_DIR/bash_output.txt" 2>&1
    EXIT_BASH=$?

    # Compare outputs
    if diff -u "$TEST_DIR/bash_output.txt" "$TEST_DIR/minishell_output.txt"; then
        echo "✅ Passed"
    else
        echo "❌ Failed"
        echo "  Check diff between bash_output.txt and minishell_output.txt"
    fi

    # Compare exit codes
    if [ "$EXIT_MINISHELL" -ne "$EXIT_BASH" ]; then
        echo "⚠️ Exit codes differ: minishell($EXIT_MINISHELL) vs bash($EXIT_BASH)"
    fi
done

echo "Testing completed."
