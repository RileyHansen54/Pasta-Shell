#ifndef PASTAP_H
#define PASTAP_H
#define MAX_CMD_LENGTH 4096
#define MAX_ARGS 64
#define MAX_COMMANDS 8



typedef struct {
    char *command;
    char **arguments;
} Single;

typedef struct {
   Single commands[MAX_COMMANDS];
    int num_commands;
    char *input_file;
    char *output_file;
    int append_flag;
} Command;







void parser(char *input, Command *cmd);

int is_builtin_command(Single *cmd);

void execute_builtin_command(Single *cmd);




#endif
