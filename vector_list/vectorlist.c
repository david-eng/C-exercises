#include "vectorlist.h"

int VectorList_copy(VectorList *const target, const VectorList *const source);
int VectorList_insert(VectorList *const list, const DataType newDataItem);
int VectorList_remove(VectorList *const list);
int VectorList_replace(VectorList *const list, const DataType newDataItem);
void VectorList_clear(VectorList *const list);
bool VectorList_isEmpty(VectorList *const list);
bool VectorList_isFull(VectorList *const list);
void VectorList_showStructure(VectorList *const list);
int VectorList_gotoBegin(VectorList *const list);
int VectorList_gotoEnd(VectorList *const list);
bool VectorList_gotoNext(VectorList *const list);
bool VectorList_gotoPrior(VectorList *const list);
DataType VectorList_getFromCursor(VectorList *const list);
int VectorList_getCursor(VectorList *const list);

struct VectorList_Meths meths = {
    .VectorList_copy          = VectorList_copy,
    .VectorList_insert        = VectorList_insert,
    .VectorList_remove        = VectorList_remove,
    .VectorList_replace       = VectorList_replace,
    .VectorList_clear         = VectorList_clear,
    .VectorList_isEmpty       = VectorList_isEmpty,
    .VectorList_isFull        = VectorList_isFull,
    .VectorList_showStructure = VectorList_showStructure,
    .VectorList_gotoBegin     = VectorList_gotoBegin,
    .VectorList_gotoEnd       = VectorList_gotoEnd,
    .VectorList_gotoNext      = VectorList_gotoNext,
    .VectorList_gotoPrior     = VectorList_gotoPrior,
    .VectorList_getFromCursor = VectorList_getFromCursor,
    .VectorList_getCursor     = VectorList_getCursor};

VectorList *VectorList_new(int maxNumber) {
	int maximo = MAX_LIST_SIZE;
	if (maxNumber > 0 && maxNumber < maximo) {
		VectorList *list;
		list            = malloc(sizeof(VectorList));
		list->tam_atual = 0;
		list->tam_max   = maxNumber;
		list->cursor    = -1;
		list->dados     = (DataType *)calloc(maxNumber, sizeof(DataType));
		list->meths     = &meths;
		return list;
	}
}

/*
	Para inserir um item na lista
	A lista não pode estar cheia
	O tamanho da lista precisa ser maior que 0.
*/
int VectorList_insert(VectorList *const list, const DataType item) {
	assert(list);
	if (list->tam_max > list->tam_atual) {
		if (list->cursor != list->tam_atual - 1 && list->tam_atual != 0) {
			for (int i = list->tam_atual - 1; i >= list->cursor; i--) {
				list->dados[i + 1] = list->dados[i];
			}
			list->tam_atual++;
			list->dados[list->cursor] = ("%s", item);
		} else {
			list->cursor++;
			list->dados[list->cursor] = ("%s", item);
			list->tam_atual++;
		}
		return list->cursor;
	}
}

/*
	Insere os elementos de source em target
	target e source devem existir e não podem ser nulos
	Target é reescrito
	Sãp copiados os valores até satisfazer o tamanho
	Em caso de erro retorna -1
*/
int VectorList_copy(VectorList *const target, const VectorList *const source) {
	if (target->tam_atual > 0 && source->tam_atual > 0) {
		if (target->tam_atual == source->tam_atual) {
			target->dados = source->dados;
		} else {
			int i = 0;
			for (i; i <= target->tam_atual - 1; i++) {
				target->dados[i] = source->dados[i];
			}
			printf("Tamanho de lista incompatível. Itens copiados %i itens\n", i);
		}
	} else {
		return -1;
	}
}

/*
	A lista não pode estar vazia
	Remove o item indicado pelo cursor
	Retorna a nova posição do cursor
	Retorna -1 em caso de erro
*/
int VectorList_remove(VectorList *const list) {
	if (!VectorList_isEmpty(list)) {
		if (list->tam_atual == 1) {
			list->dados[0] = '\0';
			list->cursor   = -1;
		} else if (list->cursor != list->tam_atual - 1) {
			for (int i = list->cursor; i <= list->tam_atual - 1; i++) {
				list->dados[i] = list->dados[i + 1];
			}
			list->cursor--;
		}
		list->tam_atual--;
		return list->cursor;
	} else {
		return -1;
	}
}

/*
	A lista não pode estar vazia
	Substitui o item de dado marcado pelo cursor por newDataItem.
	Retorna a posição atual do cursor
*/
int VectorList_replace(VectorList *const list, const DataType newDataItem) {
	if (!VectorList_isEmpty(list)) {
		list->dados[list->cursor] = ("%s", newDataItem);
		return list->cursor;
	} else
		printf("Erro na substituição \n");
}

/*
	Remove todos os itens de dados da lista
*/
void VectorList_clear(VectorList *const list) {
	for (int i = 0; i <= (list->tam_atual - 1); i++) {
		list->dados[i] = '\0';
	}
	list->cursor    = -1;
	list->tam_atual = 0;
}

/*
	Verifica se a lista tá vazia
	Returna true se a lista está vazia, caso contrário, retorna false
*/
bool VectorList_isEmpty(VectorList *const list) {
	if (list->tam_atual == 0) {
		return 1;
	} else
		return 0;
}

/*
	Returna true se a lista está cheia, caso contrário, retorna false
*/
bool VectorList_isFull(VectorList *const list) {
	if (list->tam_atual == list->tam_max) {
		return 1;
	} else
		return 0;
}

/*
    Mostra todos os daddos da lista.
*/
void VectorList_showStructure(VectorList *const list) {
	assert(list);
	printf("Cursor: %i\n", list->cursor);
	printf("Tamanho: %i\n", list->tam_atual);
	printf("Cheio: %i\n", list->meths->VectorList_isFull(list));
	printf("Vazio: %i\n", list->meths->VectorList_isEmpty(list));
	printf("%s", "Lista: [");
	for (int i = 0; i <= (list->tam_atual - 1); i++) {
		if (i == (list->tam_atual - 1)) {
			printf("%c", list->dados[i]);
		} else {
			printf("%c ", list->dados[i]);
		}
	}
	printf("%s", "]\n");
}

/*
    move o cursor para o primeiro item de dado e retorna o valor 0. Seestiver vazia retorna -1.
*/
int VectorList_gotoBegin(VectorList *const list) {
	list->cursor = 0;
	if (VectorList_isEmpty(list)) {
		return -1;
	} else
		return 0;
}

/*
Se a lista não estiver vazia, move o cursor para o último item de dado e retorna este índice. Se
estiver vazia retorna -1.
*/
int VectorList_gotoEnd(VectorList *const list) {
	if (!VectorList_isEmpty(list)) {
		list->cursor = list->tam_atual - 1;
		return 0;
	} else
		return -1;
}

/*
 Se o cursor não está no fim da lista, move-o para o próximo item e retorna true. Caso contrário,
retorna false
*/
bool VectorList_gotoNext(VectorList *const list) {
	assert(list);
	if (list->cursor < list->tam_atual - 1) {
		list->cursor++;
		return 1;
	} else {
		return 0;
	}
}

/*
Se o cursor não está no início da lista, move-o para o item anterior e retorna true. Caso contrário,
retorna false.
*/
bool VectorList_gotoPrior(VectorList *const list) {
	assert(list);
	if (list->cursor > 0) {
		list->cursor--;
		return 1;
	} else {
		return 0;
	}
}

/*
Retorna o valor do item de dado apontado atualmente pelo cursor.
*/

DataType VectorList_getFromCursor(VectorList *const list) {
	assert(list);
	if (list->tam_atual != 0) {
		return list->dados[list->cursor];
	}
}

/*
Retorna o valor do item de dado apontado atualmente pelo cursor.
*/
int VectorList_getCursor(VectorList *const list) {
	assert(list);
	return list->cursor;
}
