#include<stdio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>
#include<conio.h>
#include"semantics.h"

int main(int argc, char** argv){
	fflush(stdin);
//	FILE *input;
	
	input = fopen("test.txt","r");
//	input = fopen(argv[1],"r");
	bool first = true;
	
	L = strlen(str);
	reset();
	getCh();
	
	Token = getToken();
	
	program();

}
