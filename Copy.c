/** Mimics the cp command in shells */ 
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[] {
	FILE *source; 
	FILE *destination;
	char *outFileName = "bar.txt";	
	char ch;
	char *program_name;		
	program_name = argv[0];	
	source = fopen(argv[1], "rb");
	destination = fopen(argv[2], "wb");	

	if(argc < 3) {
		fprintf(stderr, "Error: Not enough arguments.\n");
		exit(1);
	}	
	if (source == NULL) {
		fprintf(stderr, "Error: Cannot find source file.\n");
		exit(8);
	}	
	if (destination == NULL) {	
		destination = fopen(outFileName, "wb");	
	}	
	/** Read until the end of file */ 	
	while(!feof(source))
    {
		ch = getc(source);
		if(ferror(source))
		{
			printf("Read Error");
			clearerr(source);
			break;
		}
		else
		{
			if(!feof(source)) putc(ch, destination);
			if(ferror(destination))
			{
				printf("Write Error");
				clearerr(destination);
				break;
				
			}
		}
    }	
	fclose(source);
	fclose(destination);	
	return 0;
}