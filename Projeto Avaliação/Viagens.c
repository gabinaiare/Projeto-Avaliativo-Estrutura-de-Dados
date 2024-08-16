#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

typedef struct { // Estrutura para login e cadastro
    char nome[21], email[81], senha[9];
} Passageiro;

typedef struct { // Estrutura para os dados do motorista
    char nome[50], email[81], senha[9], transporte[21], CNH[10];
} Motorista;

// Protótipos de funções
void cadastro_login();
void pergunta_cadastro();
void pergunta_login();
void cadastro_passageiro();
void cadastro_motorista();
int login_passageiro();
int login_motorista();
void menu_passageiro();
void menu_motorista();
void visualizar_passageiro();
void editar_passageiro();
void excluir_passageiro();
void visualizar_motorista();
void editar_motorista();
void excluir_motorista();

int main() {
    setlocale(LC_ALL, "Portuguese");

    printf("==== Seja Bem-Vindo! ====\n"); // Mensagem de boas-vindas
    cadastro_login();
    return 0;
}

void cadastro_login() { 
    system("cls");
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
    system("cls");
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
    system("cls");
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

void cadastro_motorista() { // Função para cadastrar motorista
    system("cls");
    FILE *file = fopen("cadastro_motorista.txt", "a");
    Motorista motorista;

    if (file == NULL) {
        printf("Erro ao abrir o arquivo para cadastro de motorista!\n");
        return;
    }

    printf("Digite seu nome de usuário: ");
    scanf("%49s", motorista.nome); 

    do {
        printf("Digite o seu email: ");
        scanf("%80s", motorista.email);

        if (strchr(motorista.email, '@') != NULL) {
            printf("E-mail válido.\n");
            break;
        } else {
            printf("E-mail inválido, não contém '@'.\n");
        }
    } while (1);

    printf("Digite uma senha de até 8 dígitos: ");
    scanf("%8s", motorista.senha); 

    printf("Digite qual é o seu meio de transporte: ");
    scanf("%20s", motorista.transporte); 

    printf("Digite seu número de registro da CNH (9 dígitos): ");
    scanf("%9s", motorista.CNH);

    fprintf(file, "%s %s %s %s %s\n", motorista.email, motorista.nome, motorista.senha, motorista.transporte, motorista.CNH);
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

int login_motorista() { // Função para login de motorista
    system("cls");
    FILE *file = fopen("cadastro_motorista.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de cadastro!\n");
        return 0;
    }

    Motorista motorista;
    char email[81], senha[9];
    int encontrar = 0;

    printf("Digite o seu email: ");
    scanf("%80s", email); 

    printf("Digite sua senha: ");
    scanf("%8s", senha); 

    while (fscanf(file, "%80s %50s %8s %20s %9s", motorista.email, motorista.nome, motorista.senha, motorista.transporte, motorista.CNH) == 5) {
        if (strcmp(email, motorista.email) == 0 && strcmp(senha, motorista.senha) == 0) {
            printf("Login bem-sucedido! Bem-vindo de volta, %s!\n", motorista.nome);
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
        printf("==== Menu ====\n");
        printf("1 - Visualizar lista de passagerios\n");
        printf("2 - Editar dados de passageiro\n");
        printf("3 - Excluir dados\n");
        printf("0 - Voltar\n");
        printf("============================\n");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            visualizar_passageiro();
            break;
        case 2:
            editar_passageiro();
            break;
        case 3:
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

void menu_motorista() {
    system("cls");
    int op;

    do
    {
        printf("==== Menu ====\n");
        printf("1 - Visualizar lista de passageiros\n");
        printf("2 - Editar dados do motorista\n");
        printf("3 - Visualizar dados de motorista\n");
        printf("4 - Excluir dados\n");
        printf("0 - Voltar\n");
        printf("============================\n");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            visualizar_passageiro();
            break;
        case 2:
            editar_motorista();
            break;
        case 3:
            visualizar_motorista();
            break;
        case 4:
            excluir_motorista;
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

void visualizar_motorista() {
    system("cls");
    FILE *file = fopen("cadastro_motorista.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de cadastro!\n");
        return;
    }

    Motorista motorista;
    while (fscanf(file, "%80s %50s %8s %20s %9s", motorista.email, motorista.nome, motorista.senha, motorista.transporte, motorista.CNH) == 5) {
        printf("%s %s %s %s %s %s\n", motorista.email, motorista.nome, motorista.senha, motorista.transporte, motorista.CNH);
    }
    fclose(file);
}

void editar_motorista() {
    system("cls");
    FILE *file = fopen("cadastro_motorista.txt", "r+");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de cadastro!\n");
        return;
    }

    FILE *tempFile = fopen("temp_motorista.txt", "w");
    if (tempFile == NULL) {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(file);
        return;
    }

    Motorista motorista;
    char email[81];
    int encontrado = 0;

    printf("Digite o e-mail do motorista a ser editado: ");
    scanf("%80s", email);

    while (fscanf(file, "%80s %50s %8s %20s %9s", motorista.email, motorista.nome, motorista.senha, motorista.transporte, motorista.CNH) == 5) {
        if (strcmp(email, motorista.email) == 0) {
            encontrado = 1;
            printf("Digite o novo nome: ");
            char novo_nome[50];
            scanf(" %[^\n]s", novo_nome); // Lê a linha inteira

            printf("Digite a nova senha: ");
            char nova_senha[9];
            scanf(" %[^\n]s", nova_senha); // Lê a linha inteira

            printf("Digite o novo meio de transporte: ");
            char novo_transporte[21];
            scanf(" %[^\n]s", novo_transporte); // Lê a linha inteira

            printf("Digite o novo número de CNH: ");
            char nova_CNH[9];
            scanf(" %[^\n]s", nova_CNH); // Lê a linha inteira

            if (strlen(novo_nome) > 0) {
                strcpy(motorista.nome, novo_nome);
            }
            if (strlen(nova_senha) > 0) {
                strcpy(motorista.senha, nova_senha);
            }
            if (strlen(novo_transporte) > 0) {
                strcpy(motorista.transporte, novo_transporte);
            }
            if (strlen(nova_CNH) > 0) {
                strcpy(motorista.CNH, nova_CNH);
            }

            fprintf(tempFile, "%s %s %s %s %s\n", motorista.email, motorista.nome, motorista.senha, motorista.transporte, motorista.CNH);
        } else {
            fprintf(tempFile, "%s %s %s %s %s\n", motorista.email, motorista.nome, motorista.senha, motorista.transporte, motorista.CNH);
        }
    }

    if (!encontrado) {
        printf("Motorista não encontrado!\n");
    } else {
        printf("Dados atualizados com sucesso!\n");
    }

    fclose(file);
    fclose(tempFile);

    remove("cadastro_motorista.txt");
    rename("temp_motorista.txt", "cadastro_motorista.txt");
}

void excluir_motorista() {
    system("cls");
    FILE *file = fopen("cadastro_motorista.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de cadastro!\n");
        return;
    }

    FILE *tempFile = fopen("temp_motorista.txt", "w");
    if (tempFile == NULL) {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(file);
        return;
    }

    Motorista motorista;
    char email[81];
    int encontrado = 0;

    printf("Digite o e-mail do motorista a ser excluído: ");
    scanf("%80s", email);

    while (fscanf(file, "%80s %50s %8s %20s %9s", motorista.email, motorista.nome, motorista.senha, motorista.transporte, motorista.CNH) == 5) {
        if (strcmp(email, motorista.email) == 0) {
            encontrado = 1;
            printf("Motorista %s excluído com sucesso!\n", motorista.nome);
        } else {
            fprintf(tempFile, "%s %s %s %s %s\n", motorista.email, motorista.nome, motorista.senha, motorista.transporte, motorista.CNH);
        }
    }

    if (!encontrado) {
        printf("Motorista não encontrado!\n");
    }

    fclose(file);
    fclose(tempFile);

    remove("cadastro_motorista.txt");
    rename("temp_motorista.txt", "cadastro_motorista.txt");
}