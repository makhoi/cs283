#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "dshlib.h"

/*
 * Implement your exec_local_cmd_loop function by building a loop that prompts the 
 * user for input.  Use the SH_PROMPT constant from dshlib.h and then
 * use fgets to accept user input.
 */

// Function to allocate memory for command buffer
int alloc_cmd_buff(cmd_buff_t *cmd_buff) {
    cmd_buff->_cmd_buffer = (char *)malloc(ARG_MAX);
    if (cmd_buff->_cmd_buffer == NULL) {
        return ERR_MEMORY;
    }
    clear_cmd_buff(cmd_buff);
    return OK;
}

// Function to free memory for command buffer
int free_cmd_buff(cmd_buff_t *cmd_buff) {
    if (cmd_buff->_cmd_buffer != NULL) {
        free(cmd_buff->_cmd_buffer);
        cmd_buff->_cmd_buffer = NULL;
    }
    return OK;
}

// Function to clear command buffer
int clear_cmd_buff(cmd_buff_t *cmd_buff) {
    if (cmd_buff->_cmd_buffer != NULL) {
        memset(cmd_buff->_cmd_buffer, 0, ARG_MAX);
    }
    cmd_buff->argc = 0;
    for (int i = 0; i < CMD_ARGV_MAX; i++) {
        cmd_buff->argv[i] = NULL;
    }
    return OK;
}

// Function to close command buffer (free and clear)
int close_cmd_buff(cmd_buff_t *cmd_buff) {
    free_cmd_buff(cmd_buff);
    clear_cmd_buff(cmd_buff);
    return OK;
}

// Function to free command list
int free_cmd_list(command_list_t *cmd_lst) {
    for (int i = 0; i < cmd_lst->num; i++) {
        free_cmd_buff(&cmd_lst->commands[i]);
    }
    cmd_lst->num = 0;
    return OK;
}

// Function to parse a single command into cmd_buff_t
int build_cmd_buff(char *cmd_line, cmd_buff_t *cmd_buff) {
    // Allocate memory for the command buffer
    if (alloc_cmd_buff(cmd_buff) != OK) {
        return ERR_MEMORY;
    }
    
    // Trim leading whitespace
    while (*cmd_line && isspace(*cmd_line)) {
        cmd_line++;
    }
    
    // Copy the command line to the buffer
    strncpy(cmd_buff->_cmd_buffer, cmd_line, ARG_MAX - 1);
    cmd_buff->_cmd_buffer[ARG_MAX - 1] = '\0';
    
    // Split the command line into arguments
    cmd_buff->argc = 0;
    char *token = strtok(cmd_buff->_cmd_buffer, " \t");
    while (token != NULL && cmd_buff->argc < CMD_ARGV_MAX - 1) {
        cmd_buff->argv[cmd_buff->argc++] = token;
        token = strtok(NULL, " \t");
    }
    cmd_buff->argv[cmd_buff->argc] = NULL;  // NULL-terminate the argument list
    
    // If no arguments were parsed, this is an empty command
    if (cmd_buff->argc == 0) {
        return WARN_NO_CMDS;
    }
    
    return OK;
}

// Function to match built-in commands
Built_In_Cmds match_command(const char *input) {
    if (input == NULL) {
        return BI_NOT_BI;
    }
    
    if (strcmp(input, EXIT_CMD) == 0) {
        return BI_CMD_EXIT;
    } else if (strcmp(input, "cd") == 0) {
        return BI_CMD_CD;
    } else if (strcmp(input, "dragon") == 0) {
        return BI_CMD_DRAGON;
    }
    
    return BI_NOT_BI;
}

// Function to execute built-in commands
Built_In_Cmds exec_built_in_cmd(cmd_buff_t *cmd) {
    if (cmd->argc == 0 || cmd->argv[0] == NULL) {
        return BI_NOT_BI;
    }
    
    Built_In_Cmds cmd_type = match_command(cmd->argv[0]);
    
    switch (cmd_type) {
        case BI_CMD_EXIT:
            exit(0);  // Exit the shell
            return BI_EXECUTED;
            
        case BI_CMD_CD:
            if (cmd->argc < 2) {
                printf("cd: missing argument\n");
            } else if (chdir(cmd->argv[1]) != 0) {
                perror("cd");
            }
            return BI_EXECUTED;
            
        case BI_CMD_DRAGON:
            printf("Here be dragons!\n");
            return BI_EXECUTED;
            
        case BI_NOT_BI:
        default:
            return BI_NOT_BI;
    }
}

int exec_local_cmd_loop() {
    char input_line[SH_CMD_MAX];
    command_list_t clist;
    int rc;
    int first_command_executed = 0;

    while (1) {
        fflush(stdout);
        
        if (first_command_executed) {
            printf("%s ", SH_PROMPT);  // Print prompt after the first command executes
        }
    
        // Read user input
        if (fgets(input_line, SH_CMD_MAX, stdin) == NULL) {
            break;
        }
    
        // Remove trailing newline
        input_line[strcspn(input_line, "\n")] = '\0';
    
        // Parse input into command_list_t
        rc = build_cmd_list(input_line, &clist);
        if (rc != OK) {
            if (rc == WARN_NO_CMDS) {
                printf(CMD_WARN_NO_CMD);
            } else if (rc == ERR_TOO_MANY_COMMANDS) {
                // Error message already printed in build_cmd_list
            } else {
                printf("Error parsing command\n");
            }
            continue;
        }
    
        // Execute the first command and capture if it was a built-in
        Built_In_Cmds result = exec_built_in_cmd(&clist.commands[0]);
        if (result == BI_EXECUTED) {
            first_command_executed = 1;
            printf("\n%s ", SH_PROMPT);  // Ensure prompt is printed after execution
            continue;
        }
    
        // Execute pipeline and wait for all child processes
        execute_pipeline(&clist);
        free_cmd_list(&clist);
    
        first_command_executed = 1;
        printf("\n%s ", SH_PROMPT);  // Print the next prompt after execution
    }

    return OK;
}

// Function to parse input into multiple commands separated by pipes
int build_cmd_list(char *cmd_line, command_list_t *clist) {
    memset(clist, 0, sizeof(command_list_t));
    
    if (cmd_line == NULL || *cmd_line == '\0') {
        return WARN_NO_CMDS;
    }
    
    char cmd_copy[SH_CMD_MAX];
    strncpy(cmd_copy, cmd_line, SH_CMD_MAX - 1);
    cmd_copy[SH_CMD_MAX - 1] = '\0';

    char *saveptr;
    char *token = strtok_r(cmd_copy, PIPE_STRING, &saveptr);
    
    if (token == NULL) {
        return WARN_NO_CMDS;
    }

    while (token != NULL) {
        if (clist->num >= CMD_MAX) {
            printf(CMD_ERR_PIPE_LIMIT, CMD_MAX);
            return ERR_TOO_MANY_COMMANDS;
        }

        // Call build_cmd_buff but ensure it does not use strtok
        int rc = build_cmd_buff(token, &clist->commands[clist->num]);
        if (rc == OK) {
            clist->num++;
        } else if (rc != WARN_NO_CMDS) {
            return rc; // Propagate errors
        }

        token = strtok_r(NULL, PIPE_STRING, &saveptr);
    }

    if (clist->num == 0) {
        return WARN_NO_CMDS;
    }

    return OK;
}


// Function to execute a pipeline of commands
int execute_pipeline(command_list_t *clist) {
    // Check if there are any commands to execute
    if (clist->num == 0) {
        return WARN_NO_CMDS;
    }
    
    int num_commands = clist->num;
    int pipes[CMD_MAX][2];  // Use a fixed-size array to avoid VLA warnings
    pid_t pids[CMD_MAX];

    // Create pipes
    for (int i = 0; i < num_commands - 1; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            return ERR_EXEC_CMD;
        }
    }

    // Fork processes for each command
    for (int i = 0; i < num_commands; i++) {
        pids[i] = fork();

        if (pids[i] == -1) {
            perror("fork");
            // Close already created pipes
            for (int j = 0; j < i; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }
            return ERR_EXEC_CMD;
        }

        if (pids[i] == 0) { // Child process
            // Set up pipes for stdin/stdout
            if (i > 0) {
                // Connect stdin to previous command's output
                if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1) {
                    perror("dup2 stdin");
                    exit(EXIT_FAILURE);
                }
            }
            
            if (i < num_commands - 1) {
                // Connect stdout to next command's input
                if (dup2(pipes[i][1], STDOUT_FILENO) == -1) {
                    perror("dup2 stdout");
                    exit(EXIT_FAILURE);
                }
            }
            
            // Close all pipe file descriptors in child
            for (int j = 0; j < num_commands - 1; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }
            
            // Execute command
            execvp(clist->commands[i].argv[0], clist->commands[i].argv);
            // If execvp returns, it means there was an error
            perror(clist->commands[i].argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    // Close all pipes in parent
    for (int i = 0; i < num_commands - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    // Wait for all child processes
    for (int i = 0; i < num_commands; i++) {
        int status;
        waitpid(pids[i], &status, 0);
    }

    // Ensure output is flushed before returning
    fflush(stdout);
    
    return OK;
}
