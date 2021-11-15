/*
Código que apresenta a implementação de uma fila utilizando lista de vetores (vectorlist).
Em 2021
Para o curso de Programação Avançada
*/

#include "vector_queue.h"

void comdandos() {
	printf("Testes \n");
	printf("+x         Insere o item de dado x após o cursor na fila\n");
	printf("-          Retira o item de dado mais antigo e o retorna\n");
	printf("=          Retorna o item de dado mais antigo, mas não o remove da fila.\n");
	printf("@          Copiar uma fila para outra.\n");
	printf("E          Verifica se a fila está vazia\n");
	printf("F          Verifica se a fila está cheia\n");
	printf("C          Limpa a fila\n");
	printf("Q          Sai do programa de testes\n");
}

int main(int argc, char *argv[]) {
	// Criação de  queues para testes
	Queue *teste = queue_new(10);
	Queue *copy  = queue_new(9);

	char opcao[2] = {'\0'};

	do {
		comdandos();
		printf("\nInput: ");
		scanf("%s", opcao);
		if (opcao[0] == '+') {
			METH(queue_enqueue, teste, opcao[1]);
			METH(queue_showStructure, teste);
		} else if (opcao[0] == '-') {
			printf("Item retirado %c \n", METH(queue_dequeue, teste));
			METH(queue_showStructure, teste);
		} else if (opcao[0] == '=') {
			printf("Item mais antigo: %c \n", METH(queue_get, teste));
			METH(queue_showStructure, teste);
		} else if (opcao[0] == '@') {
			METH(queue_copy, copy, teste);
			printf("A fila (teste) foi copiada para a fila (copy)\n");
			printf("fila copy : ");
			METH(queue_showStructure, copy);
			printf("\nfila teste : ");
			METH(queue_showStructure, teste);
		} else if (opcao[0] == 'E') {
			if (METH(queue_isEmpty, teste)) {
				printf("Fila vazia! \n");
			} else {
				printf("A fila não está vazia!\n");
			}
			METH(queue_showStructure, teste);
		} else if (opcao[0] == 'F') {
			if (METH(queue_isFull, teste)) {
				printf("A fila está cheia!\n");
			} else {
				printf("A fila não está cheia!\n");
			}
			METH(queue_showStructure, teste);
		} else if (opcao[0] == 'C') {
			METH(queue_clear, teste);
			METH(queue_showStructure, teste);
		} else if (opcao[0] != 'Q') {
			printf("Erro 404. Comando não reconhecido, tente novamente. \n\n");
		}
	} while (opcao[0] != 'Q');

	return 0;
}