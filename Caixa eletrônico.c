#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <ctype.h>

int menuPrincipal(int *opcao) {

    printf("................ CAIXA ELETRÔNICO ................\n\n");

    //sleep(1);

    printf("              [  1  ]\tCONSULTAR SALDO\n");
    printf("              [  2  ]\tDEPÓSITO\n");
    printf("              [  3  ]\tSAQUE\n");
    printf("              [  4  ]\tFINALIZAR\n");

    printf("...................................................\n\n");

    printf("Escolha a opção desejada: ");
    scanf("%d", opcao);

    while (*opcao < 1 || *opcao > 4) {
        setbuf(stdin, NULL);
        printf("Opção inválida! Tente novamente!\n\n");
        printf("Escolha a opção desejada: ");
        scanf("%d", opcao);
    }
}

int menuInterno(int *opcao, int *opcao_interna) {

    printf("[  1  ]\tVOLTAR AO MENU PRINCIPAL\n");
    printf("[  2  ]\tSAIR\n");

    printf("Escolha a sua opção: ");
    setbuf(stdin, NULL);

    scanf("%d", opcao_interna);

    while (*opcao_interna < 1 || *opcao_interna > 2) {
        setbuf(stdin, NULL);
        printf("Opção inválida! Tente novamente!\n\n");
        printf("Escolha a opção desejada: ");
        scanf("%d", opcao_interna);
    }

    if (*opcao_interna == 1) {
        *opcao = 0;
        system("cls");
    }
    else {
        *opcao = 4;
    }
}

float novoDeposito(float *saldo, float *valor) {

    printf("\nDeseja fazer um novo depósito [S/N]? ");
    setbuf(stdin, NULL);
    char resp = getchar();
    resp = toupper(resp);
    while (resp != 'N') {
        system("cls");
        printf("Informe o valor a ser depositado: R$ ");
        scanf("%f", valor);
        printf("\nVocê depositou mais R$ %.2f!\n", *valor);
        *saldo += *valor;
        printf("\nSeu saldo atual é de R$ %.2f\n", *saldo);
        printf("\nDeseja fazer um novo depósito [S/N]? ");
        sleep(2);
        setbuf(stdin, NULL);
        resp = toupper(getchar());
    }

}

float novoSaque(float *saldo, float *valor, int *opcao, int *opcao_interna) {
    while (*valor > *saldo) {
        verificaNegativo(saldo, valor, opcao, opcao_interna);
    }
        *saldo -= *valor;
        if (*valor == 0 && *saldo == 0) {
            printf("Você necessita ter algum valor em conta para sacar!\n\n");
            sleep(1);
        } else {
           printf("\nVocê sacou R$ %.2f!\n", *valor);
            sleep(1);
            printf("\nSeu saldo atual é de R$ %.2f\n", *saldo);

            printf("\nDeseja fazer um novo saque [S/N]? ");
            setbuf(stdin, NULL);
            char resp = getchar();
            resp = toupper(resp);

            while (resp != 'N') {
                system("cls");
                printf("Informe o valor a ser sacado: R$ ");
                scanf("%f", valor);
                while (*valor > *saldo || *saldo == 0) {
                    verificaNegativo(saldo, valor, opcao, opcao_interna);
                }
                *saldo -= *valor;
                printf("\nVocê sacou R$ %.2f!\n", *valor);
                sleep(1);
                printf("\nSeu saldo atual é de R$ %.2f\n", *saldo);
                printf("\nDeseja fazer um novo saque [S/N]? ");
                setbuf(stdin, NULL);
                resp = toupper(getchar());
            }
        }

        menuInterno(opcao, opcao_interna);
    }

void verificaNegativo(float *saldo, float *valor, int *opcao, int *opcao_interna) {
    printf("\nVocê não pode sacar este valor, pois o seu saldo atual é de apenas R$ %.2f.\n", *saldo);
    printf("\nInforme o valor a ser sacado: R$ ");
    scanf("%f", valor);
}

int main () {

    setlocale(LC_ALL, "Portuguese");

    float valor = 0, saldo = 0;
    int opcao = 0;
    int opcao_interna;

    sleep(1);

    printf("Desenvolvido por: Daniel Azevedo de Oliveira Maia ©\n\n");

    sleep(1);

    printf("Versão 1.0 - 2022\n\n");

    sleep(2);

    while (opcao == 0) {

        menuPrincipal(&opcao);

        switch(opcao) {

        case 1:
            system("cls");
            printf("Consultando saldo...\n\n");
            sleep(2);
            printf("Seu saldo atual é: R$ %.2f.\n\n", saldo);
            sleep(2);
            menuInterno(&opcao, &opcao_interna);
            break;

        case 2:
            system("cls");
            printf("Informe o valor a ser depositado: R$ ");
            scanf("%f", &valor);
            printf("\nVocê depositou R$ %.2f!\n", valor);
            saldo += valor;
            sleep(1);
            printf("\nSeu saldo atual é de R$ %.2f\n", saldo);
            novoDeposito(&saldo, &valor);
            menuInterno(&opcao, &opcao_interna);
            break;

        case 3:
            system("cls");
            printf("Informe o valor a ser sacado: R$ ");
            scanf("%f", &valor);

            novoSaque(&saldo, &valor, &opcao, &opcao_interna);
            break;

        default:
            opcao = 1;
        }

    }

    puts("\nVOLTE SEMPRE!");


    return 0;
}


