#include <stdio.h>
#include <math.h>

void printar(int matriz[2][32], int len_negativo1, FILE *arquivo_saida) {
    int i, j;
    for (i = 0; i < 2; i++) {
        for (j = len_negativo1 - 1; j >= 0; j--) {
            fprintf(arquivo_saida, "%d", matriz[i][j]);
        }
        
        if (i == 0) {
            fprintf(arquivo_saida, " ");
        }
    }
}

int decimal_binario(int vetor[], int num){
    int i, bkp_num = num;

    // para garantir que todo o vetor será zerado
    for (i = 0; i < 32; i++){
        vetor[i] = 0;
    }
    
    // transformando o número em um número positivo, pra ficar mais fácil de converter
    if (num < 0) {
        num = num * -1;
    }

    // i contabiliza o número de bits 
    i = 0;
    // transformando o número em binário
    // cada passagem aumenta a quantidade de bits
    while (num > 0) {
        vetor[i] = num % 2;
        num = num / 2;
        i += 1;
    }

    
    // se o número decimal for negativo, precisa fazer a soma do complemento mais um
    // utiliza o "backup" do número decimal porque o número original foi transofrmado em positivo para a conversão em binário
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

            // se o valor da soma for 2, o carry continua 1 e o resultado fica 0
            if (valor_soma > 1) {
                carry = 1;
                vetor[j] = 0;
            }
            // senão, o resultado fica um e o carry zera, e o resto do número continua igual
            else {
                carry = 0;
                vetor[j] = 1;
            }
        }
    }
    
    // se o número binário for de 32 bits, nao tem como retornar 33 bits sendo que o vetor nao tem esse espaço
    // precisa ser com um bit a mais porque o primeiro bit é o sinal do número
    if (i < 32) {
        return i + 1;
    }
    else {
        return i;
    }
}

long binario_decimal(int matriz[2][32], int len_negativo1) {
    int i, j, multiplicador = 1;
    long valor, resultado = 0;
    
    if (matriz[0][len_negativo1 - 1] == 1) {
        multiplicador = -1;
        // fazendo o complemento
        for (i = 0; i < 2; i++) {
            for (j = 31; j >= 0; j--) {
                if (matriz[i][j] == 0) {
                    matriz[i][j] = 1;
                }
                else {
                    matriz[i][j] = 0;
                }
            }
        }
        
        // fazendo a soma
        int carry = 1;
        int valor_soma;
        
        for (i = 1; i >= 0; i--) {
            for(j = 0; j < 32; j++){
                // se o carry for zero, não precisa fazer a soma porque tudo vai ficar igual independente
                if (carry == 0) {
                    break;
                }
                
                valor_soma = matriz[i][j] + carry;
    
                // se o valor da soma for 2, o carry continua 1 e o resultado fica 0
                if (valor_soma > 1) {
                    carry = 1;
                    matriz[i][j] = 0;
                }
                // senão, o resultado fica um e o carry zera, e o resto do número continua igual
                else {
                    carry = 0;
                    matriz[i][j] = 1;
                }
            }
        }
    }
    
    for (i = 1; i >= 0; i--) {
        for (j = 0; j < len_negativo1; j++) {
            if (i == 0) {
                valor = pow(2, len_negativo1);
            }
            else {
                valor = 1;
            }
            
            resultado += matriz[i][j] * valor * pow(2, j);
        }
    }
    
    // se o binário for 1, multiplica por -1 (o número é negativo)
    return resultado * multiplicador;
}

void deslocamento_direita(int matriz[2][32], int *QP, int len_negativo1, FILE *arquivo_saida) {
    int i, j;
    
    // o binário está ao contrário, então percorre a matriz da esquerda para a deslocamento_direita
    // se ele tivesse invertido já, seria da direita para a esquerda
    *QP = matriz[1][0];
    
    // na segunda linha, o bit pega o valor do bit da frente
    // com exceção do último bit, que pega do primeiro bit da primeira linha
    for (i = 0; i < len_negativo1 - 1; i++) {
        matriz[1][i] = matriz[1][i + 1];
    }
    
    // pega o primeiro bit da primeira linha, assim como o QP
    matriz[1][len_negativo1 - 1] = matriz[0][0];
    
    // mesmo processo da segunda linha, mas na primeira
    for (i = 0; i < len_negativo1 - 1; i++) {
        matriz[0][i] = matriz[0][i + 1];
    }
    
    // printando o resultado
    fprintf(arquivo_saida, "Deslocamento a direita: ");
    printar(matriz, len_negativo1, arquivo_saida);
    fprintf(arquivo_saida, "\n");
}

void soma(int matriz1[2][32], int matriz2[2][32], int len_negativo1, FILE *arquivo_saida) {
    // matriz1 -> P e matriz2 -> S ou A
    int i, j, carry = 0, valor_soma;
    
    for (i = 1; i >= 0; i--) {
        // o binário já tá ao contrário, não precisa inverter se não dá errado ( o P estaria invertido e o A ou S não)
        for(j = 0; j < 32; j++){
            
            valor_soma = matriz1[i][j] + matriz2[i][j] + carry;
        
            // nesse caso, a soma pode dar 3. se der 3, o resultado na matriz tem que dar 1 mesmo
            matriz1[i][j] = valor_soma % 2;
            
            // se for 3 / 2, o carry fica 1
            carry = valor_soma / 2;
        }
    }
    
    // printando o resultado
    printar(matriz1, len_negativo1, arquivo_saida);
    fprintf(arquivo_saida, "\n");
}

int main(){
    int n1, binario_um[32], binario_negativo1[32], len_binario1, len_negativo1;
    int n2, binario_dois[32], len_binario2;
    int i, j;
    FILE *arquivo = fopen("teste.txt", "r");
    FILE *arquivo_saida = fopen("saida.txt", "wt");
    
    if (arquivo == NULL) {
        printf("Arquivo de teste não encontrado!");
        fclose(arquivo_saida);
        fclose(arquivo);
        return -1;
    }
    else {
        if(arquivo_saida == NULL) {
            printf("Arquivo de saída não criado!");
            fclose(arquivo_saida);
            fclose(arquivo);
            return -1;
        }
        else {
            while (fscanf(arquivo, "%d %d", &n1, &n2) == 2) {
                
                // chamando as funções de transformação em binário, que retorna a quantidade de bits de cada um
                len_binario1 = decimal_binario(binario_um, n1); // binário do primeiro número e qtde de bits dele
                len_negativo1 = decimal_binario(binario_negativo1, -n1); // binário do primeiro número negativo e qtde de bits dele
                len_binario2 = decimal_binario(binario_dois, n2); // binário do segundo número e qtde de bits dele
                
                // igualando a quantidade de bits entre os números
                // se um dos binários tiver 4 bits e o outro tiver 5, usa a quantidade de bits do maior (5)
                if (len_negativo1> len_binario2) {
                    len_binario2 = len_negativo1;
                    len_binario1 = len_negativo1;
                }
                else {
                    len_negativo1 = len_binario2;
                    len_binario1 = len_binario2;
                }
                
                // printando os binários com sinal positivo ou negativo, apenas com a quantidade de bits estabelecida, não 32
		fprintf(arquivo_saida, "Números informados: %d e %d\n\n", n1, n2);

                fprintf(arquivo_saida, "(%+d): ", n1);
                for (i = len_binario1 - 1; i >= 0; i--) {
                    fprintf(arquivo_saida, "%d", binario_um[i]);
                }
                fprintf(arquivo_saida, "\n");
                
                fprintf(arquivo_saida, "(%+d): ", n2);
                for (i = len_binario2 - 1; i >= 0; i--) {
                    fprintf(arquivo_saida, "%d", binario_dois[i]);
                }
                fprintf(arquivo_saida, "\n");
                
                fprintf(arquivo_saida, "(%+d): ", -n1);
                for (i = len_negativo1 - 1; i >= 0; i--){
                    fprintf(arquivo_saida, "%d", binario_negativo1[i]);
                }
                fprintf(arquivo_saida, "\n\n");
                
                // criando as matrizes com os binários
                // duas linhas e cada linha tem 32 colunas, mas pode ser len_negativo1 (pra não ter que rodar por 32 bits) 
                // QA, QS e QP é pro último bit separado do resto 
                int A[2][32], QA = 0;
                int S[2][32], QS = 0;
                int P[2][32], QP = 0;
                
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
            
                // printando A
                fprintf(arquivo_saida, "A: ");
                printar(A, len_negativo1, arquivo_saida);
                fprintf(arquivo_saida, "%d\n", QA);
            
                // printando S
                fprintf(arquivo_saida, "S: ");
                printar(S, len_negativo1, arquivo_saida);
                fprintf(arquivo_saida, "%d\n", QS);
            
                // printando P
                fprintf(arquivo_saida, "P: ");
                printar(P, len_negativo1, arquivo_saida);
                
                fprintf(arquivo_saida, "%d\n\n", QP);
                
                // printando o processo de soma e deslocamento
                for (i = 0; i < len_negativo1; i++) {
                    if (P[1][0] == QP) {
                        deslocamento_direita(P, &QP, len_negativo1, arquivo_saida);
                    }
                    else if (P[1][0] == 1 && QP == 0) {
                        fprintf(arquivo_saida, "Soma de P e S: ");
                        soma(P, S, len_negativo1, arquivo_saida);
                        deslocamento_direita(P, &QP, len_negativo1, arquivo_saida);
                    }
                    else {
                        fprintf(arquivo_saida, "Soma de P e A: ");
                        soma(P, A, len_negativo1, arquivo_saida);
                        deslocamento_direita(P, &QP, len_negativo1, arquivo_saida);
                    }
                }
                
                fprintf(arquivo_saida, "\n");
                
                // printando resultado final
                fprintf(arquivo_saida, "Resultado de %d * %d: ", n1, n2);
                printar(P, len_negativo1, arquivo_saida);
                fprintf(arquivo_saida, ", que é %ld", binario_decimal(P, len_negativo1));
                fprintf(arquivo_saida, "\n\n\n");
            }
        }
    
    }
    
    fclose(arquivo_saida);
    fclose(arquivo);
    
    return 0;
    
}
