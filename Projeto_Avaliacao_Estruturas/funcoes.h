#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<string.h>
#ifndef FUNCOES_H
#define FUNCOES_H

/*Área do Pasageiro*/

typedef struct { // Estrutura para login e cadastro
    char nome[21];
    char email[81];
    char senha[9];
} Passageiro;

/*Estrutura para os dados dos passageiros*/

/*Protótipos das funções envolvendo a área do passageiro*/
void cadastro_passageiro();
int login_passageiro();
void menu_passageiro();
void visualizar_passageiro();
void editar_passageiro();
void excluir_passageiro();

/*Área do motorista*/

/*Estrutura para os dados do motorista*/
typedef struct {
    char nome[50];
    char email[81];
    char senha[9];
    char transporte[21];
    char CNH[10];
} Motorista;

/*Protótipos das funções envolvendo a área do motorista*/
void cadastro_motorista();
int login_motorista();
void menu_motorista();
void visualizar_motorista();
void editar_motorista();
void excluir_motorista();

/*Estrutura para o agendamento das viagens*/
typedef struct {
    int dia_ida, dia_volta;
    int mes_ida, mes_volta;
    char cidade[21];
    char estado[3];
} Viagem;

/*Protótipos das funções envolvendo o agendamento das viagens*/
void agendar_viagem();
void editar_viagem();
void listar_viagens();
void apagar_viagem();

/*Protótipos das funções envolvendo a compra de passagens*/
void compra_passagem();
void visualizar_compras();
void cancelar_passagem();
int compara_viagem();
int busca_binaria();

#endif