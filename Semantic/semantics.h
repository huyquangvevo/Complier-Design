#ifndef _SEMANTICS_H_
#define _SEMANTICS_H_
#include "scanner.h"
#include "error.h"
//#include "grammar.h"

void compileStatement();
void checkSemicolon();
void compileBlock();
void compileCallProcedure();



void getError(ErrorType ET);
void expression();
void block();
void factor();
void term();
void program();
void condition();
void statement();

void printToken(){
	
		printf("\n%s\n",keyword[Token]);
		

}



void getError(ErrorType ET){
	printf("\n\n________________ERROR________________\n");
	printf("\n\n%s, \n \t tai dong %d\n",errors[ET],countLine);

	if(ET==UNDECLARED_VARIABLE||ET==UNDECLARED_NAME){		
		printf("Bien: ");
		printIdent();
	//	int i=0;
	//	for(i=0;i<=i_ident;i++)
	//		printf("%c",Id[i]);
	} else if(ET==CONFLICT_NAME){
		printf("Trung ten: ");
		printIdent();
	} 
	exit(0);
	
};


void expression(){
	
	if(Token == PLUS || Token == MINUS)
		Token = getToken();
	term();
	while(Token==PLUS || Token == MINUS){
		Token = getToken();
		term();
	}

};


void factor(){
	
	if(Token == IDENT) {
		
		if(!checkIdent(Id)){
			Token = getToken();
		} else {
			getError(UNDECLARED_VARIABLE);
		}
		
	//	Token = getToken();
		if(Token == LBRACK) {
			Token = getToken();
			expression();
			//Token = getToken();
			if(Token == RBRACK) {
				Token = getToken();
			} else {
				getError(MISSING_RBRACK);
			}
		}
	} else if(Token == NUMBER) {
		Token = getToken();
	} else if(Token == LPARENT) {
		Token = getToken();
		expression();
		if(Token == RPARENT) {
			Token = getToken();
		} else {
			getError(MISSING_RPARENT);
		};
	}; // Loi bieu thuc 
	
};


void term(){
	factor();
	while(Token == TIMES || Token == SLASH || Token == PERCENT){
		Token = getToken();
		factor();
	}
};


void condition(){
	if(Token == ODD){
		Token = getToken();
		expression();
	} else {	
		expression();
		if(Token == EQU || Token == NEQ || Token == LSS|| 
		Token == LEQ || Token == GRT || Token == GEQ) {
			Token = getToken();
			expression();
		} else {
			getError(CONDITION_SYNTAX_ERROR);
		}
	}
};



void statement(){
	
	if(Token == IDENT) {
	/*	Token = getToken();
		if(Token == LBRACK) {
			Token = getToken();
			expression();
			if(Token == RBRACK){
				Token = getToken();
			} else {
				getError(MISSING_RBRACK);
			}
		};
		if(Token == ASSIGN){
			Token = getToken();
			expression();
		} else {
			getError(MISSING_ASSIGN);
		}
	*/ 
		compileStatement();
	} else if(Token == CALL){
	/*	Token = getToken();
		if(Token == IDENT){
			Token = getToken();			
			if(Token == LPARENT){
				Token = getToken();
				expression();
				while(Token==COMMA){
					Token = getToken();
					expression();
				}
				if(Token = RPARENT)
					Token = getToken(); 
				else 
					getError(MISSING_RPARENT);
			};
		} else 
			getError(MISSING_NAME_FUNCTION);
	*/
		Token = getToken();
		compileCallProcedure();
	} else if (Token == BEGIN) {
		int tx = row_tab;
		do {
		Token = getToken();
		statement();
		} while(Token == SEMICOLON);
		if(Token==END) {
			row_tab = tx;
			Token = getToken();
		}
		else 
			getError(MISSING_END);
	
	//	compileBlock();
	} else if (Token == IF){
		Token = getToken();
		condition();
		if(Token == THEN){
			Token = getToken();
			statement();
			if(Token == ELSE){
				Token = getToken();	
				statement();
			};
		} else {
			getError(MISSING_THEN);
		}
	} else if(Token == WHILE){
		Token = getToken();
		condition();
		if(Token == DO) {
			Token = getToken();
			statement();
		} else {
			getError(MISSING_DO);
		};
		
	} else if (Token == FOR){
		Token = getToken();
		if(Token == IDENT){
			
			if(!checkIdent(Id))
					getError(UNDECLARED_VARIABLE);
								
			Token = getToken();
			if(Token == ASSIGN){
				Token = getToken();
				expression();
				if(Token == TO) {
					Token = getToken();
					if(Token == DO) 
						getError(MISSING_EXPRESSION);
					expression();
					
					if(Token == DO) {
						Token = getToken();
						statement();
					
					} else {
						getError(MISSING_DO);
					}
				} else {
					getError(MISSING_TO);
				}
			} else {
				getError(MISSING_ASSIGN);
			};
			
		} else {
			getError(MISSING_IDENT);
		};
	} else if(Token == VAR){
		Token = getToken();
		compileDeclareVariable();
		statement();
	}

};


void block(){
	if(Token == CONST) {
		do{
			Token = getToken();
			if(Token == IDENT){
				Token = getToken();
					if(Token == EQU){
						Token = getToken();
						if(Token == NUMBER){
							Token = getToken();
						} else {
							getError(ERROR_VALUE_INT);
						}
					} else {
						getError(MISSING_EQL);
					}
				
			} else {
				getError(ERROR_CONST);
			}
		} while (Token == COMMA);
		
			if(Token == SEMICOLON){
				Token = getToken();
				block();
			} else {
				getError(MISSING_SEMICOLON);
			}
		
		
	} else if (Token == VAR){
		do{
			Token = getToken();
			if(Token == IDENT) {
				Token = getToken();
				if(Token == LBRACK){
					Token = getToken();
					if(Token == NUMBER){
						Token = getToken();
						if(Token == RBRACK){
							Token = getToken();
						} else {
							getError(MISSING_RBRACK);
						}
					} else {
						getError(MISSING_NUMBER);
					};
				};
				
			} else {
				getError(ERROR_VAR);
			}
		} while (Token == COMMA);
		
			if(Token == SEMICOLON){
				Token = getToken();
				block();
			} else {
				getError(MISSING_SEMICOLON);
			}
		
	} else if (Token == PROCEDURE){
		Token = getToken();
		if (Token == IDENT){
			Token = getToken();
			if(Token == LPARENT) {

					Token = getToken();
					if(Token == VAR)
						Token = getToken();
					if(Token == IDENT)
						Token = getToken();
					else 
						getError(MISSING_DECLARE_VAR);

				while(Token == SEMICOLON){ 
					Token = getToken();
					if(Token == VAR)
						Token = getToken();
					if(Token == IDENT)
						Token = getToken();
					else 
						getError(MISSING_IDENT);
				};
				if(Token == RPARENT)
					Token = getToken();
				else 
					getError(MISSING_RPARENT);
			}
			
			if(Token == SEMICOLON){
				Token = getToken();
				block();
			} else {
				getError(MISSING_SEMICOLON);
			}
			
		} else {
			getError(MISSING_IDENT);
		}
	} else if(Token == BEGIN){
		do{	
			Token = getToken();
			statement();
		} while(Token == SEMICOLON);
		if(Token == END){		
			Token = getToken();
		if(Token == SEMICOLON){
				Token = getToken();
				block();
			}
		} else {
			getError(MISSING_END);
		}
	} 
};



void program(){
	
	if(Token == PROGRAM) {
		Token = getToken();
		if(Token == IDENT){
			Token = getToken();
			if(Token == SEMICOLON){
				Token = getToken();
			//	block();
				compileBlock();
				//if(isProcedure)
				//	getError(MISSING_MAIN);
				if(Token == PERIOD){
					printf("\n\n ----- Successfull! -----");
				} else {
					getError(MISSING_DOT);
				}
			} else {
				getError(MISSING_SEMICOLON);
			}
		} else {
			getError(MISSING_NAME_PROGRAM);
		} 
	} else {
			getError(MISSING_PROGRAM);
	}
	
};

#endif
