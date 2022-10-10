#include <stdio.h>
#include <stdlib.h>

#define clear() printf("\033[H\033[J")

// Internal commands -> cd echo pwd 
// External commands -> ls cat date rm mkdir



void shell() {
	const char* USERNAME = "arman";
	char* line;

	printf("%s $ ", USERNAME);
	scanf(" %[^\n]s", line);

	printf("You entered: %s\n", line);


};





int main(){
	
	clear();
	printf("[!] Switched to UNIX Shell.\n\n");
	while (1) {
		shell();
	}
	
	
	return 0;
}
