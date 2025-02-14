#ifndef QUARTOS_H
#define QUARTOS_H

#include "hotel.h" //redireciona para hotel.h que � onde tem todos os dados da struct Quarto

void cadastrarQuarto(Quarto quartos[], int *total);//& cita o endere�o e * indica o apontado
void editarQuarto(Quarto quartos[], int total); //pede a struct Quarto q est� em hotel.h
void listarQuartos(Quarto quartos[], int total);
void buscarQuarto(Quarto quartos[], int total);
void gravarQuartos(Quarto quartos[], int total);
int carregarQuartos(Quarto quartos[]);//fun��o de carregamento de inicializa��o

#endif

