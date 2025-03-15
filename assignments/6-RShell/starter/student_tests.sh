#!/usr/bin/env bats

# File: student_tests.sh
# Unit tests for dsh (remote shell)

# Test basic command execution
@test "Check if ls runs without errors" {
    run ./dsh <<EOF
ls
EOF
    [ "$status" -eq 0 ]
}

# Test running a simple command
@test "Check if whoami runs successfully" {
    run ./dsh <<EOF
whoami
EOF
    [ "$status" -eq 0 ]
}

# Test redirection (>)
@test "Check if output redirection (>) works" {
    run ./dsh <<EOF
echo "Hello, Test!" > testfile.txt
EOF
    [ "$status" -eq 0 ]

    run ./dsh <<EOF
cat testfile.txt
EOF
    [ "$output" = "Hello, Test!" ]
}

# Test piping (|)
@test "Check if piping (|) works" {
    run ./dsh <<EOF
echo "Hello, Pipe!" | grep Pipe
EOF
    [ "$status" -eq 0 ]
    [ "$output" = "Hello, Pipe!" ]
}

# Test multiple piped commands
@test "Check if multi-step piping works" {
    run ./dsh <<EOF
echo "one two three" | awk '{print \$2}'
EOF
    [ "$status" -eq 0 ]
    [ "$output" = "two" ]
}

# Test built-in exit command
@test "Check if exit command works" {
    run ./dsh <<EOF
exit
EOF
    [ "$status" -eq 0 ]
}

# Test stop-server command
@test "Check if stop-server shuts down the server" {
    run ./dsh <<EOF
stop-server
EOF
    [ "$status" -eq 0 ]
}
