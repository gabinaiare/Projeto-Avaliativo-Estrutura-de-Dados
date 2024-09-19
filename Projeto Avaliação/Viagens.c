#include "funcoes.h"

// Protótipos de funções
void cadastro_login();
void pergunta_cadastro();
void pergunta_login();

int main() {
    setlocale(LC_ALL, "Portuguese");

    printf("==== Seja Bem-Vindo! ====\n"); // Mensagem de boas-vindas
    cadastro_login();
    return 0;
}

void cadastro_login() { 
    int op;
    
    do {
        printf("==== Escolha uma opção ====\n");
        printf("1 - Cadastrar\n");
        printf("2 - Login\n");
        printf("0 - Sair\n");
        printf("============================\n");

        scanf("%d", &op); // Ler a entrada do usuário

        if (op == 1) {
            pergunta_cadastro();
        } else if (op == 2) {
            pergunta_login();
        }
    } while (op != 0);
}

void pergunta_cadastro() {
    int op;

    do {
        printf("==== O que você é? ====\n");
        printf("1 - Passageiro\n");
        printf("2 - Motorista\n");
        scanf("%d", &op);

        if (op == 1) {
            cadastro_passageiro();
        } else if (op == 2) {
            cadastro_motorista();
        } else {
            printf("Opção inválida! Tente novamente.\n");
        }        
    } while (op != 1 && op != 2);
}

void pergunta_login() {
    int op, verificador;

    do {
        printf("==== O que você é? ====\n");
        printf("1 - Passageiro\n");
        printf("2 - Motorista\n");
        scanf("%d", &op);

        if (op == 1) {
            verificador = login_passageiro();
            if (verificador == 1) {
                menu_passageiro();
            }  
        } else if (op == 2) {
            verificador = login_motorista();
            if (verificador == 1) {
                menu_motorista();
            }
        } else {
            printf("Opção inválida! Tente novamente.\n");
        }     
    } while (op != 1 && op != 2);
}
