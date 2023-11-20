//bibliotecas----------------------------------------------------------------------------------------------------------------
#include <locale.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//constantes-----------------------------------------------------------------------------------------------------------------
#define id 15
#define num_max 100

//STRUCT---------------------------------------------------------------------------------------------------------------------
typedef struct{
    char nome_usina[num_max];
    char cnpj[id];
    int dia;
    int mes;
    int ano;
    double potencia_estimada;
} STRUCTusina;

typedef struct{
    char nome_consumidor[num_max];
    char CPF[id];
    char CNPJ[id];
} STRUCTconsumidor;

typedef struct{
    char cnpj_usina, cnpj_consumidor, cpf_consumidor;
    int d, m, a;
    float potencia_contratada;
} STRUCTcontrato;

//iniciar -------------------------------------------------------------------------------------------------------------------
void iniciar (void){

    setlocale(LC_ALL, "Portuguese");

    fflush (stdin);     //limpar teclado
    system("clear||cls");       //limpar tela

    printf("//////////////////////////////////////\n");
    printf("SGC - SISTEMA DE GERAÇÃO COMPARTILHADA\n");     //nome do sistema
    printf("//////////////////////////////////////\n\n");

}

//menu ----------------------------------------------------------------------------------------------------------------------
void menu (void){

    iniciar();      //limpezas e nome do sistema

//declarações ---------------------------------------------------------------------------------------------------------------
    int opcao;

//comandos ------------------------------------------------------------------------------------------------------------------

    //opções de funções
    printf("SELECIONE A OPÇÃO DESEJADA\n");
    printf("\t1) Cadastrar Usina\n");
    printf("\t2) Cadastrar Consumidor\n");
    printf("\t3) Cadastrar Contrato entre Consumidor e Usina\n");
    printf("\t4) Consultar Usina Cadastrada\n");
    printf("\t5) Consultar Consumidor Cadastrado\n");
    printf("\t6) Excluir Usina\n");
    printf("\t7) Excluir Consumidor\n\n");

    printf("Escolha uma opção: ");      //solicita a função
    scanf("%d", &opcao);       //leitura da escolha

//chamamento das funções ----------------------------------------------------------------------------------------------------

    if(opcao==1){
        cadastro_usina();
    }else if(opcao==2){
        cadastro_consumidor();
    }else if(opcao==3){
        cadastro_contrato();
    }else if(opcao==4){
        consultar_usina();
    }else if(opcao==5){
        consultar_consumidor();
    }else if(opcao==6){
        excluir_usina();
    }else if(opcao==7){
        excluir_consumidor();
    }else if(opcao<1||opcao>7){
        printf("ERRO: OPÇÃO INEXISTENTE");
    }

}

//cadastro usina ------------------------------------------------------------------------------------------------------------
void cadastro_usina (void){

    iniciar();      //limpezas e nome do sistema

//declarações----------------------------------------------------------------------------------------------------------------
    STRUCTusina usina;      //dados da usina

    char cop_cnpj[id];  //copia do cnpj informado

    //variaveis auxiliares
    int numero[id], cont;
    int somatorioA, somatorioB;
    int restoA, restoB;
    char digitoA, digitoB;
    double potencia;
    int f; f="----";

    int v_cnpj, v_dia, v_mes, v_ano, v_potencia;        //verificadores

    FILE*usinas;        //declaração do arquivo

//comandos ------------------------------------------------------------------------------------------------------------------

    usinas = fopen("arquivo_usinas.txt", "a+");     //abertura do arquivo

    //confere a existencia, abertura e autorização do arquivo
    if(usinas == NULL){
        printf("ERRO NA ABERTURA DO ARQUIVO!");
    return 1;
    }

    printf("nome da usina: \n");        //solicita o nome da usina
    gets(usina.nome_usina);     //leitura do nome da usina
    fflush (stdin);     //limpeza do teclado

    printf("\nCNPJ: \n");       //solicita o cnpj da usina
    gets(usina.cnpj);       //leitura do cnpj da usina
    strcpy(cop_cnpj, usina.cnpj);       //copia o cnpj na variavel auxiliar

    //transforma os numeros do cnpj em int para a verificação da validade
    for (cont=0; cont<14; cont++){
        numero[cont]=cop_cnpj[cont]-48;     //'48' para tira o 0 armazenado nas strings
    }

    //multiplica cada um dos primeiros 12 numeros pelo seu correspondente da sequencia auxiliar (5,4,3,2,9,8,7,6,5,4,3,2) e soma os resultados
    somatorioA = (numero[0]*5)+(numero[1]*4)+(numero[2]*3)+(numero[3]*2)+(numero[4]*9)+(numero[5]*8)+(numero[6]*7)+(numero[7]*6)+(numero[8]*5)+(numero[9]*4)+(numero[10]*3)+(numero[11]*2);

    //obtem o resto da divisão do somatorio anterior por 11
    restoA = somatorioA % 11;

    //condiciona resto de acordo com o valor obtido anteriormente para obter o primeiro digito verificador
    if(restoA==1||restoA==0){
        digitoA=0;
    }else{
        digitoA=11-restoA;
    }

    //multiplica cada um dos primeiros 12 numeros e do primeiro digito verificador pelo seu correspondente da sequencia auxiliar (6,5,4,3,2,9,8,7,6,5,4,3,2) e soma os resultados
    somatorioB = (numero[0]*6)+(numero[1]*5)+(numero[2]*4)+(numero[3]*3)+(numero[4]*2)+(numero[5]*9)+(numero[6]*8)+(numero[7]*7)+(numero[8]*6)+(numero[9]*5)+(numero[10]*4)+(numero[11]*3)+(digitoA*2);

    //obtem o resto da divisão do somatorio anterior por 11
    restoB = somatorioB % 11;

    //condiciona o resto de acordo com o valor obtido anteriormente para obter o segundo digito verificador
    if(restoB==1||restoB==0){
         digitoB=0;
    }else{
         digitoB=11-restoB;
    }

    //compara os digitos obtidos com os digitos informados para poder validar o cnpj
    if(digitoA==numero[12]&&digitoB==numero[13]){
        printf("CNPJ VÁLIDO\n\n");      //informa que é valido o cnpj
        v_cnpj=1;       //atribui 1 ao validador
    }else{
        printf("CNPJ INVÁLIDO\n\n");        //informa que é inválido o cnpj
        v_cnpj=2;       //atribui 2 ao validador
    }

    printf("data início da operação (DD/MM/AAA):\n");       //solicita a data da operação
    scanf_s("%d/%d/%d", &usina.dia, &usina.mes, &usina.ano);        //leitura da data informada

        //condições de validação da data, considerando 12 meses, quantidade de dias previstos para cada mês, anos D.C. e anos bissextos
        if (usina.mes < 1 || usina.mes > 12 || usina.ano < 0){
            printf ("DATA INVÁLIDA\n\n");       //informa que é inválida a data
            v_dia=2; v_mes=2; v_ano=2;      //atribui 2 aos validadores
        }else if (usina.mes == 2 && (usina.dia > 28 || usina.dia < 1)&& ((usina.ano % 4 != 0) || ((usina.ano % 100 == 0 && (usina.ano % 400 != 0))))){
            printf ("DATA INVÁLIDA\n\n");       //informa que é inválida a data
            v_dia=2; v_mes=2; v_ano=2;      //atribui 2 aos validadores
        }else if ((usina.mes == 4 || usina.mes == 6 || usina.mes == 9 || usina.mes == 11)&& (usina.dia < 1 || usina.dia > 30)){
            printf ("DATA INVÁLIDA\n\n");       //informa que é inválida a data
            v_dia=2; v_mes=2; v_ano=2;      //atribui 2 aos validadores
        }else if ((usina.mes == 1 || usina.mes == 3 || usina.mes == 5 || usina.mes == 7 || usina.mes == 8 || usina.mes == 10|| usina.mes == 12) && (usina.dia < 1 || usina.dia > 31)){
            printf ("DATA INVÁLIDA\n\n");       //informa que é inválida a data
            v_dia=2; v_mes=2; v_ano=2;      //atribui 2 aos validadores
        }else if (usina.mes == 2 && (usina.dia < 1 || usina.dia > 29)){
            printf ("DATA INVÁLIDA\n\n");       //informa que é inválida a data
            v_dia=2; v_mes=2; v_ano=2;      //atribui 2 aos validadores
        }else{
            printf ("DATA VÁLIDA\n\n");     //informa que é válida a data
            v_dia=1; v_mes=1; v_ano=1;      //atribui 1 aos validadores
        }

    fflush (stdin);     //limpa o teclado
    printf("potência estimada: \n");        //solicita a potencia estimada
    scanf("%lf", &usina.potencia_estimada);         //leitura da potencia informada

    //verificação da potencia considerando apenas que seja positiva
    if(usina.potencia_estimada<=0){
        printf("POTENCIA INVÁLIDA\n\n");        //informa que é inválida a potencia
        v_potencia=2;       //atribui 2 ao validador
    }else{
        printf("POTÊNCIA VÁLIDA\n\n");      //informa que é válida a potencia
        v_potencia=1;       //atribui 1 ao validado
    }

    //salvar dados apenas se os verificadores tiverem valor 1(válidos)
    if(v_cnpj==1&&v_dia==1&&v_mes==1&&v_ano==1&&v_potencia==1){

        fprintf(usinas, "\ni%s\n", usina.cnpj);        //armazena no arquivo o cnpj informado
        fprintf(usinas, ">%s\n", usina.nome_usina);      //armazena no arquivo o nome informado
        fprintf(usinas, "%d\t%d\t%d\n", usina.dia, usina.mes, usina.ano);     //armazena no arquivo a data informado
        fprintf(usinas, "%lf\n", usina.potencia_estimada);      //armazena no arquivo a potencia informada
        fputc('_', usinas);  //separa o bloco de cadastro

        printf("\nDADOS GRAVADOS COM SUCESSO!");        //informa que os dados foram salvos
        getch();        //pausa
    }else{
        printf("\nNÃO FOI POSSÍVEL GRAVAR OS DADOS!");      //informa que os dados não foram salvos
        getch();        //pausa
    }

    fclose(usinas);     //fechar arquivo

    printf("\n\tENTER PARA RETORNAR AO MENU PRINCIPAL");
    menu();     //direciona para o menu principal

}

//cadastro consumidor -------------------------------------------------------------------------------------------------------
void cadastro_consumidor(void){

    iniciar();      //limpezas e nome do sistema

//declarações --------------------------------------------------------------------------------------------------------------
    STRUCTconsumidor consumidor;        //dados do consumidor

    //copia do cpf e do cnpj
    char cop_cpf[id];
    char cop_cnpj[id];

    //variaveis auxiliares
    int num[id], contador;
    int numero[id], cont;
    int id_consumidor;
    int somatorioA, somatorioB;
    int restoA, restoB;
    char digitoA, digitoB;
    int somatorioAA, somatorioBB;
    char digitoAA, digitoBB;
    int restoAA, restoBB;

    int v_cfp_consumidor, v_cnpj_consumidor;        //validadores

    FILE*consumidores;      //declaração do arquivo

//comandos ------------------------------------------------------------------------------------------------------------------

    consumidores = fopen("arquivo_consumidores.txt", "a+");     //abrir arquivo

    //confere a existencia, abertura e autorização do arquivo
    if(consumidores == NULL){
        printf("ERRO NA ABERTURA DO ARQUIVO!");
    return 1;
    }

    //identificação


    printf("nome do consumidor: \n");       //solicita o nome do consumidor
    gets(consumidor.nome_consumidor);       //leitura do nome do consumidor
    fflush (stdin);     //limpeza do teclado

    printf("IDENTIFICAÇÃO\n 1-CPF\n 2-CNPJ\n");     //solicita o documento de identificação do consumidor
    scanf("%d", &id_consumidor);        //leitura da escolha de documento

    if(id_consumidor==1){       //em caso de cpf
        printf("CPF: \n");      //solicita o cpf do consumidor
        scanf("%s",&consumidor.CPF);        //leitura do cpf do consumidor
        strcpy(cop_cpf, consumidor.CPF);        //copia o cpf na variavel auxiliar

        //transforma os numeros do cpf em int para a verificação da validade
        for (contador=0; contador<11; contador++){
            num[contador]=cop_cpf[contador]-48;
        }

        //multiplica cada um dos primeiros 9 numeros pelo seu correspondente da sequencia auxiliar (10,9,8,7,6,5,4,3,2) e soma os resultados
        somatorioA = (num[0]*10)+(num[1]*9)+(num[2]*8)+(num[3]*7)+(num[4]*6)+(num[5]*5)+(num[6]*4)+(num[7]*3)+(num[8]*2);

        //obtem o resto da divisão do somatorio anterior por 11
        restoA = somatorioA % 11;

        //condiciona resto de acordo com o valor obtido anteriormente para obter o primeiro digito verificador
        if(restoA==1||restoA==0){
            digitoA=0;
        }else{
            digitoA=11-restoA;
        }

        //multiplica cada um dos primeiros 9 numeros e do primeiro digito verificador pelo seu correspondente da sequencia auxiliar (11,10,9,8,7,6,5,4,3,2) e soma os resultados
        somatorioB = (num[0]*11)+(num[1]*10)+(num[2]*9)+(num[3]*8)+(num[4]*7)+(num[5]*6)+(num[6]*5)+(num[7]*4)+(num[8]*3)+(digitoA*2);

        //obtem o resto da divisão do somatorio anterior por 11
        restoB = somatorioB % 11;

        //condiciona o resto de acordo com o valor obtido anteriormente para obter o segundo digito verificador
        if(restoB==1||restoB==0){
            digitoB=0;
        }else{
            digitoB=11-restoB;
        }

        //compara os digitos obtidos com os digitos informados para poder validar o cpf
        if(digitoA==num[9]&&digitoB==num[10]){
            printf("CPF VÁLIDO\n\n");       //informa que é valido o cpf
            v_cfp_consumidor=1;       //atribui 1 ao validador
        }else{
            printf("CPF INVÁLIDO\n\n");     //informa que é inválido o cpf
            v_cfp_consumidor=2;       //atribui 2 ao validador
        }
    }else if(id_consumidor==2){     //em caso de cnpj
        printf("CNPJ: \n");     //solicita o cnpj do consumidor
        scanf("%s",&consumidor.CNPJ);       //leitura do cnpj da do consumidor
        strcpy(cop_cnpj, consumidor.CNPJ);      //copia o cnpj na variavel auxiliar

        //transforma os numeros do cnpj em int para a verificação da validade
        for (cont=0; cont<14; cont++){
            numero[cont]=cop_cnpj[cont]-48;     //'48' para tira o 0 armazenado nas strings
        }

        //multiplica cada um dos primeiros 12 numeros pelo seu correspondente da sequencia auxiliar (5,4,3,2,9,8,7,6,5,4,3,2) e soma os resultados
        somatorioAA = (numero[0]*5)+(numero[1]*4)+(numero[2]*3)+(numero[3]*2)+(numero[4]*9)+(numero[5]*8)+(numero[6]*7)+(numero[7]*6)+(numero[8]*5)+(numero[9]*4)+(numero[10]*3)+(numero[11]*2);

        //obtem o resto da divisão do somatorio anterior por 11
        restoAA = somatorioAA % 11;

        //condiciona resto de acordo com o valor obtido anteriormente para obter o primeiro digito verificador
        if(restoAA==1||restoAA==0){
            digitoAA=0;
        }else{
            digitoAA=11-restoAA;
        }

        //multiplica cada um dos primeiros 12 numeros e do primeiro digito verificador pelo seu correspondente da sequencia auxiliar (6,5,4,3,2,9,8,7,6,5,4,3,2) e soma os resultados
        somatorioBB = (numero[0]*6)+(numero[1]*5)+(numero[2]*4)+(numero[3]*3)+(numero[4]*2)+(numero[5]*9)+(numero[6]*8)+(numero[7]*7)+(numero[8]*6)+(numero[9]*5)+(numero[10]*4)+(numero[11]*3)+(digitoAA*2);

        //obtem o resto da divisão do somatorio anterior por 11
        restoBB = somatorioBB % 11;

        //condiciona o resto de acordo com o valor obtido anteriormente para obter o segundo digito verificador
        if(restoBB==1||restoBB==0){
            digitoBB=0;
        }else{
            digitoBB=11-restoBB;
        }

        //compara os digitos obtidos com os digitos informados para poder validar o cnpj
        if(digitoAA==numero[12]&&digitoBB==numero[13]){
            printf("CNPJ VÁLIDO\n\n");      //informa que é valido o cnpj
            v_cnpj_consumidor=1;       //atribui 1 ao validador
        }else{
            printf("CNPJ INVÁLIDO\n\n");        //informa que é inválido o cnpj
            v_cnpj_consumidor=2;       //atribui 2 ao validador
        }
    }

    //salvar dados apenas se o verificadore tiver valor 1(válido)
    if(v_cfp_consumidor==1){
        fprintf(consumidores, "\n>%s\n", consumidor.nome_consumidor);       //armazena no arquivo o nome informado
        fprintf(consumidores, "f%s\n", consumidor.CPF);     //armazena no arquivo o cpf informado
        fputc('_', consumidores);  //separa o bloco de cadastro

        printf("\nDADOS GRAVADOS COM SUCESSO!");
        printf("\n\tENTER PARA RETORNAR AO MENU PRINCIPAL");
        getch();        //pausa
    }else if (v_cnpj_consumidor==1){
        fprintf(consumidores, "\n>%s\n", consumidor.nome_consumidor);       //armazena no arquivo o nome informado
        fprintf(consumidores, "j%s\n", consumidor.CNPJ);        //armazena no arquivo o cnpj informado
        fputc('_', consumidores);  //separa o bloco de cadastro

        printf("\nDADOS GRAVADOS COM SUCESSO!");        //informa que os dados foram salvos
        getch();        //pausa
    }else{
        printf("\nNÃO FOI POSSÍVEL GRAVAR OS DADOS!");      //informa que os dados não foram salvos
        getch();        //pausa
    }

    fclose(consumidores);       //fechar arquivo

    printf("\n\tENTER PARA RETORNAR AO MENU PRINCIPAL");
    menu();     //direciona para o menu principal

}

//cadastro contrato ---------------------------------------------------------------------------------------------------------
void cadastro_contrato (void){

    iniciar();      //limpezas e nome do sistema

//declarações --------------------------------------------------------------------------------------------------------------
    //STRUCTs com dados do consumidor, usina e cotrato a ser realizado
    STRUCTconsumidor consumidor;
    STRUCTusina usina;
    STRUCTcontrato contrato;

    //variaveis auxiliares
    int etapa;
    int id_consumidor;
    char usina_id[id], consumidor_id[id];
    char consulta[num_max];
    char nomes[num_max];
    char nomes2[num_max];
    char i[num_max]; i[0]='i';
    char a[num_max];
    int cont;

    FILE *usinas, *consumidores, *contratos;        //declaração dos arquivos

//comandos ------------------------------------------------------------------------------------------------------------------

    //abertura dos arquivos
    usinas = fopen("arquivo_usinas.txt", "r");
    consumidores = fopen("arquivo_consumidores.txt", "r");
    contratos = fopen("arquivo_contratos.txt", "a+");

    etapa=1;        //iniciar o processo de contratação

    while(etapa==1){        //obter dados da usina
        printf("NOME DAS USINAS CADASTRADAS: \n");      //lista as usinas que ja estão cadastradas
        while (fgets(nomes, num_max, usinas) != NULL){      //leitura do arquivo todo
            if(nomes[0] == '>'){        //criterio de seleção do nome
                printf("%s", nomes);        //imprime na tela
            }
        }
        rewind(usinas);     //retorna ao inicio do arquivo

        fflush(stdin);      //limpa o teclado

        printf("CNPJ DA USINA QUE DESEJA CONTRATAR: ");     //solicita o cnpj da contratada
        scanf("%s", &contrato.cnpj_consumidor);      //leitura do cnpj

        strcpy(i, contrato.cnpj_usina);

        //concatena o cnpj informado de modo que seja inserido no inicio o criterio de busca de cnpj
        for(cont=0; cont<14; cont++){
            i[cont+1]=a[cont];
        }

        while(fgets(nomes, num_max, usinas) != NULL){       //leitura de todo o arquivo
        printf("salvo1");
            if (strcmp(nomes, contrato.cnpj_usina) == 0){     //compara o cnpj informado com os cadastrados
        printf("salvo2");
                while (fgets(nomes2, num_max, usinas) != NULL){     //leitura das informações posteriores ao cnpj encontrado
        printf("salvo3");
                    fprintf(contratos, "%s\n", contrato.cnpj_usina);        //salva o cnpj da usina no arquivo de contrato
                    printf("salvo4");
                    if(strcmp(nomes2, ">") >0){         //criterio de finalização das informações
                    etapa=2;
                    }
                }
            }
        }
    }
fclose(usinas);     //fecha o arquivo das usinas
    while (etapa==2){       //obter dados do consumidor
        printf("IDENTIFICAÇÃO\n 1-CPF\n 2-CNPJ\n");     //solicita o documento de identificação do consumidor
        scanf("%d", &id_consumidor);        //leitura da escolha de documento

        if(id_consumidor==1){       //caso seja cpf
            printf("CPF do contratante: ");     //solicita o cpf do consumidor
            scanf ("%s", &contrato.cpf_consumidor);     //leitura do cpf

            while (fgets(consumidor_id, num_max, consumidores)!=NULL){      //leitura do arquivo com o cadastro dos consumidores
                if(strcmp(contrato.cpf_consumidor, consumidor_id)==0){      //compara o cpf informado com os cadastrados, buscando as informações relacionadas ao cpf
                    //caso encontre
                    fprintf(contratos, "%s\n", contrato.cpf_consumidor);        //salva o cpf do usuario no arquivo de contrato
                    etapa=3;        //autoriza a proxima parte do processo, quebrando o ciclo while
                    break;      //sai do ciclo while
                }
            }
        }else if(id_consumidor==2){     //caso seja cnpj
            printf("CNPJ do contratante: ");        //solicita o cnpj do consumidor
            scanf ("%s", &contrato.cnpj_consumidor);        //leitura do cnpj

            while (fgets(consumidor_id, num_max, consumidores)!=NULL){      //leitura do arquivo com o cadastro dos consumidores
                if(strcmp(contrato.cnpj_consumidor, consumidor_id)==0){      //compara o cnpj informado com os cadastrados, buscando as informações relacionadas ao cnpj
                    //caso encontre
                    fprintf(contratos, "%s\n", contrato.cnpj_consumidor);        //salva o cnpj do usuario no arquivo de contrato
                    etapa=3;        //autoriza a proxima parte do processo, quebrando o ciclo while
                    break;      //sai do ciclo while
                }
            }
        }
    }
fclose(consumidores);     //fecha o arquivo dos consumidores
    while(etapa==3){        //obter dados da potencia para o contrato
        printf("potencia desejada: ");        //solicita a potencia que deseja contratar
        scanf("%lf", contrato.potencia_contratada);     //leitura da potencia

        fprintf(contratos, "%lf\n", contrato.potencia_contratada);      //salva a potencia no arquivo de contratos
        etapa=4;        //autoriza a proxima parte do processo, quebrando o ciclo while
        break;      //sai do ciclo while
    }

    while(etapa==4){        //obter a data do contrato
        printf("data do contrato: (DD/MM/AAAA) ");        //solicita a data de quando deseja iniciar o contrato
        scanf_s("%d/%d/%d", contrato.d, contrato.m, contrato.a);     //leitura da data

        fprintf(contratos, "%d\t%d\t/%d\n", contrato.d, contrato.m, contrato.a);      //salva a data no arquivo de contratos
        etapa=5;        //autoriza a proxima parte do processo, quebrando o ciclo while
        break;      //sai do ciclo while
    }
fclose(contratos);     //fecha o arquivo dos contratos

    printf("\n\tENTER PARA RETORNAR AO MENU PRINCIPAL");
    getch();        //pausa
    menu();     //direciona para o menu principal

}

//consultar usina -----------------------------------------------------------------------------------------------------------
void consultar_usina (void){

    iniciar();      //limpezas e nome do sistema

//declarações --------------------------------------------------------------------------------------------------------------
    STRUCTusina usina;      //STRUCT com dados das usinas

    //variaveis auxiliares
    char consulta[num_max];
    char nomes[num_max];
    char nomes2[num_max];
    char i[num_max]; i[0]='i';
    char a[num_max];
    int cont;

    FILE*usinas;        //declaração do arquivo

//comandos ------------------------------------------------------------------------------------------------------------------

    usinas = fopen ("arquivo_usinas.txt", "rb");        //abertura do arquivo das usinas

    printf("NOME DAS USINAS CADASTRADAS: \n");      //lista as usinas que ja estão cadastradas
    while (fgets(nomes, num_max, usinas) != NULL){      //leitura do arquivo todo
        if(nomes[0] == '>'){        //criterio de seleção do nome
        printf("%s", nomes);        //imprime na tela
        }
    }

    rewind(usinas);     //retorna ao inicio do arquivo

    fflush(stdin);      //limpa o teclado

    printf("\nDIGITE O CNPJ DA EMPRESA QUE DESEJA OBTER MAIS INFORMAÇÕES: \n");     //solicita o cnpj da usina desejada
    scanf("%s", &a);        //leitura do cnpj desejado

    //concatena o cnpj informado de modo que seja inserido no inicio o criterio de busca de cnpj
    for (cont=0; cont<14; cont++){
        i[cont+1]=a[cont];
    }

    while(fscanf(usinas,"%s",nomes) != NULL){       //leitura de todo o arquivo
        if (strcmp(nomes, i) == 0){     //compara o cnpj informado com os cadastrados
            while (fgets(nomes2, num_max, usinas) != NULL){     //leitura das informações posteriores ao cnpj encontrado
                printf("%s", nomes2);       //imprime as informações encontradas
                printf("NÃO HÁ MAIS INFORMAÇÕES SOBRE ESSE CADASTRO");      //informa sobre a ausencia de mais informações
                if(strcmp(nomes2, "_") >0){         //criterio de finalização do bloco de informações
                    break;      //pausa do sistema
                    fclose(usinas);     //fecha o arquivo
                }
            }
        }
    printf("\n\t ENTER PARA RETORNAR AO MENU PRINCIPAL");
    getch();        //pausa

    menu();     //direciona para o menu principal
    }

}

//consultar consumidor ------------------------------------------------------------------------------------------------------
void consultar_consumidor (void){

    iniciar();      //limpezas e nome do sistema

//declarações----------------------------------------------------------------------------------------------------------------
    STRUCTusina consumidor;     //STRUCT com dados dos consumidores

    //variaveis auxiliares
    char consulta[id];
    char nomes[num_max];
    char nomes2[num_max];
    char f[num_max]; f[0]='f';
    char j[num_max]; j[0]='j';
    char a[num_max];
    char b[num_max];
    int cont;
    int id_consumidor;

    FILE*consumidores;      //declaração do arquivo

//comandos ------------------------------------------------------------------------------------------------------------------

    consumidores = fopen ("arquivo_consumidores.txt", "rb");        //abertura do arquivo dos consumidores

    printf("NOME DOS CONSUMIDORES CADASTRADOS: \n");      //lista dos consumidores que ja estão cadastrados
    while (fgets(nomes, num_max, consumidores) != NULL){      //leitura do arquivo todo
        if(nomes[0] == '>'){        //criterio de seleção do nome
            printf("%s", nomes);        //imprime na tela
        }
    }

    rewind(consumidores);     //retorna ao inicio do arquivo

    fflush(stdin);      //limpa o teclado

    printf("\nFORMA DE IDENTIFICAÇÃO DO CONSUMIDOR\n 1-CPF\n 2-CNPJ\n");        //solicita o tipo de documento de identificação do consumidor
    scanf("%d", &id_consumidor);        //leitura da escolha de documento

    if(id_consumidor==1){       //em caso de cpf
        printf("\nDIGITE O CPF DO CONSUMIDOR QUE DESEJA OBTER MAIS INFORMAÇÕES: \n");     //solicita o cpf do consumidor desejado
        scanf("%s", &a);        //leitura do cpf desejado

        //concatena o cpf informado de modo que seja inserido no inicio o criterio de busca de cpf
        for (cont=0; cont<12; cont++){
            f[cont+1]=a[cont];
        }

        while(fscanf(consumidores,"%s",nomes) != NULL){       //leitura de todo o arquivo
            if (strcmp(consumidores, f) == 0){     //compara o cnpj informado com os cadastrados
                while (fgets(nomes2, num_max, consumidores) != NULL){     //leitura das informações posteriores ao cpf encontrado
                    printf("%s", nomes2);       //imprime as informações encontradas
                    printf("NÃO HÁ MAIS INFORMAÇÕES SOBRE ESSE CADASTRO");      //informa sobre a ausencia de mais informações
                    if(strcmp(nomes2, "_") >0){         //criterio de finalização do bloco de informações
                        break;      //pausa do sistema
                        fclose(consumidores);     //fecha o arquivo
                    }
                }
            }
            printf("\n\tENTER PARA RETORNAR AO MENU PRINCIPAL");
            getch();        //pausa

            menu();     //direciona para o menu principal
        }
    }else if(id_consumidor==1){       //em caso de cnpj
        printf("\nDIGITE O CNPJ DO CONSUMIDOR QUE DESEJA OBTER MAIS INFORMAÇÕES: \n");     //solicita o cnpj do consumidor desejado
        scanf("%s", &b);        //leitura do cnpj desejado

        //concatena o cnpj informado de modo que seja inserido no inicio o criterio de busca de cpf
        for (cont=0; cont<12; cont++){
            j[cont+1]=b[cont];
        }

        while(fscanf(consumidores,"%s",nomes) != NULL){       //leitura de todo o arquivo
            if (strcmp(nomes, j) == 0){     //compara o cnpj informado com os cadastrados
                while (fgets(nomes2, num_max, consumidores) != NULL){     //leitura das informações posteriores ao cnpj encontrado
                    printf("%s", nomes2);       //imprime as informações encontradas
                    printf("NÃO HÁ MAIS INFORMAÇÕES SOBRE ESSE CADASTRO");      //informa sobre a ausencia de mais informações
                    if(strcmp(nomes2, "_") >0){         //criterio de finalização do bloco de informações
                        break;      //pausa do sistema
                        fclose(consumidores);     //fecha o arquivo
                    }
                }
            }
            printf("\n\tENTER PARA RETORNAR AO MENU PRINCIPAL");
            getch();        //pausa

            menu();     //direciona para o menu principal
        }
    }
}

//excluir usina -------------------------------------------------------------------------------------------------------------
void excluir_usina (void){

    iniciar();      //limpezas e nome do sistema

//declarações----------------------------------------------------------------------------------------------------------------
    STRUCTusina usina;      //STRUCT com dados da usina

    //variaveis auxiliares
    char consulta[num_max];
    char nomes[num_max];
    char nomes2[num_max];
    char i[num_max]; i[0]='i';
    char a[num_max];
    int cont;

    //declaração dos arquivos
    FILE*usinas;
    FILE*arq_usinas;        //arquivo temporario

//comandos ------------------------------------------------------------------------------------------------------------------

    //abertura dos arquivos
    usinas = fopen ("arquivo_usinas.txt", "rb");
    arq_usinas = fopen ("arquivo_novo_usinas.txt", "ab");

    printf("NOME DAS USINAS CADASTRADAS: \n");      //lista as usinas que ja estão cadastradas
    while (fgets(nomes, num_max, usinas) != NULL){      //leitura do arquivo todo
        if(nomes[0] == '>'){        //criterio de seleção do nome
        printf("%s", nomes);        //imprime na tela
        }
    }

    rewind(usinas);     //retorna ao inicio do arquivo

    fflush(stdin);      //limpa o teclado

    
    printf("DIGITE O CNPJ DA USINA A SER EXCLUIDA: ");      //solicita o cnpj da usina a ser apagada
    scanf("%s", &consulta);     //leitura do cnpj informado

    while(fread(&usina, sizeof(STRUCTusina), 1, usinas)==1){        //ciclo de leitura do arquivo das usinas
        if(strcmp(consulta, usina.cnpj)!=0){        //compara o cnpj informado com os salvos no arquivo, buscando os que sao diferentes do informado
            fwrite(&usina, sizeof(STRUCTusina), 1, arq_usinas);     //escreve no arquivo temporario as informações que são diferentes da informada
        }
    }

    //fechar os arquivos
    fclose(usinas);
    fclose(arq_usinas);

    remove("arquivo_usinas.txt");       //remove o arquivo usado anteriormente

    rename("arquivo_novo_usinas.txt", "arquivo_usinas.txt");        //renomea o novo arquivo

    printf("\nUSINA EXCLUIDA!");        //informa que a usina foi realmente excluida

    printf("\n\t PARA RETORNAR AO MENU PRINCIPAL");     
    getch();        //pausa

    menu();     //direciona para o menu principal


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

//excluir consumidor --------------------------------------------------------------------------------------------------------
void excluir_consumidor (void){

    iniciar();      //limpezas e nome do sistema

//declarações----------------------------------------------------------------------------------------------------------------
    STRUCTconsumidor consumidor;      //STRUCT com dados do consumidor

    //variaveis auxiliares
    char consulta[id];
    int id_consumidor;

    //declaração dos arquivos
    FILE*consumidores;
    FILE*arq_consumidores;      //arquivo temporario

//comandos ------------------------------------------------------------------------------------------------------------------

    //abertura dos arquivos
    consumidores = fopen ("arquivo_consumidores.txt", "rb");
    arq_consumidores = fopen ("arquivo_novo_consumidores.txt", "ab");

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


    //fecha os arquivos
    fclose(consumidores);
    fclose(arq_consumidores);

    remove("arquivo_consumidores.txt");       //remove o arquivo usado anteriormente

    rename("arquivo_novo_consumidores.txt", "arquivo_consumidores.txt");        //renomea o novo arquivo

//pausa e menu
    printf("\nCONSUMIDORES EXCLUIDOS!");        //informa que o consumidor foi realmente excluida

    printf("\n\tENTER PARA RETORNAR AO MENU PRINCIPAL");
    getch();        //pausa

    menu();     //direciona para o menu principal

}

//sistema--------------------------------------------------------------------------------------------------------------------
int main(){

    setlocale(LC_ALL, "Portuguese");
    menu();     //direciona para o menu principal

    return 0;
}