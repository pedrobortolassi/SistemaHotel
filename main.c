#include <stdio.h>
#include <stdlib.h>

#include "quartos.h" //incluindo os 3 arquivos h que v�o ser puxadas as fun��es
#include "hospedes.h"
#include "reservas.h"

int main() {
    Quarto quartos[MAX_QUARTOS];    //inicializa as fun��es de quartos.h
    Hospede hospedes[MAX_HOSPEDES]; //inicializa as fun��es de hospedes.h
    Reserva reservas[MAX_RESERVAS]; //inicializa as fun��es de reserva.h

    int totalQuartos = carregarQuartos(quartos); //fun��es chamadas apenas uma vez para inicializar as arrays de cima
    int totalHospedes = carregarHospedes(hospedes);//
    int totalReservas = carregarReservas(reservas);//

    int opcao; //armazena a op��o escolhida pelo usu�rio no menu

    do {
        printf("\n======= Menu Principal =======\n");
        printf("1. Cadastrar Quarto\n");
        printf("2. Editar Quarto\n");
        printf("3. Listar Quartos\n");
        printf("4. Buscar Quarto por ID\n");
        printf("5. Cadastrar Hospede\n");
        printf("6. Editar Hospede\n");
        printf("7. Listar Hospedes\n");
        printf("8. Buscar Hospede por Documento/ID\n");
        printf("9. Realizar Reserva\n");
        printf("10. Listar Reservas\n");
        printf("11. Cancelar Reserva\n");
        printf("12. Sair/Salvar\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) { //compara a op��o escolhida pelo usu�rio e executa a fun��o q corresponde ao numero
            case 1:
                cadastrarQuarto(quartos, &totalQuartos);//& � uma vari�vel atualiz�vel/modific�vel; referencia o endere�o de mem�ria (*)
                break;//sair do bloco switch
            case 2:
                editarQuarto(quartos, totalQuartos);//totalQuartos passa uma c�pia do valor
                break;
            case 3:
                listarQuartos(quartos, totalQuartos);
                break;
            case 4:
                buscarQuarto(quartos, totalQuartos);
                break;
            case 5:
                cadastrarHospede(hospedes, &totalHospedes);
                break;
            case 6:
                editarHospede(hospedes, totalHospedes);
                break;
            case 7:
                listarHospedes(hospedes, totalHospedes);
                break;
            case 8:
                buscarHospede(hospedes, totalHospedes);
                break;
            case 9:
                realizarReserva(reservas, &totalReservas, quartos, totalQuartos, hospedes, totalHospedes);
                break;
            case 10:
                listarReservas(reservas, totalReservas);
                break;
            case 11:
                cancelarReserva(reservas, totalReservas, quartos, totalQuartos);
                 break;
            case 12:
    printf("Saindo...\n");
    gravarQuartos(quartos, totalQuartos);
    gravarHospedes(hospedes, totalHospedes);
    gravarReservas(reservas, totalReservas);
    break;

            default: //nenhum dos casos anteriores
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 12); // loop que repete o menu at� que o usu�riof escolha a op��o 12 para sair

    return 0;
}
