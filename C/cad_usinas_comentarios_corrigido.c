// Inclusão de bibliotecas necessárias
#include <locale.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Definição de constantes
#define id 15       // Valor constante para id
#define num_max 100  // Valor constante para num_max

// Definição das estruturas (STRUCTs)

// Estrutura para representar uma usina
typedef struct {
    char nome_usina[num_max];
    char cnpj[id];
    int dia;
    int mes;
    int ano;
    double potencia_estimada;
} STRUCTusina;

// Estrutura para representar um consumidor
typedef struct {
    char nome_consumidor[num_max];
    char CPF[id];
    char CNPJ[id];
} STRUCTconsumidor;

// Estrutura para representar um contrato
typedef struct {
    char cnpj_usina, cnpj_consumidor, cpf_consumidor;
    int d, m, a;
    float potencia_contratada;
} STRUCTcontrato;

// Função para inicializar o sistema
void iniciar(void) {
    setlocale(LC_ALL, "Portuguese");   // Configuração da localidade para Português

    fflush(stdin);                    // Limpar o buffer do teclado
    system("clear||cls");             // Limpar a tela

    printf("//////////////////////////////////////\n");
    printf("SGC - SISTEMA DE GERAÇÃO COMPARTILHADA\n");  // Nome do sistema
    printf("//////////////////////////////////////\n\n");
}

// Função para exibir o menu principal
void menu(void) {
    iniciar();  // Limpezas e nome do sistema

    // Declarações
    int opcao;

    // Comandos
    printf("SELECIONE A OPÇÃO DESEJADA\n");
    printf("\t1) Cadastrar Usina\n");
    printf("\t2) Cadastrar Consumidor\n");
    printf("\t3) Cadastrar Contrato entre Consumidor e Usina\n");
    printf("\t4) Consultar Usina Cadastrada\n");
    printf("\t5) Consultar Consumidor Cadastrado\n");
    printf("\t6) Excluir Usina\n");
    printf("\t7) Excluir Consumidor\n\n");

    printf("Escolha uma opção: ");  // Solicita a escolha da função
    scanf("%d", &opcao);            // Leitura da escolha

    // Chamamento das funções
    if (opcao == 1) {
        cadastro_usina();
    } else if (opcao == 2) {
        cadastro_consumidor();
    } else if (opcao == 3) {
        cadastro_contrato();
    } else if (opcao == 4) {
        consultar_usina();
    } else if (opcao == 5) {
        consultar_consumidor();
    } else if (opcao == 6) {
        excluir_usina();
    } else if (opcao == 7) {
        excluir_consumidor();
    } else if (opcao < 1 || opcao > 7) {
        printf("ERRO: OPÇÃO INEXISTENTE");
    }
}

// Função para cadastrar uma usina
void cadastro_usina(void) {
    iniciar();  // Limpezas e nome do sistema

    // Declarações
    STRUCTusina usina;      // Dados da usina
    char cop_cnpj[id];      // Cópia do CNPJ informado
    int numero[id];         // Números do CNPJ
    int cont;
    int somatorioA, somatorioB;
    int restoA, restoB;
    char digitoA, digitoB;
    double potencia;
    int f; f = "----";

    int v_cnpj, v_dia, v_mes, v_ano, v_potencia;  // Verificadores

    FILE* usinas;  // Declaração do arquivo

    // Comandos
    usinas = fopen("arquivo_usinas.txt", "a+");  // Abertura do arquivo

    // Conferência da existência, abertura e autorização do arquivo
    if (usinas == NULL) {
        printf("ERRO NA ABERTURA DO ARQUIVO!");
        return;
    }

    printf("Nome da usina: \n");  // Solicita o nome da usina
    gets(usina.nome_usina);       // Leitura do nome da usina
    fflush(stdin);                // Limpeza do teclado

    printf("\nCNPJ: \n");         // Solicita o CNPJ da usina
    gets(usina.cnpj);             // Leitura do CNPJ da usina
    strcpy(cop_cnpj, usina.cnpj); // Cópia do CNPJ na variável auxiliar

    // Transforma os números do CNPJ em int para a verificação da validade
    for (cont = 0; cont < 14; cont++) {
        numero[cont] = cop_cnpj[cont] - 48; //'48' para tira o 0 armazenado nas strings
    }

    // Multiplica cada um dos primeiros 12 números pelo seu correspondente da sequência auxiliar (5,4,3,2,9,8,7,6,5,4,3,2) e soma os resultados
    somatorioA = (numero[0] * 5) + (numero[1] * 4) + (numero[2] * 3) + (numero[3] * 2) + (numero[4] * 9) + (numero[5] * 8) + (numero[6] * 7) + (numero[7] * 6) + (numero[8] * 5) + (numero[9] * 4) + (numero[10] * 3) + (numero[11] * 2);

    // Obtém o resto da divisão do somatório anterior por 11
    restoA = somatorioA % 11;

    // Condição de resto de acordo com o valor obtido anteriormente para obter o primeiro dígito verificador
    if (restoA == 1 || restoA == 0) {
        digitoA = 0;
    } else {
        digitoA = 11 - restoA;
    }

    // Multiplica cada um dos primeiros 12 números e do primeiro dígito verificador pelo seu correspondente da sequência auxiliar (6,5,4,3,2,9,8,7,6,5,4,3,2) e soma os resultados
    somatorioB = (numero[0] * 6) + (numero[1] * 5) + (numero[2] * 4) + (numero[3] * 3) + (numero[4] * 2) + (numero[5] * 9) + (numero[6] * 8) + (numero[7] * 7) + (numero[8] * 6) + (numero[9] * 5) + (numero[10] * 4) + (numero[11] * 3) + (digitoA * 2);

    // Obtém o resto da divisão do somatório anterior por 11
    restoB = somatorioB % 11;

    // Condição do resto de acordo com o valor obtido anteriormente para obter o segundo dígito verificador
    if (restoB == 1 || restoB == 0) {
        digitoB = 0;
    } else {
        digitoB = 11 - restoB;
    }

    // Compara os dígitos obtidos com os dígitos informados para validar o CNPJ
    if (digitoA == numero[12] && digitoB == numero[13]) {
        printf("CNPJ VÁLIDO\n\n");  // Informa que o CNPJ é válido
        v_cnpj = 1;                  // Atribui 1 ao validador
    } else {
        printf("CNPJ INVÁLIDO\n\n");  // Informa que o CNPJ é inválido
        v_cnpj = 2;                  // Atribui 2 ao validador
    }

    printf("Data de início da operação (DD/MM/AAAA):\n");  // Solicita a data de início da operação
    scanf("%d/%d/%d", &usina.dia, &usina.mes, &usina.ano); // Leitura da data informada

    // Condições de validação da data, considerando 12 meses, quantidade de dias previstos para cada mês, anos D.C. e anos bissextos
    if (usina.mes < 1 || usina.mes > 12 || usina.ano < 0) {
        printf("DATA INVÁLIDA\n\n");  // Informa que a data é inválida
        v_dia = 2; v_mes = 2; v_ano = 2;  // Atribui 2 aos validadores
    } else if (usina.mes == 2 && (usina.dia > 28 || usina.dia < 1) && ((usina.ano % 4 != 0) || ((usina.ano % 100 == 0 && (usina.ano % 400 != 0))))) {
        printf("DATA INVÁLIDA\n\n");  // Informa que a data é inválida
        v_dia = 2; v_mes = 2; v_ano = 2;  // Atribui 2 aos validadores
    } else if ((usina.mes == 4 || usina.mes == 6 || usina.mes == 9 || usina.mes == 11) && (usina.dia < 1 || usina.dia > 30)) {
        printf("DATA INVÁLIDA\n\n");  // Informa que a data é inválida
        v_dia = 2;v_mes = 2; v_ano = 2;  // Atribui 2 aos validadores
    } else if ((usina.mes == 1 || usina.mes == 3 || usina.mes == 5 || usina.mes == 7 || usina.mes == 8 || usina.mes == 10 || usina.mes == 12) && (usina.dia < 1 || usina.dia > 31)) {
        printf("DATA INVÁLIDA\n\n");  // Informa que a data é inválida
        v_dia = 2; v_mes = 2; v_ano = 2;  // Atribui 2 aos validadores
    } else if (usina.mes == 2 && (usina.dia < 1 || usina.dia > 29)) {
        printf("DATA INVÁLIDA\n\n");  // Informa que a data é inválida
        v_dia = 2; v_mes = 2; v_ano = 2;  // Atribui 2 aos validadores
    } else {
        printf("DATA VÁLIDA\n\n");  // Informa que a data é válida
        v_dia = 1; v_mes = 1; v_ano = 1;  // Atribui 1 aos validadores
    }

    fflush(stdin);  // Limpa o teclado
    printf("Potência estimada: \n");  // Solicita a potência estimada
    scanf("%lf", &usina.potencia_estimada);  // Leitura da potência informada

    // Verificação da potência considerando apenas valores positivos
    if (usina.potencia_estimada <= 0) {
        printf("POTÊNCIA INVÁLIDA\n\n");  // Informa que a potência é inválida
        v_potencia = 2;  // Atribui 2 ao validador
    } else {
        printf("POTÊNCIA VÁLIDA\n\n");  // Informa que a potência é válida
        v_potencia = 1;  // Atribui 1 ao validador
    }

    // Salvar dados apenas se os validadores tiverem valor 1 (válidos)
    if (v_cnpj == 1 && v_dia == 1 && v_mes == 1 && v_ano == 1 && v_potencia == 1) {
        fprintf(usinas, "\ni%s\n", usina.cnpj);        // Armazena no arquivo o CNPJ informado
        fprintf(usinas, ">%s\n", usina.nome_usina);      // Armazena no arquivo o nome informado
        fprintf(usinas, "%d\t%d\t%d\n", usina.dia, usina.mes, usina.ano);     // Armazena no arquivo a data informada
        fprintf(usinas, "%lf\n", usina.potencia_estimada);      // Armazena no arquivo a potência informada
        fputc('_', usinas);  // Separa o bloco de cadastro

        printf("\nDADOS GRAVADOS COM SUCESSO!");        // Informa que os dados foram salvos
        getch();        // Pausa
    } else {
        printf("\nNÃO FOI POSSÍVEL GRAVAR OS DADOS!");      // Informa que os dados não foram salvos
        getch();        // Pausa
    }

    fclose(usinas);     // Fechar arquivo

    printf("\n\tENTER PARA RETORNAR AO MENU PRINCIPAL");
    menu();     // Direciona para o menu principal
}

// Cadastro do consumidor
void cadastro_consumidor(void) {

    iniciar();  // Limpeza e nome do sistema

    // Declarações
    STRUCTconsumidor consumidor;  // Dados do consumidor
    char cop_cpf[id];  // Cópia do CPF
    char cop_cnpj[id];  // Cópia do CNPJ

    // Variáveis auxiliares
    int num[id], contador;
    int numero[id], cont;
    int id_consumidor;
    int somatorioA, somatorioB;
    int restoA, restoB;
    char digitoA, digitoB;
    int somatorioAA, somatorioBB;
    char digitoAA, digitoBB;
    int restoAA, restoBB;

    int v_cpf_consumidor, v_cnpj_consumidor;  // Validadores

    FILE* consumidores;  // Declaração do arquivo

    // Comandos
    consumidores = fopen("arquivo_consumidores.txt", "a+");  // Abrir arquivo

    // Confere a existência, abertura e autorização do arquivo
    if (consumidores == NULL) {
        printf("ERRO NA ABERTURA DO ARQUIVO!");
        return 1;
    }

    // Identificação
    printf("Nome do consumidor: \n");  // Solicita o nome do consumidor
    gets(consumidor.nome_consumidor);  // Leitura do nome do consumidor
    fflush(stdin);  // Limpeza do teclado

    printf("IDENTIFICAÇÃO\n 1-CPF\n 2-CNPJ\n");  // Solicita o documento de identificação do consumidor
    scanf("%d", &id_consumidor);  // Leitura da escolha de documento

    if (id_consumidor == 1) {  // Em caso de CPF
        printf("CPF: \n");  // Solicita o CPF do consumidor
        scanf("%s", &consumidor.CPF);  // Leitura do CPF do consumidor
        strcpy(cop_cpf, consumidor.CPF);  // Copia o CPF na variável auxiliar

        // Transforma os números do CPF em int para a verificação da validade
        for (contador = 0; contador < 11; contador++) {
            num[contador] = cop_cpf[contador] - 48;
        }

        // Multiplica cada um dos primeiros 9 números pelo seu correspondente da sequência auxiliar (10,9,8,7,6,5,4,3,2) e soma os resultados
        somatorioA = (num[0] * 10) + (num[1] * 9) + (num[2] * 8) + (num[3] * 7) + (num[4] * 6) + (num[5] * 5) + (num[6] * 4) + (num[7] * 3) + (num[8] * 2);

        // Obtém o resto da divisão do somatório anterior por 11
        restoA = somatorioA % 11;

        // Condiciona o resto de acordo com o valor obtido anteriormente para obter o primeiro dígito verificador
        if (restoA == 1 || restoA == 0) {
            digitoA = 0;
        } else {
            digitoA = 11 - restoA;
        }

        // Multiplica cada um dos primeiros 9 números e do primeiro dígito verificador pelo seu correspondente da sequência auxiliar (11,10,9,8,7,6,5,4,3,2) e soma os resultados
        somatorioB = (num[0] * 11) + (num[1] * 10) + (num[2] * 9) + (num[3] * 8) + (num[4] * 7) + (num[5] * 6) + (num[6] * 5) + (num[7] * 4) + (num[8] * 3) + (digitoA * 2);

        // Obtém o resto da divisão do somatório anterior por 11
        restoB = somatorioB % 11;

        // Condiciona o resto de acordo com o valor obtido anteriormente para obter o segundo dígito verificador
        if (restoB == 1 || restoB == 0) {
            digitoB = 0;
        } else {
            digitoB = 11 - restoB;
        }

        // Compara os dígitos obtidos com os dígitos informados para poder validar o CPF
        if (digitoA == num[9] && digitoB == num[10]) {
            printf("CPF VÁLIDO\n\n");  // Informa que é válido o CPF
            v_cpf_consumidor = 1;  // Atribui 1 ao validador
        } else {
            printf("CPF INVÁLIDO\n\n");  // Informa que é inválido o CPF
            v_cpf_consumidor = 2;  // Atribui 2 ao validador
        }
    } else if (id_consumidor == 2) {  // Em caso de CNPJ
        printf("CNPJ: \n");  // Solicita o CNPJ do consumidor
        scanf("%s", &consumidor.CNPJ);  // Leitura do CNPJ do consumidor
        strcpy(cop_cnpj, consumidor.CNPJ);  // Copia o CNPJ na variável auxiliar

        // Transforma os números do CNPJ em int para a verificação da validade
        for (cont = 0; cont < 14; cont++) {
            numero[cont] = cop_cnpj[cont] - 48;  //'48' para tirar o 0 armazenado nas strings
        }

        // Multiplica cada um dos primeiros 12 números pelo seu correspondente da sequência auxiliar (5,4,3,2,9,8,7,6,5,4,3,2) e soma os resultados
        somatorioAA = (numero[0] * 5) + (numero[1] * 4) + (numero[2] * 3) + (numero[3] * 2) + (numero[4] * 9) + (numero[5] * 8) + (numero[6] * 7) + (numero[7] * 6) + (numero[8] * 5) + (numero[9] * 4) + (numero[10] * 3) + (numero[11] * 2);

        // Obtém o resto da divisão do somatório anterior por 11
        restoAA = somatorioAA % 11;

        // Condiciona o resto de acordo com o valor obtido anteriormente para obter o primeiro dígito verificador
        if (restoAA == 1 || restoAA == 0) {
            digitoAA = 0;
        } else {
            digitoAA = 11 - restoAA;
        }

        // Multiplica cada um dos primeiros 12 números e do primeiro dígito verificador pelo seu correspondente da sequência auxiliar (6,5,4,3,2,9,8,7,6,5,4,3,2) e soma os resultados
        somatorioBB = (numero[0] * 6) + (numero[1] * 5) + (numero[2] * 4) + (numero[3] * 3) + (numero[4] * 2) + (numero[5] * 9) + (numero[6] * 8) + (numero[7] * 7) + (numero[8] * 6) + (numero[9] * 5) + (numero[10] * 4) + (numero[11] * 3) + (digitoAA * 2);

        // Obtém o resto da divisão do somatório anterior por 11
        restoBB = somatorioBB % 11;

        // Condiciona o resto de acordo com o valor obtido anteriormente para obter o segundo dígito verificador
        if (restoBB == 1 || restoBB == 0) {
            digitoBB = 0;
        } else {
            digitoBB = 11 - restoBB;
        }

        // Compara os dígitos obtidos com os dígitos informados para poder validar o CNPJ
        if (digitoAA == numero[12] && digitoBB == numero[13]) {
            printf("CNPJ VÁLIDO\n\n");  // Informa que é válido o CNPJ
            v_cnpj_consumidor = 1;  // Atribui 1 ao validador
        } else {
            printf("CNPJ INVÁLIDO\n\n");  // Informa que é inválido o CNPJ
            v_cnpj_consumidor = 2;  // Atribui 2 ao validador
        }
    }

    // Salvar dados apenas se o validador tiver valor 1 (válido)
    if (v_cpf_consumidor == 1) {
        fprintf(consumidores, "\n>%s\n", consumidor.nome_consumidor);  // Armazena no arquivo o nome informado
        fprintf(consumidores, "f%s\n", consumidor.CPF);  // Armazena no arquivo o CPF informado
        fputc('_', consumidores);  // Separa o bloco de cadastro

        printf("\nDADOS GRAVADOS COM SUCESSO!");
        printf("\n\tENTER PARA RETORNAR AO MENU PRINCIPAL");
        getch();  // Pausa
    } else if (v_cnpj_consumidor == 1) {
        fprintf(consumidores, "\n>%s\n", consumidor.nome_consumidor);  // Armazena no arquivo o nome informado
        fprintf(consumidores, "j%s\n", consumidor.CNPJ);  // Armazena no arquivo o CNPJ informado
        fputc('_', consumidores);  // Separa o bloco de cadastro

        printf("\nDADOS GRAVADOS COM SUCESSO!");  // Informa que os dados foram salvos
        getch();  // Pausa
    } else {
        printf("\nNÃO FOI POSSÍVEL GRAVAR OS DADOS!");  // Informa que os dados não foram salvos
        getch();  // Pausa
    }

    fclose(consumidores);  // Fechar arquivo

    printf("\n\tENTER PARA RETORNAR AO MENU PRINCIPAL");
    menu();  // Direciona para o menu principal

}

// Cadastro de contrato 
void cadastro_contrato(void) {
    iniciar(); // Limpezas e nome do sistema

    // Declarações 
    // STRUCTs com dados do consumidor, usina e contrato a ser realizado
    STRUCTconsumidor consumidor;
    STRUCTusina usina;
    STRUCTcontrato contrato;

    // Variáveis auxiliares
    int etapa;
    int id_consumidor;
    char usina_id[id], consumidor_id[id];
    char consulta[num_max];
    char nomes[num_max];
    char nomes2[num_max];
    char i[num_max]; i[0] = 'i';
    char a[num_max];
    int cont;

    FILE *usinas, *consumidores, *contratos; // Declaração dos arquivos

    // Comandos 
    // Abertura dos arquivos
    usinas = fopen("arquivo_usinas.txt", "r");
    consumidores = fopen("arquivo_consumidores.txt", "r");
    contratos = fopen("arquivo_contratos.txt", "a+");

    etapa = 1; // Iniciar o processo de contratação

    while (etapa == 1) { // Obter dados da usina
        printf("NOME DAS USINAS CADASTRADAS: \n"); // Lista as usinas cadastradas
        while (fgets(nomes, num_max, usinas) != NULL) { // Leitura do arquivo todo
            if (nomes[0] == '>') { // Critério de seleção do nome
                printf("%s", nomes); // Imprime na tela
            }
        }
        rewind(usinas); // Retorna ao início do arquivo

        fflush(stdin); // Limpa o teclado

        printf("CNPJ DA USINA QUE DESEJA CONTRATAR: "); // Solicita o CNPJ da usina
        scanf("%s", contrato.cnpj_usina); // Leitura do CNPJ

        strcpy(i, contrato.cnpj_usina);

        // Concatena o CNPJ informado para ser inserido no início do critério de busca
        for (cont = 0; cont < 14; cont++) {
            i[cont + 1] = a[cont];
        }

        while (fgets(nomes, num_max, usinas) != NULL) { // Leitura de todo o arquivo
            printf("salvo1");
            if (strcmp(nomes, contrato.cnpj_usina) == 0) { // Compara o CNPJ informado com os cadastrados
                printf("salvo2");
                while (fgets(nomes2, num_max, usinas) != NULL) { // Leitura das informações posteriores ao CNPJ encontrado
                    printf("salvo3");
                    fprintf(contratos, "%s\n", contrato.cnpj_usina); // Salva o CNPJ da usina no arquivo de contrato
                    printf("salvo4");
                    if (strcmp(nomes2, ">") > 0) { // Critério de finalização das informações
                        etapa = 2;
                    }
                }
            }
        }
    }
    fclose(usinas); // Fecha o arquivo das usinas

    while (etapa == 2) { // Obter dados do consumidor
        printf("IDENTIFICACAO\n 1-CPF\n 2-CNPJ\n"); // Solicita o documento de identificação do consumidor
        scanf("%d", &id_consumidor); // Leitura da escolha de documento

        if (id_consumidor == 1) { // Caso seja CPF
            printf("CPF do contratante: "); // Solicita o CPF do consumidor
            scanf("%s", contrato.cpf_consumidor); // Leitura do CPF

            while (fgets(consumidor_id, num_max, consumidores) != NULL) { // Leitura do arquivo com o cadastro dos consumidores
                if (strcmp(contrato.cpf_consumidor, consumidor_id) == 0) { // Compara o CPF informado com os cadastrados, buscando as informações relacionadas ao CPF
                    // Caso encontre
                    fprintf(contratos, "%s\n", contrato.cpf_consumidor); // Salva o CPF do usuário no arquivo de contrato
                    etapa = 3; // Autoriza a próxima parte do processo, quebrando o ciclo while
                    break; // Sai do ciclo while
                }
            }
        } else if (id_consumidor == 2) { // Caso seja CNPJ
            printf("CNPJ do contratante: "); // Solicita o CNPJ do consumidor
            scanf("%s", contrato.cnpj_consumidor); // Leitura do CNPJ

            while (fgets(consumidor_id, num_max, consumidores) != NULL) { // Leitura do arquivo com o cadastro dos consumidores
                if (strcmp(contrato.cnpj_consumidor, consumidor_id) == 0) { // Compara o CNPJ informado com os cadastrados, buscando as informações relacionadas ao CNPJ
                    // Caso encontre
                    fprintf(contratos, "%s\n", contrato.cnpj_consumidor); // Salva o CNPJ do usuário no arquivo de contrato
                    etapa = 3; // Autoriza a próxima parte do processo, quebrando o ciclo while
                    break; // Sai do ciclo while
                }
            }
        }
    }
    fclose(consumidores); // Fecha o arquivo dos consumidores

    while (etapa == 3) { // Obter dados da potência para o contrato
        printf("Potencia desejada: "); // Solicita a potência que deseja contratar
        scanf("%lf", &contrato.potencia_contratada); // Leitura da potência

        fprintf(contratos, "%lf\n", contrato.potencia_contratada); // Salva a potência no arquivo de contratos
        etapa = 4; // Autoriza a próxima parte do processo, quebrando o ciclo while
        break; // Sai do ciclo while
    }

    while (etapa == 4) { // Obter a data do contrato
        printf("Data do contrato: (DD/MM/AAAA) "); // Solicita a data de início do contrato
        scanf_s("%d/%d/%d", &contrato.d, &contrato.m, &contrato.a); // Leitura da data

        fprintf(contratos, "%d\t%d\t/%d\n", contrato.d, contrato.m, contrato.a); // Salva a data no arquivo de contratos
        etapa = 5; // Autoriza a próxima parte do processo, quebrando o ciclo while
        break; // Sai do ciclo while
    }
    fclose(contratos); // Fecha o arquivo dos contratos

    printf("\n\tENTER PARA RETORNAR AO MENU PRINCIPAL");
    getch(); // Pausa
    menu(); // Direciona para o menu principal
}

// Consultar usina 
void consultar_usina(void) {

    iniciar(); // Limpezas e nome do sistema

    // Declarações 
    STRUCTusina usina; // STRUCT com dados das usinas

    // Variáveis auxiliares
    char consulta[num_max];
    char nomes[num_max];
    char nomes2[num_max];
    char i[num_max]; i[0] = 'i';
    char a[num_max];
    int cont;

    FILE *usinas; // Declaração do arquivo

    // Comandos 
    usinas = fopen("arquivo_usinas.txt", "rb"); // Abertura do arquivo das usinas

    printf("NOME DAS USINAS CADASTRADAS: \n"); // Lista as usinas cadastradas
    while (fgets(nomes, num_max, usinas) != NULL) { // Leitura do arquivo todo
        if (nomes[0] == '>') { // Critério de seleção do nome
            printf("%s", nomes); // Imprime na tela
        }
    }

    rewind(usinas); // Retorna ao início do arquivo

    fflush(stdin); // Limpa o teclado

    printf("\nDIGITE O CNPJ DA EMPRESA QUE DESEJA OBTER MAIS INFORMACOES: \n"); // Solicita o CNPJ da usina desejada
    scanf("%s", &a); // Leitura do CNPJ desejado

    // Concatena o CNPJ informado para ser inserido no início do critério de busca de CNPJ
    for (cont = 0; cont < 14; cont++) {
        i[cont + 1] = a[cont];
    }

    while (fscanf(usinas, "%s", nomes) != NULL) { // Leitura de todo o arquivo
        if (strcmp(nomes, i) == 0) { // Compara o CNPJ informado com os cadastrados
            while (fgets(nomes2, num_max, usinas) != NULL) { // Leitura das informações posteriores ao CNPJ encontrado
                printf("%s", nomes2); // Imprime as informações encontradas
                printf("NAO HA MAIS INFORMACOES SOBRE ESSE CADASTRO"); // Informa sobre a ausência de mais informações
                if (strcmp(nomes2, "_") > 0) { // Critério de finalização do bloco de informações
                    break; // Pausa do sistema
                    fclose(usinas); // Fecha o arquivo
                }
            }
        }
    }
    printf("\n\t ENTER PARA RETORNAR AO MENU PRINCIPAL");
    getch(); // Pausa

    menu(); // Direciona para o menu principal
}

// Consultar consumidor 
void consultar_consumidor(void) {

    iniciar(); // Limpezas e nome do sistema

    // Declarações 
    STRUCTusina consumidor; // STRUCT com dados dos consumidores

    // Variáveis auxiliares
    char consulta[id];
    char nomes[num_max];
    char nomes2[num_max];
    char f[num_max]; f[0] = 'f';
    char j[num_max]; j[0] = 'j';
    char a[num_max];
    char b[num_max];
    int cont;
    int id_consumidor;

    FILE *consumidores; // Declaração do arquivo

    // Comandos 
    consumidores = fopen("arquivo_consumidores.txt", "rb"); // Abertura do arquivo dos consumidores

    printf("NOME DOS CONSUMIDORES CADASTRADOS: \n"); // Lista dos consumidores cadastrados
    while (fgets(nomes, num_max, consumidores) != NULL) { // Leitura do arquivo todo
        if (nomes[0] == '>') { // Critério de seleção do nome
            printf("%s", nomes); // Imprime na tela
        }
    }

    rewind(consumidores); // Retorna ao início do arquivo

    fflush(stdin); // Limpa o teclado

    printf("\nFORMA DE IDENTIFICACAO DO CONSUMIDOR\n 1-CPF\n 2-CNPJ\n"); // Solicita a forma de identificação do consumidor
    scanf("%d", &id_consumidor); // Leitura da escolha de documento

    if (id_consumidor == 1) { // Em caso de CPF
        printf("\nDIGITE O CPF DO CONSUMIDOR QUE DESEJA OBTER MAIS INFORMACOES: \n"); // Solicita o CPF do consumidor desejado
        scanf("%s", &a); // Leitura do CPF desejado

        // Concatena o CPF informado para ser inserido no início do critério de busca de CPF
        for (cont = 0; cont < 12; cont++) {
            f[cont + 1] = a[cont];
        }

        while (fscanf(consumidores, "%s", nomes) != NULL) { // Leitura de todo o arquivo
            if (strcmp(consumidores, f) == 0) { // Compara o CPF informado com os cadastrados
                while (fgets(nomes2, num_max, consumidores) != NULL) { // Leitura das informações posteriores ao CPF encontrado
                    printf("%s", nomes2); // Imprime as informações encontradas
                    printf("NAO HA MAIS INFORMACOES SOBRE ESSE CADASTRO"); // Informa sobre a ausência de mais informações
                    if (strcmp(nomes2, "_") > 0) { // Critério de finalização do bloco de informações
                        break; // Pausa do sistema
                        fclose(consumidores); // Fecha o arquivo
                    }
                }
            }
            printf("\n\tENTER PARA RETORNAR AO MENU PRINCIPAL");
            getch(); // Pausa

            menu(); // Direciona para o menu principal
        }
    } else if (id_consumidor == 2) { // Em caso de CNPJ
        printf("\nDIGITE O CNPJ DO CONSUMIDOR QUE DESEJA OBTER MAIS INFORMACOES: \n"); // Solicita o CNPJ do consumidor desejado
        scanf("%s", &b); // Leitura do CNPJ desejado

        // Concatena o CNPJ informado para ser inserido no início do critério de busca de CNPJ
        for (cont = 0; cont < 12; cont++) {
            j[cont + 1] = b[cont];
        }

        while (fscanf(consumidores, "%s", nomes) != NULL) { // Leitura de todo o arquivo
            if (strcmp(nomes, j) == 0) { // Compara o CNPJ informado com os cadastrados
                while (fgets(nomes2, num_max, consumidores) != NULL) { // Leitura das informações posteriores ao CNPJ encontrado
                    printf("%s", nomes2); // Imprime as informações encontradas
                    printf("NAO HA MAIS INFORMACOES SOBRE ESSE CADASTRO"); // Informa sobre a ausência de mais informações
                    if (strcmp(nomes2, "_") > 0) { // Critério de finalização do bloco de informações
                        break; // Pausa do sistema
                        fclose(consumidores); // Fecha o arquivo
                    }
                }
            }
            printf("\n\tENTER PARA RETORNAR AO MENU PRINCIPAL");
            getch(); // Pausa

            menu(); // Direciona para o menu principal
        }
    }
}

// Excluir usina -
void excluir_usina(void) {

    iniciar(); // Limpezas e nome do sistema

    // Declarações 
    STRUCTusina usina; // STRUCT com dados da usina

    // Variáveis auxiliares
    char consulta[num_max];
    char nomes[num_max];
    char nomes2[num_max];
    char i[num_max]; i[0] = 'i';
    char a[num_max];
    int cont;

    // Declaração dos arquivos
    FILE *usinas;
    FILE *arq_usinas; // Arquivo temporário

    // Comandos 
    // Abertura dos arquivos
    usinas = fopen("arquivo_usinas.txt", "rb");
    arq_usinas = fopen("arquivo_novo_usinas.txt", "ab");

    printf("NOME DAS USINAS CADASTRADAS: \n"); // Lista as usinas cadastradas
    while (fgets(nomes, num_max, usinas) != NULL) { // Leitura do arquivo todo
        if (nomes[0] == '>') { // Critério de seleção do nome
            printf("%s", nomes); // Imprime na tela
        }
    }

    rewind(usinas); // Retorna ao início do arquivo

    fflush(stdin); // Limpa o teclado

    printf("DIGITE O CNPJ DA USINA A SER EXCLUIDA: "); // Solicita o CNPJ da usina a ser apagada
    scanf("%s", &consulta); // Leitura do CNPJ informado

    while (fread(&usina, sizeof(STRUCTusina), 1, usinas) == 1) { // Ciclo de leitura do arquivo das usinas
        if (strcmp(consulta, usina.cnpj) != 0) { // Compara o CNPJ informado com os salvos no arquivo, buscando os que são diferentes do informado
            fwrite(&usina, sizeof(STRUCTusina), 1, arq_usinas); // Escreve no arquivo temporário as informações que são diferentes da informada
        }
    }

    // Fechar os arquivos
    fclose(usinas);
    fclose(arq_usinas);

    remove("arquivo_usinas.txt"); // Remove o arquivo usado anteriormente

    rename("arquivo_novo_usinas.txt", "arquivo_usinas.txt"); // Renomeia o novo arquivo

    printf("\nUSINA EXCLUIDA!"); // Informa que a usina foi realmente excluída

    printf("\n\t PARA RETORNAR AO MENU PRINCIPAL");
    getch(); // Pausa

    menu(); // Direciona para o menu principal

/*  
    //TENTATIVA DE EXCLUIR APENAS A USINA ESCOLHIDA
    printf("\nDIGITE O CNPJ DA EMPRESA QUE DESEJA REMOVER: \n");     //solicita o cnpj da usina desejada
    scanf("%s", &a);        //leitura do cnpj desejado

    //concatena o cnpj informado de modo que seja inserido no inicio o criterio de busca de cnpj
    for (cont=0; cont<14; cont++){
        i[cont+1]=a[cont];
    }

    while(fscanf(usinas,"%s",nomes) != NULL){       //leitura de todo o arquivo
        if (strcmp(nomes, i) == 0){     //compara o cnpj informado com os cadastrados
            while (fgets(nomes2, num_max, usinas) != NULL){     //leitura das informações posteriores ao cnpj encontrado
                fwrite(&usina, sizeof(STRUCTusina), 1, arq_usinas);     //escreve no arquivo temporario as informações que são diferentes da informada
                if(strcmp(nomes2, "_") >0){         //criterio de finalização do bloco de informações
                    //fechar os arquivos
                    fclose(usinas);
                    fclose(arq_usinas);

                    remove("arquivo_usinas.txt");       //remove o arquivo usado anteriormente

                    rename("arquivo_novo_usinas.txt", "arquivo_usinas.txt");        //renomea o novo arquivo

                    printf("\nUSINA EXCLUIDA!");        //informa que a usina foi realmente excluida
                    break;      //pausa do sistema
                }
            }
        }
    printf("\n\t ENTER PARA RETORNAR AO MENU PRINCIPAL");
    getch();        //pausa

    menu();     //direciona para o menu principal
    }

*/

}

// Excluir consumidor 
void excluir_consumidor(void) {

    iniciar(); // Limpezas e nome do sistema

    // Declarações 
    STRUCTconsumidor consumidor; // STRUCT com dados do consumidor

    // Variáveis auxiliares
    char consulta[id];
    int id_consumidor;

    // Declaração dos arquivos
    FILE *consumidores;
    FILE *arq_consumidores; // Arquivo temporário

    // Comandos 
    // Abertura dos arquivos
    consumidores = fopen("arquivo_consumidores.txt", "rb");
    arq_consumidores = fopen("arquivo_novo_consumidores.txt", "ab");

    if (consumidores == NULL || arq_consumidores == NULL) { // Confere a existência, abertura e autorização do arquivo
        printf("ERRO NA ABERTURA DO ARQUIVO!"); // Informa caso haja erro
        return 1; // Sai do sistema
    } else { // Caso esteja tudo certo
        printf("IDENTIFICACAO DO CONSUMIDOR A SER EXCLUIDO\n 1-CPF\n 2-CNPJ\n"); // Solicita o documento de identificação do consumidor
        scanf("%d", &id_consumidor); // Leitura da escolha de documento

        if (id_consumidor == 1) { // Em caso de CPF
            printf("DIGITE O CPF DO CONSUMIDOR A SER EXCLUIDO: "); // Solicita o CPF do consumidor
            scanf("%s", &consulta); // Leitura do CPF do consumidor

            while (fread(&consumidor, sizeof(STRUCTconsumidor), 1, consumidores) == 1) { // Ciclo de leitura do arquivo dos consumidores
                if (strcmp(consulta, consumidor.CPF) != 0) { // Compara o CPF informado com os salvos no arquivo, buscando os que são diferentes do informado
                    fwrite(&consumidor, sizeof(STRUCTconsumidor), 1, arq_consumidores); // Escreve no arquivo temporário as informações que são diferentes da informada
                }
            }

        } else if (id_consumidor == 2) { // Em caso de CNPJ
            printf("DIGITE O CNPJ DO CONSUMIDOR A SER EXCLUIDO: "); // Solicita o CNPJ do consumidor
            scanf("%s", &consulta); // Leitura do CNPJ do consumidor

            while (fread(&consumidor, sizeof(STRUCTconsumidor), 1, consumidores) == 1) { // Ciclo de leitura do arquivo dos consumidores
                if (strcmp(consulta, consumidor.CNPJ) != 0) { // Compara o CNPJ informado com os salvos no arquivo, buscando os que são diferentes do informado
                    fwrite(&consumidor, sizeof(STRUCTconsumidor), 1, arq_consumidores); // Escreve no arquivo temporário as informações que são diferentes da informada
                }
            }

        }
    }

/*
    //TENTATIVA DE EXCLUIR APENAS O CONSUMIDOR ESCOLHIDO
    if(consumidores == NULL || arq_consumidores ==NULL){         //confere a existencia, abertura e autorização do arquivo
        printf("ERRO NA ABERTURA DO ARQUIVO!");     //informa caso haja erro
        return 1;       //sai do sistema
    }else{      //caso esteja tudo certo
        printf("IDENTIFICAÇÃO DO CONSUMIDOR A SER EXCLUIDO\n 1-CPF\n 2-CNPJ\n");        //solicita o documento de identificação do consumidor
        scanf("%d", &id_consumidor);        //leitura da escolha de documento

        if(id_consumidor==1){       //em caso de cpf
            printf("DIGITE O CPF DO CONSUMIDOR A SER EXCLUIDO: ");      //solicita o cpf do consumidor
            scanf("%s", &consulta);        //leitura do cpf do consumidor

            while(fread(&consumidor, sizeof(STRUCTconsumidor), 1, consumidores)==1){        //ciclo de leitura do arquivo dos consumidores
                if(strcmp(consulta, consumidor.CPF)!=0){        //compara o cpf informado com os salvos no arquivo, buscando os que sao diferentes do informado
                    fwrite(&consumidor, sizeof(STRUCTconsumidor), 1, arq_consumidores);     //escreve no arquivo temporario as informações que são diferentes da informada
                }
            }

        }else if(id_consumidor==2){     //em caso de cnpj
            printf("DIGITE O CNPJ DO CONSUMIDOR A SER EXCLUIDO: ");     //solicita o cnpj do consumidor
            scanf("%s", &consulta);     //leitura do cnpj do consumidor

            while(fread(&consumidor, sizeof(STRUCTconsumidor), 1, consumidores)==1){        //ciclo de leitura do arquivo dos consumidores
                if(strcmp(consulta, consumidor.CNPJ)!=0){       //compara o cmpj informado com os salvos no arquivo, buscando os que são diferentes do informado
                    fwrite(&consumidor, sizeof(STRUCTconsumidor), 1, arq_consumidores);     //escreve no arquivo temporario as nformações que são diferente da informada
                }
            }

        }
    }
*/


    // Fecha os arquivos
    fclose(consumidores);
    fclose(arq_consumidores);

    remove("arquivo_consumidores.txt"); // Remove o arquivo usado anteriormente

    rename("arquivo_novo_consumidores.txt", "arquivo_consumidores.txt"); // Renomeia o novo arquivo

    // Pausa e menu
    printf("\nCONSUMIDORES EXCLUIDOS!"); // Informa que o consumidor foi realmente excluído

    printf("\n\tENTER PARA RETORNAR AO MENU PRINCIPAL");
    getch(); // Pausa

    menu(); // Direciona para o menu principal
}

// Programa principal
int main() {
    setlocale(LC_ALL, "Portuguese");  // Configuração da localidade para Português
    menu();                           // Chama a função menu() para direcionar para o menu principal

    return 0;                         // Retorna 0 para indicar que o programa foi executado com sucesso
}