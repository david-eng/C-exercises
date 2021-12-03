#include "node_stack.h"

int stack_copy(Stack *const target, const Stack *const source);
int stack_push(Stack *const stack, const DataType newDataItem);
DataType stack_pop(Stack *const stack);
DataType stack_get(Stack *const stack);
void stack_clear(Stack *const stack);
bool stack_isEmpty(Stack *const stack);
bool stack_isFull(Stack *const stack);
void stack_showStructure(Stack *const stack);
int stack_getCursor(Stack *queue);
DataType stack_getFromCursor(Stack *const stack);
bool stack_gotoNext(Stack *const stack);
int stack_gotoEnd(Stack *const stack);
int stack_gotoBegin(Stack *const stack);
bool stack_gotoPrior(Stack *queue);
int stack_replace(Stack *const stack, const DataType newDataItem);

struct Stack_Meths meths = {
    .stack_copy          = stack_copy,
    .stack_push          = stack_push,
    .stack_pop           = stack_pop,
    .stack_get           = stack_get,
    .stack_clear         = stack_clear,
    .stack_isEmpty       = stack_isEmpty,
    .stack_isFull        = stack_isFull,
    .stack_showStructure = stack_showStructure,
};

/*
	Construtor
*/
Stack *stack_new(int maxNumber) {
	int maximo = MAX_STACK_SIZE;
	if (maxNumber > 0 && maxNumber < maximo) {
		Stack *stack     = (Stack *)malloc(sizeof(Stack));
		stack->tam_atual = 0;
		stack->tam_max   = maxNumber;
		stack->cursor    = NULL;
		stack->meths     = &meths;
	}
}

ListNode *ListNode_new(DataType nodeData, ListNode *nextPtr) {
	ListNode *node = (ListNode *)malloc(sizeof(node));
	node->nodeData = nodeData;
	node->nextPtr  = NULL;
	return node;
}

void stack_del(Stack *stack) {
	assert(stack);
	ListNode *temp = stack->top;
	ListNode *nPtr;
	for (int i = 0; i < stack->tam_atual; i++) {
		nPtr = (struct ListNode *)temp->nextPtr;
		free(temp);
		temp = nPtr;
	}
}

/*
	Para inserir um item na pilha
*/
int stack_push(Stack *const stack, const DataType newDataItem) {
	assert(stack);
	ListNode *node = ListNode_new(newDataItem, NULL);
	if (!stack_isFull(stack)) {
		if (stack->tam_atual == 0) {
			stack->top    = (struct ListNode *)node;
			node->nextPtr = NULL;
			stack->cursor = node;
		} else if (stack->cursor->nextPtr == NULL) {
			stack->cursor->nextPtr = node;
			node->nextPtr          = NULL;
			stack->cursor          = node;
		}
		stack->tam_atual++;
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
int stack_copy(Stack *const target, const Stack *const source) {
	assert(target);
	assert(source);
	if (target->tam_max > 0 && source->tam_max > 0) {
		stack_clear(target);
		ListNode *aux = source->top;
		for (int i = 0; i < source->tam_atual; i++) {
			stack_push(target, aux->nodeData);
			stack_gotoNext(target);
			aux = (struct ListNode *)aux->nextPtr;
		}
		printf("%i itens copiados\n", target->tam_atual);
		return 0;
	} else {
		return -1;
	}
}

/*
	A pilha não pode estar vazia
	Retira o item de dado mais novo e o retorna
	Retorna -1 em caso de erro
*/
DataType stack_pop(Stack *const stack) {
	assert(stack);
	if (!stack_isEmpty(stack)) {
		DataType removido = stack->cursor->nodeData;
		Stack *aux        = (struct Stack *)stack->cursor->nextPtr;
		if (stack->tam_atual == 1) {
			stack->top    = NULL;
			stack->cursor = NULL;
		} else if (stack_getCursor(stack) == stack->tam_atual - 1) {
			stack_gotoPrior(stack);
			free(stack->cursor->nextPtr);
			stack->cursor->nextPtr = NULL;
		} else {
			Stack *aux = (struct Stack *)stack->cursor->nextPtr;
			stack_gotoPrior(stack);
			free(stack->cursor->nextPtr);
			stack->cursor->nextPtr = (struct ListNode *)aux;
			stack->cursor          = (struct ListNode *)aux;
		}
		stack->tam_atual--;
		return removido;
	} else {
		return -1;
	}
}

/*
	Retorna o item de dado mais novo, mas não o retira da pilha
*/
DataType stack_get(Stack *const stack) {
	stack_gotoBegin(stack);
	return stack->cursor->nodeData;
}

/*
	A pilha não pode estar vazia
	Substitui o item de dado marcado pelo cursor por newDataItem
	Retorna 1 em caso de sucesso e -1 se tiver erro
*/
int stack_replace(Stack *const stack, const DataType newDataItem) {
	assert(stack);
	if (!stack_isEmpty(stack)) {
		stack->cursor->nodeData = newDataItem;
		return 1;
	} else {
		printf("Erro na substituição \n");
		return -1;
	}
}

/*
	Remove todos os itens de dados da pilha
*/
void stack_clear(Stack *const stack) {
	assert(stack);
	stack->top       = NULL;
	stack->cursor    = NULL;
	stack->tam_atual = 0;
}

/*
	Verifica se a pilha tá vazia
	Retorna true se a pilha está vazia, caso contrário, retorna false
*/
bool stack_isEmpty(Stack *const stack) {
	assert(stack);
	if (stack->tam_atual == 0) {
		return 1;
	} else
		return 0;
}

/*
	Retorna true se a pilha está cheia, caso contrário, retorna false
*/
bool stack_isFull(Stack *const stack) {
	assert(stack);
	if (stack->tam_atual == stack->tam_max) {
		return 1;
	} else
		return 0;
}

/*
	Mostra todos os dados da pilha
*/
void stack_showStructure(Stack *const stack) {
	assert(stack);
	printf("Cursor: %i\n", stack_getCursor(stack));
	printf("Tamanho: %i\n", stack->tam_atual);
	printf("Cheio: %i\n", stack_isFull(stack));
	printf("Vazio: %i\n", stack_isEmpty(stack));
	printf("%s", "queue: [");
	ListNode *aux = stack->top;
	while (aux) {
		printf("%c ", aux->nodeData);
		aux = (struct ListNode *)aux->nextPtr;
	}
	printf("%s", "]\n");
}

/*
	Move o cursor para o primeiro item de dado e retorna o valor 0. Se estiver vazia retorna -1
*/
int stack_gotoBegin(Stack *const stack) {
	assert(stack);
	if (stack_isEmpty(stack)) {
		stack->cursor = stack->top;
		return -1;
	} else
		return 0;
}

/*
	Se a pilha não estiver vazia, move o cursor para o último item de dado e retorna este índice. Se
	estiver vazia retorna -1
*/
int stack_gotoEnd(Stack *const stack) {
	assert(stack);
	if (!stack_isEmpty(stack)) {
		while (stack->cursor->nextPtr) {
			stack->cursor = (struct ListNode *)stack->cursor->nextPtr;
		}
		return 0;
	} else
		return -1;
}

/*
	Se existe um proximo cursor. Nove-o para o próximo item e retorna true. Caso contrário,
	retorna false
*/
bool stack_gotoNext(Stack *const stack) {
	assert(stack);
	if (stack->cursor->nextPtr) {
		stack->cursor = (struct ListNode *)stack->cursor->nextPtr;
		return 1;
	} else {
		return 0;
	}
}

/*
	Se o cursor não está no início da pilha, move-o para o item anterior e retorna true. Caso contrário,
	retorna false
*/

bool stack_gotoPrior(Stack *stack) {
	assert(stack);
	ListNode *aux = stack->top;
	if (stack->cursor != stack->top) {
		while (aux->nextPtr != stack->cursor) {
			aux = (struct ListNode *)aux->nextPtr;
		}
		stack->cursor = aux;
		return 1;
	} else {
		return 0;
	}
}

/*
	Retorna o valor do item de dado apontado atualmente pelo cursor
*/
DataType stack_getFromCursor(Stack *const stack) {
	assert(stack);
	ListNode *aux = stack->top;
	if (stack->cursor != stack->top) {
		while (aux->nextPtr != stack->cursor) {
			aux = (struct ListNode *)aux->nextPtr;
		}
		stack->cursor = aux;
		return 1;
	} else {
		return 0;
	}
}

/*
	Retorna a posição do cursor atual.
*/
int stack_getCursor(Stack *stack) {
	assert(stack);
	ListNode *aux = stack->top;

	int i = 0;
	while (stack->cursor != aux) {
		aux = (struct ListNode *)aux->nextPtr;
		i++;
	}
	return i;
}
