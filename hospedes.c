#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // para usar a função isdigit
#include "hospedes.h"

void cadastrarHospede(Hospede hospedes[], int *total) {
    if (*total >= MAX_HOSPEDES) {
        printf("Limite de hospedes atingido!\n");
        return;
    }

    Hospede novo;
    novo.id = *total + 1;

    printf("Digite o nome do hospede: ");
    scanf(" %[^\n]", novo.nome);//pega todos os caracteres até o enter

    // validação do cpf para cadastro
    char cpf[12], excess[50];
    while (1) {         //o loop vai continuar ate q o usuario digite certo
        printf("Digite o CPF (somente numeros): ");
        if (scanf("%11s", cpf) != 1) {  //le ate 11 caracteres
            printf("Erro na entrada.\n");
            while (getchar() != '\n'); // Limpa o buffer
            continue;
        }
        if (fgets(excess, sizeof(excess), stdin) && excess[0] != '\n') {
            printf("CPF invalido: voce digitou mais de 11 caracteres.\n");
            continue;
        }
        if (strlen(cpf) != 11) {
            printf("CPF invalido: numero de digitos incorreto.\n");
            continue;
        }


        int valido = 1;
        for (int i = 0; i < 11; i++) {
            if (!isdigit(cpf[i])) {
                printf("CPF invalido: caractere invalido encontrado.\n");
                valido = 0;
                break;
            }
        }

        if (!valido) continue;
        snprintf(novo.documento, sizeof(novo.documento), "%c%c%c.%c%c%c.%c%c%c-%c%c",
                 cpf[0], cpf[1], cpf[2], cpf[3], cpf[4], cpf[5],
                 cpf[6], cpf[7], cpf[8], cpf[9], cpf[10]);
        break;
    }

    // validação do e-mail
    while (1) {
        printf("Digite o email: ");
        scanf(" %[^\n]", novo.email);

        // verifica se tem @
        if (strchr(novo.email, '@') == NULL) {
            printf("Email invalido: nao contem '@'.\n");
            continue;
        }

        // verifica se tem um . após o @
        if (strrchr(novo.email, '.') <= strchr(novo.email, '@')) {
            printf("Email invalido: nao contem '.'\n");
            continue;
        }

        break;
    }

    printf("Digite o telefone: ");
    scanf(" %[^\n]", novo.telefone);
    printf("Digite o endereco (Rua, Cidade, Estado, CEP):\n");
    printf("Rua: ");
    scanf(" %[^\n]", novo.endereco.rua);
    printf("Cidade: ");
    scanf(" %[^\n]", novo.endereco.cidade);
    printf("Estado: ");
    scanf(" %[^\n]", novo.endereco.estado);
    printf("CEP: ");
    scanf(" %[^\n]", novo.endereco.cep);

    hospedes[*total] = novo;
    (*total)++;
    printf("Hospede cadastrado com sucesso!");
}

void editarHospede(Hospede hospedes[], int total) {
    int id;
    printf("Digite o ID do hospede a editar: ");
    scanf("%d", &id);
    if (id < 1 || id > total) {
        printf("ID invalido!\n");
        return;
    }
    Hospede *hospede = &hospedes[id - 1];

    printf("Digite o novo nome do hospede: ");
    scanf(" %[^\n]", hospede->nome);

    // validação do CPF em editar

    char cpf[12], excess[100];
    while (1) {
        printf("Digite o CPF (somente numeros): ");
        if (scanf("%11s", cpf) != 1) {
            printf("Erro na entrada.\n");
            while (getchar() != '\n'); // limpa o buffer apos leitura invalida para n afetar as proximas passagens
            continue;
        }

        // limpa o restante do buffer após a leitura
        if (fgets(excess, sizeof(excess), stdin)) {
            if (excess[0] != '\n') {
                printf("CPF invalido: numero de digitos incorreto.\n");
                continue;
            }
        }

        // Verifica se o tamanho do CPF está correto
        if (strlen(cpf) != 11) {
            printf("CPF invalido: numero de digitos incorreto.\n");
            continue;
        }

        // Verifica se todos os caracteres são dígitos
        int valido = 1;
        for (int i = 0; i < 11; i++) {
            if (!isdigit(cpf[i])) {
                printf("CPF invalido: caractere invalido encontrado.\n");
                valido = 0;
                break;
            }
        }
        if (!valido) continue;

        // Formata o CPF e armazena
        snprintf(hospede->documento, sizeof(hospede->documento), "%c%c%c.%c%c%c.%c%c%c-%c%c",
                 cpf[0], cpf[1], cpf[2], cpf[3], cpf[4], cpf[5],
                 cpf[6], cpf[7], cpf[8], cpf[9], cpf[10]);
        break;
    }

    printf("Digite o novo email: ");
    scanf(" %[^\n]", hospede->email);
    printf("Digite o novo telefone: ");
    scanf(" %[^\n]", hospede->telefone);
    printf("Hospede atualizado com sucesso!");
}

void listarHospedes(Hospede hospedes[], int total) {
    printf("\n===== Lista de Hospedes ======\n");
    for (int i = 0; i < total; i++) {
        printf("ID: %d, Nome: %s, Documento: %s, Email: %s, Telefone: %s\n",
               hospedes[i].id, hospedes[i].nome, hospedes[i].documento,
               hospedes[i].email, hospedes[i].telefone);
    }
}

void buscarHospede(Hospede hospedes[], int total) {
    int id;
    printf("Digite o ID do hospede: ");
    scanf("%d", &id);
    if (id < 1 || id > total) {
        printf("ID invalido!\n");
        return;
    }
    Hospede hospede = hospedes[id - 1];
    printf("ID: %d, Nome: %s, Documento: %s, Email: %s, Telefone: %s\n",
           hospede.id, hospede.nome, hospede.documento,
           hospede.email, hospede.telefone);
}

void gravarHospedes(Hospede hospedes[], int total) {
    FILE *file = fopen("hospedes.dat", "wb");
    if (file == NULL) {
        printf("Erro ao abrir arquivo para gravacao.\n");
        return;
    }
    fwrite(hospedes, sizeof(Hospede), total, file);
    fclose(file);
    printf("Hospedes gravados com sucesso!\n");
}

int carregarHospedes(Hospede hospedes[]) {
    FILE *file = fopen("hospedes.dat", "rb");
    if (file == NULL) {
        printf("Arquivo hospedes.dat não encontrado. Criando novo...\n");
        return 0;
    }
    int total = fread(hospedes, sizeof(Hospede), MAX_HOSPEDES, file);
    fclose(file);
    printf("Hospedes carregados com sucesso!\n");
    return total;
}
