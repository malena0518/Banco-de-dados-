#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO "arquivo.txt"

struct Aluno {
    int id_aluno;
    char nome[50];
    char curso[50];
    float nota;
};

// Cadastrar
void cadastrar() {
    FILE *arq = fopen(ARQUIVO, "a");

    if (arq == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    struct Aluno a;

    printf("\nID do aluno: ");
    scanf("%d", &a.id_aluno);
    getchar();

    printf("Nome: ");
    fgets(a.nome, 50, stdin);
    a.nome[strcspn(a.nome, "\n")] = 0;

    printf("Curso: ");
    fgets(a.curso, 50, stdin);
    a.curso[strcspn(a.curso, "\n")] = 0;

    printf("Nota: ");
    scanf("%f", &a.nota);

    fprintf(arq, "%d;%s;%s;%.2f\n", a.id_aluno, a.nome, a.curso, a.nota);

    fclose(arq);
    printf("Aluno cadastrado com sucesso!\n");
}

// Listar
void listar() {
    FILE *arq = fopen(ARQUIVO, "r");

    if (arq == NULL) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    struct Aluno a;

    printf("\n--- Lista de Alunos ---\n");

    while (fscanf(arq, "%d;%49[^;];%49[^;];%f\n",
                  &a.id_aluno, a.nome, a.curso, &a.nota) == 4) {
        printf("ID: %d | Nome: %s | Curso: %s | Nota: %.2f\n",
               a.id_aluno, a.nome, a.curso, a.nota);
    }

    fclose(arq);
}

// Alterar tudo
void alterar() {
    FILE *arq = fopen(ARQUIVO, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (arq == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    int idBusca;
    struct Aluno a;
    int encontrado = 0;

    printf("Digite o ID do aluno para alterar: ");
    scanf("%d", &idBusca);

    while (fscanf(arq, "%d;%49[^;];%49[^;];%f\n",
                  &a.id_aluno, a.nome, a.curso, &a.nota) == 4) {

        if (a.id_aluno == idBusca) {
            encontrado = 1;

            printf("Novo nome: ");
            getchar();
            fgets(a.nome, 50, stdin);
            a.nome[strcspn(a.nome, "\n")] = 0;

            printf("Novo curso: ");
            fgets(a.curso, 50, stdin);
            a.curso[strcspn(a.curso, "\n")] = 0;

            printf("Nova nota: ");
            scanf("%f", &a.nota);
        }

        fprintf(temp, "%d;%s;%s;%.2f\n",
                a.id_aluno, a.nome, a.curso, a.nota);
    }

    fclose(arq);
    fclose(temp);

    remove(ARQUIVO);
    rename("temp.txt", ARQUIVO);

    if (encontrado)
        printf("Aluno alterado com sucesso!\n");
    else
        printf("Aluno não encontrado.\n");
}

// Alterar apenas curso
void alterarCurso() {
    FILE *arq = fopen(ARQUIVO, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (arq == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    int idBusca;
    struct Aluno a;
    int encontrado = 0;

    printf("Digite o ID do aluno para mudar o curso: ");
    scanf("%d", &idBusca);

    while (fscanf(arq, "%d;%49[^;];%49[^;];%f\n",
                  &a.id_aluno, a.nome, a.curso, &a.nota) == 4) {

        if (a.id_aluno == idBusca) {
            encontrado = 1;

            printf("Curso atual: %s\n", a.curso);

            printf("Novo curso: ");
            getchar();
            fgets(a.curso, 50, stdin);
            a.curso[strcspn(a.curso, "\n")] = 0;
        }

        fprintf(temp, "%d;%s;%s;%.2f\n",
                a.id_aluno, a.nome, a.curso, a.nota);
    }

    fclose(arq);
    fclose(temp);

    remove(ARQUIVO);
    rename("temp.txt", ARQUIVO);

    if (encontrado)
        printf("Curso atualizado com sucesso!\n");
    else
        printf("Aluno não encontrado.\n");
}

// Deletar
void deletar() {
    FILE *arq = fopen(ARQUIVO, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (arq == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    int idBusca;
    struct Aluno a;
    int encontrado = 0;

    printf("Digite o ID do aluno para deletar: ");
    scanf("%d", &idBusca);

    while (fscanf(arq, "%d;%49[^;];%49[^;];%f\n",
                  &a.id_aluno, a.nome, a.curso, &a.nota) == 4) {

        if (a.id_aluno != idBusca) {
            fprintf(temp, "%d;%s;%s;%.2f\n",
                    a.id_aluno, a.nome, a.curso, a.nota);
        } else {
            encontrado = 1;
        }
    }

    fclose(arq);
    fclose(temp);

    remove(ARQUIVO);
    rename("temp.txt", ARQUIVO);

    if (encontrado)
        printf("Aluno deletado com sucesso!\n");
    else
        printf("Aluno não encontrado.\n");
}

// Menu
int main() {
    int opcao;

    do {
        printf("\n--- Sistema de Alunos ---\n");
        printf("1 - Cadastrar\n");
        printf("2 - Listar\n");
        printf("3 - Alterar tudo\n");
        printf("4 - Deletar\n");
        printf("5 - Alterar apenas curso\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrar(); break;
            case 2: listar(); break;
            case 3: alterar(); break;
            case 4: deletar(); break;
            case 5: alterarCurso(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
