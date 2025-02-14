#ifndef HOTEL_H //diretiva que garante q um bloco de codigo seja incluido apenas uma vez no arquivo; evitar duplicações
#define HOTEL_H

#define MAX_QUARTOS 10
#define MAX_HOSPEDES 50
#define MAX_RESERVAS 50

typedef enum { Simples, Duplo, Suite } TipoQuarto;//dados enumerados; 3 valores para tipoquarto
typedef enum { Disponivel, Ocupado, Manutencao } StatusQuarto;
typedef enum { Ativa, Concluida, Cancelada } StatusReserva;

typedef struct {
    int id;
    int numero;
    TipoQuarto tipo;
    float precoDiaria;
    StatusQuarto status;
} Quarto;

typedef struct {
    int id;
    char nome[50];
    char documento[15];
    char email[40];
    char telefone[15];
    struct {
        char rua[150];
        char cidade[50];
        char estado[50];
        char cep[10];
    } endereco;
} Hospede;

typedef struct {
    int id;
    int hospedeID;
    int quartoID;
    struct {
        int dia, mes, ano;
    } dataCheckIn, dataCheckOut;
    StatusReserva status;
} Reserva;

#endif

