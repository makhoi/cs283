#!/usr/bin/env bats

# File: student_tests.sh
# 
# Create your unit tests suit in this file

# Ensure pipes (`|`) work as expected
@test "Pipes with grep" {
    run "./dsh" <<EOF                
ls | grep dshlib.c
EOF

    stripped_output=$(echo "$output" | tr -d '[:space:]')
    expected_output="dshlib.cdsh3>dsh3>cmdloopreturned0"

    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    [ "$stripped_output" = "$expected_output" ]
    [ "$status" -eq 0 ]
}

# Ensure `cd` command works and prompt appears correctly
@test "Built-in cd command" {
    run "./dsh" <<EOF
cd ..
EOF

    stripped_output=$(echo "$output" | tr -d '[:space:]')
    expected_output="dsh3>dsh3>cmdloopreturned0"

    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    [ "$stripped_output" = "$expected_output" ]
    [ "$status" -eq 0 ]
}

# Ensure `exit` command properly terminates the shell
@test "Exit command" {
    run "./dsh" <<EOF
exit
EOF

    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"

    [ "$status" -eq 0 ]
}

# Ensure `ls` command output appears before the prompt
@test "Check ls command output and prompt behavior" {
    run "./dsh" <<EOF
ls
EOF

    stripped_output=$(echo "$output" | tr -d '[:space:]')
    
    # Ensure ls outputs something
    [[ -n "${output}" ]]

    # Check that the prompt appears twice
    [[ "$stripped_output" == *"dsh3>dsh3>cmdloopreturned0"* ]]
}


