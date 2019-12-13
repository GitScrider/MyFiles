#include <iostream>
#include <string>
#include <stddef.h>
#include <stdlib.h>


using namespace std;

typedef struct TipoCelula{
  int numero;
  string caracter;
  struct TipoCelula *proximo;
} TipoCelula;



typedef struct TipoPilha{
	int tamanho;
	struct TipoCelula *base, *topo;

}TipoPilha;

void inicializa(TipoPilha *pilha){
	TipoCelula *novaCelula = new TipoCelula();
	pilha->base=novaCelula;
	pilha->topo=pilha->base;
	pilha->tamanho=0;
	pilha->topo->proximo=NULL;

}

bool verificaVazia(TipoPilha *pilha){
	if(pilha->base == pilha->topo){
		return true;
	}
	else{
		return false;
	}
}

void empilha(TipoPilha *pilha, int n,string s){
	TipoCelula *novaCelula = new TipoCelula();
	pilha->topo->numero=n;
	pilha->topo->caracter=s;
	novaCelula->proximo=pilha->topo;
	pilha->topo=novaCelula;
	pilha->tamanho++;


}

void desempilha(TipoPilha *pilha){
	if(verificaVazia(pilha)){
		cout << "Pilha vazia" << endl;
	}
	else{
		pilha->topo=pilha->topo->proximo;
		pilha->tamanho--;
	}

}

void imprimeElemento(TipoPilha *pilha){
	if(verificaVazia(pilha)){
		cout << "Pilha vazia" << endl;
	}
	else{
		cout << pilha->topo->proximo->numero << " " << pilha->topo->proximo->caracter << endl;

	}
}


void informaTamanho(TipoPilha *pilha){
	cout << pilha->tamanho << endl;
}


int main(void){
int n, controle=1;
char c;
string s;

TipoPilha pilha;

inicializa(&pilha);

while(controle){
	cin>>c;
	switch(c){

		case 'E':
			cin>>n;
			cin>>s;
			empilha(&pilha,n,s);

		break;

		case 'D':
			desempilha(&pilha);

		break;

		case 'I':
			imprimeElemento(&pilha);
		break;

		case 'T':
			informaTamanho(&pilha);

		break;

		case 'S':
			controle=0;
		break;

	}
}

return 0;
}
