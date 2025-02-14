#ifndef RESERVAS_H
#define RESERVAS_H

#include "hotel.h" //redireciona para hotel.h que é onde tem todos os dados da struct Reserva

void realizarReserva(Reserva reservas[], int *totalReservas, Quarto quartos[], int totalQuartos, Hospede hospedes[], int totalHospedes);
void listarReservas(Reserva reservas[], int totalReservas);
void gravarReservas(Reserva reservas[], int totalReservas);
void cancelarReserva(Reserva reservas[], int totalReservas, Quarto quartos[], int totalQuartos);
int carregarReservas(Reserva reservas[]);//função de carregamento de inicialização


#endif
