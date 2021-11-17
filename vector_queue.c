#include "vector_queue.h"

int queue_copy(Queue *const target, const Queue *const source);
int queue_enqueue(Queue *const queue, const DataType newDataItem);
DataType queue_dequeue(Queue *const queue);
DataType queue_get(Queue *const queue);
void queue_clear(Queue *const queue);
bool queue_isEmpty(Queue *const queue);
bool queue_isFull(Queue *const queue);
void queue_showStructure(Queue *const queue);
int queue_gotoBegin(Queue *const queue);
int queue_gotoEnd(Queue *const queue);
bool queue_gotoNext(Queue *const queue);
bool queue_gotoPrior(Queue *const queue);
DataType queue_getFromCursor(Queue *const queue);
int queue_getCursor(Queue *const queue);
DataType queue_remove(Queue *const list);

struct Queue_Meths meths = {
    .queue_copy          = queue_copy,
    .queue_enqueue       = queue_enqueue,
    .queue_dequeue       = queue_dequeue,
    .queue_get           = queue_get,
    .queue_clear         = queue_clear,
    .queue_isEmpty       = queue_isEmpty,
    .queue_isFull        = queue_isFull,
    .queue_showStructure = queue_showStructure,
    .queue_gotoBegin     = queue_gotoBegin,
    .queue_gotoNext      = queue_gotoNext,
    .queue_gotoEnd       = queue_gotoEnd,
    .queue_gotoPrior     = queue_gotoPrior,
    .queue_getFromCursor = queue_getFromCursor,
    .queue_getCursor     = queue_getCursor,
    .queue_remove        = queue_remove,
};

/*
	Construtor -> Cria uma fila vazia. 
	Aloca memória suficiente para que a fila contenha maxNumber itens se necessário.
*/
Queue *queue_new(int maxNumber) {
	int maximo = MAX_QUEUE_SIZE;
	if (maxNumber > 0 && maxNumber < maximo) {
		Queue *queue;
		queue            = malloc(sizeof(Queue));
		queue->tam_atual = 0;
		queue->tam_max   = maxNumber;
		queue->cursor    = -1;
		queue->dados     = (DataType *)calloc(maxNumber, sizeof(DataType));
		queue->meths     = &meths;
	}
}

/*	
	Destrutor
*/
void queue_delete(Queue *queue) {
	assert(queue);
	if (!queue_isEmpty(queue)) {
		free(queue->dados);
		free(queue);
		queue->tam_atual = 0;
		queue->cursor    = -1;
	}
}

/*
	Insere os elementos de source em target
	target e source devem existir e não podem ser nulos
	Target é reescrito
	Sãp copiados os valores até satisfazer o tamanho
	Em caso de erro retorna -1
*/
int queue_copy(Queue *const target, const Queue *const source) {
	if (target->tam_max > 0 && source->tam_max > 0) {
		queue_clear(target);
		for (int i = 0; i < source->tam_atual; i++) {
			queue_enqueue(target, source->dados[i]);
		}
		printf("%i itens copiados\n", target->tam_atual);
	} else {
		return -1;
	}
}

/*
 	Insere newDataItem no fim da fila. Retorna o novo número de elementos na fila.
*/
int queue_enqueue(Queue *const queue, const DataType newDataItem) {
	assert(queue);
	if (!queue_isFull(queue)) {
		queue->tam_atual++;
		queue->cursor++;
		queue->dados[queue->cursor] = ("%s", newDataItem);
		return queue->tam_atual;
	} else {
		return -1;
	}
}

/*
	Retira o item de dado mais antigo e o retorna.
*/
DataType queue_dequeue(Queue *const queue) {
	assert(queue);
	DataType removido = queue->dados[0];
	if (!queue_isEmpty(queue)) {
		if (queue->tam_atual == 1) {
			queue->dados[0] = '\0';
			queue->cursor   = -1;
		} else {
			for (int i = 0; i <= queue->tam_atual - 1; i++) {
				queue->dados[i] = queue->dados[i + 1];
			}
			queue->cursor--;
		}
		queue->tam_atual--;
		return removido;
	} else {
		return -1;
	}
}

/*
	Retorna o item de dado mais antigo, mas não o remove da fila
*/
DataType queue_get(Queue *const queue) {
	assert(queue);
	if (!queue_isEmpty(queue)) {
		DataType item_antigo = queue->dados[0];
		return item_antigo;
	} else {
		return -1;
	}
}

/*
	Remove todos os itens de dados da fila
*/
void queue_clear(Queue *const queue) {
	assert(queue);
	for (int i = 0; i <= (queue->tam_atual - 1); i++) {
		queue->dados[i] = '\0';
	}
	queue->cursor    = -1;
	queue->tam_atual = 0;
}

/*
	Verifica se a fila tá vazia
	Retorna true se a fila está vazia, caso contrário, retorna false
*/
bool queue_isEmpty(Queue *const queue) {
	assert(queue);
	if (queue->tam_atual == 0) {
		return 1;
	} else
		return 0;
}

/*
	Retorna true se a fila está cheia, caso contrário, retorna false
*/
bool queue_isFull(Queue *const queue) {
	assert(queue);
	if (queue->tam_atual == queue->tam_max) {
		return 1;
	} else
		return 0;
}

/*
    Mostra todos os dados da fila.
*/
void queue_showStructure(Queue *const queue) {
	assert(queue);
	printf("Cursor: %i\n", queue->cursor);
	printf("Tamanho: %i\n", queue->tam_atual);
	printf("Cheio: %i\n", queue->meths->queue_isFull(queue));
	printf("Vazio: %i\n", queue->meths->queue_isEmpty(queue));
	printf("%s", "fila: [");
	for (int i = 0; i <= (queue->tam_atual - 1); i++) {
		if (i == (queue->tam_atual - 1)) {
			printf("%i", queue->dados[i]);
		} else {
			printf("%i ", queue->dados[i]);
		}
	}
	printf("%s", "]\n");
}

/*
    Move o cursor para o primeiro item de dado e retorna o valor 0. Seestiver vazia retorna -1.
*/
int queue_gotoBegin(Queue *const queue) {
	queue->cursor = 0;
	if (queue_isEmpty(queue)) {
		return -1;
	} else
		return 0;
}

/*
	Se a fila não estiver vazia, move o cursor para o último item de dado e retorna este índice. Se
	estiver vazia retorna -1.
*/
int queue_gotoEnd(Queue *const queue) {
	if (!queue_isEmpty(queue)) {
		queue->cursor = queue->tam_atual - 1;
		return 0;
	} else
		return -1;
}

/*
	Se o cursor não está no fim da fila, move-o para o próximo item e retorna true. Caso contrário,
	retorna false
*/
bool queue_gotoNext(Queue *const queue) {
	assert(queue);
	if (queue->cursor < queue->tam_atual) {
		queue->cursor++;
		return 1;
	} else {
		return 0;
	}
}

/*
	Se o cursor não está no início da fila, move-o para o item anterior e retorna true. Caso contrário,
	retorna false.
*/
bool queue_gotoPrior(Queue *const queue) {
	assert(queue);
	if (queue->cursor > 0) {
		queue->cursor--;
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
	if (queue->tam_atual != 0) {
		return queue->dados[queue->cursor];
	}
}

/*
	Retorna o valor do item de dado apontado atualmente pelo cursor.
*/
int queue_getCursor(Queue *const queue) {
	assert(queue);
	return queue->cursor;
}

/*
	Remove o item indicado pelo cursor
*/
DataType queue_remove(Queue *const queue) {
	assert(queue);
	DataType removido = queue->dados[0];
	if (!queue_isEmpty(queue)) {
		if (queue->tam_atual == 1) {
			queue->dados[0] = '\0';
			queue->cursor   = -1;
		} else {
			for (int i = queue->cursor; i <= queue->tam_atual - 1; i++) {
				queue->dados[i] = queue->dados[i + 1];
			}
			queue->cursor--;
		}
		queue->tam_atual--;
		return removido;
	} else {
		return -1;
	}
}
