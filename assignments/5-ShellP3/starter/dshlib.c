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
            break;
        }

        // Remove trailing newline
        input_line[strcspn(input_line, "\n")] = '\0';

        // Parse input into command_list_t
        rc = build_cmd_list(input_line, &clist);
        if (rc != OK) {
            if (rc == WARN_NO_CMDS) {
                printf(CMD_WARN_NO_CMD);
            } else {
                printf("Error parsing command\n");
            }
            continue;
        }

        // Check if the first command is a built-in command
        Built_In_Cmds result = exec_built_in_cmd(&clist.commands[0]);
        if (result == OK) {
            continue;
        }

        // Execute pipeline
        execute_pipeline(&clist);
    }

    return OK;
}

// Function to parse input into multiple commands separated by pipes
int build_cmd_list(char *cmd_line, command_list_t *clist) {
    memset(clist, 0, sizeof(command_list_t));
    
    char *token = strtok(cmd_line, PIPE_STRING);
    while (token != NULL) {
        if (clist->num >= CMD_MAX) {
            printf(CMD_ERR_PIPE_LIMIT);
            return ERR_TOO_MANY_COMMANDS;
        }
        build_cmd_buff(token, &clist->commands[clist->num]);
        clist->num++;
        token = strtok(NULL, PIPE_STRING);
    }
    return OK;
}

