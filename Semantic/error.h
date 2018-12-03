#ifndef _ERROR_H_
#define _ERROR_H_

//#include<string.h>


#define ERROR_COUNT 30


typedef enum ErrorType{
	NO = 0,
	MISSING_ASSIGN,
	MISSING_RPARENT,
	MISSING_RBRACK,
	MISSING_NAME_FUNCTION,
	CONDITION_SYNTAX_ERROR,
	MISSING_END, 
	MISSING_SEMICOLON,
	MISSING_DO,
	MISSING_THEN,
//	MISSING_IDENT,
	MISSING_TO,
	MISSING_DOT,
	MISSING_NAME_PROGRAM,
	MISSING_PROGRAM,
	MISSING_EQL,
	ERROR_VALUE_INT,
	ERROR_CONST,
	ERROR_VAR,
	MISSING_NUMBER,
	MISSING_IDENT,
	MISSING_EXPRESSION,
	// Loi grammar,
	CONFLICT_NAME,
	MISSING_NUMBER_ARRAY,
	MISSING_VARIABLE_NAME,
	MISSING_VALUE,
	MISSING_PROCEDURE_NAME,
	MISSING_VARIABLE_CONST,
	MISSING_VARIABLE,
	MISSING_DECLARE_VAR,
	UNDECLARED_PROCEDURE,
	UNDECLARED_NAME,
	EXPECT_VARIABLE,
	NOT_IS_ARRAY,
	UNDECLARED_VARIABLE,
	MISSING_VALUE_CONST,
	MISSING_MAIN,
	
} ErrorType;

const char* errors[] = {
	"NONE",
	"Thieu toan tu gan",
	"Thieu dau dong ngoac )",
	"Thieu dau dong ngoac ]",
	"Thieu ten thu tuc/ham",
	"Dieu kien loi cu phap",
	"Thieu tu khoa End",
	"Thieu dau ;",
	"Loi vong lap, thieu DO",
	"Loi cau lenh IF, thieu THEN",
//	"Thieu dinh danh vong lap FOR",
	"Loi vong lap FOR, thieu TO",
	"Thieu dau .",
	"Thieu ten chuong trinh",
	"Thieu tu khoa program",
	"Thieu dau = ",
	"Khong phai so nguyen",
	"Loi hang so",
	"Loi khai bao bien",
	"Loi khai bao mang",
	"Thieu dinh danh",
	"Thieu bieu thuc",
	// Loi grammar 
	"Trung ten",
	"Thieu so phan tu mang",
	"Thieu ten bien",
	"Thieu gia tri bien",
	"Thieu ten thu tuc",
	"Thieu bien hang",
	"Thieu bien",
	"Chua dinh danh tham tri",
	"Chua dinh nghia ham",
	"Ten chua khai bao",
	"expected variable",
	"Khong phai la bien Array",
	"Bien chua duoc khai bao",
	"Chua gan gia tri cho hang",
	"Thieu main chuong trinh",
};
/*
void getError(ErrorType ET){
	printf("\n\n%s\n\n",errors[ET]);
}
*/
#endif
