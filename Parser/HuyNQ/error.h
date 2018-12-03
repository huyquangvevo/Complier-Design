#include<string.h>

#define ERROR_COUNT 30


typedef enum {
	NO_ERROR = 0,
	MISSING_ASSIGN,
	MISSING_RPARENT,
	MISSING_RBRACK,
	MISSING_NAME_FUNCTION,
	CONDITION_SYNTAX,
	MISSING_END, 
	MISSING_SEMICOLON,
	MISSING_DO,
	MISSING_THEN,
	MISSING_IDENT,
	MISSING_TO,
	MISSING_DOT,
	MISSING_NAME_PROGRAM,
	MISSING_PROGRAM,
	MISSING_EQL,
	ERROR_VALUE_INT,
	ERROR_CONST,
	ERROR_VAR,
	MISSING_NUMBER,
	MISSING_NAME_PROCEDURE,
	MISSING_NAME_CONSTANT,
	MISSING_NAME_VARIABLE,
	MISSING_NAME_PARAMETER,
	MISSING_NAME_FOR_INDEX,
	MISSING_DOES,
	MISSING_EXPRESSION,
	MISSING_STATEMENT,
	
} ErrorType;

const char* errors[] = {
	"NONE",
	"Thieu toan tu gan",
	"Thieu dau dong ngoac )",
	"Thieu dau dong ngoac ]",
	"Thieu ten thu tuc/ham",
	"Dieu kien loi",
	"Thieu tu khoa End",
	"Thieu dau ;",
	"Loi vong lap, thieu DO",
	"Loi cau lenh IF, thieu THEN",
	"Thieu ten bien",
	"Loi vong lap FOR, thieu TO",
	"Thieu dau .",
	"Thieu ten chuong trinh",
	"Thieu tu khoa PROGRAM",
	"Thieu dau = ",
	"Khong phai so nguyen",
	"Loi hang so",
	"Loi khai bao bien",
	"Loi khai bao mang",
	"Thieu dinh danh",
	"Thieu ten thu tuc",
	"Thieu ten hang so",
	"Thieu tham so",
	"Thieu tham so",
	"Thieu bien vong lap",
	"Expected expression",
	"Expected statement",
};
