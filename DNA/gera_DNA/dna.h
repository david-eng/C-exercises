#ifndef _DNA_H
#define _DNA_H

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "doublelistnode.h"

// Classe
struct DNA {
	LinkedList *node;

	//variáveis para a contagem do DNA e tempo
	unsigned long int a, g, c, t, total;
	clock_t timea, timeg, timec, timet;
	double total_time_a, total_time_g, total_time_c, total_time_t;
};

typedef struct DNA DNA;

void DNA_new(unsigned long int tam);
void DNA_cont(LinkedList *list, DNA *dna, char base);
void save_dna(LinkedList *list, unsigned long int tam);
void save_data(DNA *dna, unsigned long int tam);
void read_data(char *dados);

#endif