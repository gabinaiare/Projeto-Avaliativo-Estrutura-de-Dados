#include "funcoes.h"

void agendar_viagem() {
    system("cls");

    FILE *file = fopen("agendamento_viagem.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Viagem viagem;

    printf("Digite a cidade (máx. 20 caracteres): ");
    scanf("%20s", viagem.cidade);

    printf("Digite o estado (sigla de 2 letras): ");
    scanf("%2s", viagem.estado);

    while (getchar() != '\n');

    int valido = 0;
    while (!valido) {
        printf("Digite o dia de ida (1-31): ");
        if (scanf("%d", &viagem.dia_ida) != 1) {
            printf("Entrada inválida. Tente novamente.\n");
            while (getchar() != '\n'); 
            continue;
        }

        printf("Digite o mês de ida (1-12): ");
        if (scanf("%d", &viagem.mes_ida) != 1) {
            printf("Entrada inválida. Tente novamente.\n");
            while (getchar() != '\n'); 
            continue;
        }

        printf("Digite o dia de volta (1-31): ");
        if (scanf("%d", &viagem.dia_volta) != 1) {
            printf("Entrada inválida. Tente novamente.\n");
            while (getchar() != '\n'); 
            continue;
        }

        printf("Digite o mês de volta (1-12): ");
        if (scanf("%d", &viagem.mes_volta) != 1) {
            printf("Entrada inválida. Tente novamente.\n");
            while (getchar() != '\n'); 
            continue;
        }

        // Validação das datas
        if ((viagem.dia_ida < 1 || viagem.dia_ida > 31) || 
            (viagem.mes_ida < 1 || viagem.mes_ida > 12)) {
            printf("Data de ida inválida. Tente novamente.\n");
        } else if ((viagem.dia_volta < 1 || viagem.dia_volta > 31) || 
                   (viagem.mes_volta < 1 || viagem.mes_volta > 12)) {
            printf("Data de volta inválida. Tente novamente.\n");
        } else {
            valido = 1;
        }

        while (getchar() != '\n');
    }

    fprintf(file, "Cidade: %s | Estado: %s | Ida: %02d/%02d | Volta: %02d/%02d\n", 
            viagem.cidade, viagem.estado, viagem.dia_ida, viagem.mes_ida, viagem.dia_volta, viagem.mes_volta);

    fclose(file);
    printf("Viagem agendada com sucesso!\n");
}

void editar_viagem() {
    system("cls");
    
    FILE *file = fopen("agendamento_viagem.txt", "r+");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de agendamento de viagens!\n");
        return;
    }

    FILE *tempFile = fopen("temp_viagem.txt", "w");
    if (tempFile == NULL) {
        printf("Erro ao criar o arquivo temporário!\n");
        fclose(file);
        return;
    }

    Viagem viagem;
    char cidade[21];
    int encontrado = 0;

 
    printf("Digite a cidade da viagem que deseja editar: ");
    scanf("%20s", cidade);

    // Ler as viagens do arquivo original e procurar a viagem a ser editada
    while (fscanf(file, "%d %d %d %d %20s %2s", 
                  &viagem.dia_ida, &viagem.mes_ida, 
                  &viagem.dia_volta, &viagem.mes_volta, 
                  viagem.cidade, viagem.estado) != EOF) {
        
        if (strcmp(cidade, viagem.cidade) == 0) {
            encontrado = 1;
            
            // Solicitar novos dados para a viagem
            printf("Digite a nova cidade (ou mantenha a atual %s): ", viagem.cidade);
            char nova_cidade[21];
            scanf("%20s", nova_cidade);

            printf("Digite o novo estado (ou mantenha o atual %s): ", viagem.estado);
            char novo_estado[3];
            scanf("%2s", novo_estado);

            printf("Digite o novo dia de ida (ou mantenha o atual %02d): ", viagem.dia_ida);
            int novo_dia_ida;
            scanf("%d", &novo_dia_ida);

            printf("Digite o novo mês de ida (ou mantenha o atual %02d): ", viagem.mes_ida);
            int novo_mes_ida;
            scanf("%d", &novo_mes_ida);

            printf("Digite o novo dia de volta (ou mantenha o atual %02d): ", viagem.dia_volta);
            int novo_dia_volta;
            scanf("%d", &novo_dia_volta);

            printf("Digite o novo mês de volta (ou mantenha o atual %02d): ", viagem.mes_volta);
            int novo_mes_volta;
            scanf("%d", &novo_mes_volta);

            // Atualizar os dados da viagem se o usuário digitou novos valores
            if (strlen(nova_cidade) > 0) strcpy(viagem.cidade, nova_cidade);
            if (strlen(novo_estado) > 0) strcpy(viagem.estado, novo_estado);
            viagem.dia_ida = novo_dia_ida;
            viagem.mes_ida = novo_mes_ida;
            viagem.dia_volta = novo_dia_volta;
            viagem.mes_volta = novo_mes_volta;

            // Escrever a viagem atualizada no arquivo temporário
            fprintf(tempFile, "%d %d %d %d %s %s\n", 
                    viagem.dia_ida, viagem.mes_ida, 
                    viagem.dia_volta, viagem.mes_volta, 
                    viagem.cidade, viagem.estado);

        } else {
            // Copiar as viagens não alteradas para o arquivo temporário
            fprintf(tempFile, "%d %d %d %d %s %s\n", 
                    viagem.dia_ida, viagem.mes_ida, 
                    viagem.dia_volta, viagem.mes_volta, 
                    viagem.cidade, viagem.estado);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Substituir o arquivo original pelo temporário
    remove("agendamento_viagem.txt");
    rename("temp_viagem.txt", "agendamento_viagem.txt");

    if (encontrado) {
        printf("Viagem editada com sucesso!\n");
    } else {
        printf("Viagem não encontrada.\n");
    }
}

void listar_viagens() {
    system("cls");
    FILE *file = fopen("agendamento_viagem.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de agendamento de viagens!\n");
        return;
    }

    Viagem viagem;
    printf("Lista de Viagens Agendadas:\n");
    printf("==========================================\n");
    printf("Cidade         Estado   Ida       Volta\n");
    printf("==========================================\n");

    // Ler todas as viagens do arquivo e exibi-las
    while (fscanf(file, "%d %d %d %d %20s %2s", 
                  &viagem.dia_ida, &viagem.mes_ida, 
                  &viagem.dia_volta, &viagem.mes_volta, 
                  viagem.cidade, viagem.estado) != EOF) {
        printf("%-15s %-7s %02d/%02d    %02d/%02d\n", 
               viagem.cidade, viagem.estado, 
               viagem.dia_ida, viagem.mes_ida, 
               viagem.dia_volta, viagem.mes_volta);
    }

    fclose(file);
}

void apagar_viagem() {
    system("cls");
    FILE *file = fopen("agendamento_viagem.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de agendamento de viagens!\n");
        return;
    }

    FILE *tempFile = fopen("temp_viagem.txt", "w");
    if (tempFile == NULL) {
        printf("Erro ao criar o arquivo temporário!\n");
        fclose(file);
        return;
    }

    Viagem viagem;
    char cidade[21];
    int encontrado = 0;

    // Solicitar o nome da cidade para encontrar a viagem a ser apagada
    printf("Digite a cidade da viagem que deseja apagar: ");
    scanf("%20s", cidade);

    // Ler as viagens e copiar todas, exceto a que será apagada, para o arquivo temporário
    while (fscanf(file, "%d %d %d %d %20s %2s", 
                  &viagem.dia_ida, &viagem.mes_ida, 
                  &viagem.dia_volta, &viagem.mes_volta, 
                  viagem.cidade, viagem.estado) != EOF) {
        
        if (strcmp(cidade, viagem.cidade) != 0) {
            // Copiar viagens que não são a que será apagada
            fprintf(tempFile, "%d %d %d %d %s %s\n", 
                    viagem.dia_ida, viagem.mes_ida, 
                    viagem.dia_volta, viagem.mes_volta, 
                    viagem.cidade, viagem.estado);
        } else {
            encontrado = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    // Substituir o arquivo original pelo temporário
    remove("agendamento_viagem.txt");
    rename("temp_viagem.txt", "agendamento_viagem.txt");

    if (encontrado) {
        printf("Viagem apagada com sucesso!\n");
    } else {
        printf("Viagem não encontrada.\n");
    }
}