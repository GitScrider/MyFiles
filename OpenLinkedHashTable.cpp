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


typedef struct THEA{
string *vetString;
int contador;
int NCOL,TINS,TCON,TDEL;
}TabelahashEderecamentoAberto;

int hashing(string N,int M){

    hash<string> hash_fn;
    size_t str_hash = hash_fn(N);

    return str_hash%M;
}


void inicializaTHEA(THEA *tabela,int tamanho){
	tabela->vetString = new string[tamanho];
	tabela->contador=0;
	tabela->NCOL=0;
	tabela->TINS=0;
	tabela->TCON=0;
	tabela->TDEL=0;
}


void insereTHEA(THEA *tabela,string str,int M){
	int n;
	n=hashing(str,M);
	if(tabela->vetString[n][0]!=0){
		tabela->NCOL++;
	}
	while(tabela->vetString[n][0]!=0){

		if(n<M-1){
			n++;
		}
		else{
			n=0;
		}
		tabela->contador++;
		if(tabela->contador==M){
			//cout<<"Tabela Cheia"<<endl;
			break;
		}
	}
	if(tabela->contador<M){
		tabela->vetString[n]=str;
		tabela->contador=0;
	}
	else{
		tabela->contador=0;
	}
}

void removeTHEA(THEA *tabela,string str,int M){
	int n;
	n=hashing(str,M);
	while(tabela->vetString[n]!=str){
		if(n<M-1){
			n++;
		}
		else{
			n=0;
		}
		tabela->contador++;
		if(tabela->contador==M){
			//cout<<"Elemento Nao Encontrado"<<endl;
			break;
		}
	}
	if(tabela->contador<M){
		tabela->vetString[n]="";
		tabela->contador=0;
	}
	else{
		tabela->contador=0;
	}

}

void pesquisaTHEA(THEA *tabela,string str,int M){
	int n;
	n=hashing(str,M);
	while(tabela->vetString[n]!=str){
		if(n<M-1){
			n++;
		}
		else{
			n=0;
		}
		tabela->contador++;
		if(tabela->contador==M){
			//cout<<"Elemento Nao Encontrado"<<endl;
			break;
		}
	}
	if(tabela->contador<M){
		//cout<<"Elemento Encontrado"<<endl;
		tabela->contador=0;
	}
	else{
		tabela->contador=0;
	}
}

void listaTHEA(THEA *tabela,int M){
	for(int i=0;i<M;i++){
		cout<<tabela->vetString[i]<<endl;
	}

}

void GravaArquivoTXT(THEA *tabela,int N,int M){
	fstream entrada_dados ("Arquivo.txt",ios::out|ios::app);
	entrada_dados<<"Tamanho da tabela: "<<M<<endl<<"Tamanho da entrada: "<<N<<endl<<"Numero de colisoes na insercao: "<<tabela->NCOL<<endl<<"Tempo medio para inserir um elemento: "<<tabela->TINS/N<<" (nanosegundos)"<<endl<<"Tempo medio para consultar um elemento: "<<tabela->TCON/N<<" (nanosegundos)"<<endl<<"Tempo medio para apagar um elemento: "<<tabela->TDEL/N<<" (nanosegundos)"<<endl;
}


int main(){
ifstream arquivotxt;
THEA thea;
int M[3]={500,1000,5000},N[3]={2000,7000,10000},n,m,i,j,cont=0;
unsigned long int_ns;
auto t1 = high_resolution_clock::now();
auto t2 = high_resolution_clock::now();

string str;



for(i=0;i<3;i++){
	m=M[i];
	for(j=0;j<3;j++){
		n=N[j];
		inicializaTHEA(&thea,m);
		arquivotxt.open("chaves-inserir.txt");
		while(!arquivotxt.eof() && cont<n){
			getline(arquivotxt,str);
			t1 = high_resolution_clock::now();
			insereTHEA(&thea,str,m);
			t2 = high_resolution_clock::now();
			int_ns = static_cast<unsigned long>(duration_cast<nanoseconds>(t2-t1).count());
			thea.TINS=thea.TINS+int_ns;
			cont++;
		}
		arquivotxt.close();
		cont=0;
		arquivotxt.open("chaves-pesquisar.txt");
		while(!arquivotxt.eof() && cont<2000){
			getline(arquivotxt,str);
			t1 = high_resolution_clock::now();
			pesquisaTHEA(&thea,str,m);
			t2 = high_resolution_clock::now();
			int_ns = static_cast<unsigned long>(duration_cast<nanoseconds>(t2-t1).count());
			thea.TCON=thea.TCON+int_ns;
		}
		arquivotxt.close();
		cont=0;
		arquivotxt.open("chaves-apagar.txt");
		while(!arquivotxt.eof() && cont<1000){
			getline(arquivotxt,str);
			t1 = high_resolution_clock::now();
			removeTHEA(&thea,str,m);
			t2 = high_resolution_clock::now();
			int_ns = static_cast<unsigned long>(duration_cast<nanoseconds>(t2-t1).count());
			thea.TDEL=thea.TDEL+int_ns;
		}
		arquivotxt.close();
		cont=0;
		GravaArquivoTXT(&thea,n,m);
	}
}



/*while(controle){
	cin>>c;
	switch(c){
		case 'I':
		cin>>str;
		insereTHEA(&thea,str,M);
		break;
		case 'R':
		cin>>str;
		removeTHEA(&thea,str,M);
		break;
		case 'P':
		cin>>str;
		pesquisaTHEA(&thea,str,M);
		break;
		case 'L':
		listaTHEA(&thea,M);
		break;
		case 'S':
		controle=0;
		break;
	}

}*/

return 0;

}
