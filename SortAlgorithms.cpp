#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

void imprimeVetor(int*,int);

void Select( int v[],int tamanho){
	 int indice,aux,n;
	for( int i=0;i<tamanho-1;i++){
		n=v[i];
		for( int j=i+1;j<tamanho;j++){
			if(n>v[j]){
				n=v[j];
				indice=j;
				aux=1;
			}
		}
		if(aux==1){
			aux=v[i];
			v[i]=v[indice];
			v[indice]=aux;
			aux=0;
		}
	}

}

void Insert(int v[],int tamanho){
	int aux;
	for(int i=1;i<tamanho;i++){
		for(int j=i;j>0;j--){
			if(v[j]<v[j-1]){
				aux=v[j];
				v[j]=v[j-1];
				v[j-1]=aux;
			}
			else{
				break;
			}
		}

	}
}

void ShellAlternativo(int vet[],int tamanho){
    int i , j , x;
    int h = 1;
    while(h < tamanho) {
        h = 3*h+1;
    }
    while ( h != 1) {
        h /= 3;
        for(i = h; i < tamanho; i++) {
	    	x = vet[i];
            	j = i - h;
            while (j >= 0 && x < vet[j]) {
                vet [j + h] = vet[j];
                j -= h;
            }
            vet [j + h] = x;
        }
    }
}

//Nao funciona corretamente, tempo de execucao e extremamente grande e desproporcinal//
void Shell(int v[],int tamanho){  //meu jeito
	int h=tamanho,aux=1;
	while(h>1 || aux){
		h=(h+1)/2;
		aux=0;
		for(int i=0;i<tamanho-h;i++){
			imprimeVetor(v,tamanho);
			if(v[i]>v[i+h]){
				aux=v[i];
				v[i]=v[i+h];
				v[i+h]=aux;
				aux=1;
			}
		}
	}
}

void mergeOrdena(int v[], int inicio, int meio, int fim) {
	int i, j, k, *v_aux;

	//aloca vetor que recebera a juncao ordenada
	v_aux = new int[fim - inicio + 1];

	i = inicio; j = meio + 1; k = 0;

	//junta os dados de forma ordenada em v_aux
	while(i <= meio && j <= fim)
		if(v[i] < v[j])
			v_aux[k++] = v[i++];
		else
			v_aux[k++] = v[j++];
	//dados restantes
	while(i <= meio)
		v_aux[k++] = v[i++];
	while(j <= fim)
		v_aux[k++] = v[j++];

	//copia dos dados ordenados para o vetor original
	for(i = inicio; i <= fim; i++)
		v[i] = v_aux[i - inicio ];

	delete[] v_aux;
}
void Merge(int v[], int inicio, int fim){

    if (inicio < fim) {

        int meio = (inicio+fim)/2;
        Merge(v, inicio, meio);
        Merge(v, meio+1, fim);
        mergeOrdena(v, inicio, meio, fim);
    }
}


void Quick1(int v[],int esquerda,int direita){
	int i=esquerda,j=direita,aux,pivo;
	pivo=v[(i+j)/2];
	while(i<=j){
		while(v[i]<pivo){
			i++;
		}
		while(v[j]>pivo){
			j--;
		}
		if(i<=j){
			aux=v[i];
			v[i]=v[j];
			v[j]=aux;
			j--;
			i++;
		}
	}
	if(esquerda<j){
		Quick1(v,esquerda,j);
	}
	if(direita>i){
		Quick1(v,i,direita);
	}
}


int SelecionaPivo(int n1, int n2, int n3){
int v[3];
v[0]=n1;v[1]=n2;v[2]=n3;
Insert(v,3);
return v[1];
}

void Quick2(int v[],int esquerda,int direita){
	int i=esquerda,j=direita,aux,pivo;
	pivo=SelecionaPivo(v[i],v[(i+j)/2],v[j]);
	while(i<=j){
		while(v[i]<pivo){
			i++;
		}
		while(v[j]>pivo){
			j--;
		}
		if(i<=j){
			aux=v[i];
			v[i]=v[j];
			v[j]=aux;
			j--;
			i++;
		}
	}
	if(esquerda<j){
		Quick1(v,esquerda,j);
	}
	if(direita>i){
		Quick1(v,i,direita);
	}
}

void QuickInsert(int v[],int esquerda,int direita){
	int i=esquerda,j=direita,aux,pivo;
		pivo=SelecionaPivo(v[i],v[(i+j)/2],v[j]);
	if(j-i>50){
		while(i<=j){
			while(v[i]<pivo){
				i++;
			}
			while(v[j]>pivo){
				j--;
			}
			if(i<=j){
				aux=v[i];
				v[i]=v[j];
				v[j]=aux;
				j--;
				i++;
			}
		}

			if(esquerda<j){
				Quick1(v,esquerda,j);
			}
			if(direita>i){
				Quick1(v,i,direita);
			}
	}
	else{
		Insert(v,j-i+1);
	}
}

void imprimeVetor(int v[],int tamanho){
	for(int i=0;i<tamanho;i++){
			cout<<v[i]<<" ";
	}
	cout<<endl;
}

void GravaArquivoCSV(string algoritmo,int tamanho,int tempo){
	fstream entrada_dados ("Arquivo.csv",ios::out|ios::app);
	entrada_dados<<algoritmo<<","<<tamanho<<","<<tempo<<endl;
}

void preencheVetor(int v[],int tamanho){
	mt19937 rng;
	uniform_int_distribution<int> unif_int_d(0, 20000);
	rng.seed(high_resolution_clock::now().time_since_epoch().count());
	for( int i = 0; i < tamanho; i++){
		v[i] = unif_int_d(rng);
	}
}

void vetorCapturaTempo(int *v){
int vetor[7]={1000,2000,5000,10000,50000,100000,500000};
string algoritmo[7]={"Selection","Insertion","ShellSort","MergeSort","QuickSort1","QuickSort2","QuickInsert Sort"};
unsigned long int_ms;
int i,j;
auto t1 = high_resolution_clock::now();
auto t2 = high_resolution_clock::now();
	fstream entrada_dados ("Arquivo.csv",ios::out|ios::app);
	entrada_dados<<"Algoritmo,Dimensao,Tempo"<<endl;
	for(i=0;i<7;i++){
		v=new int[vetor[i]];
		for(j=0;j<30;j++){
			preencheVetor(v,vetor[i]);
			t1 = high_resolution_clock::now();
				Select(v,vetor[i]);
			t2 = high_resolution_clock::now();
			int_ms = static_cast<unsigned long>(duration_cast<milliseconds>(t2-t1).count());
			GravaArquivoCSV(algoritmo[0],vetor[i],int_ms);

		}
		delete(v);
	}
	for(i=0;i<7;i++){
		v=new int[vetor[i]];
		for(j=0;j<30;j++){
			preencheVetor(v,vetor[i]);
			t1 = high_resolution_clock::now();
				Insert(v,vetor[i]);
			t2 = high_resolution_clock::now();
			int_ms = static_cast<unsigned long>(duration_cast<milliseconds>(t2-t1).count());
			GravaArquivoCSV(algoritmo[1],vetor[i],int_ms);

		}
		delete(v);
	}
	for(i=0;i<7;i++){
		v=new int[vetor[i]];
		for(j=0;j<30;j++){
			preencheVetor(v,vetor[i]);
			t1 = high_resolution_clock::now();
				ShellAlternativo(v,vetor[i]);
			t2 = high_resolution_clock::now();
			int_ms = static_cast<unsigned long>(duration_cast<milliseconds>(t2-t1).count());
			GravaArquivoCSV(algoritmo[2],vetor[i],int_ms);

		}
		delete(v);
	}
	for(i=0;i<7;i++){
		v=new int[vetor[i]];
		for(j=0;j<30;j++){
			preencheVetor(v,vetor[i]);
			t1 = high_resolution_clock::now();
				Merge(v,0,vetor[i]-1);
			t2 = high_resolution_clock::now();
			int_ms = static_cast<unsigned long>(duration_cast<milliseconds>(t2-t1).count());
			GravaArquivoCSV(algoritmo[3],vetor[i],int_ms);

		}
		delete(v);
	}
	for(i=0;i<7;i++){
		v=new int[vetor[i]];
		for(j=0;j<30;j++){
			preencheVetor(v,vetor[i]);
			t1 = high_resolution_clock::now();
				Quick1(v,0,vetor[i]-1);
			t2 = high_resolution_clock::now();
			int_ms = static_cast<unsigned long>(duration_cast<milliseconds>(t2-t1).count());
			GravaArquivoCSV(algoritmo[4],vetor[i],int_ms);

		}
		delete(v);
	}
	for(i=0;i<7;i++){
		v=new int[vetor[i]];
		for(j=0;j<30;j++){
			preencheVetor(v,vetor[i]);
			t1 = high_resolution_clock::now();
				Quick2(v,0,vetor[i]-1);
			t2 = high_resolution_clock::now();
			int_ms = static_cast<unsigned long>(duration_cast<milliseconds>(t2-t1).count());
			GravaArquivoCSV(algoritmo[5],vetor[i],int_ms);

		}
		delete(v);
	}
	for(i=0;i<7;i++){
		v=new int[vetor[i]];
		for(j=0;j<30;j++){
			preencheVetor(v,vetor[i]);
			t1 = high_resolution_clock::now();
				QuickInsert(v,0,vetor[i]-1);
			t2 = high_resolution_clock::now();
			int_ms = static_cast<unsigned long>(duration_cast<milliseconds>(t2-t1).count());
			GravaArquivoCSV(algoritmo[6],vetor[i],int_ms);

		}
		delete(v);
	}
}


void preencheAlternativo(int v[], int tamanho){
	int j=tamanho;
	for(int i=0;i<tamanho;i++){
		v[i]=j;
		j--;
	}
}

int main(){
int *v=nullptr;

vetorCapturaTempo(v);


return 0;
}
