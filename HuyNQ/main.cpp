#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include"scanner.h"

int main(){
	fflush(stdin);
	FILE *input,*output;
	char result[] = " ";
	
	input = fopen("test.txt","r");
	output = fopen("result.txt","w");

	while(!feof(input)){
		fgets(str,10000,input);
		L = strlen(str);
		reset();
	
		getCh();
			
		while(index_ch<L){
			Token = getToken();
			if(isComment) continue;
			if(Token==0){
				fprintf(output," ");
			}
			else if(Token==1){
				checkKey(output);
			}
			else if(Token==2){
			 	fprintf(output," NUMBER(%d) ",num);
				
			}
			else{
			 	fprintf(output,"%s",getTokenString(Token));
			};
		};
		fprintf(output,"\n");
	}
	fclose(input);
	fclose(output);
				
}
