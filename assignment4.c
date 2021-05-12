#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#define MAX_LINES 10000
#define MAX_CHAR 200

struct instruction_s{
    int step ;
    int index ;
}CALL_INSTR[MAX_LINES];

char* get_word(char* s, int n){
    int i = 0;
	int WORD_ORDER = 1;
	int k = 0;
    char CHAR;
    char* WORD = (char*)malloc(sizeof(char) *50);
	while( true ) {
        CHAR = s[i];
        if( CHAR == ' ' ){
            i++;
            continue;
        }
        if( WORD_ORDER == n ){
            while((CHAR <= 122 && CHAR >= 97) || (CHAR <= 57 && CHAR >= 48)){
                WORD[k]= CHAR;
                k++;
                i++;
                CHAR = s[i];
			}
            return WORD;
        }
        while( CHAR != ' ' ){
            CHAR = s[i];
            i++;
        }
        WORD_ORDER++;
	}
}

void get_sentence(char** lines, struct instruction_s* instructions, 
				int n_instructions, char* sentence){
    int i;
	int LINE = 0;
	int j;
	int k = 0;
	int CHAR_LENGTH = 50;
    char* WORD_X ;
    for (i = 0; i <= n_instructions;i++) {
        LINE += instructions[i].step;
        WORD_X = get_word(lines[LINE], instructions[i].index);
		for (j = 0; j < CHAR_LENGTH;j++) {
            if (WORD_X[j] == 0){
            	continue;
			} 
            sentence[k] = WORD_X[j];
            k++;
        }
        sentence[k] = ' ';
        k++;
	}
    free(WORD_X);
}

int main(int argc, char **argv) {
    int k = 0;
    int l = 0;
    int CHAR_X = 0;
    int LINE = 1;
    int BUFFER = 0;
    int n_instructions;
    int NUM_OF_BIN = 2;
    int SPACE = 32;
    
	FILE *alice_book;
    alice_book = fopen(argv[1], "r");
	FILE *instructions;
    instructions = fopen(argv[2], "r");
    while(instructions != NULL){
        fscanf(instructions,"%d %d",&CALL_INSTR[k].step,&CALL_INSTR[k].index);
        k++;
        if(feof(instructions)){
            break;
        }
	}
    n_instructions = k - NUM_OF_BIN;
	char ** C_SENTENCE = (char**)malloc(MAX_LINES * sizeof(char*));
    for(k=0;k < MAX_LINES;k++){
        C_SENTENCE[k] = (char*)malloc(MAX_CHAR * sizeof(char));
    }
	while(true){
        while(true){
            CHAR_X = fgetc(alice_book);
            if( CHAR_X != SPACE ){
            	BUFFER = 0;
			}
            if( CHAR_X == EOF ){
            	break;
			} 
            if( CHAR_X == 10 ){
            	break;
			} 
            if(CHAR_X <= SPACE + 58 && CHAR_X >= SPACE + 33){
                CHAR_X += 32;
            }
            if((CHAR_X <= SPACE + 90 && CHAR_X >= SPACE + 65) || (CHAR_X <= SPACE + 25 && CHAR_X >= SPACE + 16)){
                C_SENTENCE[LINE][l] = (char)CHAR_X;
                l++;
            }
            if( CHAR_X == SPACE ){
                if( BUFFER == 1 ) {
                	continue;
				}
				else{
                    C_SENTENCE[LINE][l] = (char)CHAR_X;
                    l++;
                    BUFFER = 1;
                }
            }
        }
		l = 0;
        LINE++;
        if(CHAR_X == EOF){
        	break;
	    } 
    }
	char* SENTENCE = (char*)malloc(sizeof(char) *MAX_CHAR);
    get_sentence(C_SENTENCE,CALL_INSTR,n_instructions,SENTENCE);
    printf("%s",SENTENCE);
	fclose(alice_book);
    fclose(instructions);
    free(C_SENTENCE);
    free(SENTENCE);
	return EXIT_SUCCESS;
}
