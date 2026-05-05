#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>  
#include <time.h>
#include <ctype.h> // Necessário para isalpha e isspace

#define ARQUIVO "alunos.txt" 

struct Aluno {
    int id_aluno;      
    char nome[50];     
    char turma[20];    
};

// --- FUNÇÕES DE VALIDAÇÃO E AUXILIARES ---

// Verifica se o nome contém apenas letras e espaços
int nomeEhValido(char *nome) {
    if (strlen(nome) == 0) return 0;
    
    for (int i = 0; nome[i] != '\0'; i++) {
        // isalpha verifica se é letra, isspace verifica se é espaço
        if (!isalpha(nome[i]) && !isspace(nome[i])) {
            return 0; // Contém números ou símbolos
        }
    }
    return 1;
}

int idExiste(int id) {
    FILE *arq = fopen(ARQUIVO, "r");
    if (arq == NULL) return 0;

    int tempId;
    char n[50], t[20];
    
    while (fscanf(arq, "%d;%49[^;];%19[^\n]\n", &tempId, n, t) == 3) {
        if (tempId == id) {
            fclose(arq);
            return 1; 
        }
    }
    fclose(arq);
    return 0;
}

int gerarIDAleatorio() {
    int novoId;
    static int sementeInicializada = 0;
    if (!sementeInicializada) {
        srand(time(NULL));
        sementeInicializada = 1;
    }
    
    do {
        novoId = (rand() % 9000) + 1000; 
    } while (idExiste(novoId)); 
    
    return novoId;
}

// --- FUNÇÕES PRINCIPAIS ---

void cadastrar() {
    FILE *arq = fopen(ARQUIVO, "a");
    if (!arq) return;

    struct Aluno a;
    a.id_aluno = gerarIDAleatorio();

    printf("\nID Gerado: [%d]\n", a.id_aluno);
    
    // Validação do Nome (Apenas letras)
    getchar(); // Limpa buffer
    while (1) {
        printf("Nome do Aluno: ");
        fgets(a.nome, 50, stdin);
        a.nome[strcspn(a.nome, "\n")] = 0;

        if (nomeEhValido(a.nome)) {
            break;
        } else {
            printf("[!] Erro: o nome deve conter apenas letras. Tente novamente.\n");
        }
    }

    printf("Turma: ");
    fgets(a.turma, 20, stdin);
    a.turma[strcspn(a.turma, "\n")] = 0;

    fprintf(arq, "%d;%s;%s\n", a.id_aluno, a.nome, a.turma);
    fclose(arq);
    printf("Aluno cadastrado com sucesso!\n");
}

void listar() {
    FILE *arq = fopen(ARQUIVO, "r");
    if (arq == NULL) {
        printf("\nNenhum aluno cadastrado.\n");
        return;
    }

    struct Aluno a;
    printf("\n%-6s | %-25s | %-10s\n", "ID", "NOME", "TURMA");
    printf("--------------------------------------------------\n");

    while (fscanf(arq, "%d;%49[^;];%19[^\n]\n", &a.id_aluno, a.nome, a.turma) == 3) {
        printf("%-6d | %-25s | %-10s\n", a.id_aluno, a.nome, a.turma);
    }
    fclose(arq);
}

int main() {
    int opcao;
    
    while (1) {
        printf("\n========= CONTROLE DE TURMAS =========\n");
        printf("1. Cadastrar Aluno\n");
        printf("2. Listar Alunos\n");
        printf("======================================\n");
        printf("Escolha: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("[!] Digite apenas 1 ou 2.\n");
            while (getchar() != '\n'); 
            continue;
        }

        switch (opcao) {
            case 1: cadastrar(); break;
            case 2: listar(); break;
            default: printf("Opcao invalida!\n");
        }
    }

    return 0;
}
