#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define clear() printf("\033[H\033[J")

// Internal commands -> cd echo pwd 
// External commands -> ls cat date rm mkdir


void parseShellLine(const char *line) {
	if (strcmp(line, "clear") == 0) {
		clear();
	}
	else if (strcmp(line, "exit") == 0) {
		printf("\n");
		exit(0);
	}
}



void shell() {
	const char USERNAME[] = "arman";
	char line[1000];

	
	printf("%s $ ", USERNAME);
	fgets(line, 1000, stdin);
	strtok(line, "\n"); // remove the trailing \n at the end of the line

	parseShellLine(line);


};





int main() {
	
	printf("[!] Switched to UNIX Shell.\n\n");
	while (1) {
		shell();
	}
	
	
	return 0;
}
