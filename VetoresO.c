// Cria um vetor com o tamanho indicado pelo usuario e preenche-o com numeros aleatorios
// E o usuario pode escolher qual metodo será utilizado para ordenar o vetor
#include <stdio.h>
#include <string.h>
#include<stdbool.h>
#include <stdlib.h>
#include <time.h> //Obtem a hora atual do computador

void imprimeVetor(int *V, int tam);
void selectionSort(int *V, int tam);
void insertionSort(int *V, int tam);
void bubbleSort(int *V, int tam);
void merge1(int *V, int inicio, int meio, int fim);
void mergeSort(int *V,int inicio, int fim);
int particao(int *V, int p, int r);
void quickSort(int *V, int p, int r);


void main(){
    int i=0, tam=0, *V, op=0;

    printf("Digite o tamanho do vetor: ");
    scanf("%d",&tam);

    V = (int *) malloc (tam * sizeof(int)); //Cria um vetor de tamanho indicado pelo usuario

    srand(time(NULL)); //Altera a semente da função rand()
    for(i=0; i<tam; i++){
        V[i] = rand() % tam + 1; //Preenche o vetor com numeros aleatorios de 1 à tam
    }

     printf("\nVetor Gerado: [ ");
    for (int i = 0; i < tam; i++){
        printf("%d ", V[i]);
    }
    printf(" ]\n");


    printf("--------------------------------------------------------\n");
    printf("Opções de Metodos de ordenação: \n");
    printf("--------------------------------------------------------\n");
    printf("[1] Selection Sort \n[2] Inserction Sort \n[3] Bubble Sort \n[4] Merge Sort \n[5] Quick Sort \n[0] Sair\n");
    printf("--------------------------------------------------------\n");
    printf("Digite a opção: ");
    scanf("%d",&op);
    
    switch(op){
        case 1:
            selectionSort(V,tam);
            break;
        case 2:
            insertionSort(V,tam);
            break;
        case 3:
            bubbleSort(V,tam);
            break;
        case 4:
            mergeSort(V,0,tam-1);
            break;
        case 5:
            quickSort(V,0,tam);
            break;
        default:
            break;
    }
    imprimeVetor(V,tam);
    free(V);

}

void imprimeVetor(int *V, int tam){
    printf("--------------------------------------------------------\n");
    printf("\nVetor Ordenado: [ ");
    for (int i = 0; i < tam; i++){
        printf("%d ", V[i]);
    }
    printf(" ]\n");
     printf("--------------------------------------------------------\n");
}


void selectionSort(int *V, int tam){ // O(n²) no pior dos casos que é o vetor estar em ordem decrescente
    int i=0, j=0, aux=0, min=0;
    for(i=0; i<tam-1; i++){
        min = i;
        for(j=i+1; j<tam; j++){ //Percorre o vetor procurando o menor elemento
            if(V[min]>V[j]){    // Ao fim da primeira iteração o menor elemento vai estar na primeira posição
                min=j;
            }
        }
        //Troca as posições
        aux=V[min];
        V[min]=V[i];
        V[i]=aux;
    }
}

void insertionSort(int *V, int tam){ //O(N)
    int i=0, j=0, aux=0;
    for(i=1; i<tam; i++){
        aux=V[i];
        for(j=i-1; j>-1 & V[j]>aux; j--){   //Se o anterior for maior que o atual faz a troca
            V[j+1]=V[j];                    //O Vetor é ordenado do primeiro para o ultimo
                                            
        }
        V[j+1]=aux;
    }
}

void bubbleSort(int *V, int tam){//O(n²) no pior dos casos que é quando o vetor estar em ordem decrescente
    int i=0, j=0, aux=0;

    for(i=tam; i>-1; i--){
        for(j=1;j<i; j++){
            if(V[j-1]>V[j]){//Troca as posições se o anterior é maior que o atual( de 1 a tam)
                aux=V[j-1]; // O Vetor é ordenado do ultimo para o primeiro
                V[j-1]=V[j];// Ao fim da primeira iteração o maior elemento vai estar na ultima posição
                V[j]=aux;
            }
        }
    }
}


void merge (int *V, int inicio, int meio, int fim) {
  int tamanho = fim - inicio + 1;
  int parte1 = inicio;
  bool fimParte1 = false;
  int parte2 = meio + 1;
  bool fimParte2 = false;
  
  int *temp = malloc (tamanho * sizeof(int));

  for (int i = 0; i < tamanho; i++) {
    if (!fimParte1 && !fimParte2) {
      if (V[parte1] < V[parte2]) {
        temp[i] = V[parte1++];
      } else {
        temp[i] = V[parte2++];
      }

      if (parte1 > meio) { fimParte1 = true; }
      if (parte2 > fim)  { fimParte2 = true; }
    } else {
      if (!fimParte1) { temp[i] = V[parte1++]; }
      else { temp[i] = V[parte2++]; }
    }
  }

  for (int j = 0, k = inicio; j < tamanho; j++, k++) {
    V[k] = temp[j];
  }

  free(temp);
  temp = NULL;
}


void mergeSort(int *V,int inicio, int fim){
    int meio = 0;

    if (inicio < fim){
        meio = (inicio + fim)/2;

        mergeSort(V, inicio, meio);

        mergeSort(V, meio+1, fim);

        merge(V, inicio, meio, fim);
    }
}

int particao(int *V, int p, int r){
    int x=0, i=0, j=0, aux=0;
    x = V[r];
    i = p-1;
    for ( j = p; j < r-1; j++){
        if (V[j]<=x){
            i = i+1;
            aux = V[i];
            V[i] = V[j];
            V[j] = aux;
        }
        
    }
    aux = V[i+1];
    V[i+1] = V[r];
    V[r] = aux;
    
}

void quickSort(int *V, int p, int r){
    int q=0;
    if (p < r){
        q = particao(V,p,r);
        quickSort(V,p,q-1);
        quickSort(V,q+1,r);
    }
}