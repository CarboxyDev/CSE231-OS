#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Internal commands -> cd echo pwd 
// External commands -> ls cat date rm mkdir


void checkForBasicCommand(char* command) {
	if (strcmp(command, "clear") == 0) {
		printf("\033[H\033[J"); // clears the console
	}
	else if (strcmp(command, "exit") == 0) {
		printf("\n");
		exit(0);
	};
}

void shellPrompt() {
	char* user = getenv("USER");
	printf("%s $ ", user);
}

void shellInput(char command[], char* args[]) {
	char line[1000];
	char* arr[100];
	char* parse;

	int c = 0;
	while (1) {
		int chr = getc(stdin);
		line[c++] = (char) chr;
		if (chr == '\n') {
			break;
		}
	};

	if (c == 1) { return; }; // no command was written
	parse = strtok(line, "\n"); // remove the trailing \n at the end of the line. This solution might not be thread-safe

	int c2 = 0;
	while (parse != NULL) { // turn the line into -> words
		arr[c2++] = strdup(parse);
		parse = strtok(NULL, "\n");
	} 

	strcpy(command, arr[0]);
 
	for (int x=0; x < c2; x++) {
		args[x] = arr[x];
	}

	args[c2] = NULL; // end the arguments list with a NULL terminator
	printf("%s\n", line);

	/*
	fgets(line, 1000, stdin);
	strtok(line, "\n"); // remove the trailing \n at the end of the line. This solution might not be thread-safe
 	*/
	//checkForBasicCommand(line); // run commands like exit, clear

};

int main()
{
	printf("[!] Switched to UNIX Shell.\n\n");

	while (1)
	{
		char command[100];
		char rootCommand[100]; // basically the first word of the command like echo, ls, etc
		char *args[100];

		shellPrompt(); // prompt for the shell
		shellInput(command, args); // gets the input for the shell

		checkForBasicCommand(command); // check and run commands like exit, clear
	}

	return 0;
}


void echoCommand(char **allArgs)
{
	printf("echo command found. First arg is %s", allArgs[0]);
};

int getWordCount(char *line)
{
	int wordCount = 1;
	for (int i = 0; i < strlen(line); i++)
	{
		if (line[i] == 32 && i != 0)
		{
			wordCount++;
		}
	}
	return wordCount;
}
