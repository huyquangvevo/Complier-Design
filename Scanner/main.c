#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include"scanner.h"
#include<stdbool.h>
#include<conio.h>

int main(int argc, char** argv){
	fflush(stdin);
	FILE *input,*output;
	char result[] = " ";
		
//	input = fopen("test.txt","r");
	input = fopen(argv[1],"r");

	while(1){
		if(fgets(str,10000,input)==NULL)
			return -1;
		L = strlen(str);
		reset();
	
		getCh();
			
		while(index_ch<L){
			Token = getToken();
			if(isComment) continue;
			if(Token==0){
				system("cls");
				printf("error syntax: %c",c);
				return -1;
			}
			else if(Token==1){
				if(!checkKey())
				if(i_ident>10){
					system("cls");
					printf("Ident is too long");
					return -1;
				}
			}
			else if(Token==2){
				if(countDigit>9){
					system("cls");
					printf("Number is too large");
					return -1;
					}
			 	printf(" NUMBER(%d) ",num);				
			} else if(Token==37);
			else{
			 	printf("%s",getTokenString(Token));
			};
		};	
		printf("\n");
	};
	fclose(input);
	fclose(output);
	return 0;
				
}
