#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define clear() printf("\033[H\033[J")

// Internal commands -> cd echo pwd 
// External commands -> ls cat date rm mkdir

int getWordCount(const char* line) {
	int wordCount = 1;
	for (int i = 0; i < strlen(line); i++) {
		if (line[i] == 32 && i != 0) {
			wordCount++;
		}
	}
	return wordCount;
}



void parseShellLine(char* line) {
	if (strcmp(line, "clear") == 0) {
		clear();
	}
	else if (strcmp(line, "exit") == 0) {
		printf("\n");
		exit(0);
	};


	if (getWordCount(line) > 1) {
		char* lineArgs = strtok(line, " ");
	}


}



void shell() {
	const char USERNAME[] = "arman";
	char line[1000];

	
	printf("%s $ ", USERNAME);
	fgets(line, 1000, stdin);
	strtok(line, "\n"); // remove the trailing \n at the end of the line. This solution might not be thread-safe

	parseShellLine(line);


};





int main() {
	
	printf("[!] Switched to UNIX Shell.\n\n");
	while (1) {
		shell();
	}
	
	
	return 0;
}
