#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUNOS 100
#define MAX_NOME 50
#define MAX_NOTAS 10

typedef struct {
    char nome[MAX_NOME];
    char telefone[15]; 
    char curso[MAX_NOME];
    float notas[MAX_NOTAS];
    int num_notas;
    float media;
    char situacao[10];
} Aluno;

int lerAlunos(Aluno alunos[]);
void calcularMediaSituacao(Aluno *aluno);
void salvarSituacaoFinal(Aluno alunos[], int num_alunos);

int main() {
    Aluno alunos[MAX_ALUNOS];
    int num_alunos;

    num_alunos = lerAlunos(alunos);

    for (int i = 0; i < num_alunos; i++) {
        calcularMediaSituacao(&alunos[i]);
    }

    salvarSituacaoFinal(alunos, num_alunos);

    return 0;
}

int lerAlunos(Aluno alunos[]) {
    FILE *arquivo;
    char linha[1024];
    int num_alunos = 0;
    int primeira_linha = 1;

    arquivo = fopen("DadosEntrada.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {

        if (primeira_linha) {
            primeira_linha = 0;
            continue;
        }

        char *token;
        token = strtok(linha, ",");
        strcpy(alunos[num_alunos].nome, token);

        token = strtok(NULL, ",");
        strcpy(alunos[num_alunos].telefone, token);

        token = strtok(NULL, ",");
        strcpy(alunos[num_alunos].curso, token);

        alunos[num_alunos].num_notas = 0;
        while ((token = strtok(NULL, ",")) != NULL && alunos[num_alunos].num_notas < MAX_NOTAS) {
            alunos[num_alunos].notas[alunos[num_alunos].num_notas++] = atof(token);
        }

        num_alunos++;
    }

    fclose(arquivo);

    return num_alunos;
}
void calcularMediaSituacao(Aluno *aluno) {
    float soma = 0;
    for (int i = 0; i < aluno->num_notas; i++) {
        soma += aluno->notas[i];
    }
    aluno->media = soma / aluno->num_notas;
    if (aluno->media >= 7.0) {
        strcpy(aluno->situacao, "APROVADO");
    } else {
        strcpy(aluno->situacao, "REPROVADO");
    }
}

void salvarSituacaoFinal(Aluno alunos[], int num_alunos) {
    FILE *arquivo;
    arquivo = fopen("SituacaoFinal.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo de saída.\n");
        exit(1);
    }

    for (int i = 0; i < num_alunos; i++) {
        fprintf(arquivo, "%s, %.2f, %s\n", alunos[i].nome, alunos[i].media, alunos[i].situacao);
    }

    fclose(arquivo);
}
