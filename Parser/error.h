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
//	MISSING_IDENT,
	
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
	"Thieu dinh danh vong lap FOR",
	"Loi vong lap FOR, thieu TO",
	"Thieu dau .",
	"Thieu ten chuong trinh",
	"Thieu tu khoa program",
	"Thieu dau = ",
	"Khong phai so nguyen",
	"Loi hang so",
	"Loi khai bao bien",
	"Loi khai bao mang",
	"Thieu dinh danh"
};
