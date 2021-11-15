/*
Código que apresenta a uma estrutura VectorList
Em 2021
Para o curso de Programação Avançada
*/

#include "vectorlist.h"

void comdandos() {
	printf("+x         Insere o item de dado x após o cursor na lista\n");
	printf("-          Remove o item de dado na posição do cursor\n");
	printf("=x         Substitui o item atual pelo novo item x.\n");
	printf("@          Mostra o item de dado atualmente marcado pelo cursor\n");
	printf("N ou n     Move o cursor para o próximo item\n");
	printf("P ou p     Move o cursor para item anterior\n");
	printf("<          Vai para o início da lista\n");
	printf(">          Vai para o fim da lista\n");
	printf("E          Verifica se a lista está vazia\n");
	printf("F          Verifica se a lista está cheia\n");
	printf("C          Limpa a lista\n");
	printf("Q          Sai do programa de testes\n");
}

int main(int argc, char *argv[]) {
	// Criação de um VectorList para testes
	VectorList *teste = VectorList_new(10);

	char opcao[2] = {'\0'};

	do {
		comdandos();
		printf("\n Input: ");
		scanf("%s", opcao);
		if (opcao[0] == '+') {
			teste->meths->VectorList_insert(teste, opcao[1]);
			teste->meths->VectorList_showStructure(teste);
		} else if (opcao[0] == '-') {
			teste->meths->VectorList_remove(teste);
			teste->meths->VectorList_showStructure(teste);
		} else if (opcao[0] == '=') {
			teste->meths->VectorList_replace(teste, opcao[1]);
			teste->meths->VectorList_showStructure(teste);
		} else if (opcao[0] == '@') {
			char item = teste->meths->VectorList_getFromCursor(teste);
			if (item != '\0') {
				printf("Item atual : %c \n\n", item);
			} else if (teste->meths->VectorList_isEmpty(teste)) {
				printf("A lista está vazia. O item atual é nulo. \n\n");
			}
			teste->meths->VectorList_showStructure(teste);
		} else if (opcao[0] == 'N' || opcao[0] == 'n') {
			teste->meths->VectorList_gotoNext(teste);
			teste->meths->VectorList_showStructure(teste);
		} else if (opcao[0] == 'P' || opcao[0] == 'p') {
			teste->meths->VectorList_gotoPrior(teste);
			teste->meths->VectorList_showStructure(teste);
		} else if (opcao[0] == '<') {
			teste->meths->VectorList_gotoBegin(teste);
			teste->meths->VectorList_showStructure(teste);
		} else if (opcao[0] == '>') {
			teste->meths->VectorList_gotoEnd(teste);
			teste->meths->VectorList_showStructure(teste);
		} else if (opcao[0] == 'E') {
			if (teste->meths->VectorList_isEmpty(teste)) {
				printf("A lista está vazia!\n");
			} else {
				printf("A lista não está vazia!\n");
			}
			teste->meths->VectorList_showStructure(teste);
		} else if (opcao[0] == 'F') {
			if (teste->meths->VectorList_isFull(teste)) {
				printf("A lista está cheia!\n");
			} else {
				printf("A lista não está cheia!\n");
			}
			teste->meths->VectorList_showStructure(teste);
		} else if (opcao[0] == 'C') {
			teste->meths->VectorList_clear(teste);
			teste->meths->VectorList_showStructure(teste);
		} else if (opcao[0] != 'Q') {
			printf("Erro 404. Comando não reconhecido, tente novamente. \n\n");
		}
	} while (opcao[0] != 'Q');

	return 0;
}