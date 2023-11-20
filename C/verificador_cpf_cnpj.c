// Bibliotecas utilizadas 
#include <locale.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Constante
#define id 15

// Função para verificar CPF 
void verificador_cpf(void) {
    // Declaração de variáveis
    char CPF[id];
    char cop_cpf[id];
    int num[id], contador;
    int somatorioA, somatorioB;
    int restoA, restoB;
    char digitoA, digitoB;

    // Comandos 
    printf("CPF: \n");      // Solicita o CPF 
    scanf("%s", &CPF);       // Leitura do CPF
    strcpy(cop_cpf, CPF);    // Copia o CPF na variável auxiliar

    // Transforma os números do CPF em int para a verificação da validade
    for (contador = 0; contador < 11; contador++) {
        num[contador] = cop_cpf[contador] - '0';
    }

    // Multiplica cada um dos primeiros 9 números pelo seu correspondente da sequência auxiliar (10,9,8,7,6,5,4,3,2) e soma os resultados
    somatorioA = (num[0] * 10) + (num[1] * 9) + (num[2] * 8) + (num[3] * 7) + (num[4] * 6) + (num[5] * 5) + (num[6] * 4) + (num[7] * 3) + (num[8] * 2);

    // Obtém o resto da divisão do somatório anterior por 11
    restoA = somatorioA % 11;

    // Condiciona o resto de acordo com o valor obtido anteriormente para obter o primeiro dígito verificador
    digitoA = (restoA <= 1) ? 0 : 11 - restoA;

    // Multiplica cada um dos primeiros 9 números e do primeiro dígito verificador pelo seu correspondente da sequência auxiliar (11,10,9,8,7,6,5,4,3,2) e soma os resultados
    somatorioB = (num[0] * 11) + (num[1] * 10) + (num[2] * 9) + (num[3] * 8) + (num[4] * 7) + (num[5] * 6) + (num[6] * 5) + (num[7] * 4) + (num[8] * 3) + (digitoA * 2);

    // Obtém o resto da divisão do somatório anterior por 11
    restoB = somatorioB % 11;

    // Condiciona o resto de acordo com o valor obtido anteriormente para obter o segundo dígito verificador
    digitoB = (restoB <= 1) ? 0 : 11 - restoB;

    // Compara os dígitos obtidos com os dígitos informados para validar o CPF
    if (digitoA == num[9] && digitoB == num[10]) {
        printf("CPF VÁLIDO\n");  // Informa que o CPF é válido
        printf("\nENTER PARA RETORNAR AO MENU PRINCIPAL\n");
        getch();  // Pausa
    } else {
        printf("CPF INVÁLIDO\n");  // Informa que o CPF é inválido
        printf("\nENTER PARA RETORNAR AO MENU PRINCIPAL\n");
        getch();  // Pausa
    }

    main();  // Direciona para o menu principal
}

// Função para verificar CNPJ 
void verificador_cnpj(void) {
    char cnpj[id];
    char cop_cnpj[id];
    int numero[id], cont;
    int somatorioA, somatorioB;
    int restoA, restoB;
    char digitoA, digitoB;

    printf("\nCNPJ: \n");  // Solicita o CNPJ
    gets(cnpj);             // Leitura do CNPJ
    strcpy(cop_cnpj, cnpj); // Copia o CNPJ na variável auxiliar

    // Transforma os números do CNPJ em int para a verificação da validade
    for (cont = 0; cont < 14; cont++) {
        numero[cont] = cop_cnpj[cont] - '0'; //'48' para tirar o 0 armazenado nas strings
    }

    // Multiplica cada um dos primeiros 12 números pelo seu correspondente da sequência auxiliar (5,4,3,2,9,8,7,6,5,4,3,2) e soma os resultados
    somatorioA = (numero[0] * 5) + (numero[1] * 4) + (numero[2] * 3) + (numero[3] * 2) + (numero[4] * 9) + (numero[5] * 8) + (numero[6] * 7) + (numero[7] * 6) + (numero[8] * 5) + (numero[9] * 4) + (numero[10] * 3) + (numero[11] * 2);

    // Obtém o resto da divisão do somatório anterior por 11
    restoA = somatorioA % 11;

    // Condiciona o resto de acordo com o valor obtido anteriormente para obter o primeiro dígito verificador
    digitoA = (restoA <= 1) ? 0 : 11 - restoA;

    // Multiplica cada um dos primeiros 12 números e do primeiro dígito verificador pelo seu correspondente da sequência auxiliar (6,5,4,3,2,9,8,7,6,5,4,3,2) e soma os resultados
    somatorioB = (numero[0] * 6) + (numero[1] * 5) + (numero[2] * 4) + (numero[3] * 3) + (numero[4] * 2) + (numero[5] * 9) + (numero[6] * 8) + (numero[7] * 7) + (numero[8] * 6) + (numero[9] * 5) + (numero[10] * 4) + (numero[11] * 3) + (digitoA * 2);

    // Obtém o resto da divisão do somatório anterior por 11
    restoB = somatorioB % 11;

    // Condiciona o resto de acordo com o valor obtido anteriormente para obter o segundo dígito
    digitoB = (restoB <= 1) ? 0 : 11 - restoB;

    // Compara os dígitos obtidos com os dígitos informados para validar o CNPJ
    if (digitoA == numero[12] && digitoB == numero[13]) {
        printf("CNPJ VÁLIDO\n");  // Informa que o CNPJ é válido
        printf("\nENTER PARA RETORNAR AO MENU PRINCIPAL\n");
        getch();  // Pausa
    } else {
        printf("CNPJ INVÁLIDO\n");  // Informa que o CNPJ é inválido
        printf("\nENTER PARA RETORNAR AO MENU PRINCIPAL\n");
        getch();  // Pausa
    }

    main();  // Direciona para o menu principal
}

// Função principal
int main() {
    setlocale(LC_ALL, "Portuguese");  // Permite o uso do português e leitura de acentos

    int opcao;  // Declaração da variável de opção

    // Mostra na tela as opções
    printf("SELECIONE A OPÇÃO DESEJADA\n");
    printf("\t1) Verificar CPF\n");
    printf("\t2) Verificar CNPJ\n");

    printf("Escolha uma opção: ");  // Solicita a função
    scanf("%d", &opcao);  // Leitura da escolha

    // Chamamento das funções 
    if (opcao == 1) {
        verificador_cpf();
    } else if (opcao == 2) {
        verificador_cnpj();
    } else if (opcao < 1 || opcao > 2) {
        printf("ERRO: OPÇÃO INEXISTENTE");
    }

    return 0;
}

/*
CPF funciona sem inserção de pontuações
CNPJ não está recebendo entrada de valores
*/