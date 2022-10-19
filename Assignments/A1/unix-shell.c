#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>


#define DEBUG 0
#define MAX_ARR_LEN 1000


// Internal commands -> cd echo pwd 
// External commands -> ls cat date rm mkdir


char fullPathToBinaries[PATH_MAX];


void echo(char command[], char rootCommand[]);
void cd(char command[], char rootCommand[]);
void pwd(char command[], char rootCommand[]);


void runExternalCommand(char command[], char rootCommand[], char* args[]) {
	pid_t forkType = fork();

	if (forkType == -1) {
		printf("Error: Failed to run this external command due to a forking error.");
	}
	else if (forkType == 0) { // for child process
		char binPath[PATH_MAX];
		strcpy(binPath, fullPathToBinaries);
		strcat(binPath, rootCommand);

		int execBin = execv(binPath, args);

		exit(0);
	}
	else { // for parent process
		wait(NULL);
	} 

}


void debug(char command[], char rootCommand[], char* args[]) {
	if (DEBUG) {
		printf("[ROOT] %s\n", rootCommand);
		printf("[CMD] %s\n", command);
		printf("[ARGS] ");
		
		for (int i = 0; i < 10; i++) {
			if (args[i] == NULL) { 
				break;
			}
			printf("%s,", args[i]);
		}
		printf("\n");
	}
}


void checkForBasicCommand(char command[]) {
	if (strcmp(command, "clear") == 0) {
		printf("\033[H\033[J"); // clears the console
	}
	else if (strcmp(command, "exit") == 0) {
		printf("\n");
		exit(0);
	}
	else if(strcmp(command, "dog") == 0) {
		printf("woof\n");
	}
}


void checkForInternalCommand(char command[], char rootCommand[]) {
	if (strcmp(rootCommand, "echo") == 0) {
		echo(command, rootCommand);
	}
	else if (strcmp(rootCommand, "pwd") == 0) {
		pwd(command, rootCommand);
	}
	else if (strcmp(rootCommand, "cd") == 0) {
		cd(command, rootCommand);
	}
}


void checkForExternalCommand(char command[], char rootCommand[], char* args[]) {
	if (strcmp(rootCommand, "cat") == 0 || strcmp(rootCommand, "ls") == 0 || strcmp(rootCommand, "date") == 0 || strcmp(rootCommand, "rm") == 0 || strcmp(rootCommand, "mkdir") == 0) {
		runExternalCommand(command, rootCommand, args);
	}
}


void shellPrompt() {
	//todo: fix any bugs with the path name in the prompt
	char* user = getenv("USER");
	char currentDir[PATH_MAX];
	char pwdLastDir[MAX_ARR_LEN];
	int skipToken = 0;

	if (getcwd(currentDir, sizeof(currentDir)) != NULL) {
		if (strcmp(currentDir, "/") == 0) {
			char* p = "/";
			strcpy(pwdLastDir, p);
			skipToken = 1;

		}
		if (!skipToken) {
			char *token = strtok(currentDir, "/");
			char checkedToken[MAX_ARR_LEN];
			while (token != NULL)
			{
				token = strtok(NULL, "/");
				if (token != NULL)
				{
					strcpy(checkedToken, token);
				}
			}
			strcpy(pwdLastDir, checkedToken);
		}
	}
	printf("\033[38;5;39m"); // turn color to custom color
	printf("%s", user); // print the username in custom color
	printf("\033[97m"); // reset color to default
	printf(" %s $ ", pwdLastDir);
}


void shellInput(char command[], char rootCommand[], char* args[]) {
	char line[MAX_ARR_LEN];
	char arr[MAX_ARR_LEN][MAX_ARR_LEN];

	int chrCount = 0;
	while (1) {
		int chr = fgetc(stdin);
		line[chrCount++] = (char) chr;
		if (chr == '\n') {
			break;
		}
	};

	if (chrCount == 1) { // executes when no command was written
		return;
	};

	char *parse;
	parse = strtok(line, "\n"); // remove the trailing \n at the end of the line. This solution might not be thread-safe
	
	strcpy(command, parse);

	// to generate the root command
	for (int i=0; i < MAX_ARR_LEN; i++) {
		char chr = command[i];
		if (chr == '\0' || chr == ' ' || chr == '\n') {
			rootCommand[i] = '\0';
			break;
		}
		rootCommand[i] = chr;
	}

	/* Generate the args array of Strings */
	char *argsTemp[MAX_ARR_LEN]; // create a temporary array of Strings for holding the arguments
	char commandCopy[MAX_ARR_LEN]; // create a temporary copy of the command line input
	strcpy(commandCopy, command);	
	char *parseToken; 
	parseToken = strtok(commandCopy, " ");
	int wordCount = 0; // keep track of word count to discard the 0th word as it isn't an argument but only the root command

	while (parseToken != NULL) {
		if (wordCount != 0) {
			argsTemp[wordCount - 1] = parseToken;
		}
		parseToken = strtok(NULL, " ");
		if (parseToken == NULL) {
			argsTemp[wordCount] = NULL; // NULL terminate the array of char*/Strings because it's useful for finding the end of the array
			break;
		}
		wordCount++;
	}

	memcpy(args, argsTemp, sizeof(argsTemp)); // transfer contents of the arguments list to the args array of strings
}


int checkForValidCommand(char rootCommand[]) {
	if (strcmp(rootCommand, "clear") == 0 || strcmp(rootCommand, "exit") == 0 || strcmp(rootCommand, "dog") == 0) {
		return 1;
	}
	else if (strcmp(rootCommand, "echo") == 0 || strcmp(rootCommand, "cd") == 0 || strcmp(rootCommand, "pwd") == 0) {
		return 1;
	}
	else if (strcmp(rootCommand, "cat") == 0 || strcmp(rootCommand, "ls") == 0 || strcmp(rootCommand, "date") == 0 || strcmp(rootCommand, "rm") == 0 || strcmp(rootCommand, "mkdir") == 0) {
		return 1;
	}
	else {
		return 0;
	}
}


int main() {
	printf("\033[H\033[J"); // clears the console
	printf("\033[48;5;62m"); // sets foreground and/or background to custom colors
	printf("[!] Switched to ");
	printf("ARMSH \n\n");
	printf("\033[0m");	   // reset color to default

	if (getcwd(fullPathToBinaries, sizeof(fullPathToBinaries)) != NULL) {
		strcat(fullPathToBinaries, "/cmdbin/");
	};

	while (1) {	
		char command[MAX_ARR_LEN]; // contains one giant line of the command input by the user. This is parsed soon after.
		char rootCommand[MAX_ARR_LEN]; // basically the first word of the command like echo, ls, etc
		char* args[MAX_ARR_LEN]; // contains the arguments of the command in an array of strings which excludes the root command

		shellPrompt(); // prompt for the shell
		shellInput(command, rootCommand, args); // gets the input for the shell

		debug(command, rootCommand, args); // For debugging purposes. #define DEBUG sets the debug mode for 0/1

		checkForBasicCommand(command); // check and run commands like exit, clear
		checkForInternalCommand(command, rootCommand); // check for internal commands like echo, pwd
		checkForExternalCommand(command, rootCommand, args); // check for external commands like ls, cat

		if (!checkForValidCommand(rootCommand)) {
			printf("armsh: command not found: %s\n", rootCommand);
		}
	
	}
	return 0;
}


/* Functions related to the working of INTERNAL commands */

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

	if (containsFlag) {
		for (int i = 0; i < MAX_ARR_LEN; i++) {
			char chr = command[i];
			if (chr == '\0' || chr == '\n') {
				content[x] = '\0';
				break;
			}

			if (whitespaceCount > 1) {
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


void echo(char command[], char rootCommand[]) {
	char sw[MAX_ARR_LEN];
	char secondWord[MAX_ARR_LEN]; // second word is basically the flag
	char* secondWordPtr = findFlagInCommand(command, sw);
	strcpy(secondWord, secondWordPtr);

	char cnt[MAX_ARR_LEN];
	char content[MAX_ARR_LEN];

	if (strcmp(secondWord,"-n") == 0) {
		char* contentPtr = getContent(command, cnt, 1);
		strcpy(content, contentPtr);
		printf("%s", content);
	}
	else if (strcmp(secondWord, "--help") == 0) {
		// print the help menu for echo
		printf("HELP FOR ECHO\n");
		printf("Usage format:\n");
		printf("Without flags: echo <message>\n\n");
		printf("With flags: echo [-n/--help] <message>\n\n");
		printf("Flags: \n");
		printf("-n : Prints the message without a newline character at the end\n");
		printf("--help : Prints this message\n");
	}
	else {
		// contains all the content which excludes the root command and the flag
		char* contentPtr = getContent(command, cnt, 0);
		strcpy(content, contentPtr);
		printf("%s\n", content);
	};

}


void cd(char command[], char rootCommand[]) {
	char sw[MAX_ARR_LEN];
	char secondWord[MAX_ARR_LEN]; // second word is basically the flag
	char *secondWordPtr = findFlagInCommand(command, sw);
	strcpy(secondWord, secondWordPtr);

	int success = chdir(secondWord);
	if (success == -1) { // failure
		perror("Error"); // print the error
	}
}


void pwd(char command[], char rootCommand[]) {
	char currentDir[PATH_MAX];

	if (getcwd(currentDir, sizeof(currentDir)) != NULL) {
		printf("%s\n", currentDir);
	}
};