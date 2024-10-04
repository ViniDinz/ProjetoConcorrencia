#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


int tamanho = 10;


void pushZerosToEnd(int *arr, int n) {
    int temp[n];
    
    int j = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] != 0)
            temp[j++] = arr[i];
    }

    while (j < n)
        temp[j++] = 0;

    
    for (int i = 0; i < n; i++)
        arr[i] = temp[i];
}


int comp (const void * elem1, const void * elem2) 
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

double round(double v) {
    return ((int)(v * 100 + .5)) / 100.;
}


int main()
{

srand(time(NULL));

int valores[tamanho];

int valores_sort[tamanho];

int metade1[tamanho/2];

int metade2[tamanho/2];

int mediana1;

int mediana2;

int mediana_ponderada;

int l1 = 0;
int e1 = 0;
int g1 = 0;

int l2 = 0;
int e2 = 0;
int g2 = 0;

int kth;

kth = rand() % (tamanho - 1) + 1;

printf("kth: %d\n", kth);

clock_t begin = clock();


for(int a = 0;a < tamanho;a++)
{
    valores[a] =  (rand() % 99) + 1;
}

for(int a = 0;a<tamanho;a++)
{
    valores_sort[a] = valores[a];
}

qsort (valores_sort, sizeof(valores_sort)/sizeof(*valores_sort), sizeof(*valores_sort), comp);

for(int a = 0;a < tamanho;a++)
{
    printf("ValoresSort%d\n",valores_sort[a]);
}

memcpy(metade1, valores, tamanho/2 * sizeof(int));
memcpy(metade2, valores + tamanho/2, tamanho/2 * sizeof(int));

qsort (metade1, sizeof(metade1)/sizeof(*metade1), sizeof(*metade1), comp);
qsort (metade2, sizeof(metade2)/sizeof(*metade2), sizeof(*metade2), comp);
size_t tamanho_metade = (sizeof(valores) / sizeof(*valores)) / 2;

if(tamanho_metade%2 == 0)
{

    mediana1 = (metade1[tamanho_metade/2 - 1] + metade1[tamanho_metade/2]) / 2;
    mediana2 = (metade2[tamanho_metade/2 - 1] + metade2[tamanho_metade/2]) / 2;
}
else
{
    mediana1 = metade1[tamanho_metade/2];
    mediana2 = metade2[tamanho_metade/2];
}

int M[2] = {mediana1,mediana2};

int W[2] = {tamanho_metade,tamanho_metade};

int soma_pesos = tamanho_metade*2;

int i = 0;

int sum = soma_pesos - W[0];

while (sum > soma_pesos/2)
{
    ++i;
    sum -=W[i];
}

mediana_ponderada = M[i];

printf("mediana_ponderada:%d\n\n",mediana_ponderada);

for(int a = 0;a < tamanho_metade;a++)
{
    if(metade1[a] < mediana_ponderada)
    l1++;
    else if(metade1[a] == mediana_ponderada)
    e1++;
    else if(metade1[a] > mediana_ponderada)
    g1++;
}

for(int a = 0;a < tamanho_metade;a++)
{
    if(metade2[a] < mediana_ponderada)
    l2++;
    else if(metade2[a] == mediana_ponderada)
    e2++;
    else if(metade2[a] > mediana_ponderada)
    g2++;
}

int L = l1 + l2;
int E = e1 + e2;
int G = g1 + g2;

printf("L:%d E:%d G:%d\n",L,E,G);

if(L < kth && kth <= L + E)
{
    printf("A solucaoL é: %d\n",mediana_ponderada);
}
else if(kth <= L)
{
   int index = 0;
   int novos_valores[tamanho];

   for(int a = 0; a<tamanho;a++)
   {
    novos_valores[a] = 0;
   }

   for(int a = 0;a < tamanho;a++)
   {

    if(valores[a] < mediana_ponderada)
    {
        novos_valores[index] = valores[a];
        printf("valoresN:%d\n",novos_valores[index]);
        index++;
    }
   }

    qsort (novos_valores, sizeof(novos_valores)/sizeof(*novos_valores), sizeof(*novos_valores), comp);
    pushZerosToEnd(novos_valores,tamanho);
    printf("A solucaoE é:%d\n",novos_valores[kth - 1]);
}

else if(kth > L + E)
{
   int index = 0;
   int index_medina_ponderada = 0;
   int novos_valores[tamanho];

   for(int a = 0; a<tamanho;a++)
   {
    novos_valores[a] = 0;
   }


   for(int a = 0;a < tamanho;a++)
   {
   
    if(valores[a] > mediana_ponderada)
    {
        novos_valores[index] = valores[a];
        printf("valoresN:%d\n",novos_valores[index]);
        index++;
    }
   }
    qsort (novos_valores, sizeof(novos_valores)/sizeof(*novos_valores), sizeof(*novos_valores), comp);
    pushZerosToEnd(novos_valores,tamanho);
    for(int a = 0; a < tamanho;a++)
    {
        if(valores_sort[a] == mediana_ponderada){
        index_medina_ponderada = a;
        }
    }

    printf("A solucaoG é: %d\n",novos_valores[kth - index_medina_ponderada - 2]);
}

clock_t end = clock();
double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
printf("\nTempo de Execucao:%d\n",time_spent);

}
