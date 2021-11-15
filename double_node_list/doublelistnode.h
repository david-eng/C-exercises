#ifndef _DOUBLELISTNODE_H
#define _DOUBLELISTNODE_H

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIST_SIZE 100000000;

typedef char DataType;

// Classe

typedef struct ListNode {
	struct ListNode *nextPtr;
	struct ListNode *prevPtr;
	DataType nodeData;
} ListNode;

typedef struct LinkedList {
	struct ListNode_Meths *meths;
	ListNode *top;
	ListNode *cursor;
	int tam_atual;
	int tam_max;

} LinkedList;

// Operadoress
struct ListNode_Meths {
	int (*LinkedList_copy)(LinkedList *const target, const LinkedList *const source);
	int (*LinkedList_insert)(LinkedList *list, const DataType newDataItem);
	int (*LinkedList_remove)(LinkedList *const list);
	int (*LinkedList_replace)(LinkedList *const list, const DataType newDataItem);
	void (*LinkedList_clear)(LinkedList *const list);
	bool (*LinkedList_isEmpty)(LinkedList *const list);
	bool (*LinkedList_isFull)(LinkedList *const list);
	void (*LinkedList_showStructure)(LinkedList *const list);
	int (*LinkedList_gotoBegin)(LinkedList *const list);
	int (*LinkedList_gotoEnd)(LinkedList *const list);
	bool (*LinkedList_gotoNext)(LinkedList *const list);
	bool (*LinkedList_gotoPrior)(LinkedList *list);
	DataType (*LinkedList_getFromCursor)(LinkedList *const list);
	int (*LinkedList_getCursor)(LinkedList *const list);
};

// Construtor
LinkedList *LinkedList_new(int ignored);

ListNode *ListNode_new(DataType nodeData, ListNode *nextPtr);

// Destrutor
void ListNode_del(LinkedList *list);

#endif