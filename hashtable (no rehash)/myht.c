#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
	int chave;
	short int hashtable;
	int indice;
	struct nodo *esq, *dir;
} nodo;

void imprime_intercalado(hashtable *t1, hashtable *t2);
/* ============= funções de BST ============= */
nodo* cria_nodo(int i, short int t, int pos);

nodo* insere(nodo *raiz, int i, short int t, int pos);

void inorder_arvore(nodo *no);
/* ========================================== */



int main(){
	hashtable t1, t2;
	inicia_hashtable(&t1);
	inicia_hashtable(&t2);

	char comando;
	int chave;

	while (1){
		/* Leitura de uma linha da entrada em stdin */
		/* Verifica se a entrada realmente possui os 2 requisitos para execução do comando */
		if (fscanf(stdin, "%c %d\n", &comando, &chave) == 2){
			switch (comando){
				case 'i':
					inserir_hash(chave, &t1, &t2);
					break;
				case 'r':
					remove_hash(chave, &t1, &t2);
					break;
				default:
					printf("Comando inválido!\n");
			}
		}

		/* Se for fim do arquivo, para leitura */
		if (feof(stdin))
			break;
	}

	/* Imprimir saida com chaves em ordem crscente */
	imprime_intercalado(&t1, &t2);

	encerra_hashtable(&t1);
	encerra_hashtable(&t2);

	return 1;
}





/* Imprime as chaves de 2 hashtables em ordem crescente */
void imprime_intercalado(hashtable *t1, hashtable *t2){
	nodo * raiz = NULL;
	int i;
	for(i = 0 ; i < M ; i++){
		if (t1->table[i].valido == 1)
			raiz = insere(raiz, t1->table[i].chave, 1, i);
		if (t2->table[i].valido == 1)
			raiz = insere(raiz, t2->table[i].chave, 2, i);
	}

	inorder_arvore(raiz);
}

/* Cria um nodo com a chave i e em um inteiro dizendo qual hashtable ela está */ 
nodo* cria_nodo(int i, short int t, int pos){
	nodo *temp = malloc(sizeof(nodo));
	if (temp != NULL){
		temp->esq = temp->dir = NULL;
		temp->chave = i;
		temp->hashtable = t;
		temp->indice = pos;
	}
	return temp;
}

/* Insere uma chave i na arvore */ 
nodo* insere(nodo *raiz, int i, short int t, int pos){
	if (raiz == NULL){
		raiz = cria_nodo(i, t, pos);
		return raiz;
	}

	if (i < raiz->chave)
		raiz->esq = insere(raiz->esq, i, t, pos);
	else
		raiz->dir = insere(raiz->dir, i, t, pos);
	
	return raiz;
}

/* Imprime as chaves em ordem crescente no formato esperado */
/* "chave, qual hashtable ela está, indice nessa hashtable" */
void inorder_arvore(nodo *no){
	if (no == NULL)
		return;
	inorder_arvore(no->esq);
	printf("%d,T%d,%d\n", no->chave, no->hashtable, no->indice);
	inorder_arvore(no->dir);
}