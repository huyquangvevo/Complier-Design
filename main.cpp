#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
//#include"scanner.h"

typedef enum {
	NONE=0, IDENT, NUMBER,
	BEGIN, CALL, CONST, DO,  ELSE, END, FOR, IF, ODD,
	PROCEDURE, PROGRAM, THEN, TO, VAR, WHILE,
	PLUS, MINUS, TIMES, SLASH, EQU, NEQ, LSS, LEQ, GRT, GEQ, LPARENT, RPARENT, LBRACK, RBRACK, PERIOD, COMMA, SEMICOLON,  ASSIGN, PERCENT
} TokenType;

char* keyword[] = {"NONE","IDENT","NUMBER","BEGIN","CAL",
	"CONST","DO","ELSE","END","FOR","IF","ODD","PROCEDURE",
	"PROGRAM","THEN","TO","VAR","WHILE","PLUS","MINUS","TIMES",
	"SLASH","EQU","NEQ","LSS","LEQ","GRT","GEQ","LPARENT","RPARENT",	
	"LBRACK","RBRACK","PERIOD","COMMA","SEMICOLON","ASSIGN","PERCENT"};
	
int numKey = 37;
TokenType Token;
int num;
const int MAX_IDENT_LEN = 50;
char Id[MAX_IDENT_LEN+1];
char c, str[10000];
int i_ident = -1;
int index_ch = -1;
int L;

void getCh(){
	index_ch++;
	c = str[index_ch];
}

TokenType getToken(){
	if(isspace(c)){
		getCh();
		return NONE;
	};
	
	if(isalpha(c)||c==95){
		i_ident = -1;
		while(c==95||isdigit(c)||isalpha(c)){
			i_ident++;
			Id[i_ident]=c;
			getCh();	
		}	
		return IDENT;	
	}
	
	if(isdigit(c)){
		num = 0;
		while(isdigit(c)){
			int digit = c - '0';
			num = num*10 + digit;
			getCh();
		}
		if(isalpha(c)||c==95)
			printf("\nLoi cu phap\n");
		return NUMBER;
	};
	
	switch(c){
		case '+':
			getCh();
			return PLUS;
		
		case '-':
			getCh();
			return MINUS;
			
		case '*':
			getCh();
			return TIMES;
		
		case '/':
			getCh();
			return SLASH;
			
		case '%':
			getCh();
			return PERCENT;
			
		case '=':
			getCh();
			return EQU;
			
		case '<':
			getCh();
			if(c=='>'){
				getCh();
				return NEQ;
				}
			else if (c=='='){
				getCh();
				return LEQ;
				}
			return LSS;
		
		case '>':
			getCh();
			if(c=='='){
				getCh();
				return GEQ;
			};
			return GRT;
		
		case '(':
			getCh();
			return LPARENT;
			
		case ')':
			getCh();
			return RPARENT;
			
		case '[':
			getCh();
			return LBRACK;
			
		case ']':
			getCh();
			return RBRACK;
			
		case '.':
			getCh();
			return PERIOD;
			
		case ',':
			getCh();
			return COMMA;
			
		case ';':
			getCh();
			return SEMICOLON;
			
		case ':':
			getCh();
			if(c=='='){
				getCh();
				return ASSIGN;
			}
			
	}
	
	return NONE;
	
}

char* getTokenString(int i){
	return keyword[i];
}

bool compareStr(char s1[],char s2[]){
	for(int j=0;j<=i_ident;j++){
		if(s1[j]!=toupper(s2[j]))
		return false;
	}
	return true;
}

void checkKey(){
	
	for(int i=0;i<numKey;i++){
		if(strlen(keyword[i])==i_ident+1)
		if(compareStr(keyword[i],Id)){
			printf(" %s ",keyword[i]);
			return;
		}; 
	};
	
	char s[i_ident];
	strncpy(s,Id,i_ident+1);
	printf(" %s(%s) ",keyword[1],s);
}

void reset(){
	i_ident = -1;
	index_ch = -1;
}


int main(){
	fflush(stdin);
	FILE *input,*output;
	
	input = fopen("test.txt","r");
		
	while(!feof(input)){
		fgets(str,10000,input);
		L = strlen(str);
		reset();
	
		getCh();
			
		while(index_ch<L){
			Token = getToken();
			if(Token==0)
				printf(" ");
			else if(Token==1){
				checkKey();
			}
			else if(Token==2)
			 	printf(" NUMBER(%d) ",num);		
			else
			 	printf("%s",getTokenString(Token));
		};
		printf("\n");
	}
	fclose(input);
				
}
