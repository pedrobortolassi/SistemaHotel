#include <stdio.h>
#include <stdlib.h>
#include "quartos.h"

void cadastrarQuarto(Quarto quartos[], int *total) {
    if (*total >= MAX_QUARTOS) {
        printf("Limite de quartos atingido!\n");
        return;
    }
    Quarto novo;
    novo.id = *total + 1;

    printf("Digite o numero do quarto: ");
    scanf("%d", &novo.numero);

    printf("Digite o tipo do quarto (0: Simples, 1: Duplo, 2: Suite): ");
    scanf("%d", (int *)&novo.tipo);

    // validação do preço
    do {
        printf("Digite o preco da diaria (ex: 120.00): ");
        scanf("%f", &novo.precoDiaria);
        if (novo.precoDiaria <= 0) {
            printf("Preco invalido! O valor deve ser maior que zero.\n");
        }
    } while (novo.precoDiaria <= 0);

    novo.status = Disponivel;
    quartos[*total] = novo;
    (*total)++;
    printf("Quarto cadastrado com sucesso!\n");
}

void editarQuarto(Quarto quartos[], int total) {
    int id;
    printf("Digite o ID do quarto a editar: ");
    scanf("%d", &id);
    if (id < 1 || id > total) {
        printf("ID invalido!\n");
        return;
    }
    Quarto *quarto = &quartos[id - 1];

    printf("Digite o novo numero do quarto: ");
    scanf("%d", &quarto->numero);

    printf("Digite o novo tipo do quarto (0: Simples, 1: Duplo, 2: Suite): ");
    scanf("%d", (int *)&quarto->tipo);

    // Validação do preço
    do {
        printf("Digite o novo preco da diaria: ");
        scanf("%f", &quarto->precoDiaria);
        if (quarto->precoDiaria <= 0) {
            printf("Preco invalido! O valor deve ser maior que zero.\n");
        }
    } while (quarto->precoDiaria <= 0);

    printf("Quarto atualizado com sucesso!\n");
}

void listarQuartos(Quarto quartos[], int totalQuartos) {
    if (totalQuartos == 0) {
        printf("Nao ha quartos cadastrados.\n");
        return;
    }

    printf("\n===== Lista de Quartos ======\n");
    for (int i = 0; i < totalQuartos; i++) {
        // Traduz o tipo do quarto para texto
        const char *tipoTexto;
        switch (quartos[i].tipo) {
            case Simples:
                tipoTexto = "Simples";
                break;
            case Duplo:
                tipoTexto = "Duplo";
                break;
            case Suite:
                tipoTexto = "Suite";
                break;
            default:
                tipoTexto = "Desconhecido";
        }

        // Traduz o status do quarto para texto
        const char *statusTexto;
        switch (quartos[i].status) {
            case Disponivel:
                statusTexto = "Disponivel";
                break;
            case Ocupado:
                statusTexto = "Ocupado";
                break;
            case Manutencao:
                statusTexto = "Em Manutencao";
                break;
            default:
                statusTexto = "Desconhecido";
        }

        // Exibe os dados do quarto
        printf("ID: %d, Numero: %d, Tipo: %s, Preco: %.2f, Status: %s\n",
               quartos[i].id, quartos[i].numero, tipoTexto,
               quartos[i].precoDiaria, statusTexto);
    }
}

void buscarQuarto(Quarto quartos[], int total) {
    int id;
    printf("Digite o ID do quarto: ");
    scanf("%d", &id);
    if (id < 1 || id > total) {
        printf("ID invalido!\n");
        return;
    }
    Quarto quarto = quartos[id - 1];
    printf("ID: %d, Numero: %d, Tipo: %d, Preco: %.2f, Status: %d\n",
           quarto.id, quarto.numero, quarto.tipo, quarto.precoDiaria, quarto.status);
}

void gravarQuartos(Quarto quartos[], int total) {
    FILE *file = fopen("quartos.dat", "wb");
    if (file == NULL) {
        printf("Erro ao abrir arquivo para gravacao.\n");
        return;
    }
    fwrite(quartos, sizeof(Quarto), total, file);
    fclose(file);
    printf("Quartos gravados com sucesso!\n");
}

int carregarQuartos(Quarto quartos[]) {
    FILE *file = fopen("quartos.dat", "rb");
    if (file == NULL) {
        printf("Arquivo quartos.dat não encontrado. Criando novo...\n");
        return 0;
    }
    int total = fread(quartos, sizeof(Quarto), MAX_QUARTOS, file);
    fclose(file);
    printf("Quartos carregados com sucesso!\n");
    return total;
}
