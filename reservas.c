
#include <stdio.h>
#include <stdlib.h>
#include "reservas.h"

void realizarReserva(Reserva reservas[], int *totalReservas, Quarto quartos[], int totalQuartos, Hospede hospedes[], int totalHospedes) {
    if (*totalReservas >= MAX_RESERVAS) {
        printf("Limite de reservas atingido!\n");
        return;
    }
    Reserva nova;
    nova.id = *totalReservas + 1;
    printf("Digite o ID do hospede: ");
    scanf("%d", &nova.hospedeID);
    printf("Digite o ID do quarto: ");
    scanf("%d", &nova.quartoID);
    printf("Digite a data de check-in (DD MM AAAA): ");
    scanf("%d %d %d", &nova.dataCheckIn.dia, &nova.dataCheckIn.mes, &nova.dataCheckIn.ano);
    printf("Digite a data de check-out (DD MM AAAA): ");
    scanf("%d %d %d", &nova.dataCheckOut.dia, &nova.dataCheckOut.mes, &nova.dataCheckOut.ano);
    nova.status = Ativa;
    reservas[*totalReservas] = nova;
    (*totalReservas)++;
    printf("Reserva realizada com sucesso!\n");
}

void listarReservas(Reserva reservas[], int totalReservas) {
    if (totalReservas == 0) {
        printf("Nao ha reservas cadastradas.\n");
        return;
    }

    printf("\n===== Lista de Reservas ======\n");
    for (int i = 0; i < totalReservas; i++) {
        printf("ID: %d\n", reservas[i].id);
        printf("Hospede ID: %d\n", reservas[i].hospedeID);
        printf("Quarto ID: %d\n", reservas[i].quartoID);
        printf("Check-in: %02d/%02d/%04d\n",
               reservas[i].dataCheckIn.dia,
               reservas[i].dataCheckIn.mes,
               reservas[i].dataCheckIn.ano);
        printf("Check-out: %02d/%02d/%04d\n",
               reservas[i].dataCheckOut.dia,
               reservas[i].dataCheckOut.mes,
               reservas[i].dataCheckOut.ano);

        // Traduz o status da reserva para texto
        const char *statusTexto;
        switch (reservas[i].status) {
            case Ativa:
                statusTexto = "Ativa";
                break;
            case Concluida:
                statusTexto = "Concluida";
                break;
            case Cancelada:
                statusTexto = "Cancelada";
                break;
            default:
                statusTexto = "Desconhecido";
        }

        printf("Status: %s\n\n", statusTexto);
    }
}
void cancelarReserva(Reserva reservas[], int totalReservas, Quarto quartos[], int totalQuartos) {
    int idReserva;
    printf("Digite o ID da reserva que deseja cancelar: ");
    scanf("%d", &idReserva);

    if (idReserva < 1 || idReserva > totalReservas) {
        printf("ID de reserva invalido!\n");
        return;
    }

    Reserva *reserva = &reservas[idReserva - 1];

    if (reserva->status == Cancelada) {
        printf("A reserva ja esta cancelada.\n");
        return;
    }

    reserva->status = Cancelada;

    for (int i = 0; i < totalQuartos; i++) {
        if (quartos[i].id == reserva->quartoID) {
            quartos[i].status = Disponivel;
            printf("O quarto ID %d agora esta disponivel.\n", quartos[i].id);
            break;
        }
    }

    printf("Reserva ID %d cancelada com sucesso!\n", idReserva);
}
void gravarReservas(Reserva reservas[], int totalReservas) {
    FILE *file = fopen("reservas.dat", "wb");
    if (file == NULL) {
        printf("Erro ao abrir arquivo para gravacao.\n");
        return;
    }
    fwrite(reservas, sizeof(Reserva), totalReservas, file);
    fclose(file);
    printf("Reservas gravadas com sucesso!\n");
}

int carregarReservas(Reserva reservas[]) {
    FILE *file = fopen("reservas.dat", "rb");
    if (file == NULL) {
        printf("Arquivo reservas.dat nao encontrado. Criando novo...\n");
        return 0;
    }
    int total = fread(reservas, sizeof(Reserva), MAX_RESERVAS, file);
    fclose(file);
    printf("Reservas carregadas com sucesso!\n");
    return total;
}
