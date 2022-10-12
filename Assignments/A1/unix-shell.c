#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_ARR_LEN 100
// Internal commands -> cd echo pwd 
// External commands -> ls cat date rm mkdir

void echo(char command[], char rootCommand[], char* args[]);
void cd(char command[], char rootCommand[], char *args[]);
void pwd(char command[], char rootCommand[], char *args[]);


void debug(char command[], char rootCommand[], char *args[]) {
	/*
	printf("[ROOT] %s\n", rootCommand);
	printf("[CMD] %s\n", command);
	printf("[ARGS] ");

	for (int i=0; i < MAX_ARR_LEN; i++) {
		if (args[i] == NULL) { // reached the end of arguments list
			break;
		}
		printf("%s || ", args[i]);
	}
	printf("\n");
	*/
}

	

void checkForBasicCommand(char command[]) {
	if (strcmp(command, "clear") == 0) {
		printf("\033[H\033[J"); // clears the console
	}
	else if (strcmp(command, "exit") == 0) {
		printf("\n");
		exit(0);
	};
}

void checkForInternalCommand(char command[], char rootCommand[], char *args[]) {

	if (strcmp(rootCommand, "echo") == 0) {
		echo(command, rootCommand, args);
	}



}

void shellPrompt() {
	char* user = getenv("USER");
	printf("%s $ ", user);
}

void shellInput(char command[], char rootCommand[], char* args[]) {
	char line[1000];
	char* arr[MAX_ARR_LEN];
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

	// to generate the root command
	for (int i=0; i < MAX_ARR_LEN; i++) {
		char chr = command[i];
		if (chr == '\0' || chr == ' ' || chr == '\n') {
			rootCommand[i] = '\0';
			break;
		}
		rootCommand[i] = chr;

	}

};

int main()
{
	printf("[!] Switched to UNIX Shell.\n\n");

	while (1)
	{	
		char command[MAX_ARR_LEN];
		char rootCommand[MAX_ARR_LEN]; // basically the first word of the command like echo, ls, etc
		char *args[MAX_ARR_LEN];

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

char* findFlagInCommand(char command[], char* secondWord) {
	// check the second word and see if it is a flag
	int whitespaceCount = 0;
	int x = 0;

	for (int i=0; i < MAX_ARR_LEN; i++) {
		char chr = command[i];
		if (chr == '\0' || chr == '\n') {
			secondWord[x] = '\0';
			break;
		}
		if (chr == ' ') { 
			whitespaceCount++;
		}
		if (whitespaceCount > 1) {
			secondWord[x] = '\0';
			break;
		}
		if (whitespaceCount == 1 && command[i] != ' ') { // second word is starting now
			secondWord[x] = command[i];
			x++;
		}

	}

	return secondWord;

}

char* getContent(char command[], char* content, int containsFlag) {

	int whitespaceCount = 0;
	int x = 0;
	if (!containsFlag) {
		for (int i=0; i < MAX_ARR_LEN; i++) {
			char chr = command[i];
			if (chr == '\0' || chr == '\n') {
				content[x] = '\0';
				break;
			}

			if (whitespaceCount > 0) {
				content[x] = chr;
				x++;
			}
			
			if (chr == ' ') {
				whitespaceCount++;
			}

		}
	}

	return content;

}




void echo(char command[], char rootCommand[], char* args[]) {

	char sw[MAX_ARR_LEN];
	char secondWord[MAX_ARR_LEN]; // second word is basically the flag
	char* secondWordPtr = findFlagInCommand(command, sw);
	strcpy(secondWord, secondWordPtr);

	if (strcmp(secondWord,"-n") == 0) {

	}
	else if (strcmp(secondWord, "--help") == 0) {
		// print the help menu for echo
	}
	else {
		char cnt[MAX_ARR_LEN];
		char content[MAX_ARR_LEN]; // contains all the content which excludes the root command and the flag
		char* contentPtr = getContent(command, cnt, 0);
		strcpy(content, contentPtr);
		printf("%s\n", content);
	};


	//printf("[!] Call echo | Secondword/flag is %s\n", secondWord);


}









