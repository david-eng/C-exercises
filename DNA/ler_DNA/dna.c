#include "dna.h"

void DNA_new(unsigned long int tam) {
	char base;
	double r;
	LinkedList *lista = LinkedList_new(tam);
	DNA *dna          = (DNA *)malloc(sizeof(DNA));
	srand((unsigned int)time(NULL));
	printf("Quantidade de bases geradas: %lu\n", tam);

	for (unsigned long int i = 0; i < tam; i++) { 
		r = rand() / (double)RAND_MAX;
		if (r < 0.25) {
			base = 'A';
		} else if (r >= 0.25 && r < 0.50) {
			base = 'G';
		} else if (r >= 0.50 && r < 0.75) {
			base = 'C';
		} else {
			base = 'T';
		}
		DNA_cont(lista, dna, base);
	}
	save_dna(lista, tam);
	save_data(dna, tam);
	ListNode_del(lista);
}

void DNA_cont(LinkedList *list, DNA *dna, char base) {
	if (list->tam_atual == 0) {
		dna->a = dna->g = dna->c = dna->t = dna->total = 0;
	}

	list->meths->LinkedList_gotoEnd(list);
	list->meths->LinkedList_insert(list, base);

	if (base == 'A') {
		dna->timea = clock();
		dna->a++;
		dna->timea = clock() - dna->timea;
		dna->total_time_a += ((double)dna->timea) / CLOCKS_PER_SEC;
	} else if (base == 'G') {
		dna->timeg = clock();
		dna->g++;
		dna->timeg = clock() - dna->timeg;
		dna->total_time_g += ((double)dna->timeg) / CLOCKS_PER_SEC;
	} else if (base == 'C') {
		dna->timec = clock();
		dna->c++;
		dna->timec = clock() - dna->timec;
		dna->total_time_c += ((double)dna->timec) / CLOCKS_PER_SEC;
	} else if (base == 'T') {
		dna->timet = clock();
		dna->t++;
		dna->timet = clock() - dna->timet;
		dna->total_time_t += ((double)dna->timet) / CLOCKS_PER_SEC;
	}

	dna->total++;

	if (dna->total == (int)(list->tam_max)) {
		printf("Resultados:\n");
		list->meths->LinkedList_showStructure(list);
		printf("Quantidade de bases A: %lu\n", dna->a);
		printf("Tempo de contagem de bases A: %f segundos \n", dna->total_time_a);
		printf("Quantidade de bases G: %lu\n", dna->g);
		printf("Tempo de contagem de bases G: %f segundos \n", dna->total_time_g);
		printf("Quantidade de bases C: %lu\n", dna->c);
		printf("Tempo de contagem de bases C: %f segundos \n", dna->total_time_c);
		printf("Quantidade de bases T: %lu\n", dna->t);
		printf("Tempo de contagem de bases T: %f segundos \n", dna->total_time_t);
		printf("Quantidade total de bases: %lu\n", dna->total);
		printf("Tempo da contagem total: %f segundos \n", dna->total_time_a + dna->total_time_g + dna->total_time_c + dna->total_time_t);
	}
}

void save_dna(LinkedList *list, unsigned long int tam) {
	// Configura o nome do arquivo como DNA+TAMANHO+.TXT
	//-------
	char nome_DNA[2000] = "DNA";
	char _txt[10]       = ".txt";
	char tamanho_[1000];
	sprintf(tamanho_, "%lu", tam);
	strcat(nome_DNA, tamanho_);
	strcat(nome_DNA, _txt);
	// --------
	FILE *arq;
	arq           = fopen(nome_DNA, "w");
	ListNode *aux = list->top;
	while (aux) {
		fprintf(arq, "%c", aux->nodeData);
		printf("%c ", aux->nodeData);
		aux = (struct ListNode *)aux->nextPtr;
	}
	fclose(arq);
}

void save_data(DNA *dna, unsigned long int tam) {
	// Configura o nome do arquivo como DADOS-DNA(TAMANHO).TXT
	//-------
	char dados[2000] = "DADOS-DNA";
	char _txt[5]     = ".txt";
	char tamanho_[1000];
	sprintf(tamanho_, "%lu", tam);
	strcat(dados, tamanho_);
	strcat(dados, _txt);
	// --------
	FILE *arq;
	arq = fopen(dados, "w");
	fprintf(arq, "%s", "Quantidade de A: ");
	fprintf(arq, "%lu", dna->a);
	fprintf(arq, "%s", "\n");
	fprintf(arq, "%s", "Quantidade de G: ");
	fprintf(arq, "%lu", dna->g);
	fprintf(arq, "%s", "\n");
	fprintf(arq, "%s", "Quantidade de C: ");
	fprintf(arq, "%lu", dna->c);
	fprintf(arq, "%s", "\n");
	fprintf(arq, "%s", "Quantidade de T: ");
	fprintf(arq, "%lu", dna->t);

	fclose(arq);
}

void read_data(char *dados) {
	FILE *arq;
	clock_t timea, timeg, timec, timet;
	int a, g, c, t, total = 0;

	double tempo_total, tempo_total_a, tempo_total_g, tempo_total_c, tempo_total_t = 0;
	char bases;
	if ((arq = fopen(dados, "r")) != NULL) {
		while ((bases = fgetc(arq)) != EOF) {
			if (bases == 'A') {
				timea = clock();
				a += 1;
				timea = clock() - timea;
				tempo_total_a += ((double)timea) / CLOCKS_PER_SEC;
			} else if (bases == 'G') {
				timeg = clock();
				g += 1;
				timeg = clock() - timeg;
				tempo_total_g += ((double)timea) / CLOCKS_PER_SEC;
			} else if (bases == 'C') {
				timec = clock();
				c += 1;
				timec = clock() - timec;
				tempo_total_c += ((double)timec) / CLOCKS_PER_SEC;
			} else if (bases == 'T') {
				timet = clock();
				t += 1;
				timet = clock() - timet;
				tempo_total_t += ((double)timet) / CLOCKS_PER_SEC;
			}
		}
		total       = a + g + c + t;
		tempo_total = tempo_total_a + tempo_total_g + tempo_total_c + tempo_total_t;
		printf("Resultados para base A: \n");
		printf("Tempo de contagem de bases A: %f segundos \n", tempo_total_a);
		printf("Quantidade de A: %d \n", a);
		printf("----------------------- \n");
		printf("Resultados para base G: \n");
		printf("Tempo de contagem de bases G: %f segundos \n", tempo_total_g);
		printf("Quantidade de  G: %d \n", g);
		printf("-----------------------\n");
		printf("Resultados para base C: \n");
		printf("Tempo de contagem de bases C: %f segundos \n", tempo_total_c);
		printf("Quantidade de C: %d \n", c);
		printf("-----------------------\n");
		printf("Resultados para base T: \n");
		printf("Tempo de contagem de bases T: %f segundos \n", tempo_total_t);
		printf("Quantidade de T: %d \n", t);
		printf("-----------------------\n");
		printf("Quantidade total de bases: %i\n", total);
		printf("Tempo da contagem total: %f segundos \n", tempo_total);
	}
	fclose(arq);
}