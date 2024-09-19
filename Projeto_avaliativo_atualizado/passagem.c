#include "funcoes.h"

int compara_viagens(const void *a, const void *b) {
    const Viagem *viagem1 = (const Viagem *)a;
    const Viagem *viagem2 = (const Viagem *)b;
    
    int cmp = strcmp(viagem1->cidade, viagem2->cidade);
    if (cmp == 0) {
        if (viagem1->mes_ida != viagem2->mes_ida)
            return viagem1->mes_ida - viagem2->mes_ida;
        return viagem1->dia_ida - viagem2->dia_ida;
    }
    return cmp;
}

int busca_binaria(Viagem viagens[], int n, Viagem *busca) {
    int esquerda = 0, direita = n - 1;
    
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        int cmp = compara_viagens(&viagens[meio], busca);

        if (cmp == 0) return meio;
        if (cmp < 0) esquerda = meio + 1;
        else direita = meio - 1;
    }
    return -1;
}

void compra_passagem() {
    FILE *viagem_file = fopen("agendamento_viagem.txt", "r");
    if (!viagem_file) {
        printf("Erro ao abrir o arquivo de viagens.\n");
        return;
    }

    Viagem viagens[100]; // Tamanho fixo do array
    int n = 0;
    while (fscanf(viagem_file, "%d/%d %d/%d %20s %2s",
                  &viagens[n].dia_ida, &viagens[n].mes_ida,
                  &viagens[n].dia_volta, &viagens[n].mes_volta,
                  viagens[n].cidade, viagens[n].estado) == 6) {
        n++;
    }
    fclose(viagem_file);

    qsort(viagens, n, sizeof(Viagem), compara_viagens);

    Viagem busca;
    printf("Digite a cidade da viagem: ");
    scanf("%20s", busca.cidade);
    printf("Digite o mês de ida (1-12): ");
    scanf("%d", &busca.mes_ida);
    printf("Digite o dia de ida (1-31): ");
    scanf("%d", &busca.dia_ida);

    int index = busca_binaria(viagens, n, &busca);
    if (index == -1) {
        printf("Viagem não encontrada.\n");
        return;
    }

    int quantidade;
    printf("Quantas passagens deseja comprar? ");
    scanf("%d", &quantidade);

    FILE *compra_file = fopen("compras.txt", "a");
    if (!compra_file) {
        printf("Erro ao abrir o arquivo de compras.\n");
        return;
    }

    fprintf(compra_file, "%d/%d %d/%d %s %s %d\n",
            viagens[index].dia_ida, viagens[index].mes_ida,
            viagens[index].dia_volta, viagens[index].mes_volta,
            viagens[index].cidade, viagens[index].estado, quantidade);
    fclose(compra_file);

    printf("Passagem comprada com sucesso!\n");
}

void visualizar_compras() {
    FILE *compra_file = fopen("compras.txt", "r");
    if (!compra_file) {
        printf("Erro ao abrir o arquivo de compras.\n");
        return;
    }

    int dia_ida, mes_ida, dia_volta, mes_volta;
    char cidade[21], estado[3];
    int quantidade;

    printf("==== Suas Compras ====\n");
    while (fscanf(compra_file, "%d/%d %d/%d %20s %2s %d",
                  &dia_ida, &mes_ida, &dia_volta, &mes_volta,
                  cidade, estado, &quantidade) == 7) {
        printf("Data de Ida: %02d/%02d, Data de Volta: %02d/%02d, Cidade: %s, Estado: %s, Quantidade: %d\n",
               dia_ida, mes_ida, dia_volta, mes_volta, cidade, estado, quantidade);
    }
    fclose(compra_file);
}

void cancelar_passagem() {
    FILE *compra_file = fopen("compras.txt", "r");
    if (!compra_file) {
        printf("Erro ao abrir o arquivo de compras.\n");
        return;
    }

    FILE *temp_file = fopen("temp_compras.txt", "w");
    if (!temp_file) {
        printf("Erro ao criar o arquivo temporário.\n");
        fclose(compra_file);
        return;
    }

    int dia_ida, mes_ida, dia_volta, mes_volta;
    char cidade[21], estado[3];
    int quantidade;
    int encontrado = 0;

    printf("Digite a cidade da passagem a cancelar: ");
    scanf("%20s", cidade);
    printf("Digite o mês de ida (1-12): ");
    scanf("%d", &mes_ida);
    printf("Digite o dia de ida (1-31): ");
    scanf("%d", &dia_ida);

    while (fscanf(compra_file, "%d/%d %d/%d %20s %2s %d",
                  &dia_ida, &mes_ida, &dia_volta, &mes_volta,
                  cidade, estado, &quantidade) == 7) {
        if (strcmp(cidade, cidade) == 0 && mes_ida == mes_ida && dia_ida == dia_ida) {
            encontrado = 1;
            printf("Passagem cancelada!\n");
        } else {
            fprintf(temp_file, "%d/%d %d/%d %s %s %d\n",
                    dia_ida, mes_ida, dia_volta, mes_volta,
                    cidade, estado, quantidade);
        }
    }

    fclose(compra_file);
    fclose(temp_file);

    remove("compras.txt");
    rename("temp_compras.txt", "compras.txt");

    if (!encontrado) {
        printf("Passagem não encontrada.\n");
    }
}