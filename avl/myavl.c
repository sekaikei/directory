#include <stdio.h>
#include "avl.h"

int main(){
	nodo *raiz = NULL;
	char comando;
	int chave;

	while (1){
		/* Leitura de uma linha da entrada em stdin */
		/* Verifica se a entrada realmente possui os 2 requisitos para execução do comando */
		if (fscanf(stdin, "%c %d\n", &comando, &chave) == 2){
			switch (comando){
				case 'i':
					raiz = insere(raiz, chave);
					break;
				case 'r':
					raiz = exclui(busca_binaria(raiz, chave), raiz);
					break;
				default:
					printf("Comando inválido!\n");
			}
		}

		/* Se for fim do arquivo, para leitura */
		if (feof(stdin))
			break;
	}

	inorder_arvore(raiz);
	
	return 0;
}