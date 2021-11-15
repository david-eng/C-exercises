#ifndef _LISTNODE_H
#define _LISTNODE_H

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 100000000;

//Chamada de métodos por parâmetros
#define METH(method, obj, ...) obj->meths->method(obj, ##__VA_ARGS__)

typedef char DataType;

// Classe

typedef struct ListNode {
	struct queue *nextPtr;
	DataType nodeData;
} ListNode;

typedef struct Queue {
	struct Queue_Meths *meths;
	ListNode *top;
	ListNode *cursor;
	int tam_atual;
	int tam_max;

} Queue;

// Métodos
struct Queue_Meths {
	int (*queue_copy)(Queue *const target, const Queue *const source);
	int (*queue_enqueue)(Queue *const queue, const DataType newDataItem);
	DataType (*queue_dequeue)(Queue *const queue);
	DataType (*queue_get)(Queue *const queue);
	void (*queue_clear)(Queue *const queue);
	bool (*queue_isEmpty)(Queue *const queue);
	bool (*queue_isFull)(Queue *const queue);
	void (*queue_showStructure)(Queue *const queue);
};

// Construtor
Queue *queue_new(int maxNumber);

ListNode *ListNode_new(DataType nodeData, ListNode *nextPtr);

// Destrutor
void queque_delete(Queue *list);

#endif