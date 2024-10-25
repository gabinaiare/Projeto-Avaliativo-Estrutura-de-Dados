#include "funcoes.h"

// Função para cadastrar motorista
void cadastro_motorista(ListaMotoristas *lista) {
    system("cls");
    Motorista *motorista = (Motorista*)malloc(sizeof(Motorista));
    
    if (motorista == NULL) {
        printf("Erro ao alocar memória para motorista!\n");
        return;
    }

    printf("Digite seu nome de usuário: ");
    scanf("%49s", motorista->nome); 

    // Validação do email
    do {
        printf("Digite o seu email: ");
        scanf("%80s", motorista->email);

        if (strchr(motorista->email, '@') != NULL) {
            printf("E-mail válido.\n");
            break;
        } else {
            printf("E-mail inválido, não contém '@'.\n");
        }
    } while (1);

    printf("Digite uma senha de até 8 dígitos: ");
    scanf("%8s", motorista->senha); 

    printf("Digite qual é o seu meio de transporte: ");
    scanf("%20s", motorista->transporte); 

    printf("Digite seu número de registro da CNH (9 dígitos): ");
    scanf("%9s", motorista->CNH); 

    motorista->proximo = lista->inicio; // Insere no início da lista
    lista->inicio = motorista; // Atualiza o início da lista
    printf("Motorista cadastrado com sucesso!\n");
}

// Função para login de motorista
int login_motorista(ListaMotoristas *lista) {
    system("cls");
    Motorista *motorista = lista->inicio;
    char email[81], senha[9];
    int encontrado = 0;

    printf("Digite o seu email: ");
    scanf("%80s", email); 

    printf("Digite sua senha: ");
    scanf("%8s", senha); 

    while (motorista != NULL) {
        if (strcmp(email, motorista->email) == 0 && strcmp(senha, motorista->senha) == 0) {
            printf("Login bem-sucedido! Bem-vindo de volta, %s!\n", motorista->nome);
            encontrado = 1;
            break;
        }
        motorista = motorista->proximo;
    }

    if (!encontrado) {
        printf("E-mail ou senha inválidos.\n");
    }

    return encontrado;
}

// Função para visualizar dados do motorista
void visualizar_motorista(ListaMotoristas *lista) {
    system("cls");
    Motorista *motorista = lista->inicio;

    while (motorista != NULL) {
        printf("Nome: %s\n", motorista->nome);
        printf("Email: %s\n", motorista->email);
        printf("Transporte: %s\n", motorista->transporte);
        printf("CNH: %s\n\n", motorista->CNH);
        motorista = motorista->proximo;
    }
}

// Função para editar dados do motorista
void editar_motorista(ListaMotoristas *lista) {
    system("cls");
    char email[81];
    printf("Digite o seu email: ");
    scanf("%80s", email);

    Motorista *motorista = lista->inicio;
    while (motorista != NULL) {
        if (strcmp(email, motorista->email) == 0) {
            printf("Digite o novo nome: ");
            scanf("%49s", motorista->nome);

            printf("Digite a nova senha: ");
            scanf("%8s", motorista->senha);

            printf("Digite o novo meio de transporte: ");
            scanf("%20s", motorista->transporte);

            printf("Digite o novo número de registro da CNH: ");
            scanf("%9s", motorista->CNH);
            printf("Dados atualizados com sucesso!\n");
            return;
        }
        motorista = motorista->proximo;
    }

    printf("Motorista não encontrado.\n");
}

// Função para excluir dados do motorista
void excluir_motorista(ListaMotoristas *lista) {
    system("cls");
    char email[81];
    printf("Digite o seu email: ");
    scanf("%80s", email);

    Motorista *motorista = lista->inicio;
    Motorista *anterior = NULL;

    while (motorista != NULL) {
        if (strcmp(email, motorista->email) == 0) {
            if (anterior == NULL) {
                lista->inicio = motorista->proximo; // Exclui o primeiro elemento
            } else {
                anterior->proximo = motorista->proximo; // Exclui um elemento do meio
            }
            free(motorista); // Libera a memória
            printf("Motorista excluído com sucesso!\n");
            return;
        }
        anterior = motorista;
        motorista = motorista->proximo;
    }

    printf("Motorista não encontrado.\n");
}

// Função para exibir o menu do motorista
void menu_motorista(ListaMotoristas *lista) {
    system("cls");
    int op;

    do {
        printf("==== Menu de Motorista ====\n");
        printf("1 - Cadastrar motorista\n");
        printf("2 - Fazer login\n");
        printf("3 - Visualizar dados do motorista\n");
        printf("4 - Editar dados do motorista\n");
        printf("5 - Excluir dados do motorista\n");
        printf("0 - Sair\n");
        printf("============================\n");
        scanf("%d", &op);

        switch (op) {
            case 1:
                cadastro_motorista(lista);
                break;
            case 2:
                if (login_motorista(lista)) {
                    printf("Você está logado!\n");
                }
                break;
            case 3:
                visualizar_motorista(lista);
                break;
            case 4:
                editar_motorista(lista);
                break;
            case 5:
                excluir_motorista(lista);
                break;
            case 0:
                printf("Saindo...\n");
                break;        
            default:
                printf("Opção inválida!\n");
                break;
        }
        printf("Pressione qualquer tecla para continuar...\n");
        getchar(); // Limpa o buffer
        getchar(); // Aguarda o usuário pressionar uma tecla
    } while (op != 0);
}