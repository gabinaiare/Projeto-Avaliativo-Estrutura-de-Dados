#include "funcoes.h"

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

void menu_motorista() {
    system("cls");
    int op;

    do
    {
        printf("==== Menu de Viagens ====\n");
        printf("1 - Agendar viagem\n");
        printf("2 - Editar viagem\n");
        printf("3 - Listar suas viagens agendadas\n");
        printf("4 - Cancelar viagem\n");
        printf("==== Menu de Motorista ====\n");
        printf("5 - Editar dados do motorista\n");
        printf("6 - Visualizar dados de motorista\n");
        printf("7 - Excluir dados\n");
        printf("0 - Voltar\n");
        printf("============================\n");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            agendar_viagem();
            break;
        case 2:
            editar_viagem();
            break;
        case 3:
            listar_viagens();
            break;
        case 4:
            apagar_viagem();
            break;
        case 5:
            editar_motorista();
            break;
        case 6:
            visualizar_motorista();
            break;
        case 7:
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
            scanf(" %[^\n]s", novo_nome);

            printf("Digite a nova senha: ");
            char nova_senha[9];
            scanf(" %[^\n]s", nova_senha);

            printf("Digite o novo meio de transporte: ");
            char novo_transporte[21];
            scanf(" %[^\n]s", novo_transporte); 

            printf("Digite o novo número de CNH: ");
            char nova_CNH[9];
            scanf(" %[^\n]s", nova_CNH);

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