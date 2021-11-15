/*
Código que apresenta a implementação de uma pilha utilizando lista de apontadores (nodelist).
Em 2021
Para o curso de Programação Avançada
*/

#include "node_stack.h"

void comdandos() {
	printf("Testes \n");
	printf("+x         Insere o item de dado x após o cursor na pilha\n");
	printf("-          Retira o item de dado mais novo e o retorna\n");
	printf("=          Retorna o item de dado mais novo, mas não o remove da pilha.\n");
	printf("@          Copiar uma pilha para outra.\n");
	printf("E          Verifica se a pilha está vazia\n");
	printf("F          Verifica se a pilha está cheia\n");
	printf("C          Limpa a pilha\n");
	printf("Q          Sai do programa de testes\n");
}

int main(int argc, char *argv[]) {
	// Criação de stacks para testes
	Stack *teste = stack_new(10);
	Stack *copy  = stack_new(9);

	char opcao[2] = {'\0'};

	do {
		comdandos();
		printf("\nInput: ");
		scanf("%s", opcao);
		if (opcao[0] == '+') {
			METH(stack_push, teste, opcao[1]);
			METH(stack_showStructure, teste);
		} else if (opcao[0] == '-') {
			printf("Item retirado %c \n", METH(stack_pop, teste));
			METH(stack_showStructure, teste);
		} else if (opcao[0] == '=') {
			printf("Item mais novo: %c \n", METH(stack_get, teste));
			METH(stack_showStructure, teste);
		} else if (opcao[0] == '@') {
			METH(stack_copy, copy, teste);
			printf("A pilha (teste) foi copiada para a pilha (copy)\n");
			printf("pilha copy : ");
			METH(stack_showStructure, copy);
			printf("\npilha teste : ");
			METH(stack_showStructure, teste);
		} else if (opcao[0] == 'E') {
			if (METH(stack_isEmpty, teste)) {
				printf("pilha vazia! \n");
			} else {
				printf("A pilha não está vazia!\n");
			}
			METH(stack_showStructure, teste);
		} else if (opcao[0] == 'F') {
			if (METH(stack_isFull, teste)) {
				printf("A pilha está cheia!\n");
			} else {
				printf("A pilha não está cheia!\n");
			}
			METH(stack_showStructure, teste);
		} else if (opcao[0] == 'C') {
			METH(stack_clear, teste);
			METH(stack_showStructure, teste);
		} else if (opcao[0] != 'Q') {
			printf("Erro 404. Comando não reconhecido, tente novamente. \n\n");
		}
	} while (opcao[0] != 'Q');

	return 0;
}