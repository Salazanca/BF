#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int returnIndex(int n, int *arr, int len){
	int i;
	for (i = 0; i < len; i++){
		if (arr[i] == n){
			return i;
		}
	}
	return -1;
}
int main(int argc, char** argv){
    int i;
    int tapeLength = 30000;
    char tape[tapeLength];
    int sz;
	/*const char* fname = argv[1];
	FILE* fp = fopen(fname, "r");
	if (fp == NULL)
    {
       fprintf(stderr, "fopen() failed in file %s at line #%d", __FILE__, __LINE__);
       exit(EXIT_FAILURE);
    }
    fseek(fp, 0L, SEEK_END);
	sz = ftell(fp);
	rewind(fp);*/
	char instructions[] = "+[-[<<[+[--->]-[<<<]]]>>>-]>-.---.>..>.<<<<-.<+.>>>>>.>.<<.<-.";
	sz = sizeof(instructions)/sizeof(instructions[0]);
	//fgets(instructions, sz, fp);
	int brackets = 0;
	for (i = 0; i < sz; i++){
		if (instructions[i] == '['){
			brackets++;
		}
	}
	int tempBrackets = 0;
	int startIndices[brackets];
	int endIndices[brackets];
	int tempIndex = 0;
	i = 0;
	while (i < sz){
		if (instructions[i] == '[' & startIndices[returnIndex(i, startIndices, brackets)] != i){
			if (tempBrackets == 0){
				startIndices[tempIndex] = i;
			}
			tempBrackets++;
		} else if (instructions[i] == ']' && endIndices[returnIndex(i, endIndices, brackets)] != i){
			tempBrackets--;
			if (tempBrackets == 0){
				endIndices[tempIndex] = i;
				i = startIndices[tempIndex];
				tempIndex++;
			}
		}
		i++;
	}
	i = 0;
	char temp;
	int currentIndex = 0;
	while (i < sz - 1){
		switch (instructions[i]){
			case '>':
				if (currentIndex < sz - 1){
					currentIndex++;
				}
				break;
			case '<':
				if (currentIndex > 0){
					currentIndex--;
				}
				break;
			case '+':
				tape[currentIndex] = (char)((int)(tape[currentIndex]) + 1);
				break;
			case '-':
				tape[currentIndex] = (char)((int)(tape[currentIndex]) - 1);
				break;
			case '.':
				printf("%c", tape[currentIndex]);
				break;
			case ',':
				scanf("%c", &temp);
				tape[currentIndex] = temp;
				break;
			case '[':
				if (tape[currentIndex] == 0){
					i = endIndices[returnIndex(i, startIndices, brackets)];
				}
				break;
			case ']':
				if (tape[currentIndex] != 0){
					i = startIndices[returnIndex(i, endIndices, brackets)] - 1;
				}
				break;
		}
		i++;
	}
	printf("\n");
	printf("Instructions: \n");
	for (i = 0; i < sz - 1; i++){
		printf("%c", instructions[i]);
	}
	printf("\n");
	return 0;
}
