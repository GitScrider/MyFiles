#include <iostream>
#include <stddef.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <functional>
#include <fstream>
#include <random>
#include <chrono>



using namespace std;
using namespace std::chrono;

typedef struct CelulaAB{
string s;
CelulaAB *esquerda,*direita;
}CelulaArvoreBinaria;

typedef struct ArvoreBinaria{
int tamanho;
CelulaAB *raiz;
}ArvoreBinaria;

typedef struct THAB{
int NCOL,TINS,TCON,TDEL;
ArvoreBinaria *vetArvoreBinaria;
}TabelaHashArvoreBinaria;


int hashing(string N,int M){
    hash<string> hash_fn;
    size_t str_hash = hash_fn(N);
    return str_hash%M;
}

bool verificaVaziaTHAB(THAB *tabela,int n){
	if(tabela->vetArvoreBinaria[n].tamanho==0){
		return true;
	}
	else{
		return false;
	}
}

void inicializaTHAB(THAB *tabela,int tamanho){
	tabela->vetArvoreBinaria = new ArvoreBinaria[tamanho];
	for(int i=0;i<tamanho;i++){
		tabela->vetArvoreBinaria[i].raiz=NULL;
		tabela->vetArvoreBinaria[i].tamanho=0;
	}
	tabela->NCOL=0;
	tabela->TINS=0;
	tabela->TCON=0;
	tabela->TDEL=0;
}

void insereTHAB(THAB *tabela,string str,int M){
	int n;
	n=hashing(str,M);
	if(verificaVaziaTHAB(tabela,n)){
		CelulaAB *novaCelula= new CelulaAB();
		tabela->vetArvoreBinaria[n].raiz=novaCelula;
		tabela->vetArvoreBinaria[n].raiz->direita=NULL;
		tabela->vetArvoreBinaria[n].raiz->esquerda=NULL;
		tabela->vetArvoreBinaria[n].raiz->s=str;
		tabela->vetArvoreBinaria[n].tamanho++;
	}
	else{
		CelulaAB *percorreArvore,*indicaRaiz;
		percorreArvore=tabela->vetArvoreBinaria[n].raiz;
		indicaRaiz=tabela->vetArvoreBinaria[n].raiz;
		while(1){
			if(percorreArvore->s<str){
				if(percorreArvore->esquerda==NULL){

				CelulaAB *novaCelula= new CelulaAB();
				novaCelula->esquerda=NULL;
				novaCelula->direita=NULL;
				novaCelula->s=str;
				tabela->vetArvoreBinaria[n].raiz=percorreArvore;
				tabela->vetArvoreBinaria[n].raiz->esquerda=novaCelula;
				tabela->vetArvoreBinaria[n].raiz=indicaRaiz;
				break;
				}
				else{
				percorreArvore=percorreArvore->esquerda;
				}

			}
			if(percorreArvore->s>str){
				if(percorreArvore->direita==NULL){

				CelulaAB *novaCelula= new CelulaAB();
				novaCelula->esquerda=NULL;
				novaCelula->direita=NULL;
				novaCelula->s=str;
				tabela->vetArvoreBinaria[n].raiz=percorreArvore;
				tabela->vetArvoreBinaria[n].raiz->direita=novaCelula;
				tabela->vetArvoreBinaria[n].raiz=indicaRaiz;
				break;
				}
				else{
				percorreArvore=percorreArvore->direita;
				}
			}
		}
		tabela->vetArvoreBinaria[n].tamanho++;
		tabela->NCOL++;
	}
}

/*void removeTHAB(THAB *tabela,string str){
	int n,controle=0;
	n=hashing(str,TAM);
	if(verificaVaziaTHAB(tabela,n)){
		cout<<"Elemento Nao Encontrado Arvore Vazia"<<endl;
	}
	else{
		CelulaAB *percorreArvore,*indicaRaiz;
		indicaRaiz=tabela->vetArvoreBinaria[n].raiz;
		percorreArvore=tabela->vetArvoreBinaria[n].raiz;
		while(1){
			if(percorreArvore->s==str){
				controle=1;
				break;
			}
			else{
				if(percorreArvore->s<str){
					percorreArvore=percorreArvore->esquerda;
						if(percorreArvore==NULL){
							cout<<"Elemento Nao Encontrado"<<endl;
							break;
						}
				}
				else{
					percorreArvore=percorreArvore->direita;
						if(percorreArvore==NULL){
							cout<<"Elemento Nao Encontrado"<<endl;
							break;
						}
				}
			}
		}
		if(percorreArvore->esquerda==NULL && percorreArvore->direita==NULL && controle){
			tabela->vetArvoreBinaria[n].raiz=percorreArvore;
			tabela->vetArvoreBinaria[n].raiz=NULL;
			tabela->vetArvoreBinaria[n].raiz=indicaRaiz;
		}


	}



}*/

void pesquisaTHAB(THAB *tabela, string str,int M){
	int n;
	n=hashing(str,M);
	if(verificaVaziaTHAB(tabela,n)){
		//cout<<"Elemento Nao Encontrado Arvore Vazia"<<endl;
	}
	else{
		CelulaAB *percorreArvore;
		percorreArvore=tabela->vetArvoreBinaria[n].raiz;
		while(1){
			if(percorreArvore->s==str){
				//cout<<"Elemento Encontrado"<<endl;
				break;
			}
			else{
				if(percorreArvore->s<str){
					percorreArvore=percorreArvore->esquerda;
						if(percorreArvore==NULL){
							//cout<<"Elemento Nao Encontrado"<<endl;
							break;
						}
				}
				else{
					percorreArvore=percorreArvore->direita;
						if(percorreArvore==NULL){
							//cout<<"Elemento Nao Encontrado"<<endl;
							break;
						}
				}
			}
		}

	}

}

void GravaArquivoTXT(THAB *tabela,int N,int M){
	fstream entrada_dados ("Arquivo.txt",ios::out|ios::app);
	entrada_dados<<"Tamanho da tabela: "<<M<<endl<<"Tamanho da entrada: "<<N<<endl<<"Numero de colisoes na insercao: "<<tabela->NCOL<<endl<<"Tempo medio para inserir um elemento: "<<tabela->TINS/N<<" (nanosegundos)"<<endl<<"Tempo medio para consultar um elemento: "<<tabela->TCON/N<<" (nanosegundos)"<<endl<<"Tempo medio para apagar um elemento: Nao implementado"<<endl;
}

int main(){
ifstream arquivotxt;
THAB thab;
int M[3]={500,1000,5000},N[3]={2000,7000,10000},n,m,i,j,cont=0;
unsigned long int_ns;
auto t1 = high_resolution_clock::now();
auto t2 = high_resolution_clock::now();

string str;



for(i=0;i<3;i++){
	m=M[i];
	for(j=0;j<3;j++){
		n=N[j];
		inicializaTHAB(&thab,m);
		arquivotxt.open("chaves-inserir.txt");
		while(!arquivotxt.eof() && cont<n){
			getline(arquivotxt,str);
			t1 = high_resolution_clock::now();
			insereTHAB(&thab,str,m);
			t2 = high_resolution_clock::now();
			int_ns = static_cast<unsigned long>(duration_cast<nanoseconds>(t2-t1).count());
			thab.TINS=thab.TINS+int_ns;
			cont++;
		}
		arquivotxt.close();
		cont=0;
		arquivotxt.open("chaves-pesquisar.txt");
		while(!arquivotxt.eof() && cont<2000){
			getline(arquivotxt,str);
			t1 = high_resolution_clock::now();
			pesquisaTHAB(&thab,str,m);
			t2 = high_resolution_clock::now();
			int_ns = static_cast<unsigned long>(duration_cast<nanoseconds>(t2-t1).count());
			thab.TCON=thab.TCON+int_ns;
		}
		arquivotxt.close();
		cont=0;
		GravaArquivoTXT(&thab,n,m);
	}
}



/*while(controle){
	cin>>c;
	switch(c){
		case 'I':
		cin>>str;
		insereTHAB(&thab,str);
		break;
		case 'R':
		cin>>str;
		removeTHAB(&thab,str);
		break;
		case 'P':
		cin>>str;
		pesquisaTHAB(&thab,str);
		break;
		case 'S':
		controle=0;
		break;
		default:
		break;
	}

}*/

}
