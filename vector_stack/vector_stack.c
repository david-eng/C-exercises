#include "vector_stack.h"

int stack_copy(Stack *const target, const Stack *const source);
int stack_push(Stack *const stack, const DataType newDataItem);
DataType stack_pop(Stack *const stack);
DataType stack_get(Stack *const stack);
void stack_clear(Stack *const stack);
bool stack_isEmpty(Stack *const stack);
bool stack_isFull(Stack *const stack);
void stack_showStructure(Stack *const stack);
int stack_gotoBegin(Stack *const stack);
int stack_gotoEnd(Stack *const stack);
bool stack_gotoNext(Stack *const stack);
bool stack_gotoPrior(Stack *const stack);
DataType stack_getFromCursor(Stack *const stack);
int stack_getCursor(Stack *const stack);
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
	Construtor -> Cria uma pilha vazia. 
	Aloca memória suficiente para que a pilha contenha maxNumber itens se necessário.
*/
Stack *stack_new(int maxNumber) {
	int maximo = MAX_STACK_SIZE;
	if (maxNumber > 0 && maxNumber < maximo) {
		Stack *stack;
		stack            = malloc(sizeof(Stack));
		stack->tam_atual = 0;
		stack->tam_max   = maxNumber;
		stack->cursor    = -1;
		stack->dados     = (DataType *)calloc(maxNumber, sizeof(DataType));
		stack->meths     = &meths;
	}
}

/*	
	Destrutor
*/
void stack_delete(Stack *stack) {
	assert(stack);
	if (!stack_isEmpty(stack)) {
		free(stack->dados);
		free(stack);
		stack->tam_atual = 0;
		stack->cursor    = -1;
	}
}

/*
	Insere os elementos de source em target
	target e source devem existir e não podem ser nulos
	Target é reescrito
	São copiados os valores até satisfazer o tamanho
	Em caso de erro retorna -1
*/
int stack_copy(Stack *const target, const Stack *const source) {
	if (target->tam_max > 0 && source->tam_max > 0) {
		stack_clear(target);
		for (int i = 0; i < source->tam_atual; i++) {
			stack_push(target, source->dados[i]);
		}
		printf("%i itens copiados\n", target->tam_atual);
		return 1;
	} else {
		return -1;
	}
}

/*
 	Insere newDataItem no topo da pilha.
*/
int stack_push(Stack *const stack, const DataType newDataItem) {
	assert(stack);
	if (!stack_isFull(stack)) {
		stack->tam_atual++;
		stack->cursor++;
		stack->dados[stack->cursor] = ("%s", newDataItem);
		return stack->tam_atual;
	} else {
		return -1;
	}
}

/*
	Retira o item de dado mais novo e o retorna.
*/
DataType stack_pop(Stack *const stack) {
	assert(stack);
	DataType removido = stack->dados[stack->tam_atual];
	if (!stack_isEmpty(stack)) {
		if (stack->tam_atual == 1) {
			stack->dados[0] = '\0';
			stack->cursor   = -1;
		} else {
			for (int i = 0; i > stack->tam_atual - 1; i--) {
				stack->dados[i] = stack->dados[i];
			}
			stack->cursor--;
		}
		stack->tam_atual--;
		return removido;
	} else {
		return -1;
	}
}

/*
	Retorna o item de dado mais novo, mas não o retira da pilha.
*/
DataType stack_get(Stack *const stack) {
	assert(stack);
	if (!stack_isEmpty(stack)) {
		DataType item_novo = stack->dados[stack->cursor];
		return item_novo;
	} else {
		return -1;
	}
}

/*
	Remove todos os itens de dados da pilha.
*/
void stack_clear(Stack *const stack) {
	assert(stack);
	for (int i = 0; i <= (stack->tam_atual - 1); i++) {
		stack->dados[i] = '\0';
	}
	stack->cursor    = -1;
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
	Mostra todos os daddos da pilha.
*/
void stack_showStructure(Stack *const stack) {
	assert(stack);
	printf("Cursor: %i\n", stack->cursor);
	printf("Tamanho: %i\n", stack->tam_atual);
	printf("Cheio: %i\n", stack->meths->stack_isFull(stack));
	printf("Vazio: %i\n", stack->meths->stack_isEmpty(stack));
	printf("%s", "stacka: [");
	for (int i = 0; i <= (stack->tam_atual - 1); i++) {
		if (i == (stack->tam_atual - 1)) {
			printf("%c", stack->dados[i]);
		} else {
			printf("%c ", stack->dados[i]);
		}
	}
	printf("%s", "]\n");
}

/*
	Move o cursor para o primeiro item de dado e retorna o valor 0. Se estiver vazia retorna -1.
*/
int stack_gotoBegin(Stack *const stack) {
	if (stack_isEmpty(stack)) {
		return -1;
	} else {
		stack->cursor = 0;
		return 0;
	}
}

/*
	Se a pilha  não estiver vazia, move o cursor para o último item de dado e retorna este índice. Se
	estiver vazia retorna -1.
*/
int stack_gotoEnd(Stack *const stack) {
	if (!stack_isEmpty(stack)) {
		stack->cursor = stack->tam_atual - 1;
		return 0;
	} else
		return -1;
}

/*
	Se o cursor não está no fim da pilha, move-o para o próximo item e retorna true. Caso contrário,
	retorna false
*/
bool stack_gotoNext(Stack *const stack) {
	assert(stack);
	if (stack->cursor < stack->tam_atual - 1) {
		stack->cursor++;
		return 1;
	} else {
		return 0;
	}
}

/*
	Se o cursor não está no início da pilha, move-o para o item anterior e retorna true. Caso contrário,
	retorna false.
*/
bool stack_gotoPrior(Stack *const stack) {
	assert(stack);
	if (stack->cursor > 0) {
		stack->cursor--;
		return 1;
	} else {
		return 0;
	}
}

/*
	Retorna o valor do item de dado apontado atualmente pelo cursor.
*/
DataType stack_getFromCursor(Stack *const stack) {
	assert(stack);
	if (stack->tam_atual != 0) {
		return stack->dados[stack->cursor];
	}
}

/*
	Retorna o valor do cursor.
*/
int stack_getCursor(Stack *const stack) {
	assert(stack);
	return stack->cursor;
}
