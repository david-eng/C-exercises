#include "listnode.h"

int LinkedList_copy(LinkedList *const target, const LinkedList *const source);
int LinkedList_insert(LinkedList *list, const DataType newDataItem);
int LinkedList_remove(LinkedList *const list);
int LinkedList_replace(LinkedList *const list, const DataType newDataItem);
void LinkedList_clear(LinkedList *const list);
bool LinkedList_isEmpty(LinkedList *const list);
bool LinkedList_isFull(LinkedList *const list);
void LinkedList_showStructure(LinkedList *const list);
int LinkedList_gotoBegin(LinkedList *const list);
int LinkedList_gotoEnd(LinkedList *const list);
bool LinkedList_gotoNext(LinkedList *const list);
bool LinkedList_gotoPrior(LinkedList *list);
DataType LinkedList_getFromCursor(LinkedList *const list);
int LinkedList_getCursor(LinkedList *const list);

struct ListNode_Meths meths = {
    .LinkedList_copy          = LinkedList_copy,
    .LinkedList_insert        = LinkedList_insert,
    .LinkedList_remove        = LinkedList_remove,
    .LinkedList_replace       = LinkedList_replace,
    .LinkedList_clear         = LinkedList_clear,
    .LinkedList_isEmpty       = LinkedList_isEmpty,
    .LinkedList_isFull        = LinkedList_isFull,
    .LinkedList_showStructure = LinkedList_showStructure,
    .LinkedList_gotoBegin     = LinkedList_gotoBegin,
    .LinkedList_gotoEnd       = LinkedList_gotoEnd,
    .LinkedList_gotoNext      = LinkedList_gotoNext,
    .LinkedList_gotoPrior     = LinkedList_gotoPrior,
    .LinkedList_getFromCursor = LinkedList_getFromCursor,
    .LinkedList_getCursor     = LinkedList_getCursor};

LinkedList *LinkedList_new(int ignored) {
	LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
	list->tam_atual  = 0;
	list->tam_max    = ignored;
	list->cursor     = NULL;
	list->meths      = &meths;
	return list;
}

ListNode *ListNode_new(DataType nodeData, ListNode *nextPtr) {
	ListNode *node = (ListNode *)malloc(sizeof(node));
	node->nodeData = nodeData;
	node->nextPtr  = NULL;
	return node;
}

void ListNode_del(LinkedList *list) {
	assert(list);
	ListNode *temp = list->top;
	ListNode *nPtr;
	for (int i = 0; i < list->tam_atual; i++) {
		nPtr = (struct ListNode *)temp->nextPtr;
		free(temp);
		temp = nPtr;
	}
}

/*
	Para inserir um item na lista
*/
int LinkedList_insert(LinkedList *list, const DataType item) {
	assert(list);
	ListNode *node = ListNode_new(item, NULL);
	if (list->tam_atual == 0) {
		list->top     = (struct ListNode *)node;
		node->nextPtr = NULL;
		list->cursor  = node;
	} else if (LinkedList_getCursor(list) < list->tam_atual - 1) {
		if (list->cursor == list->top) {
			node->nextPtr = (struct LinkedList *)list->top;
			list->top     = node;
			list->cursor  = node;
		} else {
			node->nextPtr = (struct LinkedList *)list->cursor;
			LinkedList_gotoPrior(list);
			list->cursor->nextPtr = (struct LinkedList *)node;
			list->cursor          = node;
		}
	} else if (list->cursor->nextPtr == NULL) {
		list->cursor->nextPtr = (struct LinkedList *)node;
		node->nextPtr         = NULL;
		list->cursor          = node;
	}
	list->tam_atual++;
	return 0;
}

/*
	Insere os elementos de source em target
	target e source devem existir e não podem ser nulos
	Target é reescrito
	São copiados os valores até satisfazer o tamanho
	Em caso de erro retorna -1
*/
int LinkedList_copy(LinkedList *const target, const LinkedList *const source) {
	assert(target);
	assert(source);
	if (target->tam_atual > 0 && source->tam_atual > 0) {
		if (target->tam_atual == source->tam_atual) {
			ListNode *aux = source->top;
			for (int i = 0; i < source->tam_atual; i++) {
				LinkedList_replace(target, aux->nodeData);
				LinkedList_gotoNext(target);
				aux = (struct ListNode *)aux->nextPtr;
			}
		} else {
			ListNode *aux = source->top;
			for (int i = 0; i < source->tam_atual; i++) {
				LinkedList_replace(target, aux->nodeData);
				LinkedList_gotoNext(target);
				aux = (struct ListNode *)aux->nextPtr;
				printf("Tamanho de lista incompatível. Itens copiados %i itens\n", i);
			}
		}
		return 0;
	} else {
		return -1;
	}
}

/*
	A lista não pode estar vazia
	Remove o item indicado pelo cursor
	Retorna 1 se tiver sucesso
	Retorna -1 em caso de erro
*/
int LinkedList_remove(LinkedList *const list) {
	assert(list);
	if (!LinkedList_isEmpty(list)) {
		if (list->tam_atual == 1) {
			list->top    = NULL;
			list->cursor = NULL;
		} else if (LinkedList_getCursor(list) == list->tam_atual - 1) {
			LinkedList_gotoPrior(list);
			free(list->cursor->nextPtr);
			list->cursor->nextPtr = NULL;
		} else {
			//Logica para o caso do cursor estiver apontando para o topo.
			if (list->cursor == list->top) {
				LinkedList *aux = list->cursor->nextPtr;
				free(list->top);
				list->top    = (struct ListNode *)aux;
				list->cursor = (struct ListNode *)aux;
			} else {
				LinkedList *aux = list->cursor->nextPtr;
				LinkedList_gotoPrior(list);
				free(list->cursor->nextPtr);
				list->cursor->nextPtr = (struct LinkedList *)aux;
				list->cursor          = (struct ListNode *)aux;
			}
		}
		list->tam_atual--;
		return 1;
	} else {
		return -1;
	}
}

/*
	A lista não pode estar vazia
	Substitui o item de dado marcado pelo cursor por newDataItem.
	Retorna 1 em caso de sucesso e -1 se tiver erro
*/
int LinkedList_replace(LinkedList *const list, const DataType newDataItem) {
	assert(list);
	if (!LinkedList_isEmpty(list)) {
		list->cursor->nodeData = newDataItem;
		return 1;
	} else {
		printf("Erro na substituição \n");
		return -1;
	}
}

/*
	Remove todos os itens de dados da lista
*/
void LinkedList_clear(LinkedList *const list) {
	assert(list);
	list->top       = NULL;
	list->cursor    = NULL;
	list->tam_atual = 0;
}

/*
	Verifica se a lista tá vazia
	Returna true se a lista está vazia, caso contrário, retorna false
*/
bool LinkedList_isEmpty(LinkedList *const list) {
	assert(list);
	if (list->tam_atual == 0) {
		return 1;
	} else
		return 0;
}

/*
	Returna true se a lista está cheia, caso contrário, retorna false
*/
bool LinkedList_isFull(LinkedList *const list) {
	assert(list);
	if (list->tam_atual == list->tam_max) {
		return 1;
	} else
		return 0;
}

/*
    Mostra todos os daddos da lista.
*/
void LinkedList_showStructure(LinkedList *const list) {
	assert(list);
	printf("Cursor: %i\n", LinkedList_getCursor(list));
	printf("Tamanho: %i\n", list->tam_atual);
	printf("Cheio: %i\n", list->meths->LinkedList_isFull(list));
	printf("Vazio: %i\n", list->meths->LinkedList_isEmpty(list));
	printf("%s", "Lista: [");
	ListNode *aux = list->top;
	while (aux) {
		printf("%c ", aux->nodeData);
		aux = (struct ListNode *)aux->nextPtr;
	}
	printf("%s", "]\n");
}

/*
    move o cursor para o primeiro item de dado e retorna o valor 0. Se estiver vazia retorna -1.
*/
int LinkedList_gotoBegin(LinkedList *const list) {
	assert(list);
	if (LinkedList_isEmpty(list)) {
		list->cursor = list->top;
		return -1;
	} else
		return 0;
}

/*
Se a lista não estiver vazia, move o cursor para o último item de dado e retorna este índice. Se
estiver vazia retorna -1.
*/
int LinkedList_gotoEnd(LinkedList *const list) {
	assert(list);
	if (!LinkedList_isEmpty(list)) {
		while (list->cursor->nextPtr) {
			list->cursor = (struct ListNode *)list->cursor->nextPtr;
		}
		return 0;
	} else
		return -1;
}

/*
Se existe um proximo cursor. Nove-o para o próximo item e retorna true. Caso contrário,
retorna false
*/
bool LinkedList_gotoNext(LinkedList *const list) {
	assert(list);
	if (list->cursor->nextPtr) {
		list->cursor = (struct ListNode *)list->cursor->nextPtr;
		return 1;
	} else {
		return 0;
	}
}

/*
Se o cursor não está no início da lista, move-o para o item anterior e retorna true. Caso contrário,
retorna false.
*/
bool LinkedList_gotoPrior(LinkedList *list) {
	assert(list);
	ListNode *aux = list->top;
	if (list->cursor != list->top) {
		while (aux->nextPtr != (struct LinkedList *)list->cursor) {
			aux = (struct ListNode *)aux->nextPtr;
		}
		list->cursor = aux;
		return 1;
	} else {
		return 0;
	}
}

/*
Retorna o valor do item de dado apontado atualmente pelo cursor.
*/

DataType LinkedList_getFromCursor(LinkedList *const list) {
	assert(list);
	if (!LinkedList_isEmpty(list)) {
		return list->cursor->nodeData;
	} else {
		return -1;
	}
}

/*
Retorna a posição do cursor atual.
*/
int LinkedList_getCursor(LinkedList *list) {
	assert(list);
	ListNode *aux = list->top;

	int i = 0;
	while (list->cursor != aux) {
		aux = (struct ListNode *)aux->nextPtr;
		i++;
	}
	return i;
}
