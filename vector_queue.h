#ifndef _Queue_H
#define _Queue_H

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Chamada de métodos por parâmetros
#define METH(method, obj, ...) obj->meths->method(obj, ##__VA_ARGS__)

#define MAX_QUEUE_SIZE 100000000;

typedef int DataType;

// Classe
typedef struct Queue {
	struct Queue_Priv *priv;
	struct Queue_Meths *meths;
	int tam_atual;
	int tam_max;
	int cursor;
	DataType *dados;
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
	int (*queue_gotoBegin)(Queue *const queue);
	int (*queue_gotoEnd)(Queue *const queue);
	bool (*queue_gotoNext)(Queue *const queue);
	bool (*queue_gotoPrior)(Queue *const queue);
	DataType (*queue_getFromCursor)(Queue *const queue);
	int (*queue_getCursor)(Queue *const queue);
	DataType (*queue_remove)(Queue *const list);
};

// Construtor
Queue *queue_new(int maxNumber);

// Destrutor
void queue_delete(Queue *queue);

#endif