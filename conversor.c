#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MAX_DIGITOS 500
#define LIMITE_OVERFLOW ULLONG_MAX


int validar_octal(const char *numero_str) {
    if (numero_str == NULL || strlen(numero_str) == 0) {
        return 0;
    }
    
    for (int i = 0; numero_str[i] != '\0'; i++) {
        if (numero_str[i] < '0' || numero_str[i] > '7') {
            return 0;
        }
    }
    
    return 1;
}


int validar_binario(const char *numero_str) {
    if (numero_str == NULL || strlen(numero_str) == 0) {
        return 0;
    }
    
    for (int i = 0; numero_str[i] != '\0'; i++) {
        if (numero_str[i] != '0' && numero_str[i] != '1') {
            return 0;
        }
    }
    
    return 1;
}


int verificar_overflow(const char *numero_str, int base) {
    int tamanho = strlen(numero_str);
    

    if (base == 8 && tamanho > 21) {
        return 1;
    }
    if (base == 2 && tamanho > 64) {
        return 1;
    }
    
    return 0;
}


int octal_para_binario(const char *numero_octal, char *resultado) {

    if (!validar_octal(numero_octal)) {
        printf("[ERRO] Numero octal invalido. Use apenas digitos de 0 a 7.\n");
        return 0;
    }
    

    if (verificar_overflow(numero_octal, 8)) {
        printf("[AVISO] O numero e muito grande e pode causar overflow.\n");
        printf("Deseja continuar mesmo assim? (s/n): ");
        char resposta;
        scanf(" %c", &resposta);
        getchar();
        if (tolower(resposta) != 's') {
            return 0;
        }
    }
    

    unsigned long long valor_decimal = 0;
    unsigned long long potencia = 1;
    int tamanho = strlen(numero_octal);
    

    for (int i = tamanho - 1; i >= 0; i--) {
        int digito = numero_octal[i] - '0';
        valor_decimal += digito * potencia;
        potencia *= 8;
    }
    

    if (valor_decimal == 0) {
        strcpy(resultado, "0");
        return 1;
    }
    
    char temp[MAX_DIGITOS];
    int indice = 0;
    
    while (valor_decimal > 0) {
        temp[indice++] = (valor_decimal % 2) + '0';
        valor_decimal /= 2;
    }
    

    for (int i = 0; i < indice; i++) {
        resultado[i] = temp[indice - 1 - i];
    }
    resultado[indice] = '\0';
    
    return 1;
}


int binario_para_octal(const char *numero_binario, char *resultado) {

    if (!validar_binario(numero_binario)) {
        printf("[ERRO] Numero binario invalido. Use apenas digitos 0 e 1.\n");
        return 0;
    }
    

    if (verificar_overflow(numero_binario, 2)) {
        printf("[AVISO] O numero e muito grande e pode causar overflow.\n");
        printf("Deseja continuar mesmo assim? (s/n): ");
        char resposta;
        scanf(" %c", &resposta);
        getchar();
        if (tolower(resposta) != 's') {
            return 0;
        }
    }
    

    unsigned long long valor_decimal = 0;
    unsigned long long potencia = 1;
    int tamanho = strlen(numero_binario);
    

    for (int i = tamanho - 1; i >= 0; i--) {
        int digito = numero_binario[i] - '0';
        valor_decimal += digito * potencia;
        potencia *= 2;
    }
    

    if (valor_decimal == 0) {
        strcpy(resultado, "0");
        return 1;
    }
    
    char temp[MAX_DIGITOS];
    int indice = 0;
    
    while (valor_decimal > 0) {
        int resto = valor_decimal % 8;
        temp[indice++] = '0' + resto;
        valor_decimal /= 8;
    }
    

    for (int i = 0; i < indice; i++) {
        resultado[i] = temp[indice - 1 - i];
    }
    resultado[indice] = '\0';
    
    return 1;
}


void exibir_menu() {
    printf("\n==================================================\n");
    printf("  CONVERSOR DE BASES NUMERICAS\n");
    printf("  Octal <-> Binario\n");
    printf("==================================================\n");
    printf("\nEscolha o tipo de conversao:\n");
    printf("1 - Octal -> Binario\n");
    printf("2 - Binario -> Octal\n");
    printf("0 - Sair do programa\n");
    printf("--------------------------------------------------\n");
}


void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void remover_espacos(char *str) {
    int i, j = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}


void formatar_binario(const char *binario, char *formatado) {
    int tamanho = strlen(binario);
    int j = 0;
    int contador = 0;
    

    for (int i = 0; i < tamanho; i++) {
        if (contador == 4) {
            formatado[j++] = ' ';
            contador = 0;
        }
        formatado[j++] = binario[i];
        contador++;
    }
    formatado[j] = '\0';
}


int main() {
    char numero[MAX_DIGITOS];
    char resultado[MAX_DIGITOS];
    char formatado[MAX_DIGITOS * 2];
    int opcao;
    
    printf("==================================================\n");
    printf("  Bem-vindo ao Conversor de Bases Numericas.\n");
    printf("==================================================\n");
    
    while (1) {
        exibir_menu();
        
        printf("\nDigite sua opcao (0, 1 ou 2): ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("\n[ERRO] Entrada invalida. Digite apenas numeros.\n");
            limpar_buffer();
            printf("\nPressione ENTER para continuar...");
            getchar();
            continue;
        }
        limpar_buffer();
        
        if (opcao == 0) {
            printf("\nEncerrando o programa.\n");
            break;
        }
        else if (opcao == 1) {

            printf("\n>>> CONVERSAO: Octal -> Binario\n");
            printf("Digite o numero em OCTAL: ");
            fgets(numero, MAX_DIGITOS, stdin);
            remover_espacos(numero);
            
            if (octal_para_binario(numero, resultado)) {
                unsigned long long decimal = strtoull(numero, NULL, 8);
                formatar_binario(resultado, formatado);
                
                printf("\n[RESULTADO]\n");
                printf("   Octal:   %s\n", numero);
                printf("   Binario: %s\n", resultado);
                printf("   (formatado): %s\n", formatado);
                printf("   Decimal: %llu\n", decimal);
            }
        }
        else if (opcao == 2) {

            printf("\n>>> CONVERSAO: Binario -> Octal\n");
            printf("Digite o numero em BINARIO: ");
            fgets(numero, MAX_DIGITOS, stdin);
            remover_espacos(numero);
            
            if (binario_para_octal(numero, resultado)) {
                unsigned long long decimal = strtoull(numero, NULL, 2);
                formatar_binario(numero, formatado);
                
                printf("\n[RESULTADO]\n");
                printf("   Binario: %s\n", numero);
                printf("   (formatado): %s\n", formatado);
                printf("   Octal:   %s\n", resultado);
                printf("   Decimal: %llu\n", decimal);
            }
        }
        else {
            printf("\n[ERRO] Opcao invalida. Por favor, escolha 0, 1 ou 2.\n");
        }
        
        printf("\nPressione ENTER para continuar...");
        getchar();
    }
    
    return 0;

}
