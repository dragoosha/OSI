#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char** argv)
{
	pid_t pid;
	pid_t w;
	int status;

	pid = fork();


	if (pid == 0) {
		sleep(3);

		return 1;
	}

	else if (pid == -1) {
		printf("ERROR! fork\n");

		exit(EXIT_FAILURE);
	}

	else {
		w = wait(&status);

		if (w == -1) {
			printf("waiting pid\n");
			exit(EXIT_FAILURE);
		}

		signal(SIGTERM, signalHandler);
		signal(SIGINT, signalHandler);

		if (WIFEXITED(status))
			printf("\nNormal exit\n", WEXITSTATUS(status));

		else if (WIFSIGNALED(status))
			printf("\nKilled\n", WTERMSIG(status));

		else if (WIFSTOPPED(status))
			printf("\nStopped\n", WSTOPSIG(status));

		else if (WIFCONTINUED(status))
			printf("\nContinue\n");
	}

	return 0;
}

void signalHandler(int signal)
{}
