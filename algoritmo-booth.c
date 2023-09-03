#include <stdio.h>

int decimal_binario(int vetor[], int num){
    int i, bkp_num = num;
    
    for (i = 0; i < 32; i++){
        vetor[i] = 0;
    }
    
    // transformando o número em um número positivo
    if (num < 0) {
        num = num * -1;
    }
    
    i = 0;
    // transformando o número em binário
    while (num > 0) {
        vetor[i] = num % 2;
        num = num / 2;
        i += 1;
    }
    
    // se o número for negativo, precisa fazer a soma do complemento mais um
    if (bkp_num < 0) {
        
        int j;
        // fazendo o complemento
        for (j = 31; j >= 0; j--) {
            if (vetor[j] == 0) {
                vetor[j] = 1;
            }
            else {
                vetor[j] = 0;
            }
        }
        
        // fazendo a soma
        int carry = 1;
        int valor_soma;
        
        for(j = 0; j < 32; j++){
            // se o carry for zero, não precisa fazer a soma porque tudo vai ficar igual independente
            if (carry == 0) {
                break;
            }
            valor_soma = vetor[j] + carry;
            
            if (valor_soma > 1) {
                carry = 1;
                vetor[j] = 0;
            }
            else {
                carry = 0;
                vetor[j] = 1;
            }
        }
    }
    
    // se for 32 bits, nao tem como retornar 33 bits sendo que o vetor nao tem esse espaço
    if (i < 32) {
        return i + 1;
    }
    else {
        return i;
    }
}

int main(){
    int n1, binario_um[32], binario_negativo1[32], len_binario1, len_negativo1;
    int n2, binario_dois[32], len_binario2;
    int i, j;
    
    scanf("%d %d", &n1, &n2);

    // chamando as funções de transformação em binário
    len_binario1 = decimal_binario(binario_um, n1);
    len_negativo1 = decimal_binario(binario_negativo1, -n1);
    len_binario2 = decimal_binario(binario_dois, n2);
    
    // pra usar a mesma quantidade de bits pra todos
    if (len_negativo1> len_binario2) {
        len_binario2 = len_negativo1;
        len_binario1 = len_negativo1;
    }
    else {
        len_negativo1 = len_binario2;
        len_binario1 = len_binario2;
    }
    
    // printando os binários
    printf("(%+04d): ", n1);
    for (i = len_binario1 - 1; i >= 0; i--) {
        printf("%d", binario_um[i]);
    }
    printf("\n");
    
    printf("(%+04d): ", n2);
    for (i = len_binario2 - 1; i >= 0; i--) {
        printf("%d", binario_dois[i]);
    }
    printf("\n");
    
    printf("(%+04d): ", -n1);
    for (i = len_negativo1 - 1; i >= 0; i--){
        printf("%d", binario_negativo1[i]);
    }
    printf("\n\n");
    
    // criando as matrizes com os binários
    // duas linhas e cada linha tem len_negativo1 colunas (tamanho do maior binário)
    int A[2][32], QA;
    int S[2][32], QS;
    int P[2][32], QP;
    
    for (i = 0; i < 32; i++) {
        A[0][i] = binario_um[i];
        A[1][i] = 0;
    }
    
    for (i = 0; i < 32; i++) {
        S[0][i] = binario_negativo1[i];
        S[1][i] = 0;
    }
    
    for (i = 0; i < 32; i++) {
        P[0][i] = 0;
        P[1][i] = binario_dois[i];
    }
    
    printf("A: ");
    for (i = 0; i < 2; i++) {
        // len_negativo1 pra nao printar 32 bits
        for (j = len_negativo1 - 1; j >= 0; j--) {
            printf("%d", A[i][j]);
        }
        printf(" ");
    }
    
    printf("%d\n", QA);
    
    printf("S: ");
    for (i = 0; i < 2; i++) {
        for (j = len_negativo1 - 1; j >= 0; j--) {
            printf("%d", S[i][j]);
        }
        printf(" ");
    }
    
    printf("%d\n", QS);
    
    printf("P: ");
    for (i = 0; i < 2; i++) {
        for (j = len_negativo1 - 1; j >= 0; j--) {
            printf("%d", P[i][j]);
        }
        printf(" ");
    }
    
    printf("%d\n", QP);
    
    return 0;
    
}
