#include <stdio.h>
#include "functions.h"

int main(int argc, char**argv) {
char* Buffer = malloc(sizeof(char) * 65535); 
char* fileName = argv[1]; 
FILE *targetFiles;
targetFiles = fopen(fileName, "r"); 
fread(Buffer, 1, 65535, targetFiles); 
fclose(targetFiles);
// now we have to make a function to read through the file and find the operators... 
char**tokens = separateIntoTokens(Buffer); 
char* outputFileName = malloc(sizeof(char)*strlen(fileName)+7); 
memcpy(outputFileName, fileName, strlen(fileName)+1); 
sort(tokens); 
strcat(outputFileName, ".lexer"); 
FILE * outputFile = fopen(outputFileName, "w"); 
display(tokens,outputFile); 
fclose(outputFile); 
}