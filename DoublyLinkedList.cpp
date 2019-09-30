//Scrider
#include <iostream>
#include <string>
#include <stddef.h>
#include <stdlib.h>


using namespace std;

typedef struct TipoCelula{
  int dado;
  struct TipoCelula *proximo;
  struct TipoCelula *anterior;
} TipoCelula;


typedef struct TipoLista{
	int tamanho;
	TipoCelula *inicio, *fim;

}TipoLista;

void inicializa(TipoLista *lista){
	lista->inicio = new TipoCelula();
	lista->fim = lista->inicio;
	lista->fim->proximo = NULL;
	lista->fim->anterior = NULL;
	lista->tamanho=0;
}



bool verificaVazia(TipoLista *lista){
	if(lista->tamanho==0){
		return true;
	}
	else{
		return false;
	}
}


void inserirFim(TipoLista *lista,int n){
	if(verificaVazia(lista)){
		lista->fim->dado=n;;
	}
	else{
		TipoCelula *novaCelula = new TipoCelula();
		lista->fim->proximo = novaCelula;
		novaCelula->anterior=lista->fim;
		lista->fim =novaCelula;
		lista->fim->dado = n;
		lista->fim->proximo = NULL;

	}

	lista->tamanho++;

}

void inserirInicio(TipoLista *lista, int n){
	if(verificaVazia(lista)){
		lista->inicio->dado=n;

	}
	else{
		TipoCelula *novaCelula = new TipoCelula();
		lista->inicio->anterior=novaCelula;
		novaCelula->proximo=lista->inicio;
		lista->inicio = novaCelula;
		lista->inicio->dado=n;
		lista->inicio->anterior = NULL;



	}

	lista->tamanho++;

}

void removeFim(TipoLista *lista){
	if(verificaVazia(lista)){
		cout<<"Lista Vazia"<<endl;
	}
	else{
		lista->fim = lista->fim->anterior;
      	lista->tamanho--;

	}

}

void removeInicio(TipoLista *lista){
	if(verificaVazia(lista)){
		cout<<"Lista Vazia"<<endl;
	}
	else{
		lista->inicio = lista->inicio->proximo;
      	lista->tamanho--;
	}

}

void pesquisaInicio(TipoLista *lista, int n){
	int i;
	if(verificaVazia(lista)){
		cout<<"Lista Vazia"<<endl;
	}
	else{
		TipoCelula *celula = new TipoCelula();
		celula = lista->inicio;
		for(i=0;i<lista->tamanho;i++){
			if(celula->dado==n){
				cout<<"Encontrado"<<endl;
				return;
			}

		celula=celula->proximo;

		}
			cout << "Nao encontrado" << endl;
	}
}

void pesquisaFim(TipoLista *lista, int n){
	int i;
	if(verificaVazia(lista)){
		cout<<"Lista Vazia"<<endl;
	}
	else{
		TipoCelula *celula =  lista->fim;
		for(i=0;i<lista->tamanho;i++){
			if(celula->dado==n){
				cout<<"Encontrado"<<endl;
				return;
			}

		celula=celula->anterior;

		}

			cout << "Nao encontrado" << endl;

	}
}

void imprimeLista(TipoLista *lista){
	if(verificaVazia(lista)){
		cout<<"Lista Vazia"<<endl;
	}
	else{
		TipoCelula *celula = new TipoCelula();
		celula=lista->inicio;
		for(int i=0;i<lista->tamanho;i++){
			cout<<celula->dado<<" ";
			celula=celula->proximo;
		}
	cout<<endl;
	}

}


void tamanhoLista(TipoLista *lista){
	if(verificaVazia(lista)){
		cout<<"Lista Vazia"<<endl;
	}
	else{
	cout<<lista->tamanho<<endl;
	}
}

void ordenaSelect(TipoLista *lista){
	int aux;
	if(verificaVazia(lista)){
		cout<<"Lista Vazia"<<endl;
	}
	else{

		TipoCelula *indice1, *indice2,*indice3;
		indice1=lista->inicio;
		indice3=lista->inicio;
		for(int i=0;i<lista->tamanho-1;i++){
			indice2=indice3;
			for(int j=i;j<lista->tamanho-1;j++){
				indice1=indice1->proximo;
				if(indice2->dado > indice1->dado){
					indice2=indice1;
					aux=1;

				}
			}
			if(aux==1){
				aux=indice3->dado;
				indice3->dado=indice2->dado;
				indice2->dado=aux;
				aux=0;
			}
		indice3=indice3->proximo;
		indice1=indice3;


		}
	}

}

void ordenaInsert(TipoLista *lista){
	TipoCelula *indice1,*indice2,*indice3;
	int aux;
	indice1=lista->inicio;
	indice2=lista->inicio;
	for(int i=1;i<lista->tamanho;i++){
		indice1=indice1->proximo;
		indice2=indice1;
		for(int j=i;j>0;j--){
			if(indice2->dado < indice2->anterior->dado){
				aux=indice2->dado;
				indice2->dado=indice2->anterior->dado;
				indice2->anterior->dado=aux;
			}
			else{
				break;
			}
			indice2=indice2->anterior;
		}

	}



}

int main(){
int controle=1,n;
char C;

TipoLista lista;


inicializa(&lista);


while(controle){
    cin >> C;

    switch(C){
      case 'E':
		cin>>n;
		inserirInicio(&lista,n);

        break;
      case 'e':
		removeInicio(&lista);
        break;
      case 'D':
		cin>>n;
		inserirFim(&lista,n);
        break;
      case 'd':
 		removeFim(&lista);
        break;
      case 'P':
		cin>>n;
		pesquisaInicio(&lista,n);
        break;
      case 'Q':
		cin>>n;
		pesquisaFim(&lista,n);
		break;
      case 'I':
		imprimeLista(&lista);
		break;
      case 'T':
		tamanhoLista(&lista);
		break;
      case 'O':
		ordenaInsert(&lista);
		break;
      case 'S':

		controle=0;

		break;
      default:
        break;
    }



}

return 0;

}
