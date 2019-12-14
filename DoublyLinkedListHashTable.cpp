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

typedef struct CelulaLE{
string s;
CelulaLE *proximo;
}CelulaListaEncadeada;

typedef struct ListaEncadeada{
int Manho;
CelulaLE *frente,*tras;
}ListaEncadeada;

typedef struct THLE{
int NCOL,TINS,TCON,TDEL;
ListaEncadeada *vetListaEncadeada;
}TabelaHashListaEncadeada;

int hashing(string N,int M){

    hash<string> hash_fn;
    size_t str_hash = hash_fn(N);

    return str_hash%M;
}

bool verificaVaziaTHLE(THLE *tabela,int n){
	if(tabela->vetListaEncadeada[n].Manho==0){
		return true;
	}
	else{
		return false;
	}
}

void inicializaTHLE(THLE *tabela,int tamanho){
	tabela->vetListaEncadeada = new ListaEncadeada[tamanho];
	for(int i=0;i<tamanho;i++){
		tabela->vetListaEncadeada[i].frente=NULL;
		tabela->vetListaEncadeada[i].tras=NULL;
		tabela->vetListaEncadeada[i].Manho=0;
	}
	tabela->NCOL=0;
	tabela->TINS=0;
	tabela->TCON=0;
	tabela->TDEL=0;
}

void insereTHLE(THLE *tabela,string str,int M){
	int n;
	n=hashing(str,M);
	if(verificaVaziaTHLE(tabela,n)){
		CelulaLE *novaCelula= new CelulaLE();
		tabela->vetListaEncadeada[n].tras=novaCelula;
		tabela->vetListaEncadeada[n].frente=novaCelula;
		tabela->vetListaEncadeada[n].tras->proximo=NULL;
		tabela->vetListaEncadeada[n].tras->s=str;
		tabela->vetListaEncadeada[n].Manho++;
	}
	else{
		CelulaLE *novaCelula= new CelulaLE();
		tabela->vetListaEncadeada[n].tras->proximo=novaCelula;
		tabela->vetListaEncadeada[n].tras=novaCelula;
		tabela->vetListaEncadeada[n].tras->s=str;
		tabela->vetListaEncadeada[n].tras->proximo=NULL;
		tabela->vetListaEncadeada[n].Manho++;
		tabela->NCOL++;
	}

}

void removeTHLE(THLE *tabela,string str,int M){
	int n;
	n=hashing(str,M);
	if(verificaVaziaTHLE(tabela,n)){
		//cout<<"Elemento Nao Encontrado Lista Vazia"<<endl;
	}
	else{
		if(tabela->vetListaEncadeada[n].frente->s==str){
			tabela->vetListaEncadeada[n].frente=tabela->vetListaEncadeada[n].frente->proximo;
			tabela->vetListaEncadeada[n].Manho--;
		}
		else{

			CelulaLE *percorreLista1,*percorreLista2,*indicaFrente;
			indicaFrente=tabela->vetListaEncadeada[n].frente;
			percorreLista1=tabela->vetListaEncadeada[n].frente;
			percorreLista2=tabela->vetListaEncadeada[n].frente->proximo;
			while(percorreLista2!=NULL){
				if(percorreLista2->s==str){
					tabela->vetListaEncadeada[n].frente=percorreLista1;
					percorreLista2=percorreLista2->proximo;
					tabela->vetListaEncadeada[n].frente->proximo=percorreLista2;
					tabela->vetListaEncadeada[n].frente=indicaFrente;
					tabela->vetListaEncadeada[n].Manho--;
					break;
				}
				else{
					percorreLista1=percorreLista2;
					percorreLista2=percorreLista2->proximo;
				}
			}
		}
	}
}

void pesquisaTHLE(THLE *tabela,string str,int M){
	int n,cont=0;
	n=hashing(str,M);
	CelulaLE *percorreLista;
	percorreLista=tabela->vetListaEncadeada[n].frente;
	while(percorreLista!=NULL){
		if(percorreLista->s==str){
			//cout<<"Elemento Encontrado"<<endl;
			break;
		}
		cont++;
		percorreLista=percorreLista->proximo;
	}
	if(cont==tabela->vetListaEncadeada[n].Manho){
		//cout<<"Elemento Nao Econtrado"<<endl;
	}
}

void listaTHLE(THLE *tabela, int M){
	CelulaLE *percorreLista;
	for(int i=0;i<M;i++){
		cout<<"Lista "<<i<<": ";
		percorreLista=tabela->vetListaEncadeada[i].frente;
		while(percorreLista!=NULL){
			cout<<percorreLista->s<<" ";
			percorreLista=percorreLista->proximo;
		}
		cout<<endl;
	}
}


void GravaArquivoTXT(THLE *tabela,int N,int M){
	fstream entrada_dados ("Arquivo.txt",ios::out|ios::app);
	entrada_dados<<"Tamanho da tabela: "<<M<<endl<<"Tamanho da entrada: "<<N<<endl<<"Numero de colisoes na insercao: "<<tabela->NCOL<<endl<<"Tempo medio para inserir um elemento: "<<tabela->TINS/N<<" (nanosegundos)"<<endl<<"Tempo medio para consultar um elemento: "<<tabela->TCON/N<<" (nanosegundos)"<<endl<<"Tempo medio para apagar um elemento: "<<tabela->TDEL/N<<" (nanosegundos)"<<endl;
}

int main(){
ifstream arquivotxt;
THLE thle;
int M[3]={500,1000,5000},N[3]={2000,7000,10000},n,m,i,j,cont=0;
string str;
unsigned long int_ns;
auto t1 = high_resolution_clock::now();
auto t2 = high_resolution_clock::now();



for(i=0;i<3;i++){
	m=M[i];
	for(j=0;j<3;j++){
		n=N[j];
		inicializaTHLE(&thle,m);
		arquivotxt.open("chaves-inserir.txt");
		while(!arquivotxt.eof() && cont<n){
			getline(arquivotxt,str);
			t1 = high_resolution_clock::now();
			insereTHLE(&thle,str,m);
			t2 = high_resolution_clock::now();
			int_ns = static_cast<unsigned long>(duration_cast<nanoseconds>(t2-t1).count());
			thle.TINS=thle.TINS+int_ns;
			cont++;
		}
		arquivotxt.close();
		cont=0;
		arquivotxt.open("chaves-pesquisar.txt");
		while(!arquivotxt.eof() && cont<2000){
			getline(arquivotxt,str);
			t1 = high_resolution_clock::now();
			pesquisaTHLE(&thle,str,m);
			t2 = high_resolution_clock::now();
			int_ns = static_cast<unsigned long>(duration_cast<nanoseconds>(t2-t1).count());
			thle.TCON=thle.TCON+int_ns;
		}
		arquivotxt.close();
		cont=0;
		arquivotxt.open("chaves-apagar.txt");
		while(!arquivotxt.eof() && cont<1000){
			getline(arquivotxt,str);
			t1 = high_resolution_clock::now();
			removeTHLE(&thle,str,m);
			t2 = high_resolution_clock::now();
			int_ns = static_cast<unsigned long>(duration_cast<nanoseconds>(t2-t1).count());
			thle.TDEL=thle.TDEL+int_ns;
		}
		arquivotxt.close();
		cont=0;
		GravaArquivoTXT(&thle,n,m);
	}
}


/*while(controle){
	cin>>c;
	switch(c){
		case 'I':
		cin>>str;
		insereTHLE(&thle,str);
		break;
		case 'R':
		cin>>str;
		removeTHLE(&thle,str);
		break;
		case 'P':
		cin>>str;
		pesquisaTHLE(&thle,str);
		break;
		case 'L':
		listaTHLE(&thle);
		break;
		case 'S':
		controle=0;
		break;
		default:
		break;
	}

}*/

return 0;

}
