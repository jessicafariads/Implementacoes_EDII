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
        V[i] = rand() % 10 + 1; //Preenche o vetor com numeros aleatorios de 1 à 10
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
            quickSort(V,0,tam-1);
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


void merge (int *V, int inicio, int meio, int fim) { // Função auxiliar que ordena os subvetores
  int tamanho = fim - inicio + 1; // O vetor tem peli menos uma posição
  int parte1 = inicio;
  bool fimParte1 = false;
  int parte2 = meio + 1;
  bool fimParte2 = false;
  
  int *temp = malloc (tamanho * sizeof(int)); // Aloca memoria para vetor auxiliar

  for (int i = 0; i < tamanho; i++) {
    if (!fimParte1 && !fimParte2) {
      if (V[parte1] < V[parte2]) {
        temp[i] = V[parte1++];
      } else {
        temp[i] = V[parte2++];
      }

      if (parte1 > meio) { fimParte1 = true; } // A primeira parte do vetor acabou
      if (parte2 > fim)  { fimParte2 = true; } // A segunda parte do vetor acabou
    } else {
      if (!fimParte1) { temp[i] = V[parte1++]; } // A segunda parte do vetor acabou então copiamos a primeira parte do vetor pro auxiliar
      else { temp[i] = V[parte2++]; }           // A primeira parte do vetor acabou então copiamos a segunda parte do vetor pro auxiliar                 
    }
  }

  for (int j = 0, k = inicio; j < tamanho; j++, k++) {
    V[k] = temp[j]; // Passa o conteudo (sequencia ordenada) do vetor auxilar para V
  }

  free(temp);
  temp = NULL;
}


void mergeSort(int *V,int inicio, int fim){ // O(n log(n)) no pior ou melhor caso terá a mesma complexidade 
    int meio = 0; 

    if (inicio < fim){
        meio = (inicio + fim)/2;

        mergeSort(V, inicio, meio);

        mergeSort(V, meio+1, fim);

        merge(V, inicio, meio, fim);
    }
}

int particao(int *V, int inicio, int fim){  // Função auxiliar que ordena o vetor em partições de menores que o pivo 
    int p = inicio;                         // e maiores que o pivo e retorna a posição do pivo
    int r = fim;
    int pivo = V[inicio]; // O pivo é o primeiro elemento do vetor
    int aux;

  while (p < r) {
    while (V[p] <= pivo) { p++; }
    while (V[r] > pivo) { r--; }

    if (p < r) {
      aux = V[p];
      V[p] = V[r];
      V[r] = aux;
    }
  }
    V[inicio] = V[r]; 
    V[r] = pivo;
    return r; // Posição do pivo
}

void quickSort(int *V, int inicio, int fim){    // O(n²) no pior dos casos que é um vetor com numeros repetidos ou todos os elementos 
    int q=0;                                    // do vetor serem maiores ou menores que o pivo
    if (inicio < fim){
        q = particao(V,inicio,fim);
        quickSort(V,inicio,q-1);
        quickSort(V,q+1,fim);
    }
}