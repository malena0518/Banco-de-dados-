#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Definição dos nomes dos arquivos
#define ARQ_ALUNO      "alunos.txt"
#define ARQ_PROFESSOR  "professores.txt"
#define ARQ_DISCIPLINA "disciplinas.txt"
#define ARQ_MATRICULA  "matriculas.txt"

// Estruturas
struct Aluno { int id; char nome[50]; char turma[20]; };
struct Professor { int id; char nome[50]; char area[50]; };
struct Disciplina { int id; char nome[50]; int id_prof; int carga; };
struct Matricula { int id_disc; int id_aluno; char periodo[20]; };

// --- UTILITÁRIOS ---

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int nomeEhValido(char *nome) {
    if (strlen(nome) == 0) return 0;
    for (int i = 0; nome[i] != '\0'; i++) {
        if (!isalpha(nome[i]) && !isspace(nome[i])) return 0;
    }
    return 1;
}

int gerarID(char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "r");
    if (!f) return 1001;
    int id, maior = 1000;
    char linha[200];
    while (fgets(linha, sizeof(linha), f)) {
        sscanf(linha, "%d;", &id);
        if (id > maior) maior = id;
    }
    fclose(f);
    return maior + 1;
}

// --- FUNÇÕES DE CADASTRO ---

void cadastrarAluno() {
    struct Aluno a;
    a.id = gerarID(ARQ_ALUNO);
    limparBuffer();
    
    do {
        printf("Nome do Aluno (apenas letras): ");
        fgets(a.nome, 50, stdin);
        a.nome[strcspn(a.nome, "\n")] = 0;
    } while (!nomeEhValido(a.nome) && printf("[!] Nome invalido.\n"));

    printf("Turma: ");
    fgets(a.turma, 20, stdin);
    a.turma[strcspn(a.turma, "\n")] = 0;

    FILE *f = fopen(ARQ_ALUNO, "a");
    fprintf(f, "%d;%s;%s\n", a.id, a.nome, a.turma);
    fclose(f);
    printf("Aluno cadastrado com ID: %d\n", a.id);
}

void cadastrarProfessor() {
    struct Professor p;
    p.id = gerarID(ARQ_PROFESSOR);
    limparBuffer();

    do {
        printf("Nome do Professor: ");
        fgets(p.nome, 50, stdin);
        p.nome[strcspn(p.nome, "\n")] = 0;
    } while (!nomeEhValido(p.nome) && printf("[!] Nome invalido.\n"));

    printf("Area de Atuacao: ");
    fgets(p.area, 50, stdin);
    p.area[strcspn(p.area, "\n")] = 0;

    FILE *f = fopen(ARQ_PROFESSOR, "a");
    fprintf(f, "%d;%s;%s\n", p.id, p.nome, p.area);
    fclose(f);
    printf("Professor cadastrado com ID: %d\n", p.id);
}

void cadastrarDisciplina() {
    struct Disciplina d;
    d.id = gerarID(ARQ_DISCIPLINA);
    limparBuffer();

    printf("Nome da Disciplina: ");
    fgets(d.nome, 50, stdin);
    d.nome[strcspn(d.nome, "\n")] = 0;

    printf("ID do Professor Responsavel: ");
    scanf("%d", &d.id_prof);
    printf("Carga Horaria: ");
    scanf("%d", &d.carga);

    FILE *f = fopen(ARQ_DISCIPLINA, "a");
    fprintf(f, "%d;%s;%d;%d\n", d.id, d.nome, d.id_prof, d.carga);
    fclose(f);
    printf("Disciplina cadastrada com ID: %d\n", d.id);
}

void cadastrarMatricula() {
    struct Matricula m;
    printf("ID da Disciplina: ");
    scanf("%d", &m.id_disc);
    printf("ID do Aluno: ");
    scanf("%d", &m.id_aluno);
    limparBuffer();
    printf("Periodo (ex: 2026.1): ");
    fgets(m.periodo, 20, stdin);
    m.periodo[strcspn(m.periodo, "\n")] = 0;

    FILE *f = fopen(ARQ_MATRICULA, "a");
    fprintf(f, "%d;%d;%s\n", m.id_disc, m.id_aluno, m.periodo);
    fclose(f);
    printf("Matricula realizada!\n");
}

// --- FUNÇÕES DE LISTAGEM ---

void listarTudo() {
    char nomes[4][20] = {"ALUNOS", "PROFESSORES", "DISCIPLINAS", "MATRICULAS"};
    char arquivos[4][30] = {ARQ_ALUNO, ARQ_PROFESSOR, ARQ_DISCIPLINA, ARQ_MATRICULA};
    
    for(int i = 0; i < 4; i++) {
        FILE *f = fopen(arquivos[i], "r");
        printf("\n--- %s ---\n", nomes[i]);
        if (!f) { printf("Vazio.\n"); continue; }
        char linha[200];
        while (fgets(linha, sizeof(linha), f)) printf("%s", linha);
        fclose(f);
    }
}

// --- MAIN ---

int main() {
    int opcao;
    while (1) {
        printf("\n========= SISTEMA ACADEMICO =========\n");
        printf("1. Cadastrar Aluno      2. Cadastrar Professor\n");
        printf("3. Cadastrar Disciplina 4. Matricular Aluno\n");
        printf("5. Listar Todos os Dados\n");
        printf("=====================================\nEscolha: ");
        
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            continue;
        }

        switch (opcao) {
            case 1: cadastrarAluno(); break;
            case 2: cadastrarProfessor(); break;
            case 3: cadastrarDisciplina(); break;
            case 4: cadastrarMatricula(); break;
            case 5: listarTudo(); break;
            default: printf("Opcao invalida.\n");
        }
    }
    return 0;
}
