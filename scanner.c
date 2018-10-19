
void getCh(){
	index_ch++;
	c = str[index_ch];
}

TokenType getToken(){
	if(isspace(c)){
		getCh();
		printf(" ");
		return COMMENT;
	};
	
	if(isalpha(c)||c==95){
		i_ident = -1;
		while(c==95||isdigit(c)||isalpha(c)){
			i_ident++;
			if(i_ident>10)
				break;
			Id[i_ident]=c;
			getCh();	
		}	
		return IDENT;	
	}
	
	if(isdigit(c)){
		num = 0;
		countDigit = 0;
		while(isdigit(c)){
			countDigit++;
			if(countDigit>9){
				break;
			}
			int digit = c - '0';
			num = num*10 + digit;
			getCh();
		}
	
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
			if(c=='/'){
				isComment = false;
				getCh();
				return COMMENT;
			}
			return TIMES;
		
		case '/':
			getCh();
			if(c=='/'){
				index_ch = L;
				return COMMENT;
			}
			
			if(c=='*'){
				isComment = true;
				return COMMENT;
				}
			
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

bool checkKey(){
	int i;
	for(i=0;i<numKey;i++){
		if(strlen(keyword[i])==i_ident+1)
		if(compareStr(keyword[i],Id)){
			printf(" %s ",keyword[i]);
			return true;
		}; 
	};
	int j;
	printf(" %s(",keyword[1]);
	for(j=0;j<i_ident+1;j++)
		printf("%c",Id[j]);
	printf(") ");
	return false;
//	strncat(s,Id,i_ident+1);
//	printf(" %s(%s) ",keyword[1],s);

}

void reset(){
	i_ident = -1;
	index_ch = -1;
}
