#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>

int inicia_hashtable(hashtable* t){
	t->table = (slot *) malloc(M * sizeof(slot));
	if (t->table){
		int i;
		for(i = 0 ; i < M ; i++){
			t->table[i].chave = -1;
			t->table[i].valido = -1;
		}
		return 1;
	}
	return 0;
}

void encerra_hashtable(hashtable* t){
	free(t->table);
}

int hash_function1(int k){
	return k % M;
}

int hash_function2(int k){
	int piso = M * (k * A - (int) (k * A));
	if (piso >= 0)
		return piso;
	return -piso;
}

slot * busca_hash(int k, hashtable* t1, hashtable* t2){
	int a = hash_function1(k);
	if (t1->table[a].valido == -1)
		return NULL; /* Retorna nulo e chave não existe */

	/* Senão, chave é válida ou foi excluída */
	if ( (t1->table[a].valido == 1) && (k == t1->table[a].chave) )
		return &t1->table[a];

	/* Se chave k calculada por h1(k) foi excluída ou se k diferente da chave em T1[h1(k)] */
	/* verificamos se k é igual a T2[h2(k)] e se essa chave é válida */
	int b = hash_function2(k);
	if ( (k == t2->table[b].chave) && (t2->table[b].valido == 1) ) 
		return &t2->table[b];

	return NULL;
}

int inserir_hash(int k, hashtable* t1, hashtable* t2){
	int a = hash_function1(k);
	if (t1->table[a].valido < 1){
		/* Verifica se chave k já está em T2, se sim, não insere duplicado */
		if (t2->table[hash_function2(k)].chave != k){
			t1->table[a].chave = k;
			t1->table[a].valido = 1;
		}
		else
			return 0;
	}
	else{
		/* Caso já tenha uma chave ki em T1 */
		int ki = t1->table[a].chave;
		/* Se a chave ki for igual a nova chave k, não insere duplicado */
		if (ki == k)
			return 0;

		/* Insere chave k em T1 */
		t1->table[a].chave = k;

		/* Insere chave ki em T2 */
		int b = hash_function2(ki);
		t2->table[b].chave = ki;
		t2->table[b].valido = 1;
	}
	return 1;
}

int remove_hash(int k, hashtable* t1, hashtable* t2){
	slot * chave = busca_hash(k, t1, t2);
	if (chave){
		chave->valido = 0; /* Marca como excluído */
		return 1;
	}
	return 0;
}





void imprimir_tabela_completa(hashtable* t1, hashtable* t2){
	int i;
	for(i = 0 ; i < M ; i++)
		printf("[%d].(%d) = %d ---------- [%d].(%d) = %d\n", i, t1->table[i].valido, t1->table[i].chave, 
			i, t2->table[i].valido, t2->table[i].chave);
}