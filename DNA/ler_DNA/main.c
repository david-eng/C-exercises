/*
Código que ler a uma estrutura de um DNA usando lista através de apontadores
Em 2021
Para o curso de Programação Avançada
*/

#include "dna.h"

void comandos() {
	puts("Programa que gera a sequência genética de DNA \n");
	puts("Tamanhos para criação :");
	puts("1K    --> para ler sequências de tamanho 1K de pares de nucleotídeos");
	puts("100K  --> para ler sequências de tamanho 100K de pares de nucleotídeos");
	puts("1M    --> para ler sequências de tamanho 1M de pares de nucleotídeos");
	puts("10M   --> para ler sequências de tamanho 10M de pares de nucleotídeos");
	puts("100M  --> para ler sequências de tamanho 100M de pares de nucleotídeos");
	puts("1G    --> para ler sequências de tamanho 1G de pares de nucleotídeos");
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		comandos();
		return -1;
	}
	char const *input = argv[1];
	if (!strcmp(input, "1K")) {
		read_data("DNA1000.txt");
		return 0;
	} else if (!strcmp(input, "100K")) {
		read_data("DNA100000.txt");
		return 0;
	} else if (!strcmp(input, "1M")) {
		read_data("DNA1000000.txt");
		return 0;
	} else if (!strcmp(input, "10M")) {
		read_data("DNA10000000.txt");
		return 0;
	} else if (!strcmp(input, "100M")) {
		read_data("DNA100000000.txt");
		return 0;
	} else if (!strcmp(input, "1G")) {
		read_data("DNA1000000000.txt");
		return 0;
	} else {
		printf("Comando não reconhecido: (%s)\n", input);
		return -1;
	}
	return 0;
}
