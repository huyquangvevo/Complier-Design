#ifndef _SCANNERH_
#define _SCANNER_H
#include<string.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


typedef enum {
	NONE=0, IDENT, NUMBER,
	BEGIN, CALL, CONST, DO,  ELSE, END, FOR, IF, ODD,
	PROCEDURE, PROGRAM, THEN, TO, VAR, WHILE,
	PLUS, MINUS, TIMES, SLASH, EQU, NEQ, LSS, LEQ, GRT, GEQ, LPARENT, RPARENT, LBRACK, RBRACK, PERIOD, COMMA, SEMICOLON,  ASSIGN, PERCENT,COMMENT
} TokenType;

const char* keyword[] = {"NONE","IDENT","NUMBER","BEGIN","CALL",
	"CONST","DO","ELSE","END","FOR","IF","ODD","PROCEDURE",
	"PROGRAM","THEN","TO","VAR","WHILE","PLUS","MINUS","TIMES",
	"SLASH","EQU","NEQ","LSS","LEQ","GRT","GEQ","LPARENT","RPARENT",	
	"LBRACK","RBRACK","PERIOD","COMMA","SEMICOLON","ASSIGN","PERCENT","COMMENT"};
	
int numKey = 38;
TokenType Token;
int  countDigit;
int num;
#define MAX_IDENT_LEN 50
#define MAX_LEN_VAR 10
#define MAX_LEN_NUM 9
char Id[MAX_IDENT_LEN+1];
char c, str[10000];
int i_ident = -1;
int index_ch = -1;
int L;
bool isComment = false;
FILE *input;
int countLine = 0;

extern 

int checkKey();
void reset();

void getCh(){
	index_ch++;
	c = str[index_ch];
	if(index_ch>=L) {
		if(fgets(str,10000,input)==NULL){
			exit(0);
		}
		countLine ++;
		printf("\n");	
	//	printf("\n%s\n",str);
		L = strlen(str);
		reset();
		getCh();
	}
}

TokenType getToken(){
	while (isspace(c)){
		getCh();
	
	};
	
	if(isalpha(c)||c==95){
		i_ident = -1;
		while(c==95||isdigit(c)||isalpha(c)){
			i_ident++;
			if(i_ident>MAX_LEN_VAR)
				return (TokenType) checkKey();
			//	break;
			Id[i_ident]=c;
			getCh();	
		}
		
		return (TokenType) checkKey();		
	//	return IDENT;	
	}
	
	if(isdigit(c)){
		num = 0;
		countDigit = 0;
		while(isdigit(c)){
			countDigit++;
			if(countDigit>MAX_LEN_NUM){
				break;
			}
			int digit = c - '0';
			num = num*10 + digit;
			getCh();
		}
		
		if(countDigit>9){
					system("cls");
					printf("Number is too large");
					exit(0);
			};
		printf(" NUMBER(%d) ",num);	
	
		return NUMBER;
	};
	
	switch(c){
		case '+':
			getCh();
			printf(" %s ","PLUS");
			return PLUS;
		
		case '-':
			getCh();
			printf(" %s ","MINUS");
			return MINUS;
			
		case '*':
			getCh();
			if(c==')'){
				isComment = false;
				getCh();
				return COMMENT;
			}
			printf(" %s ","TIMES");
			return TIMES;
		
		case '/':
			getCh();
			if(c=='/'){
				index_ch = L;
				return COMMENT;
			}
			printf(" %s ","SLASH");
			return SLASH;
			
		case '%':
			getCh();
			printf(" %s ","PERCENT");
			return PERCENT;
			
		case '=':
			getCh();
			printf(" %s ","EQU");
			return EQU;
			
		case '<':
			getCh();
			if(c=='>'){
				getCh();
				printf(" %s ","NEQ");
				return NEQ;
				}
			else if (c=='='){
				getCh();
				printf(" %s ","LEQ");
				return LEQ;
				}
			printf(" %s ","LSS");
			return LSS;
		
		case '>':
			getCh();
			if(c=='='){
				getCh();
				printf(" %s ","GEQ");
				return GEQ;
			};
			printf(" %s ","GRT");
			return GRT;
		
		case '(':
			getCh();
			if(c=='*'){
				isComment = true;
				printf(" %s ","COMMENT");
				return COMMENT;
			}
			printf(" %s ","LPARENT");
			return LPARENT;
			
		case ')':
			getCh();
			printf(" %s ","RPARENT");
			return RPARENT;
			
		case '[':
			getCh();
			printf(" %s ","LBRACK");
			return LBRACK;
			
		case ']':
			getCh();
			printf(" %s ","RBRACK");
			return RBRACK;
			
		case '.':
			getCh();
			printf(" %s ","PERIOD");
			return PERIOD;
			
		case ',':
			getCh();
			printf(" %s ","COMMA");
			return COMMA;
			
		case ';':
			getCh();
			printf(" %s ","SEMICOLON");
			return SEMICOLON;
			
		case ':':
			getCh();
			if(c=='='){
				getCh();
				printf(" %s ","ASSIGN");
				return ASSIGN;
			}
			
	}
	
	printf("\n\nerror syntax: %c, tai dong %d\n ",c,countLine);
	exit(0);
		
	return NONE;
	
}

const char* getTokenString(int i){
	return keyword[i];
}

bool compareStr(const char s1[],char s2[]){
	int j;
	for(j=0;j<=i_ident;j++){
		if(s1[j]!=toupper(s2[j]))
		return false;
	}
	return true;
}

int checkKey(){
	int i;
	for(i=0;i<numKey;i++){
		if(strlen(keyword[i])==i_ident+1)
		if(compareStr(keyword[i],Id)){
			printf(" %s ",keyword[i]);
		//	printf("\n %d \n",i);
			return i;
		}; 
	};
	
	int j;
	printf(" %s(",keyword[1]);
	for(j=0;j<i_ident+1;j++)
		printf("%c",Id[j]);
	printf(") ");
	return 1;

}

void reset(){
	i_ident = -1;
	index_ch = -1;
}
#endif
