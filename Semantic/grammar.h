#ifndef _GRAMMAR_H_
#define _GRAMMAR_H_
#include"Tab.h"
#include"scanner.h"
#include"error.h"
#include "semantics.h"

bool isProcedure = false;
int countVar = 0;


/*
bool isPro(){

	return isProcedure;
}
*/

void printTab(){
	int i=0;
			printf("\nTable:\n");
			for(i=0;i<row_tab;i++){
				printf("%c\n",Table[i].id[0]);
				if(Table[i].type == OBJ_PROCEDURE)
					printf("Procedure\n");
			}
}

void compileDeclareVariable(){
	if(Token == IDENT){
		if(!checkIdent(Id)){
			printTab();
			getError(CONFLICT_NAME);
		}
		saveToCache();

		Token = getToken();
		
		if(Token == LBRACK){
			Token = getToken();
			if(Token!=NUMBER)
			if(Token==MINUS)
				getError(EXPECT_UNSIGNED_INT);
			else
				getError(MISSING_NUMBER_ARRAY);
				
			Token = getToken();
			if(Token==RBRACK){
				Token = getToken();
		
				enter(cache,OBJ_ARRAY);
			
			}
			else
				getError(MISSING_RBRACK);
		
		} else {
			enter(cache,OBJ_VARIABLE);
		};
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
		int tx = row_tab;
		if(checkIdent(Id)){
			enter(Id,OBJ_PROCEDURE);
			//printTab();
		}
		else 
			getError(CONFLICT_NAME);
		
		saveToCache();
		
		Token = getToken();
		countVar = 0;
		if(Token==LPARENT){
			do{
				Token = getToken();
				int para = 1;
				if(Token==VAR){
					Token = getToken();
					para = 0;
				};
				
				if(Token == IDENT){
					if(checkIdent(Id)){
						if(para!=1)
							//printf("\nHuy\n");
							//getError(MISSING_DECLARE_VAR);
							enter(Id,OBJ_VARIABLE);
						//else
							//enter(Id,OBJ_PARA_VAR);
						Token = getToken();
					} else {
						if(para==1)
							Token = getToken();
						else
							getError(CONFLICT_NAME);
					}
				} else {
					getError(MISSING_VARIABLE);
				}
				countVar ++;	
			}while(Token==SEMICOLON);
			
			if(Token==RPARENT){
				Token = getToken();
			} else {
				getError(MISSING_RPARENT);
			}		
		};
		Table[location(cache)-1].other = countVar;
		checkSemicolon();
		isProcedure = true;
		//if(Token == BEGIN)
		compileBlock();	
		row_tab = tx+1;
	} else {
		getError(MISSING_PROCEDURE_NAME);
	}
}

void compileCallProcedure(){
	int cVar = 0;
	if(Token==IDENT){
		if(!checkIdent(Id)){
		//	enter(Id,OBJ_PROCEDURE);
		//	printf("location Id: %d",location(Id));
			if(getKind(location(Id))!=OBJ_PROCEDURE)
				getError(UNDECLARED_PROCEDURE);
			int numVar = Table[location(Id)-1].other;
			Token = getToken();
			if(Token==LPARENT){
				Token = getToken();
				expression();
				cVar++;
				while(Token==COMMA){
					cVar++;
					Token = getToken();
					expression();
				};
				
				if(Token==RPARENT){
					if(cVar != numVar)
						getError(UNDECLARED_PROCEDURE);
					Token = getToken();
				} else {
					getError(MISSING_RBRACK);
				}
			}
		} else {
		//	printTab();
			getError(UNDECLARED_PROCEDURE);
		};
	} else {
		getError(MISSING_PROCEDURE_NAME);
	}
}

void compileStatement(){
	if(Token==IDENT){
		int p = location(Id);
		if(p==0){
			getError(UNDECLARED_VARIABLE);
		}
			
	
		Token = getToken();
		
		if(Token == LBRACK){
			if(getKind(p)!=OBJ_ARRAY){
				getError(NOT_IS_ARRAY);
			}
			
			Token = getToken();
			expression();
			if(Token == RBRACK){
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
		//bool isPro = true;
		Token = getToken();
	//	int tx = row_tab;
		compileDeclareProcedure();
		
	//	printTab();
	//	row_tab = tx+1;
	//	if(isProcedure)
	//			getError(MISSING_MAIN);
		compileStatement();
		if(Token==END){
				Token = getToken();
				if(Token == SEMICOLON){
					Token = getToken();
				//	compileBlock();
				};
			} else {
				getError(MISSING_END);
			}
		compileBlock();
	} else if(Token == CALL){
		Token = getToken();
		compileCallProcedure();
	} else if(Token==BEGIN){

			int tx = row_tab;
			Token = getToken();
			compileStatement();
	//	} while(Token == SEMICOLON);
		if(Token == PROCEDURE){
			Token = getToken();
			isProcedure = true;
			compileDeclareProcedure();
		//	isProcedure = true;
		//	compileBlock();
		} else
		if(Token == END){
			row_tab = tx;	
		//	printTab();	
			Token = getToken();
			if(Token == SEMICOLON){
				Token = getToken();
				if(isProcedure){
				//	return;
					isProcedure = false;
					return;
				}
			//	isProcedure = true;
				compileBlock();
			} else if(isProcedure){
				//printf("\nDay\n");
				getError(MISSING_SEMICOLON);
			};
			
		} else {
			getError(MISSING_END);
		}
	}
	
}

#endif


