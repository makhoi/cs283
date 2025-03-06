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
 * 
 *      while(1){
 *        printf("%s", SH_PROMPT);
 *        if (fgets(cmd_buff, ARG_MAX, stdin) == NULL){
 *           printf("\n");
 *           break;
 *        }
 *        //remove the trailing \n from cmd_buff
 *        cmd_buff[strcspn(cmd_buff,"\n")] = '\0';
 * 
 *        //IMPLEMENT THE REST OF THE REQUIREMENTS
 *      }
 * 
 *   Also, use the constants in the dshlib.h in this code.  
 *      SH_CMD_MAX              maximum buffer size for user input
 *      EXIT_CMD                constant that terminates the dsh program
 *      SH_PROMPT               the shell prompt
 *      OK                      the command was parsed properly
 *      WARN_NO_CMDS            the user command was empty
 *      ERR_TOO_MANY_COMMANDS   too many pipes used
 *      ERR_MEMORY              dynamic memory management failure
 * 
 *   errors returned
 *      OK                     No error
 *      ERR_MEMORY             Dynamic memory management failure
 *      WARN_NO_CMDS           No commands parsed
 *      ERR_TOO_MANY_COMMANDS  too many pipes used
 *   
 *   console messages
 *      CMD_WARN_NO_CMD        print on WARN_NO_CMDS
 *      CMD_ERR_PIPE_LIMIT     print on ERR_TOO_MANY_COMMANDS
 *      CMD_ERR_EXECUTE        print on execution failure of external command
 * 
 *  Standard Library Functions You Might Want To Consider Using (assignment 1+)
 *      malloc(), free(), strlen(), fgets(), strcspn(), printf()
 * 
 *  Standard Library Functions You Might Want To Consider Using (assignment 2+)
 *      fork(), execvp(), exit(), chdir()
 */

// Function to allocate memory for command buffer
// int alloc_cmd_buff(cmd_buff_t *cmd_buff) {
//     cmd_buff->_cmd_buffer = (char *)malloc(ARG_MAX);
//     if (cmd_buff->_cmd_buffer == NULL) {
//         return ERR_MEMORY;
//     }
//     clear_cmd_buff(cmd_buff);
//     return OK;
// }

// // Function to free memory for command buffer
// int free_cmd_buff(cmd_buff_t *cmd_buff) {
//     if (cmd_buff->_cmd_buffer != NULL) {
//         free(cmd_buff->_cmd_buffer);
//         cmd_buff->_cmd_buffer = NULL;
//     }
//     return OK;
// }

// // Function to clear command buffer
// int clear_cmd_buff(cmd_buff_t *cmd_buff) {
//     if (cmd_buff->_cmd_buffer != NULL) {
//         memset(cmd_buff->_cmd_buffer, 0, ARG_MAX);
//     }
//     cmd_buff->argc = 0;
//     for (int i = 0; i < CMD_ARGV_MAX; i++) {
//         cmd_buff->argv[i] = NULL;
//     }
//     return OK;
// }

// // Function to close command buffer (free and clear)
// int close_cmd_buff(cmd_buff_t *cmd_buff) {
//     free_cmd_buff(cmd_buff);
//     clear_cmd_buff(cmd_buff);
//     return OK;
// }

// // Function to free command list
// int free_cmd_list(command_list_t *cmd_lst) {
//     for (int i = 0; i < cmd_lst->num; i++) {
//         free_cmd_buff(&cmd_lst->commands[i]);
//     }
//     cmd_lst->num = 0;
//     return OK;
// }

// // Function to parse a single command into cmd_buff_t
// int build_cmd_buff(char *cmd_line, cmd_buff_t *cmd_buff) {
//     // Allocate memory for the command buffer
//     if (alloc_cmd_buff(cmd_buff) != OK) {
//         return ERR_MEMORY;
//     }
    
//     // Copy the command line to the buffer
//     strncpy(cmd_buff->_cmd_buffer, cmd_line, ARG_MAX - 1);
//     cmd_buff->_cmd_buffer[ARG_MAX - 1] = '\0';
    
//     // Split the command line into arguments
//     cmd_buff->argc = 0;
//     char *token = strtok(cmd_buff->_cmd_buffer, " \t");
//     while (token != NULL && cmd_buff->argc < CMD_ARGV_MAX - 1) {
//         cmd_buff->argv[cmd_buff->argc++] = token;
//         token = strtok(NULL, " \t");
//     }
//     cmd_buff->argv[cmd_buff->argc] = NULL;  // NULL-terminate the argument list
    
//     return OK;
// }

// // Function to match built-in commands
// Built_In_Cmds match_command(const char *input) {
//     if (input == NULL) {
//         return BI_NOT_BI;
//     }
    
//     if (strcmp(input, EXIT_CMD) == 0) {
//         return BI_CMD_EXIT;
//     } else if (strcmp(input, "cd") == 0) {
//         return BI_CMD_CD;
//     } else if (strcmp(input, "dragon") == 0) {
//         return BI_CMD_DRAGON;
//     }
    
//     return BI_NOT_BI;
// }

// // Function to execute built-in commands
// Built_In_Cmds exec_built_in_cmd(cmd_buff_t *cmd) {
//     if (cmd->argc == 0 || cmd->argv[0] == NULL) {
//         return BI_NOT_BI;
//     }
    
//     Built_In_Cmds cmd_type = match_command(cmd->argv[0]);
    
//     switch (cmd_type) {
//         case BI_CMD_EXIT:
//             exit(0);  // Exit the shell
//             return BI_EXECUTED;
            
//         case BI_CMD_CD:
//             if (cmd->argc < 2) {
//                 printf("cd: missing argument\n");
//             } else if (chdir(cmd->argv[1]) != 0) {
//                 perror("cd");
//             }
//             return BI_EXECUTED;
            
//         case BI_CMD_DRAGON:
//             printf("Here be dragons!\n");
//             return BI_EXECUTED;
            
//         case BI_NOT_BI:
//         default:
//             return BI_NOT_BI;
//     }
// }

// int exec_local_cmd_loop()
// {
//     char input_line[SH_CMD_MAX];
//     command_list_t clist;
//     int rc;

//     while (1) {
//         // Display prompt
//         printf("%s", SH_PROMPT);
//         fflush(stdout);

//         // Read user input
//         if (fgets(input_line, SH_CMD_MAX, stdin) == NULL) {
//             break;
//         }

//         // Remove trailing newline
//         input_line[strcspn(input_line, "\n")] = '\0';

//         // Parse input into command_list_t
//         rc = build_cmd_list(input_line, &clist);
//         if (rc != OK) {
//             if (rc == WARN_NO_CMDS) {
//                 printf(CMD_WARN_NO_CMD);
//             } else {
//                 printf("Error parsing command\n");
//             }
//             continue;
//         }

//         // Check if the first command is a built-in command
//         Built_In_Cmds result = exec_built_in_cmd(&clist.commands[0]);
//         if (result == OK) {
//             continue;
//         }

//         // Execute pipeline
//         execute_pipeline(&clist);
//     }

//     return OK;
// }

// // Function to parse input into multiple commands separated by pipes
// int build_cmd_list(char *cmd_line, command_list_t *clist) {
//     memset(clist, 0, sizeof(command_list_t));
    
//     char *token = strtok(cmd_line, PIPE_STRING);
//     while (token != NULL) {
//         if (clist->num >= CMD_MAX) {
//             printf(CMD_ERR_PIPE_LIMIT, CMD_MAX);
//             return ERR_TOO_MANY_COMMANDS;
//         }
//         build_cmd_buff(token, &clist->commands[clist->num]);
//         clist->num++;
//         token = strtok(NULL, PIPE_STRING);
//     }
//     return OK;
// }

// // Function to execute a pipeline of commands
// int execute_pipeline(command_list_t *clist) {
//     int num_commands = clist->num;
//     int pipes[num_commands - 1][2];
//     pid_t pids[num_commands];

//     // Create pipes
//     for (int i = 0; i < num_commands - 1; i++) {
//         if (pipe(pipes[i]) == -1) {
//             perror("pipe");
//             return ERR_EXEC_CMD;
//         }
//     }

//     // Fork processes for each command
//     for (int i = 0; i < num_commands; i++) {
//         pids[i] = fork();
//         if (pids[i] == -1) {
//             perror("fork");
//             return ERR_EXEC_CMD;
//         }

//         if (pids[i] == 0) { // Child process
//             // Redirect input from previous pipe if not first command
//             if (i > 0) {
//                 dup2(pipes[i - 1][0], STDIN_FILENO);
//             }
//             // Redirect output to next pipe if not last command
//             if (i < num_commands - 1) {
//                 dup2(pipes[i][1], STDOUT_FILENO);
//             }
//             // Close all pipes in child
//             for (int j = 0; j < num_commands - 1; j++) {
//                 close(pipes[j][0]);
//                 close(pipes[j][1]);
//             }
//             // Execute command
//             execvp(clist->commands[i].argv[0], clist->commands[i].argv);
//             perror("execvp");
//             exit(EXIT_FAILURE);
//         }
//     }

//     // Close all pipes in parent
//     for (int i = 0; i < num_commands - 1; i++) {
//         close(pipes[i][0]);
//         close(pipes[i][1]);
//     }

//     // Wait for all child processes
//     for (int i = 0; i < num_commands; i++) {
//         waitpid(pids[i], NULL, 0);
//     }

//     return OK;
// }

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
 * 
 *      while(1){
 *        printf("%s", SH_PROMPT);
 *        if (fgets(cmd_buff, ARG_MAX, stdin) == NULL){
 *           printf("\n");
 *           break;
 *        }
 *        //remove the trailing \n from cmd_buff
 *        cmd_buff[strcspn(cmd_buff,"\n")] = '\0';
 * 
 *        //IMPLEMENT THE REST OF THE REQUIREMENTS
 *      }
 * 
 *   Also, use the constants in the dshlib.h in this code.  
 *      SH_CMD_MAX              maximum buffer size for user input
 *      EXIT_CMD                constant that terminates the dsh program
 *      SH_PROMPT               the shell prompt
 *      OK                      the command was parsed properly
 *      WARN_NO_CMDS            the user command was empty
 *      ERR_TOO_MANY_COMMANDS   too many pipes used
 *      ERR_MEMORY              dynamic memory management failure
 * 
 *   errors returned
 *      OK                     No error
 *      ERR_MEMORY             Dynamic memory management failure
 *      WARN_NO_CMDS           No commands parsed
 *      ERR_TOO_MANY_COMMANDS  too many pipes used
 *   
 *   console messages
 *      CMD_WARN_NO_CMD        print on WARN_NO_CMDS
 *      CMD_ERR_PIPE_LIMIT     print on ERR_TOO_MANY_COMMANDS
 *      CMD_ERR_EXECUTE        print on execution failure of external command
 * 
 *  Standard Library Functions You Might Want To Consider Using (assignment 1+)
 *      malloc(), free(), strlen(), fgets(), strcspn(), printf()
 * 
 *  Standard Library Functions You Might Want To Consider Using (assignment 2+)
 *      fork(), execvp(), exit(), chdir()
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

int exec_local_cmd_loop()
{
    char input_line[SH_CMD_MAX];
    command_list_t clist;
    int rc;

    while (1) {
        // Display prompt
        printf("%s", SH_PROMPT);
        fflush(stdout);

        // Read user input
        if (fgets(input_line, SH_CMD_MAX, stdin) == NULL) {
            printf("\n");
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

        // Check if the first command is a built-in command
        Built_In_Cmds result = exec_built_in_cmd(&clist.commands[0]);
        if (result == BI_EXECUTED) {
            continue;
        }

        // Execute pipeline
        execute_pipeline(&clist);
        
        // Free allocated memory for command list
        free_cmd_list(&clist);
    }

    return OK;
}

// Function to parse input into multiple commands separated by pipes
int build_cmd_list(char *cmd_line, command_list_t *clist) {
    memset(clist, 0, sizeof(command_list_t));
    
    // Check for empty input
    if (cmd_line == NULL || *cmd_line == '\0') {
        return WARN_NO_CMDS;
    }
    
    // Make a copy of the command line for strtok
    char cmd_copy[SH_CMD_MAX];
    strncpy(cmd_copy, cmd_line, SH_CMD_MAX - 1);
    cmd_copy[SH_CMD_MAX - 1] = '\0';
    
    char *token = strtok(cmd_copy, PIPE_STRING);
    if (token == NULL) {
        return WARN_NO_CMDS;
    }
    
    while (token != NULL) {
        if (clist->num >= CMD_MAX) {
            printf(CMD_ERR_PIPE_LIMIT, CMD_MAX);
            return ERR_TOO_MANY_COMMANDS;
        }
        
        int rc = build_cmd_buff(token, &clist->commands[clist->num]);
        if (rc == OK) {
            clist->num++;
        } else if (rc != WARN_NO_CMDS) {
            // If build_cmd_buff returns an error other than WARN_NO_CMDS,
            // we should propagate it
            return rc;
        }
        // If WARN_NO_CMDS, we just skip this command
        
        token = strtok(NULL, PIPE_STRING);
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
            if (execvp(clist->commands[i].argv[0], clist->commands[i].argv) == -1) {
                perror(clist->commands[i].argv[0]);
                exit(EXIT_FAILURE);
            }
        }
    }

    // Close all pipes in parent
    for (int i = 0; i < num_commands - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    // Wait for all child processes
    for (int i = 0; i < num_commands; i++) {
        waitpid(pids[i], NULL, 0);
    }

    return OK;
}