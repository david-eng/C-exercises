#ifndef _LISTNODE_H
#define _LISTNODE_H

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100000000;

//Chamada de métodos por parâmetros
#define METH(method, obj, ...) obj->meths->method(obj, ##__VA_ARGS__)

typedef char DataType;

// Classe

typedef struct ListNode {
	struct ListNode *nextPtr;
	DataType nodeData;
} ListNode;

typedef struct Stack {
	struct Stack_Meths *meths;
	ListNode *top;
	ListNode *cursor;
	int tam_atual;
	int tam_max;

} Stack;

// Métodos
struct Stack_Meths {
	int (*stack_copy)(Stack *const target, const Stack *const source);
	int (*stack_push)(Stack *const stack, const DataType newDataItem);
	DataType (*stack_pop)(Stack *const stack);
	DataType (*stack_get)(Stack *const stack);
	void (*stack_clear)(Stack *const stack);
	bool (*stack_isEmpty)(Stack *const stack);
	bool (*stack_isFull)(Stack *const stack);
	void (*stack_showStructure)(Stack *const stack);
};

// Construtor
Stack *stack_new(int maxNumber);

ListNode *ListNode_new(DataType nodeData, ListNode *nextPtr);

// Destrutor
void stack_delete(Stack *list);

#endif