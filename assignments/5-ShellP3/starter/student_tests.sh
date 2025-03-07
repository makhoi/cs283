#!/usr/bin/env bats

# File: student_tests.sh
# 
# Create your unit tests suit in this file

#!/usr/bin/env bats

@test "Built-in command executes correctly" {
    run dsh -c "dragon"
    [ "$output" = "Here be dragons!" ]
}

@test "Basic external command execution" {
    run dsh -c "ls"
    [[ "$output" =~ "dsh" ]]
}

@test "Simple piping works" {
    run dsh -c "echo hello | tr a-z A-Z"
    [ "$output" = "HELLO" ]
}

@test "Chained pipes execute correctly" {
    run dsh -c "echo 'one two three' | wc -w"
    [ "$output" = "3" ]
}

@test "Too many piped commands return error" {
    long_cmd=$(printf 'echo x | %.0s' {1..9})"wc -l"
    run dsh -c "$long_cmd"
    [[ "$output" =~ "error: piping limited" ]]
}
