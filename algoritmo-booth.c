#include <stdio.h>

void decimal_binario(int vetor[], int num){
    int binario[32], i = 0, j, k = 0;
    
    // transformando o número em um número positivo
    if (num < 0) {
        num = num * -1;
    }
    
    // transformando o número em binário
    while (num > 0) {
        binario[i] = num % 2;
        num = num / 2;
        i += 1;
    }
    
    for (j = i - 1; j >= 0; j--) {
        vetor[k] = binario[j];
        k += 1;
    }
}

void binario_negativo(int binario[]){
    int i;
    
    // complementando o binário
    for (i = 0; i < 6; i++){
        if (binario[i] == 0) {
            binario[i] = 1;
        }
        else {
            binario[i] = 0;
        }
    }
    
    // somando 1 ao binário
    if (binario[i] == 0) {
        binario[i] = 1;
    }
}

int main(){
    int n1, n2, binario_um[32], binario_dois[32], i;
    
    scanf("%d %d", &n1, &n2);

    // chamando as funções de transformação em binário
    decimal_binario(binario_um, n1);
    decimal_binario(binario_dois, n2);
    
    // transformando o binário em binário negativo
    if (n1 < 0) {
        binario_negativo(binario_um);
    }
    else if (n2 < 0) {
        binario_negativo(binario_dois);
    }
    
    for (i=0; i <= 5; i++) {
        printf("%d", binario_um[i]);
    }
    
    printf("\n");
    
    for (i=0; i <= 5; i++){
        printf("%d", binario_dois[i]);
    }
    
}
