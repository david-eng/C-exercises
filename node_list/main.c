/*
Código que apresenta a uma estrutura LinkedList
Em 2021
Para o curso de Programação Avançada
*/

#include "listnode.h"

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
	// Criação de um LinkedList para testes
	LinkedList *teste = LinkedList_new(10);

	char opcao[3] = {'\0'};
	char item;
	do {
		comdandos();
		printf("\n Input: ");
		scanf("%s", opcao);
		switch (opcao[0]) {
		case '+':
			teste->meths->LinkedList_insert(teste, opcao[1]);
			teste->meths->LinkedList_showStructure(teste);
			break;
		case '-':
			teste->meths->LinkedList_remove(teste);
			teste->meths->LinkedList_showStructure(teste);
			break;
		case '=':
			teste->meths->LinkedList_replace(teste, opcao[1]);
			teste->meths->LinkedList_showStructure(teste);
			break;
		case '@':
			item = teste->meths->LinkedList_getFromCursor(teste);
			if (item != '\0') {
				printf("Item atual : %c \n\n", item);
			} else if (teste->meths->LinkedList_isEmpty(teste)) {
				printf("A lista está vazia. O item atual é nulo. \n\n");
			}
			teste->meths->LinkedList_showStructure(teste);
			break;
		case 'N':
		case 'n':
			teste->meths->LinkedList_gotoNext(teste);
			teste->meths->LinkedList_showStructure(teste);
			break;
		case 'P':
		case 'p':
			teste->meths->LinkedList_gotoPrior(teste);
			teste->meths->LinkedList_showStructure(teste);
			break;
		case '<':
			teste->meths->LinkedList_gotoBegin(teste);
			teste->meths->LinkedList_showStructure(teste);
			break;
		case '>':
			teste->meths->LinkedList_gotoEnd(teste);
			teste->meths->LinkedList_showStructure(teste);
			break;
		case 'E':
			if (teste->meths->LinkedList_isEmpty(teste)) {
				printf("A lista está vazia!\n");
			} else {
				printf("A lista não está vazia!\n");
			}
			teste->meths->LinkedList_showStructure(teste);
			break;
		case 'F':
			if (teste->meths->LinkedList_isFull(teste)) {
				printf("A lista está cheia!\n");
			} else {
				printf("A lista não está cheia!\n");
			}
			teste->meths->LinkedList_showStructure(teste);
			break;
		case 'C':
			teste->meths->LinkedList_clear(teste);
			teste->meths->LinkedList_showStructure(teste);
			break;
		default:
			if (opcao[0] != 'Q') {
				printf("Erro 404. Comando não reconhecido, tente novamente. \n\n");
				break;
			}
			break;
		}
	} while (opcao[0] != 'Q');

	return 0;
}