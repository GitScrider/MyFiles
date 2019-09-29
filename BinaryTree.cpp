#include <iostream>
#include <string>
#include <stddef.h>
#include <stdlib.h>


using namespace std;

typedef struct TipoCelula{
int dado;
TipoCelula *esquerda,*direita;
}TipoCelula;

typedef struct TipoArvoreBinaria{
int tamanho;
TipoCelula *topo,*percorre;
}TipoArvoreBinaria;

void inicializaArvore(TipoArvoreBinaria *arvore){
	TipoCelula *novaCelula = new TipoCelula();
	arvore->topo= novaCelula;
	arvore->percorre=arvore->topo;
	arvore->topo->esquerda=NULL;
	arvore->topo->direita=NULL;
	arvore->tamanho=0;

}

bool verificaVazia(TipoArvoreBinaria *arvore){
	if(arvore->tamanho==0){
		return true;
	}
	else{
		return false;
	}
}

void insere(TipoArvoreBinaria *arvore,int n){
	if(verificaVazia(arvore)){
		arvore->topo->dado=n;
	}
	else{
		TipoCelula *novaCelula;
		while(1){
			if(arvore->percorre->dado <= n){


					if(arvore->percorre->esquerda==NULL){
						cout<<arvore->percorre->dado<<" teste"<<endl;
						novaCelula = new TipoCelula();
						novaCelula->esquerda=NULL;
						novaCelula->direita=NULL;
						novaCelula->dado=n;
						arvore->percorre->esquerda=novaCelula;
						break;
					}
					else{
						cout<<arvore->percorre->dado<<" teste"<<endl;
						arvore->percorre=arvore->percorre->esquerda;
					}
			}
			if(arvore->percorre->dado > n){


					if(arvore->percorre->direita==NULL){
						cout<<arvore->percorre->dado<<" teste"<<endl;
						novaCelula = new TipoCelula();
						novaCelula->esquerda=NULL;
						novaCelula->direita=NULL;
						novaCelula->dado=n;
						arvore->percorre->direita=novaCelula;
						break;
					}
					else{
						cout<<arvore->percorre->dado<<" teste"<<endl;
						arvore->percorre=arvore->percorre->direita;
					}
			}
		}
	}
	arvore->percorre=arvore->topo;
	arvore->tamanho++;
}

void pesquisaElemento(TipoArvoreBinaria *arvore,int n){
	if(verificaVazia(arvore)){
		cout<<"Elemento Nao Encontrado, Arvore Vazia"<<endl;
	}
	else{
		while(1){
			if(arvore->percorre->dado==n){
				cout<<"Elemento Encontrado"<<endl;
				break;
			}
			else{
				if(arvore->percorre->dado<=n){
					arvore->percorre=arvore->percorre->esquerda;
						if(arvore->percorre==NULL){
							cout<<"Elemento Nao Encontrado"<<endl;
							break;
						}
				}
				else{
					arvore->percorre=arvore->percorre->direita;
						if(arvore->percorre==NULL){
							cout<<"Elemento Nao Encontrado"<<endl;
							break;
						}
				}
			}
		}

	arvore->percorre=arvore->topo;
	}

}

int main(){
int controle=1,n;
TipoArvoreBinaria arvore;
inicializaArvore(&arvore);
char c;
while(controle){
	cin>>c;
	switch(c){
		case 'I':
			cin>>n;
			insere(&arvore,n);
		break;
		case 'S':
			controle=0;
		break;
		case'P':
			cin>>n;
			pesquisaElemento(&arvore,n);
		default:
		break;
	}

}

return 0;
}
