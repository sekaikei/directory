#ifndef HASHT_H
#define HASHT_H

#define M 11
#define A 0.9f

typedef struct slot{
	int chave;
	short int valido;
} slot;

typedef struct hashtable{
	slot * table;
} hashtable;

#endif



/* Inicia a estrutura de dados hashtable */
int inicia_hashtable(hashtable* t);

/* Encerra a estrutura de dados hashtable */
void encerra_hashtable(hashtable* t);

/* Procura uma chave na hashtable e retorna um ponteiro para esse slot */
slot * busca_hash(int k, hashtable* t1, hashtable* t2);

/* Insere uma chave na hashtable t1 ou t2, caso insira retorna 1 senão retorna 0 */
int inserir_hash(int k, hashtable* t1, hashtable* t2);

/* Exclui uma chave da hashtable, se encontrada, exclui e retorna 1; senão encontrar, retorna 0 */
int remove_hash(int k, hashtable* t1, hashtable* t2);





/* Função para conferir as duas tabelas, suas chaves, valores tapara valido */
void imprimir_tabela_completa(hashtable* t1, hashtable* t2);