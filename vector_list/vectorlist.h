#ifndef _VECTORLIST_H
#define _VECTORLIST_H

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIST_SIZE 100000000;

typedef char DataType;

// Classe
struct VectorList {
	struct VectorList_Priv *priv;
	struct VectorList_Meths *meths;
	int tam_atual;
	int tam_max;
	int cursor;
	DataType *dados;
};

typedef struct VectorList VectorList;

// Operadoress
struct VectorList_Meths {
	int (*VectorList_copy)(VectorList *const target, const VectorList *const source);
	int (*VectorList_insert)(VectorList *const list, const DataType newDataItem);
	int (*VectorList_remove)(VectorList *const list);
	int (*VectorList_replace)(VectorList *const list, const DataType newDataItem);
	void (*VectorList_clear)(VectorList *const list);
	bool (*VectorList_isEmpty)(VectorList *const list);
	bool (*VectorList_isFull)(VectorList *const list);
	void (*VectorList_showStructure)(VectorList *const list);
	int (*VectorList_gotoBegin)(VectorList *const list);
	int (*VectorList_gotoEnd)(VectorList *const list);
	bool (*VectorList_gotoNext)(VectorList *const list);
	bool (*VectorList_gotoPrior)(VectorList *const list);
	DataType (*VectorList_getFromCursor)(VectorList *const list);
	int (*VectorList_getCursor)(VectorList *const list);
};

// Construtor
VectorList *VectorList_new(int maxNumber);

// Destrutor
void VectorList_del(VectorList *list);

#endif