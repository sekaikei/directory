#ifndef AVL_H
#define AVL_H

typedef struct nodo{
	int chave;
	int altura;
	struct nodo *esq, *dir, *pai;
} nodo;

#endif



/* Cria um nodo com a chave i */ 
nodo* cria_nodo(int i);

/* Retorna a altura da arvore */
int altura_arvore(nodo *no);

/* Retorna a profundidade de determinado no */
int profundidade(nodo *no);

/* Retorna o maior inteiro */
int maior(int a, int b);

/* Realiza o balanceamento da arvore, mantendo ela uma AVL */
nodo* balanceia(nodo *x, int fb);

nodo* rotaciona_esquerda(nodo *a);

nodo* rotaciona_direita(nodo *a);

/* Faz com que o pai de no tenha como filho agora o novo, se novo existir seu pai também muda */ 
void ajustanopai(nodo *no, nodo *novo);

/* Retorna o nodo sucessor de um determinado no */
nodo* sucessor(nodo *no);

/* Busca binaria apenas se arvore tiver propriedade de uma BST */
nodo* busca_binaria(nodo *raiz, int i);

/* Imprime as chaves em ordem crescente */
void inorder_arvore(nodo *no);

/* Insere uma chave i na arvore */ 
nodo* insere(nodo *raiz, int i);

/* Remove o nodo no da arvore */
nodo* exclui(nodo *no, nodo *raiz);



/* Função para analisar cada componente da árvore */
void analise_arvore(nodo *no);