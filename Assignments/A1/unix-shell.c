/*
 *  The unix-shell program is a UNIX-based command line shell designed to be as POSIX-compliant for whatever implementations it has
 *  This file contains the main source code for the unix-shell program
 *  The created binary will allow the user to run this UNIX-based shell in the terminal
 * 
 * 	@name ARMSH (Short for Arman Shell)
 *	@author Arman
 *  @version 0.1.1
 * 	@since 2022-10-13 19:14:17 +0000
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>
#define MAX_ARR_LEN 1000


char fullPathToBinaries[PATH_MAX];


int noQuoteInString(char command[], char *args[]) {
	int i = 0;
	while (1) {
		char chr = command[i];
		if (chr == '\0') {
			break;
		}
		if (chr == '\"' || chr == '\'') {
			return 0;
		}
		i++;
	}

	return 1;
}


int matchQuotesInString(char command[], char *args[]) {
	int singleQuoteCount = 0;
	int doubleQuoteCount = 0;
	int i = 0;

	while (1) {
		char chr = command[i];
		if (chr == '\0') {
			break;
		}
		if (chr == '\"') {
			doubleQuoteCount++;
		}
		if (chr == '\'') {
			singleQuoteCount++;
		}

 		i++;
	}

	if (singleQuoteCount % 2 == 0 && doubleQuoteCount % 2 == 0) { // successful matching of quotes
		return 1;
	}
	else {
		return 0;
	}

}


void echoWithMatchQuotes(char command[], char *args[]) {
	int i = 5; // skip the "echo " at the start of the command
	int nFlag = 0;

	if (strcmp(args[0], "-n") == 0) { // handle the -n flag
		i = 5 + 3;
		nFlag = 1;
	};

	while (1) {
		char chr = command[i];
		if (chr == '\0') {
			break;
		}
		if (chr == '\"') {
			i++;
			continue;

		}
		if (chr == '\'') {
			i++;
			continue;
		}

		printf("%c", chr);
 		i++;
	}

	if (nFlag == 0) {
		printf("\n");
	}
}


/*
 *  This function contains the code for the internal command "echo"
 *  This function will allow the user to output any message they want via the command-line
 *  Supported Flags: -n, --help
 *  Supported Edge cases:
 *      1. Handle the case where no arguments are given with echo
 *      2. Do not print quotation marks when printing the message
 *
 *  TODO: None
 */


void echo(char command[], char rootCommand[], char *args[]) {
	if (args[0] == NULL) {
		printf("\n");
	}
	else if (strcmp(args[0], "--help") == 0) { // print the help menu for --help flag
		printf("echo: help\n");
		printf("Usage: echo <flag> <message>\n");
		printf("Supported flags: -n, --help\n");
	}
	else {
		if (noQuoteInString(command, args)) {
			int i = 5;
			int nFlag = 0;

			if (strcmp(args[0], "-n") == 0) { // handle the -n flag
				i = 5 + 3;
				nFlag = 1;
			};

			while (1) {
				char chr = command[i];
				if (chr == '\0') {
					break;
				}
				printf("%c", chr);
				i++;
			}

			if (nFlag == 0) {
				printf("\n");
			}

		}
		else { // a quote was encountered in the message
			if (matchQuotesInString(command, args)) {
				echoWithMatchQuotes(command, args);
			}
			else {
				printf("echo: Error in matching quotes used in the message\n");
			}
		}

	}
}


/*
 *  This function contains the code for the internal command "cd"
 *  This function will allow the user to change their working directories
 *  Supported Flags: -P, -L
 *  Supported Edge cases:
 *      1. Handle the case where the user tries to cd into a non-existent directory
 *      2. User gets cd'd into their user working directory when the command is ran without any argument
 *
 *  TODO: None
 */


void cd(char command[], char rootCommand[], char *args[]) {
	if (args[0] == NULL) {
		int changeDir = chdir(getenv("HOME"));
		if (changeDir == -1) { // failure in changing directory
			printf("cd: No such directory\n");
		}
	}
	else if (args[0] != NULL && strcmp(args[0], "-P") == 0) { // -P flag
		int changeDir = chdir(args[1]);
		if (changeDir == -1) {
			printf("cd: No such directory\n");
		}
	}
	else if (args[0] != NULL && strcmp(args[0], "-L") == 0) { // -L flag
		int changeDir = chdir(args[1]);
		if (changeDir == -1) {
			printf("cd: No such directory\n");
		}
	}
	else if (args[0] != NULL){
		int changeDir = chdir(args[0]);
		if (changeDir == -1) {
			printf("cd: No such directory\n");
		}
	}
	else {
		printf("cd: Invalid usage of command\n");
	}

}


/*
 *  This function contains the code for the internal command "pwd"
 *  This function will allow the user to print/view their current working directory
 *  Supported Flags: -L, -P
 *  Supported Edge cases:
 *      1. Handle case where too many arguments are provided
 *      2. Handle case where the current working directory is deleted (from external influence) but the user is still present in the directory in the shell 
 *	TODO: None
 */


void pwd(char command[], char rootCommand[], char *args[]) {
	if (args[0] == NULL || (strcmp(args[0], "-P") == 0 && args[1] == NULL)) {
		char currentDir[PATH_MAX];
		if (getcwd(currentDir, sizeof(currentDir)) != NULL) {
			printf("%s\n", currentDir);
		}
		else {
			printf("pwd: The current working directory does not exist!\n");
		}
	}
	else if (args[0] == NULL || (strcmp(args[0], "-L") == 0 && args[1] == NULL)) {
		char currentDir[PATH_MAX];
		if (getcwd(currentDir, sizeof(currentDir)) != NULL) {
			printf("%s\n", currentDir);
		}
		else {
			printf("pwd: The current working directory does not exist!\n");
		}
	}
	else {
		printf("pwd: Too many arguments\n");
	}


};


void* execThread(void* vargs) {
	char* argsAsString = (char*) vargs;
	return NULL;
}


void runExternalCommand(char command[], char rootCommand[], char* args[]) {
	
	int executionType = 0; // 0 -> fork-based, 1 -> thread-based

	int i = 0;
	while (1) {
		if (args[i] == NULL) {
			if (strcmp(args[i - 1], "&t") == 0) {
				executionType = 1;
			}
			break;
		}
		i++;
	}

	if (executionType == 0) { // Fork based execution
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
	else if (executionType == 1) { // Thread based execution
		printf("[Thread based execution]\n");

		char argsAsString[1000];

		int i = 0;
		while (1) {
			char* arg = args[i];
			if (arg == NULL) {
				break;
			}
			else if (strcmp(arg, "&t") == 0) {
				i++;
				continue;
			};

			if (i == 0) {
				strcat(argsAsString, arg);
			}
			else if (i != 0) {
				char tempArg[1000] = " ";
				strcat(tempArg, arg);
				strcat(argsAsString, tempArg);
			};

			i++;
		}

		pthread_t t;
		pthread_create(&t, NULL, execThread, (void*) argsAsString);
		pthread_join(t, NULL);

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
}


void checkForInternalCommand(char command[], char rootCommand[], char *args[]) {
	if (strcmp(rootCommand, "echo") == 0) {
		echo(command, rootCommand, args);
	}
	else if (strcmp(rootCommand, "pwd") == 0) {
		pwd(command, rootCommand, args);
	}
	else if (strcmp(rootCommand, "cd") == 0) {
		cd(command, rootCommand, args);
	}
}


void checkForExternalCommand(char command[], char rootCommand[], char* args[]) {
	if (strcmp(rootCommand, "cat") == 0 || strcmp(rootCommand, "ls") == 0 || strcmp(rootCommand, "date") == 0 || strcmp(rootCommand, "rm") == 0 || strcmp(rootCommand, "mkdir") == 0) {
		runExternalCommand(command, rootCommand, args);
	}
}


void shellPrompt() {
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
			while (token != NULL) {
				token = strtok(NULL, "/");
				if (token != NULL) {
					strcpy(checkedToken, token);
				}
			}
			strcpy(pwdLastDir, checkedToken);
		}
	}

	// Print the shell prompt in colors other than the default color
	printf("\033[38;5;7m");
	printf("%s", user); 
	printf("\033[38;5;183m"); 
	printf(" %s ", pwdLastDir); 
	printf("\033[97m"); 
	printf("$ ");
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
		strcpy(rootCommand, "");
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
	char *argsTemp[MAX_ARR_LEN]; // create a temporary array of strings for holding the arguments
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
	if (strcmp(rootCommand, "clear") == 0 || strcmp(rootCommand, "exit") == 0) {
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
	// Print the shell greet message in color
	printf("\033[H\033[J"); 
	printf("\033[48;5;183m"); // background
	printf("\033[38;5;0m"); // foreground 
	printf("[!] Switched to ARMSH \n\n");
	printf("\033[0m"); // reset colors

	if (getcwd(fullPathToBinaries, sizeof(fullPathToBinaries)) != NULL) {
		strcat(fullPathToBinaries, "/cmdbin/");
	};

	while (1) {
		char command[MAX_ARR_LEN];	   // The whole raw un-parsed input received from the user as the command
		char rootCommand[MAX_ARR_LEN]; // First word of the command i.e the command name
		char *args[MAX_ARR_LEN];	   // The arguments of the array excluding the root command / command name

		shellPrompt(); // Prints the prompt for the shell
		shellInput(command, rootCommand, args); // Gets the command to execute as input
		
		checkForBasicCommand(command); // Checks and runs basic commands if found
		checkForInternalCommand(command, rootCommand, args); // Checks and runs internal commands if found
		checkForExternalCommand(command, rootCommand, args); // Checks and runs external commands if found

		if (!checkForValidCommand(rootCommand)) {
			printf("armsh: command not found: %s\n", rootCommand);
		}
	}
	return 0;
}

