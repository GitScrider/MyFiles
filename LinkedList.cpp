#include <iostream>
#include <string>
#include <stddef.h>
#include <stdlib.h>


using namespace std;

typedef struct TipoCelula{
  int inteiro;
  float real;
  struct TipoCelula *proximo;
} TipoCelula;



typedef struct TipoFila{
	int tamanho;
	struct TipoCelula *frente, *tras;

}TipoFila;

void inicializa(TipoFila *fila){
	TipoCelula *novaCelula = new TipoCelula();
	fila->tras=novaCelula;
	fila->frente=fila->tras;
	fila->tamanho=0;
	fila->tras->proximo=NULL;

}

bool verificaVazia(TipoFila *fila){
	if(fila->frente == fila->tras){
		return true;
	}
	else{
		return false;
	}
}

void insere(TipoFila *fila, int n,float r){
	TipoCelula *novaCelula = new TipoCelula();
	fila->tras->proximo= novaCelula;
	fila->tras->proximo->inteiro = n;
	fila->tras->proximo->real = r;
	fila->tras = fila->tras->proximo;
	fila->tras->proximo = NULL;
	fila->tamanho++;


}

void remove(TipoFila *fila){
	if(verificaVazia(fila)){
		cout << "Fila vazia" << endl;
	}

	else{

		fila->frente=fila->frente->proximo;
		fila->tamanho--;
	}

}

void mostraFrente(TipoFila *fila){
	if(verificaVazia(fila)){
		cout << "Fila vazia" << endl;
	}
	else{
		cout << fila->frente->proximo->inteiro << " " << fila->frente->proximo->real<< endl;

	}
}


void informaTamanho(TipoFila *fila){
	cout << fila->tamanho << endl;
}


int main(void){
int n, controle=1;
float r;
char c;

TipoFila fila;

inicializa(&fila);

while(controle){
	cin>>c;
	switch(c){

		case 'E':
			cin>>n;
			cin>>r;
			insere(&fila,n,r);

		break;

		case 'R':
			remove(&fila);

		break;

		case 'I':
			mostraFrente(&fila);
		break;

		case 'T':
			informaTamanho(&fila);

		break;

		case 'S':
			controle=0;
		break;

	}
}


return 0;

}


S
