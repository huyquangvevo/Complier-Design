#ifndef _TAB_H_
#define _TAB_H_

#include "scanner.h"

#define MAX_IDENT_LEN_ 10

#define MAX_OBJECT 100
int row_tab = 0;

typedef enum {
	OBJ_CONSTANT,
	OBJ_TYPE,
	OBJ_VARIABLE,
	OBJ_PROCEDURE,
	OBJ_FUNCTION,
	OBJ_ARRAY,
	OBJ_PARA_VAR,
	OBJ_REFER_VAR,
} ObjectType;

struct Object{
	char id[MAX_IDENT_LEN_];
	ObjectType type;
	int other;
//	Object(char id_[],ObjectType type_){
//		id = id_;
//		type = type_;
//	}
} ;


struct Object Table[MAX_OBJECT];

void pushBack(struct Object obj){
	Table[row_tab] = obj;
	row_tab++;
}

void enter(char Id[],ObjectType type){
	struct Object obj;
	strcpy(obj.id,Id);
	obj.type = type;
	obj.other = 0;
//	if(obj.type==OBJ_PROCEDURE)
//		obj.other = coutVar;
	pushBack(obj);
}

int location(char Id[]){
	int i;
	for(i=row_tab-1;i>=0;i--){
		bool isEqual = true;
		int j;
		for(j=0;j<=i_ident;j++)
			if(Id[j] != Table[i].id[j]){
				isEqual = false;
				break;
			}
		if(isEqual)
			return i+1;
	}
	
	return 0;
}

bool checkIdent(char Id[]){
	if(!location(Id)){
		return true;
	}
	else
		return false;
}


ObjectType getKind(int pos){
//	if(pos-1<row_tab)
		return Table[pos-1].type;
//	else
//		return NULL;
}

#endif




