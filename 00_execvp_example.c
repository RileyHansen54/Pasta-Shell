#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main( int argc, char *argv[] ) 
{
    pid_t pid = fork();

    if( pid == 0 )
    {
    	// Child process
        char *command[] = { "ls", "-l", NULL };
        if( execvp( command[0], command ) == -1 )
        {
		perror( "execvp" );
            	exit( EXIT_FAILURE );
        }
    } 
    else if( pid > 0 ) 
    {
        // Parent process
        int status;
        waitpid( pid, &status, 0 );
    } else 
    {
        // Fork failed
        perror( "fork" );
        exit( EXIT_FAILURE );
    }
    return 0;
}

