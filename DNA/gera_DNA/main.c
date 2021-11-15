/*
Código que ler a uma estrutura de um DNA usando lista através de apontadores
Em 2021
Para o curso de Programação Avançada
*/

#include "dna.h"
void comandos() {
	puts("Programa que gera a sequência genética de DNA \n");
	puts("Tamanhos para criação :");
	puts("1K    --> para sequências de tamanho 1K de pares de nucleotídeos");
	puts("100K  --> para sequências de tamanho 100K de pares de nucleotídeos");
	puts("1M    --> para sequências de tamanho 1M de pares de nucleotídeos");
	puts("10M   --> para sequências de tamanho 10M de pares de nucleotídeos");
	puts("100M  --> para sequências de tamanho 100M de pares de nucleotídeos");
	puts("1G    --> para sequências de tamanho 1G de pares de nucleotídeos");
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		comandos();
		return -1;
	}
	char const *input = argv[1];

	if (!strcmp(input, "1K")) {
		DNA_new(1000);
		return 0;
	} else if (!strcmp(input, "100K")) {
		DNA_new(100000);
		return 0;
	} else if (!strcmp(input, "1M")) {
		DNA_new(1000000);
		return 0;
	} else if (!strcmp(input, "10M")) {
		DNA_new(10000000);
		return 0;
	} else if (!strcmp(input, "100M")) {
		DNA_new(100000000);
		return 0;
	} else if (!strcmp(input, "1G")) {
		DNA_new(1000000000);
		return 0;
	} else {
		printf("Comando não reconhecido: (%s)\n", input);
		return -1;
	}
}
