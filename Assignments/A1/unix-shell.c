#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LEN 100
// Internal commands -> cd echo pwd 
// External commands -> ls cat date rm mkdir

/* Internal Commands */

void checkForInternalCommand(char *command, char *rootCommand, char* args[]) {

}

void debug(char *command, char *rootCommand, char *args[]) {
	printf("[ROOT] %s\n", rootCommand);
	printf("[CMD] %s\n", command);
	printf("[ARGS] ");

	for (int i=0; i < MAX_LEN; i++) {
		if (args[i] == NULL) { // reached the end of arguments list
			break;
		}
		printf("%s #  ", args[i]);
	}
	printf("\n");

}

	/* Basic Commands */

void checkForBasicCommand(char *command) {
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

void shellInput(char command[], char rootCommand[], char* args[]) {
	char line[1000];
	char* arr[MAX_LEN];
	char* parse;

	int c = 0;
	while (1) {
		int chr = fgetc(stdin);
		line[c++] = (char) chr;
		if (chr == '\n') {
			break;
		}
	};

	if (c == 1) { // executes when no command was written
		return;
	};							
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


};

int main()
{
	printf("[!] Switched to UNIX Shell.\n\n");

	while (1)
	{
		char command[MAX_LEN];
		char rootCommand[MAX_LEN]; // basically the first word of the command like echo, ls, etc
		char *args[MAX_LEN];

		shellPrompt(); // prompt for the shell
		shellInput(command, rootCommand, args); // gets the input for the shell

		debug(command, rootCommand, args); // For debugging purposes

		checkForBasicCommand(command); // check and run commands like exit, clear
		checkForInternalCommand(command, rootCommand, args);
	}

	return 0;
}


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


void echo();
void cd();
void pwd();


