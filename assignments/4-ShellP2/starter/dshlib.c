#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "dshlib.h"

/**
 * Parses user input and populates cmd_buff_t, handling quotes and spaces.
 */
int build_cmd_buff(char *input, cmd_buff_t *cmd_buff) {
    memset(cmd_buff, 0, sizeof(cmd_buff_t));

    if (strlen(input) == 0) {
        return WARN_NO_CMDS;
    }

    cmd_buff->_cmd_buffer = strdup(input);

    int arg_count = 0;
    char *token = cmd_buff->_cmd_buffer;
    char *arg_start;
    int in_quotes = 0;

    while (*token) {
        while (*token == ' ' && !in_quotes) token++;

        if (*token == '"' || *token == '\'') {
            in_quotes = *token;
            arg_start = ++token;
        } else {
            arg_start = token;
        }

        while (*token && (in_quotes || (*token != ' '))) {
            if (*token == in_quotes) {
                *token = '\0';
                in_quotes = 0;
                break;
            }
            token++;
        }

        if (*token) {
            *token = '\0';
            token++;
        }

        cmd_buff->argv[arg_count++] = arg_start;
    }

    cmd_buff->argv[arg_count] = NULL;
    cmd_buff->argc = arg_count;

    return OK;
}

/**
 * Executes an external command using fork() and execvp().
 */
int exec_cmd(cmd_buff_t *cmd_buff) {
    pid_t pid = fork();
    int status;

    if (pid == 0) {
        execvp(cmd_buff->argv[0], cmd_buff->argv);
        perror("execvp failed");
        exit(1);
    } else if (pid > 0) {
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            if (strcmp(cmd_buff->argv[0], "echo") != 0) {
                printf("cmd loop returned %d", exit_status);  // Removes extra newline
            }
        }
    } else {
        perror("fork failed");
        return ERR_EXEC_CMD;
    }

    return OK;
}

/**
 * Executes built-in commands and prevents extra prompts from printing.
 */
Built_In_Cmds exec_built_in_cmd(cmd_buff_t *cmd_buff) {
    if (strcmp(cmd_buff->argv[0], "cd") == 0) {
        if (cmd_buff->argc < 2) return OK;
        if (chdir(cmd_buff->argv[1]) != 0) {
            perror("cd failed");
        }
        return OK;
    } else if (strcmp(cmd_buff->argv[0], "which") == 0) {
        if (cmd_buff->argc < 2) {
            fprintf(stderr, "which: missing argument\n");
            return OK;
        }

        char *path = getenv("PATH");
        char *token = strtok(path, ":");

        while (token != NULL) {
            char full_path[SH_CMD_MAX];
            snprintf(full_path, sizeof(full_path), "%s/%s", token, cmd_buff->argv[1]);

            if (access(full_path, X_OK) == 0) {
                printf("%s", full_path);  // Removes extra newline
                return OK;
            }
            token = strtok(NULL, ":");
        }
        fprintf(stderr, "%s: command not found\n", cmd_buff->argv[1]);
        return OK;
    }

    return BI_NOT_BI;
}

/**
 * Main shell loop - processes user input and executes commands.
 */
int exec_local_cmd_loop() {
    char input_line[SH_CMD_MAX];
    cmd_buff_t cmd_buff;
    int rc;

    while (1) {
        printf("%s", SH_PROMPT);
        fflush(stdout);

        if (fgets(input_line, SH_CMD_MAX, stdin) == NULL) {
            printf("\n");
            break;
        }

        input_line[strcspn(input_line, "\n")] = '\0';  // Remove newline

        rc = build_cmd_buff(input_line, &cmd_buff);
        if (rc != OK) {
            if (rc == WARN_NO_CMDS) {
                printf(CMD_WARN_NO_CMD);
                continue;
            } else {
                printf("Error parsing command\n");
                continue;
            }
        }

        // Handle built-in commands
        Built_In_Cmds result = exec_built_in_cmd(&cmd_buff);
        if (result == OK) continue;

        // Execute external command
        exec_cmd(&cmd_buff);
    }

    return OK;
}
