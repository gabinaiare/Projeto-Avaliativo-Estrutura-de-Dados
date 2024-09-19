#include "funcoes.h"

void cadastro_passageiro() { // Função para cadastrar passageiro
    system("cls");
    FILE *file = fopen("cadastro_passageiro.txt", "a");
    Passageiro passageiro;

    printf("Digite seu nome de usuário: ");
    scanf("%20s", passageiro.nome); // Limite o tamanho do input

    do {
        printf("Digite o seu email: ");
        scanf("%80s", passageiro.email);

        if (strchr(passageiro.email, '@') != NULL) {
            printf("E-mail válido.\n");
            break;
        } else {
            printf("E-mail inválido, não contém '@'.\n");
        }
    } while (1);

    printf("Digite uma senha de até 8 dígitos: ");
    scanf("%8s", passageiro.senha); 

    fprintf(file, "%s %s %s\n", passageiro.email, passageiro.nome, passageiro.senha);
    fclose(file);
}

int login_passageiro() { // Função para login de passageiro
    system("cls");
    FILE *file = fopen("cadastro_passageiro.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de cadastro!\n");
        return 0;
    }

    Passageiro passageiro;
    char email[81], senha[9];
    int encontrar = 0;

    printf("Digite o seu email: ");
    scanf("%80s", email); 

    printf("Digite sua senha: ");
    scanf("%8s", senha); 

    while (fscanf(file, "%80s %20s %8s", passageiro.email, passageiro.nome, passageiro.senha) == 3) {
        if (strcmp(email, passageiro.email) == 0 && strcmp(senha, passageiro.senha) == 0) {
            printf("Login bem-sucedido! Bem-vindo de volta, %s!\n", passageiro.nome);
            encontrar = 1;
            break;
        }
    }

    if (!encontrar) {
        printf("E-mail ou senha inválidos.\n");
    }

    fclose(file);
    return encontrar;
}

void menu_passageiro() {
    system("cls");
    int op;

    do
    {
        printf("==== Menu de Viagem ====\n");
        printf("1 - Comprar passagem\n");
        printf("2 - Visualizar compras\n");
        printf("3 - Cancelar passagem\n");
        printf("==== Menu de Passageiro ====\n");
        printf("4 - Visualizar lista de passagerios\n");
        printf("5 - Editar dados de passageiro\n");
        printf("6 - Excluir dados\n");
        printf("0 - Voltar\n");
        printf("============================\n");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            compra_passagem();
            break;
        case 2:
            visualizar_compras();
            break;
        case 3:
            cancelar_passagem();
            break;
        case 4:
            visualizar_passageiro();
            break;
        case 5:
            editar_passageiro();
            break;
        case 6:
            excluir_passageiro();
            break;
        case 0:
            break;    
        default:
            printf("Opção inválida!");
            break;
        }
    } while (op != 0);
}

void visualizar_passageiro() {
    system("cls");
    FILE *file = fopen("cadastro_passageiro.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de cadastro!\n");
        return;
    }

    Passageiro passageiro;
    while (fscanf(file, "%80s %20s %8s", passageiro.email, passageiro.nome, passageiro.senha) == 3) {
        printf("%s %s %s\n", passageiro.email, passageiro.nome, passageiro.senha);
    }
    fclose(file);
}

void editar_passageiro() {
    system("cls");
    FILE *file = fopen("cadastro_passageiro.txt", "r+");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de cadastro!\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(file);
        return;
    }

    Passageiro passageiro;
    char email[81];
    int encontrado = 0;

    printf("Digite o e-mail do passageiro a ser editado: ");
    scanf("%80s", email);

    while (fscanf(file, "%80s %20s %8s", passageiro.email, passageiro.nome, passageiro.senha) == 3) {
        if (strcmp(email, passageiro.email) == 0) {
            encontrado = 1;
            printf("Digite o novo nome: ");
            char novo_nome[21];
            scanf(" %[^\n]s", novo_nome);

            printf("Digite a nova senha: ");
            char nova_senha[9];
            scanf(" %[^\n]s", nova_senha);

            if (strlen(novo_nome) > 0) {
                strcpy(passageiro.nome, novo_nome);
            }
            if (strlen(nova_senha) > 0) {
                strcpy(passageiro.senha, nova_senha);
            }

            fprintf(tempFile, "%s %s %s\n", passageiro.email, passageiro.nome, passageiro.senha);
        } else {
            fprintf(tempFile, "%s %s %s\n", passageiro.email, passageiro.nome, passageiro.senha);
        }
    }

    if (!encontrado) {
        printf("Passageiro não encontrado!\n");
    } else {
        printf("Dados atualizados com sucesso!\n");
    }

    fclose(file);
    fclose(tempFile);

    remove("cadastro_passageiro.txt");
    rename("temp.txt", "cadastro_passageiro.txt");
}

void excluir_passageiro() {
    system("cls");
    FILE *file = fopen("cadastro_passageiro.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de cadastro!\n");
        return;
    }

    FILE *tempFile = fopen("temp_passageiro.txt", "w");
    if (tempFile == NULL) {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(file);
        return;
    }

    Passageiro passageiro;
    char email[81];
    int encontrado = 0;

    printf("Digite o e-mail do passageiro a ser excluído: ");
    scanf("%80s", email);

    while (fscanf(file, "%80s %20s %8s", passageiro.email, passageiro.nome, passageiro.senha) == 3) {
        if (strcmp(email, passageiro.email) == 0) {
            encontrado = 1;
            printf("Passageiro %s excluído com sucesso!\n", passageiro.nome);
        } else {
            fprintf(tempFile, "%s %s %s\n", passageiro.email, passageiro.nome, passageiro.senha);
        }
    }

    if (!encontrado) {
        printf("Passageiro não encontrado!\n");
    }

    fclose(file);
    fclose(tempFile);

    remove("cadastro_passageiro.txt");
    rename("temp_passageiro.txt", "cadastro_passageiro.txt");
}