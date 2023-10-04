#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include "pastap.h"
#include "exp.h"




int main() {
    char input[MAX_CMD_LENGTH];
    Command cmd;

    while (1) {
        printf("PASTA: ");
        if (fgets(input, MAX_CMD_LENGTH, stdin) == NULL) {
            if (feof(stdin)) {
                break;
            } else {
                perror("fgets");
                exit(EXIT_FAILURE);
            }
        }

        for (int i = 0; i < MAX_COMMANDS; i++) {
            cmd.commands[i].command = NULL;
            cmd.commands[i].arguments = malloc((MAX_ARGS + 1) * sizeof(char *));
        }
        cmd.input_file = NULL;
        cmd.output_file = NULL;
        cmd.append_flag = 0;

        parser(input, &cmd);

        if (cmd.commands[0].command == NULL) {
            for (int i = 0; i < MAX_COMMANDS; i++) {
                free(cmd.commands[i].arguments);
            }
            continue;
        }

        if (is_builtin_command(&cmd.commands[0])) {
            execute_builtin_command(&cmd.commands[0]);
        } else {
            execute_pipeline(&cmd);
        }

        for (int i = 0; i < MAX_COMMANDS; i++) {
            free(cmd.commands[i].arguments);
        }
    }

    return 0;
}
