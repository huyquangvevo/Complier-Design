#include'scanner.h'
#include'error.h'

void term(){
	factor();
	while(Token == TIMES || Token == SLASH){
		Token = getToken();
		factor();
	}
}

void expression(){
	
	if(Token == PLUS || Token == MINUS)
		Token = getToken();
	term();
	while(Token==PLUS || Token == MINUS){
		Token = getToken();
		term();
	}

}

void condition(){
	expression();
	if(Token == EQU || Token == NEQ || Token == LSS|| 
	Token == LEQ || Token == GRT || Token == GEQ) {
		Token = getToken();
		expression();
	} else {
		error(CONDITION_SYNTAX_ERROR);
	}
}

void statement(){
	
	if(Token == IDENT) {
		Token = getToken();
		if(Token == ASSIGN){
			getToken();
			expression();
		} else error(MISSING_ASSIGN);
	} else if(Token == CALL){
		Token = getToken();
		if(Token == IDENT){
			if(Token == LPARENT){
				Token = getToken();
				expression();
				while(Token==COMMA){
					Token = getToken();
					expression();
				}
				if(Token = RPARENT)
					getToken(); 
				else 
					error(MISSING_RPARENT);
			}
		} else error(MISSING_NAME_FUNCTION);
	} else if (Token == BEGIN) {
		Token = getToken();
		statement();
		while(Token == SEMICOLON){
			Token = getToken();
			statement();
		};
		if(Token==END) 
			Token = getToken();
		else 
			error(MISSING_END);
	} else if (Token == IF){
		Token = getToken();
		condition();
		if(Token == THEN){
				statement();
			if(Token == ELSE)
				statement();
/*			if(Token == SEMICOLON) {
				Token = getToken();
			} else {
				error(MISSING_SEMICOLON);
			}
*/		} else {
			error(MISSING_THEN);
		}
	} else if(Token == WHILE){
		Token = getToken();
		condition();
		if(Token == DO) {
			statement();
/*			if(Token == SEMICOLON){
				Token = getToken();
			} else {
				error(MISSING_SEMICOLON);
			}
*/		} else {
			error(MISSING_DO);
		};
	} else if (Token == FOR){
		Token = getToken();
		if(Token == IDENT){
			Token = getToken();
			if(Token == ASSIGN){
				Token = getToken();
				expression();
				if(Token == TO) {
					Token = getToken();
					expression();
					if(Token == DO) {
						Token = getToken();
						statement();
					//Missing semicolon
					} else {
						error(MISSING_DO);
					}
				} else {
					error(MISSING_TO);
				}
			} else {
				error(MISSING_ASSIGN);
			} 
			
		} else {
			error(MISSING_IDENT);
		}
	}
	
	if(Token == SEMICOLON)
		Token = getToken();
	else 
		error(MISSING_SEMICOLON);
	
	
}

void error(ErrorType ET){
	
	printf("\n\n%s\n\n",errors[ET]);
	
}


void factor(){
	
	if(Token == IDENT) {
		Token = getToken();
		if(Token == LBRACK) {
			Token = getToken();
			expression();
			if(Token == RBRACK) {
				Token = getToken();
				expression();
			} else {
				error(MISSING_RBRACK);
			}
		} else {
			expression();
		}
		
	};
	
	if(Token == NUMBER) {
		Token = getToken();
		expresssion();
	}
	
	if(Token == LPARENT) {
		Token = getToken();
		expression();
		if(Token == RPARENT) {
			Token = getToken();
			
		} else {
			error(MISSING_RPARENT);
		}
	}
		
}


void program(){
	
	if(Token == PROGRAM) {
		Token = getToken();
		if(Token == IDENT){
			Token = getToken();
			if(Token == SEMICOLON){
				Token = getToken();
				block();
				if(Token == PERIOD){
					printf("Successful!");
				} else {
					error(MISSING_DOT);
				}
			} else {
				error(MISSING_SEMILON);
			}
		} else {
			error(MISSING_NAME_PROGRAM);
		} 
	} else {
			error(MISSING_PROGRAM);
	}
	
}

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
							error(ERROR_VALUE_INT);
						}
					} else {
						error(MISSING_EQL);
					}
				
			} else {
				error(ERROR_CONST);
			}
		} while (Token == COMMA);
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
							error(MISSING_RBRACK);
						}
					} else {
						error(MISSING_NUMBER);
					};
				};
				
			} else {
				error(ERROR_VAR);
			}
		} while (Token == COMMA);
	} else if (Token == PROCEDURE){
		Token = getToken();
		if (Token == IDENT){
			Token = getToken();
			if(Token == LPARENT) {
				Token = getToken();
				do{
					if(Token == VAR)
						Token = getToken();
					if(Token == IDENT)
						Token = getToken();
					else 
						error(MISSING_IDENT);
				} while (Token == SEMICOLON);
				if(Token == RPARENT)
					Token = getToken();
				else 
					error(MISSING_RPARENT);
			}
			
			if(Token == SEMICOLON){
				Token = getToken();
				block();
			} else {
				error(MISSING_SEMICOLON);
			}
			
		} else {
			error(MISSING_IDENT_PROCEDURE);
		}
	} else if(Token == BEGIN){
		do{
			statement();
		} while(Token == SEMICOLON);
		if(Token == END){
			Token = getToken();
		} else {
			error(MISSING_END);
		}
		continue;
	}
	
	if(Token == SEMICOLON){
		Token = getToken();
	} else {
		error(MISSING_SEMICOLON);
	}
}
