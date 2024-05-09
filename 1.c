#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_HOSPEDES 100
#define MAX_NOME 50

typedef struct {
    char nome[MAX_NOME];
    int numero_quarto;
} Hospede;

Hospede hospedes[MAX_HOSPEDES];
int num_hospedes = 0;

void inserirHospede() {
    if (num_hospedes >= MAX_HOSPEDES) {
        printf("Limite de hospedes atingido.\n");
        return;
    }

    printf("Digite o nome do hospede: ");
    scanf("%s", hospedes[num_hospedes].nome);
    printf("Digite o número do quarto: ");
    scanf("%d", &hospedes[num_hospedes].numero_quarto);
    num_hospedes++;
}

void listarHospedes() {
    int i, j;
    Hospede temp;
    for (i = 0; i < num_hospedes - 1; i++) {
        for (j = 0; j < num_hospedes - i - 1; j++) {
            if (strcmp(hospedes[j].nome, hospedes[j + 1].nome) > 0) {
                temp = hospedes[j];
                hospedes[j] = hospedes[j + 1];
                hospedes[j + 1] = temp;
            }
        }
    }

    printf("Lista de hóspedes por ordem alfabética:\n");
    for (i = 0; i < num_hospedes; i++) {
        printf("Nome: %s, Quarto: %d\n", hospedes[i].nome, hospedes[i].numero_quarto);
    }
}

void buscarHospede() {
    char nome[MAX_NOME];
    printf("Digite o nome do hóspede a ser buscado: ");
    scanf("%s", nome);

    for (int i = 0; i < num_hospedes; i++) {
        if (strcmp(hospedes[i].nome, nome) == 0) {
            printf("Hóspede encontrado! Nome: %s, Quarto: %d\n", hospedes[i].nome, hospedes[i].numero_quarto);
            return;
        }
    }

    printf("Hóspede não encontrado.\n");
}

void editarHospede() {
    char nome[MAX_NOME];
    printf("Digite o nome do hóspede a ser editado: ");
    scanf("%s", nome);

    for (int i = 0; i < num_hospedes; i++) {
        if (strcmp(hospedes[i].nome, nome) == 0) {
            printf("Digite o novo número do quarto: ");
            scanf("%d", &hospedes[i].numero_quarto);
            printf("Hóspede editado com sucesso.\n");
            return;
        }
    }

    printf("Hóspede não encontrado.\n");
}

void liberarQuarto() {
    int quarto;
    printf("Digite o número do quarto a ser liberado: ");
    scanf("%d", &quarto);

    for (int i = 0; i < num_hospedes; i++) {
        if (hospedes[i].numero_quarto == quarto) {
            printf("Quarto liberado. Hóspede: %s\n", hospedes[i].nome);
            strcpy(hospedes[i].nome, "");
            hospedes[i].numero_quarto = 0;
            return;
        }
    }

    printf("Quarto não encontrado ou já está vazio.\n");
}

void mostrarQuartosVazios() {
    printf("Quartos vazios:\n");
    for (int i = 0; i < num_hospedes; i++) {
        if (strcmp(hospedes[i].nome, "") == 0) {
            printf("%d\n", hospedes[i].numero_quarto);
        }
    }
}

void salvarLista() {
    FILE *arquivo;
    arquivo = fopen("hospedes.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < num_hospedes; i++) {
        fprintf(arquivo, "%s %d\n", hospedes[i].nome, hospedes[i].numero_quarto);
    }

    fclose(arquivo);
    printf("Lista de hóspedes salva com sucesso.\n");
}

void carregarLista() {
    FILE *arquivo;
    arquivo = fopen("hospedes.txt", "r");

    if (arquivo == NULL) {
        printf("Arquivo não encontrado.\n");
        return;
    }

    while (!feof(arquivo) && num_hospedes < MAX_HOSPEDES) {
        fscanf(arquivo, "%s %d\n", hospedes[num_hospedes].nome, &hospedes[num_hospedes].numero_quarto);
        num_hospedes++;
    }

    fclose(arquivo);
}

int main() {
    int opcao;

    carregarLista();

    do {
        printf("\nMenu:\n");
        printf("1. Inserir hóspedes em um quarto vazio\n");
        printf("2. Listar hóspedes por ordem alfabética\n");
        printf("3. Buscar hóspede\n");
        printf("4. Editar hóspede\n");
        printf("5. Liberar um quarto\n");
        printf("6. Mostrar os números dos quartos vazios\n");
        printf("7. Salvar lista de hóspedes com respectivos quartos em arquivo\n");
        printf("8. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirHospede();
                break;
            case 2:
                listarHospedes();
                break;
            case 3:
                buscarHospede();
                break;
            case 4:
                editarHospede();
                break;
            case 5:
                liberarQuarto();
                break;
            case 6:
                mostrarQuartosVazios();
                break;
            case 7:
                salvarLista();
                break;
            case 8:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 8);

    return 0;
}
