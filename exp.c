#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include "pastap.h"
#define UNUSED(x) (void)(x)
/*
void execute_pipeline(char *commands[], char **commands_args[], int number_commands )
{
    int pipe_fd[number_commands - 1][2];

 UNUSED( pipe_fd ); // suppress unused warning remove this line

        // array of pipes
        //
        // pipe_fd[0][0] read end
        // pipe_fd[0][1] write end
        //
        // pipe_fd[1][0]
        // pipe_fd[1][1]
        //

    // STEP create pipes in a for loop

    // STEP parent forks children in a for loop
        // fork,
        // check for error in fork command,
        // STEP if child
}

*/



void execute_pipeline(Command *cmd) {
    int pipe_fd[cmd->num_commands - 1][2];

    for (int i = 0; i < cmd->num_commands - 1; i++) {
        if (pipe(pipe_fd[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < cmd->num_commands; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            if (i != 0) {
                dup2(pipe_fd[i - 1][0], STDIN_FILENO);
                close(pipe_fd[i - 1][0]);
            } else if (cmd->input_file) {
                int fd_in = open(cmd->input_file, O_RDONLY);
                if (fd_in == -1) {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                dup2(fd_in, STDIN_FILENO);
                close(fd_in);
            }

            if (i != cmd->num_commands - 1) {
                dup2(pipe_fd[i][1], STDOUT_FILENO);
                close(pipe_fd[i][1]);
            } else if (cmd->output_file) {
                int fd_out;
                if (cmd->append_flag) {
                    fd_out = open(cmd->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
                } else {
                    fd_out = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                }
                if (fd_out == -1) {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                dup2(fd_out, STDOUT_FILENO);
                close(fd_out);
            }

            for (int j = 0; j < cmd->num_commands - 1; j++) {
                if (j != i - 1) close(pipe_fd[j][0]);
                if (j != i) close(pipe_fd[j][1]);
            }

            execvp(cmd->commands[i].command, cmd->commands[i].arguments);
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < cmd->num_commands - 1; i++) {
        close(pipe_fd[i][0]);
        close(pipe_fd[i][1]);
    }

    for (int i = 0; i < cmd->num_commands; i++) {
        wait(NULL);
    }
}

























 /*
lab 13
int main()
{
  // int pid;
 // list of available commands on a command line
        // you can add to it if you like

    char *commands[] =
    {
        "ls",
	//0
        "grep",
        "sort",
        "uniq",
        "head",
        "tail",
	//5
        "wc",
        "ps",
        "who",
        "find",
        "xargs",
	//10
        "awk",
        "cut",
	"cat",
        "file.txt",
        "tr",
	//15
        "[:upper:]",
        "[:lower:]",
        "distance",
        "-l",
	"/home/myid/ingrid/1730b/",
	//20
	
        NULL
    };


 char *pipeline_commands[] = { commands[8], commands[11], "sort", commands[1], "head", NULL };
    
    char *c1_args[] = { commands[8],commands[19] , "-maxdepth", "1", "-exec", "ls", "-ld", "{}", ";", NULL };
    char *c2_args[] = { commands[11], "-v", commands[19], "{gsub(prefix, \"\", $9)}", "1", NULL };
    char *c3_args[] = { "sort", "-k", "2", "-n", NULL };
    char *c4_args[] = { commands[1], "[0-9]s$", NULL };
    char *c5_args[] = { "head", "-n", "4", NULL };
    
    char **pipeline_args[] = { c1_args, c2_args, c3_args, c4_args, c5_args };
    int number_commands = sizeof(pipeline_commands) / sizeof(pipeline_commands[0]) - 1;

    printf("Executing the following pipeline: (%d commands - %d pipes)\n",number_commands, (num\
ber_commands-1));

    execute_pipeline(pipeline_commands, pipeline_args, number_commands);
    printf("\n\n");


    
    
    //    char *pipeline1_commands[] = { commands[13], commands[15], commands[1] };
    char *cmd1_args[] = { commands[13], commands[14], NULL };
    char *cmd2_args[] = { commands[15], commands[16], commands[17], NULL };
    char *cmd3_args[] = { commands[1], commands[18], NULL };
    // char **pipeline1_args[] = { cmd1_args, cmd2_args, cmd3_args };
    char *pipeline2_commands[] = { commands[13], commands[15], commands[1], commands[6] };
    char *cmd4_args[] = { commands[6], commands[19], NULL };
    char **pipeline2_args[] = { cmd1_args, cmd2_args, cmd3_args, cmd4_args };
    int number_commands2 = sizeof(pipeline2_commands) / sizeof(pipeline2_commands[0]);

    

     number_commands = number_commands2;
    printf("Executing the following pipeline: (%d commands - %d pipes)\n",number_commands, (number_commands-1));


 execute_pipeline(pipeline2_commands, pipeline2_args, number_commands2);

    
    return 0;
}
*/
