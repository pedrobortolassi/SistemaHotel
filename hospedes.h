#ifndef HOSPEDES_H//evita duplica��es no arquivo
#define HOSPEDES_H

#include "hotel.h" //redireciona para hotel.h que � onde tem todos os dados da struct Hospede

void cadastrarHospede(Hospede hospedes[], int *total);
void editarHospede(Hospede hospedes[], int total);
void listarHospedes(Hospede hospedes[], int total);
void buscarHospede(Hospede hospedes[], int total);
void gravarHospedes(Hospede hospedes[], int total);
int carregarHospedes(Hospede hospedes[]);//fun��o de carregamento de inicializa��o

#endif
