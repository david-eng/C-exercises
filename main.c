/*
Código que resolve expressões aritméticas na forma pós-fixa - usando listas (vector_queue).
Em 2021
Para o curso de Programação Avançada
*/

#include "string.h"
#include "vector_queue.h"

// verifica se o caractere representa um número
int is_number(char c) {
	if ('0' <= c && c <= '9') {
		return 1;
	} else {
		return 0;
	}
}

int posfix(char *s) {
	int result = 0, num1, num2;
	int tam    = strlen(s);

	Queue *posfix = queue_new(tam);

	for (int i = 0; i < tam; i++) {
		if (is_number(s[i])) {
			// Insere os números na fila
			METH(queue_enqueue, posfix, s[i] - '0');

		} else {
			// Resolve as expressões e insere na fila
			METH(queue_gotoEnd, posfix);
			num2 = METH(queue_getFromCursor, posfix);
			METH(queue_gotoPrior, posfix);
			num1 = METH(queue_getFromCursor, posfix);
			METH(queue_remove, posfix);
			METH(queue_gotoEnd, posfix);
			METH(queue_remove, posfix);

			// Operações
			if (s[i] == '-') {
				METH(queue_enqueue, posfix, num1 - num2);
			} else if (s[i] == '+') {
				METH(queue_enqueue, posfix, num1 + num2);
			} else if (s[i] == '*') {
				METH(queue_enqueue, posfix, num1 * num2);
			} else if (s[i] == '/') {
				METH(queue_enqueue, posfix, num1 / num2);
			}
		}
	}
	result = METH(queue_get, posfix);
	if (result == 0) {
		printf("Erro. Insira uma equação válida \n");
	} else {
		return result;
	}
}

int main(int argc, char *argv[]) {
	/*
		Testes feitos
		13*57*+  = 38
		246*+8+  = 34
		24+68+*  = 84
		32+6+5+  = 16
		32-6+5+	 = 12
	*/

	char input[100];

	printf("Exercício de Programação 5\n");
	printf("Resolução de expressões aritméticas na forma pós-fixa - usando filas \n");
	printf("Digite a expressão: ");
	scanf("%s", input);
	remove_spaces(input);
	printf("\n%s \n", input);
	posfix(input);
	printf("Resultado da expressão: %i \n", posfix(input));

	return 0;
};