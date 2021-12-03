#include "node_queue.h"

int queue_copy(Queue *const target, const Queue *const source);
int queue_enqueue(Queue *const queue, const DataType newDataItem);
DataType queue_dequeue(Queue *const queue);
DataType queue_get(Queue *const queue);
void queue_clear(Queue *const queue);
bool queue_isEmpty(Queue *const queue);
bool queue_isFull(Queue *const queue);
void queue_showStructure(Queue *const queue);
int queue_getCursor(Queue *queue);
DataType queue_getFromCursor(Queue *const queue);
bool queue_gotoNext(Queue *const queue);
int queue_gotoEnd(Queue *const queue);
int queue_gotoBegin(Queue *const queue);
bool queue_gotoPrior(Queue *queue);
int queue_replace(Queue *const queue, const DataType newDataItem);

struct Queue_Meths meths = {
    .queue_copy          = queue_copy,
    .queue_enqueue       = queue_enqueue,
    .queue_dequeue       = queue_dequeue,
    .queue_get           = queue_get,
    .queue_clear         = queue_clear,
    .queue_isEmpty       = queue_isEmpty,
    .queue_isFull        = queue_isFull,
    .queue_showStructure = queue_showStructure,
};

Queue *queue_new(int maxNumber) {
	int maximo = MAX_QUEUE_SIZE;
	if (maxNumber > 0 && maxNumber < maximo) {
		Queue *queue     = (Queue *)malloc(sizeof(Queue));
		queue->tam_atual = 0;
		queue->tam_max   = maxNumber;
		queue->cursor    = NULL;
		queue->meths     = &meths;
	}
}

ListNode *ListNode_new(DataType nodeData, ListNode *nextPtr) {
	ListNode *node = (ListNode *)malloc(sizeof(node));
	node->nodeData = nodeData;
	node->nextPtr  = NULL;
	return node;
}

void queque_delete(Queue *queue) {
	assert(queue);
	ListNode *temp = queue->top;
	ListNode *nPtr;
	for (int i = 0; i < queue->tam_atual; i++) {
		nPtr = (struct ListNode *)temp->nextPtr;
		free(temp);
		temp = nPtr;
	}
}

/*
	Para inserir um item na queue
*/
int queue_enqueue(Queue *const queue, const DataType newDataItem) {
	assert(queue);
	ListNode *node = ListNode_new(newDataItem, NULL);
	if (!queue_isFull(queue)) {
		if (queue->tam_atual == 0) {
			queue->top    = (struct ListNode *)node;
			node->nextPtr = NULL;
			queue->cursor = node;
		} else if (queue->cursor->nextPtr == NULL) {
			queue->cursor->nextPtr = node;
			node->nextPtr          = NULL;
			queue->cursor          = node;
		}
		queue->tam_atual++;
	}
	return 0;
}

/*
	Insere os elementos de source em target
	target e source devem existir e não podem ser nulos
	Target é reescrito
	São copiados os valores até satisfazer o tamanho
	Em caso de erro retorna -1
*/
int queue_copy(Queue *const target, const Queue *const source) {
	assert(target);
	assert(source);
	if (target->tam_max > 0 && source->tam_max > 0) {
		queue_clear(target);
		ListNode *aux = source->top;
		int i;
		for (i = 0; i < source->tam_atual; i++) {
			queue_enqueue(target, aux->nodeData);
			queue_gotoNext(target);
			aux = (struct ListNode *)aux->nextPtr;
		}
		printf("%i itens copiados\n", target->tam_atual);
		return 0;
	} else {
		return -1;
	}
}

/*
	A queue não pode estar vazia
	Remove um item da lista
	Retorna o item removido
	Retorna -1 em caso de erro
*/
DataType queue_dequeue(Queue *const queue) {
	assert(queue);
	if (!queue_isEmpty(queue)) {
		DataType removido = queue->cursor->nodeData;
		if (queue->tam_atual == 1) {
			queue->top    = NULL;
			queue->cursor = NULL;
		} else {
			queue->cursor = queue->top;
			Queue *aux    = (struct Queue *)queue->cursor->nextPtr;
			free(queue->top);
			queue->top    = (struct ListNode *)aux;
			queue->cursor = (struct ListNode *)aux;
		}
		queue->tam_atual--;
		return removido;
	} else {
		return -1;
	}
}

DataType queue_get(Queue *const queue) {
	queue->cursor = queue->top;
	return queue->cursor->nodeData;
}

/*
	A queue não pode estar vazia
	Substitui o item de dado marcado pelo cursor por newDataItem.
	Retorna 1 em caso de sucesso e -1 se tiver erro
*/
int queue_replace(Queue *const queue, const DataType newDataItem) {
	assert(queue);
	if (!queue_isEmpty(queue)) {
		queue->cursor->nodeData = newDataItem;
		return 1;
	} else {
		printf("Erro na substituição \n");
		return -1;
	}
}

/*
	Remove todos os itens de dados da queue
*/
void queue_clear(Queue *const queue) {
	assert(queue);
	queue->top       = NULL;
	queue->cursor    = NULL;
	queue->tam_atual = 0;
}

/*
	Verifica se a queue tá vazia
	Returna true se a queue está vazia, caso contrário, retorna false
*/
bool queue_isEmpty(Queue *const queue) {
	assert(queue);
	if (queue->tam_atual == 0) {
		return 1;
	} else
		return 0;
}

/*
	Returna true se a queue está cheia, caso contrário, retorna false
*/
bool queue_isFull(Queue *const queue) {
	assert(queue);
	if (queue->tam_atual == queue->tam_max) {
		return 1;
	} else
		return 0;
}

/*
    Mostra todos os daddos da queue.
*/
void queue_showStructure(Queue *const queue) {
	assert(queue);
	printf("Cursor: %i\n", queue_getCursor(queue));
	printf("Tamanho: %i\n", queue->tam_atual);
	printf("Cheio: %i\n", queue_isFull(queue));
	printf("Vazio: %i\n", queue_isEmpty(queue));
	printf("queue: [");
	ListNode *aux = queue->top;
	while (aux) {
		printf("%c ", aux->nodeData);
		aux = (struct ListNode *)aux->nextPtr;
	}
	printf("]\n");
}

/*
    move o cursor para o primeiro item de dado e retorna o valor 0. Se estiver vazia retorna -1.
*/
int queue_gotoBegin(Queue *const queue) {
	assert(queue);
	if (queue_isEmpty(queue)) {
		queue->cursor = queue->top;
		return -1;
	} else
		return 0;
}

/*
Se a queue não estiver vazia, move o cursor para o último item de dado e retorna este índice. Se
estiver vazia retorna -1.
*/
int queue_gotoEnd(Queue *const queue) {
	assert(queue);
	if (!queue_isEmpty(queue)) {
		while (queue->cursor->nextPtr) {
			queue->cursor = (struct ListNode *)queue->cursor->nextPtr;
		}
		return 0;
	} else
		return -1;
}

/*
Se existe um proximo cursor. Nove-o para o próximo item e retorna true. Caso contrário,
retorna false
*/
bool queue_gotoNext(Queue *const queue) {
	assert(queue);
	if (queue->cursor->nextPtr) {
		queue->cursor = (struct ListNode *)queue->cursor->nextPtr;
		return 1;
	} else {
		return 0;
	}
}

/*
Se o cursor não está no início da queue, move-o para o item anterior e retorna true. Caso contrário,
retorna false.
*/

bool queue_gotoPrior(Queue *queue) {
	assert(queue);
	ListNode *aux = queue->top;
	if (queue->cursor != queue->top) {
		while (aux->nextPtr != queue->cursor) {
			aux = (struct ListNode *)aux->nextPtr;
		}
		queue->cursor = aux;
		return 1;
	} else {
		return 0;
	}
}

/*
Retorna o valor do item de dado apontado atualmente pelo cursor.
*/
DataType queue_getFromCursor(Queue *const queue) {
	assert(queue);
	ListNode *aux = queue->top;
	if (queue->cursor != queue->top) {
		while (aux->nextPtr != queue->cursor) {
			aux = (struct ListNode *)aux->nextPtr;
		}
		queue->cursor = aux;
		return 1;
	} else {
		return 0;
	}
}

/*
Retorna a posição do cursor atual.
*/
int queue_getCursor(Queue *queue) {
	assert(queue);
	ListNode *aux = queue->top;

	int i = 0;
	while (queue->cursor != aux) {
		aux = (struct ListNode *)aux->nextPtr;
		i++;
	}
	return i;
}
