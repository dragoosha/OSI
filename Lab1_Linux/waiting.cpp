#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	signal(SIGINT, signalHandler);
	signal(SIGTERM, signalHandler);

	while (true);


	return 0;
}

void signalHandler(int signal)
{
	if (signal == SIGINT) {
		printf("\nSIGINT %d\n", signalno);
		break;
	}

	else if (signal == SIGTERM) {
		printf("\nSIGTERM %d\n", signalno);
		break;
	}

	else {
		printf("\n Signal\n");
		break;
	}

	exit(0);
}
