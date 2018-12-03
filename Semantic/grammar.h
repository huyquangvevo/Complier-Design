#ifndef _GRAMMAR_H_
#define _GRAMMAR_H_
#include"Tab.h"
#include"scanner.h"
#include"error.h"
#include "semantics.h"

bool isProcedure = false;


/*
bool isPro(){
	return isProcedure;
}
*/
void compileDeclareVariable(){
	if(Token == IDENT){
		if(checkIdent(Id))
			enter(Id,OBJ_VARIABLE);	
		else 
			getError(CONFLICT_NAME);
		
		Token = getToken();
		
		if(Token == LBRACK){
			Token = getToken();
			if(Token!=NUMBER)
				getError(MISSING_NUMBER_ARRAY);
			if(Token==RBRACK){
				Token = getToken();
				enter(Id,OBJ_ARRAY);
			}
			else
				getError(MISSING_RBRACK);
		} 
	} else {
		getError(MISSING_VARIABLE_NAME);
	}
}

void compileDeclareConst(){
	if(Token==IDENT){
		if(checkIdent(Id))
			enter(Id,OBJ_CONSTANT);
		else
			getError(CONFLICT_NAME);
		
		Token = getToken();
		if(Token==EQU){
			Token = getToken();
			
			if(Token==NUMBER){
				Token = getToken();
				//enter(Id,OBJ_CONSTANT);
			} else {
				getError(MISSING_VALUE);
			}
		} else {
			getError(MISSING_VALUE_CONST);
		}	
	} else {
		getError(MISSING_VARIABLE_CONST);
	}
}

void compileDeclareProcedure(){
	if(Token==IDENT){
		if(checkIdent(Id))
			enter(Id,OBJ_PROCEDURE);
		else 
			getError(CONFLICT_NAME);
		
		Token = getToken();
		
		if(Token==LPARENT){
			Token = getToken();
			do{
				int para = 1;
				if(Token==VAR){
					Token = getToken();
					para = 0;
				};

				if(Token == IDENT){
					if(checkIdent(Id)){
						if(para=1)
							getError(MISSING_DECLARE_VAR);
							//enter(Id,OBJ_REFER_VAR);
						else
							enter(Id,OBJ_PARA_VAR);
						Token = getToken();
					} else {
						if(para=1)
							Token = getToken();
						else
							getError(CONFLICT_NAME);
					}
				} else {
					getError(MISSING_VARIABLE);
				}
				
			}while(Token==SEMICOLON);
			
			if(Token==RPARENT){
				Token = getToken();
			} else {
				getError(MISSING_RPARENT);
			}		
		};
		checkSemicolon();
		isProcedure = true;
		compileBlock();	
	} else {
		getError(MISSING_PROCEDURE_NAME);
	}
}

void compileCallProcedure(){
	if(Token==IDENT){
		if(checkIdent(Id)){
		//	enter(Id,OBJ_PROCEDURE);
			Token = getToken();
			if(Token==LBRACK){
				Token = getToken();
				expression();
				while(Token==COMMA){
					expression();
				}
				if(Token==RBRACK){
					Token = getToken();
				} else {
					getError(MISSING_RBRACK);
				}
			}
		} else {
			getError(UNDECLARED_PROCEDURE);
		};
		
	} else {
		getError(MISSING_PROCEDURE_NAME);
	}
}

void compileStatement(){
	if(Token==IDENT){
		int p = location(Id);
		if(p==0)
			getError(UNDECLARED_NAME);
	
		Token = getToken();
		
		if(Token == LPARENT){
			if(getKind(p)!=OBJ_ARRAY)
				getError(NOT_IS_ARRAY);
			
			Token = getToken();
			expression();
			if(Token == RPARENT){
				Token = getToken();
				if(Token== ASSIGN){
					Token = getToken();
					expression();
				} else {
					getError(MISSING_ASSIGN);
				}
			} else {
				getError(MISSING_RPARENT);
			}
			
		}
		else if(Token == ASSIGN){
			if(getKind(p)!=OBJ_VARIABLE)
				getError(EXPECT_VARIABLE);
			
			Token = getToken();
			expression();
			
		} else {
			getError(MISSING_ASSIGN);
		}	
	} else {
		statement();
	};
	if(Token == SEMICOLON){
		//checkSemicolon();
		Token = getToken();
		compileStatement();
	};
}

void checkSemicolon(){
	if(Token == SEMICOLON){
			Token = getToken();
		//	compileBlock();
		} else {
			getError(MISSING_SEMICOLON);
		};
}


void compileBlock(){
	//Token = getToken();
	if(Token==VAR){
		Token = getToken();
		compileDeclareVariable();
		while(Token==COMMA){
			Token = getToken();
			compileDeclareVariable();
		}
		checkSemicolon();
		if(isProcedure)
			isProcedure = false;
		compileBlock();
	} else if(Token == CONST){
		Token = getToken();
		compileDeclareConst();
		while(Token==COMMA){
			Token = getToken();
			compileDeclareConst();
		};
		checkSemicolon();
		if(isProcedure)
			isProcedure = false;
		compileBlock();
	} else if(Token==PROCEDURE){
		Token = getToken();
		compileDeclareProcedure();
		if(isProcedure)
				getError(MISSING_MAIN);
	} else if(Token == CALL){
		Token = getToken();
		compileCallProcedure();
	} else if(Token==BEGIN){
	//	do{	
		//	isProcedure = false;
			Token = getToken();
			compileStatement();
	//	} while(Token == SEMICOLON);
		if(Token == END){		
			Token = getToken();
			if(Token == SEMICOLON){
				Token = getToken();
				if(isProcedure)
					isProcedure = false;
				compileBlock();
			} else if(isProcedure){
				getError(MISSING_SEMICOLON);
			};
			
		} else {
			getError(MISSING_END);
		}
	}
	
}

#endif


