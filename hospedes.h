#ifndef HOSPEDES_H//evita duplicações no arquivo
#define HOSPEDES_H

#include "hotel.h" //redireciona para hotel.h que é onde tem todos os dados da struct Hospede

void cadastrarHospede(Hospede hospedes[], int *total);
void editarHospede(Hospede hospedes[], int total);
void listarHospedes(Hospede hospedes[], int total);
void buscarHospede(Hospede hospedes[], int total);
void gravarHospedes(Hospede hospedes[], int total);
int carregarHospedes(Hospede hospedes[]);//função de carregamento de inicialização

#endif
