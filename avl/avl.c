#include "avl.h"
#include <stdio.h>
#include <stdlib.h>



/* Cria um nodo com a chave i */ 
nodo* cria_nodo(int i){
	nodo *temp = malloc(sizeof(nodo));
	if (temp != NULL){
		temp->esq = temp->dir = temp->pai = NULL;
		temp->altura = 0;
		temp->chave = i;
	}
	return temp;
}

/* Retorna a altura da arvore */
int altura_arvore(nodo *no){
	if (no == NULL)
		return -1;
	return no->altura;
}

/* Retorna a profundidade de determinado no */
int profundidade(nodo *no){
	nodo* a = no;
	int profundidade = -1;
	while (a){
		profundidade++;
		a = a->pai;
	}
	return profundidade;
}

/* Retorna o maior inteiro */
int maior(int a, int b){
	if (a > b)
		return a;
	return b;
}

/* Realiza o balanceamento da arvore, mantendo ela uma AVL */
nodo* balanceia(nodo *x, int fb){
	if (fb == -2){
		if ((altura_arvore(x->dir->esq) - altura_arvore(x->dir->dir)) == -1)
			x = rotaciona_esquerda(x);
		else{
			x->dir = rotaciona_direita(x->dir);
			x = rotaciona_esquerda(x);
		}
	}
	else{
		if ((altura_arvore(x->esq->esq) - altura_arvore(x->esq->dir)) == 1)
			x = rotaciona_direita(x);
		else{
			x->esq = rotaciona_esquerda(x->esq);
			x = rotaciona_direita(x);
		}
	}

	return x;
}

nodo* rotaciona_esquerda(nodo *a){
	nodo *b = a->dir;
	a->dir = b->esq;
	if (b->esq)
		b->esq->pai = a;
	b->pai = a->pai;
	a->pai = b;
	b->esq = a;

	/* Atualiza as alturas dos nodos depois da rotação */
	a->altura = maior(altura_arvore(a->esq), altura_arvore(a->dir)) + 1;
	b->altura = maior(a->altura, altura_arvore(b->dir)) + 1;

	return b;
}

nodo* rotaciona_direita(nodo *a){
	nodo *b = a->esq;
	a->esq = b->dir;
	if (b->dir)
		b->dir->pai = a;
	b->pai = a->pai;
	a->pai = b;
	b->dir = a;

	/* Atualiza as alturas dos nodos depois da rotação */
	a->altura = maior(altura_arvore(a->esq), altura_arvore(a->dir)) + 1;
	b->altura = maior(altura_arvore(b->esq), a->altura) + 1;

	return b;
}

/* Faz com que o pai de no tenha como filho agora o novo, se novo existir seu pai também muda */ 
void ajustanopai(nodo *no, nodo *novo){
	if (no->pai){
		if (no->pai->esq == no)
			no->pai->esq = novo;
		else
			no->pai->dir = novo;
		if (novo)
			novo->pai = no->pai;
	}
}

/* Retorna o nodo sucessor de um determinado no */
nodo* sucessor(nodo *no){
	if (no == NULL)
		return NULL;
	nodo *a = no->dir;
	if (a != NULL){
		nodo *b = a->esq;
		while (b != NULL){
			a = b;
			b = a->esq;
		}
	}

	return a;
}

/* Realiza uma busca binaria na arvore e retorna o nodo, caso encontre o no com chave i */
nodo* busca_binaria(nodo *raiz, int i){
	if (! raiz)
		return raiz;

	if (raiz->chave == i)
		return raiz;

	if (i < raiz->chave)
		return busca_binaria(raiz->esq, i);
	else
		return busca_binaria(raiz->dir, i);
}

/* Imprime as chaves em ordem crescente */
void inorder_arvore(nodo *no){
	if (no == NULL)
		return;
	inorder_arvore(no->esq);
	printf("%d, %d\n", no->chave, profundidade(no));
	inorder_arvore(no->dir);
}

/* Insere uma chave i na arvore */ 
nodo* insere(nodo *raiz, int i){
	if (raiz == NULL){
		raiz = cria_nodo(i);
		return raiz;
	}

	if (i < raiz->chave){
		raiz->esq = insere(raiz->esq, i);
		raiz->esq->pai = raiz;
	}
	else{
		raiz->dir = insere(raiz->dir, i);
		raiz->dir->pai = raiz;
	}

	int fb, he, hd;
	he = altura_arvore(raiz->esq);
	hd = altura_arvore(raiz->dir);

	raiz->altura = maior(he, hd) + 1;

	/* Fator de balanceamento, para verificar se precisa balancear e manter propriedade de AVL */
	fb = he - hd;
	if ((fb == -2) || (fb == 2))
		raiz = balanceia(raiz, fb);

	return raiz;
}

/* Remove o nodo no da arvore */
nodo* exclui(nodo *no, nodo *raiz){
	nodo *s = NULL, *ajustano = NULL, *novaraiz = raiz;	
	if (no == NULL)
		return raiz;

	/* Caso de nó não possuir filhos */
	if ((no->esq == NULL) && (no->dir == NULL)){
		/* Se no for a própria raiz e não possui filhos, a arvore estará vazia após a remoção do nó */
		if (no == raiz){
			free(no);
			return NULL;
		}
		if (no->pai->esq == no)
			no->pai->esq = NULL;
		else
			no->pai->dir = NULL;

		ajustano = no->pai;
		free(no);
	}
	else{
		/* Caso de nó possuir apenas filho da direita */
		if (no->esq == NULL){
			ajustanopai(no, no->dir);
			if (no->pai == NULL){
				no->dir->pai = NULL;
				novaraiz = no->dir;
			}
			ajustano = no->dir->pai;
			free(no);
		}
		else{
			/* Caso de nó possuir apenas filho da esquerda */
			if (no->dir == NULL){
				ajustanopai(no, no->esq);
				if (no->pai == NULL){
					no->esq->pai = NULL;
					novaraiz = no->esq;
				}
				ajustano = no->esq->pai;
				free(no);
			}
			else{
				/* Caso de nó possuir 2 filhos */
				s = sucessor(no);
				ajustanopai(s, s->dir);

				if (s->pai == no)
					ajustano = s;      /* Se o sucessor é o próprio filho a direita de no, iremos atualizar as alturas dele pra cima */
				else
					ajustano = s->pai; /* Nó em que as alturas acima dele, incluindo ele mesmo, devem ser recalculadas */

				s->esq = no->esq;
				s->esq->pai = s; /* Como estamos pegando o sucessor, o no com certeza possui um filho da esquerda por isso não precisamos conferir */
				s->dir = no->dir;
				if (s->dir != NULL)	 /* Necessário conferir se no->dir possui filhos além do próprio sucessor */
					s->dir->pai = s;
				ajustanopai(no, s);
				/* Se no for raiz, a função ajustanopai não fará nada por isso: */
				/* Verificamos se o no removido é a raiz da árvore */
				if (no->pai == NULL){
					s->pai = NULL;
					novaraiz = s;
				}
				free(no);
			}
		}
	}

	int fb, he, hd;
	/* Sobe na arvore atualizando as novas alturas, assim como verificando o fator de balanceamento */
	while (ajustano != NULL){
		he = altura_arvore(ajustano->esq);
		hd = altura_arvore(ajustano->dir);
		ajustano->altura = maior(he, hd) + 1;
		/* Fator de balanceamento, para verificar se precisa balancear e manter propriedade de AVL */
		fb = he - hd;
		if (fb == -2){
			/* Verificamos se o ajustano é raiz */
			if (ajustano->pai == NULL)
				novaraiz = balanceia(ajustano, fb); 
			else
				ajustano->pai->dir = balanceia(ajustano, fb);
		}
		if (fb == 2){
			/* Verificamos se o ajustano é raiz */
			if (ajustano->pai == NULL)
				novaraiz = balanceia(ajustano, fb);
			else
				ajustano->pai->esq = balanceia(ajustano, fb);
		}

		ajustano = ajustano->pai;
	}

	return novaraiz;
}

/* Função para analisar cada componente da árvore */
void analise_arvore(nodo *no){
	if (no == NULL)
		return;
	analise_arvore(no->esq);
	if (no->pai)
		printf("%d, %d / altura = %d, pai = %d\n", no->chave, profundidade(no), no->altura, no->pai->chave);
	else
		printf("%d, %d / altura = %d, pai = NULL\n", no->chave, profundidade(no), no->altura);
	analise_arvore(no->dir);
}