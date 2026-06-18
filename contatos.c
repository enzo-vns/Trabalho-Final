#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CONTATOS 100
#define TAM_NOME     50
#define TAM_EMAIL    50
#define TAM_TELEFONE 20
#define TAM_TIPO     20
#define ARQUIVO      "contatos.dat"

typedef struct {
    char nome[TAM_NOME];
    char email[TAM_EMAIL];
    char telefone[TAM_TELEFONE];
    char tipo[TAM_TIPO];
} Contato;

void lerString(char *destino, int tam, const char *rotulo) {
    int ch;
    size_t len;

    printf("%s", rotulo);
    if (fgets(destino, tam, stdin) == NULL) {
        destino[0] = '\0';
        return;
    }
    len = strlen(destino);
    if (len > 0 && destino[len - 1] == '\n') {
        destino[len - 1] = '\0';
    } else {

        while ((ch = getchar()) != '\n' && ch != EOF);
    }
}

void paraMinusculo(const char *origem, char *destino, int tam) {
    int i;
    for (i = 0; origem[i] != '\0' && i < tam - 1; i++) {
        destino[i] = (char) tolower((unsigned char) origem[i]);
    }
    destino[i] = '\0';
}

int apenasDigitos(const char *s) {
    int i;
    if (s[0] == '\0') return 0;
    for (i = 0; s[i] != '\0'; i++) {
        if (!isdigit((unsigned char) s[i])) return 0;
    }
    return 1;
}

int lerTelefone(char *destino, int tam, int permiteVazio) {
    char ddd[8], num[16];
    size_t ln;

    while (1) {
        lerString(ddd, sizeof(ddd), "DDD (2 digitos): ");
        if (permiteVazio && ddd[0] == '\0') {
            return 0;
        }
        lerString(num, sizeof(num), "Numero (9 digitos): ");
        ln = strlen(num);

        if (apenasDigitos(ddd) && strlen(ddd) == 2 &&
            apenasDigitos(num) && ln == 9) {

            snprintf(destino, tam, "(%s) %.5s-%s", ddd, num, num + 5);
            return 1;
        }
        printf("Telefone invalido. Informe DDD com 2 digitos e numero com 9 digitos.\n");
    }
}

void exibirContato(const Contato *c, int indice) {
    printf("\n[%d]\n", indice + 1);
    printf("  Nome.....: %s\n", c->nome);
    printf("  E-mail...: %s\n", c->email);
    printf("  Telefone.: %s\n", c->telefone);
    printf("  Tipo.....: %s\n", c->tipo);
}

int carregarContatos(Contato contatos[], int *total) {
    FILE *fp = fopen(ARQUIVO, "rb");
    if (fp == NULL) {
        *total = 0;
        return 0;
    }
    *total = (int) fread(contatos, sizeof(Contato), MAX_CONTATOS, fp);
    fclose(fp);
    return *total;
}

void salvarContatos(Contato contatos[], int total) {
    FILE *fp = fopen(ARQUIVO, "wb");
    if (fp == NULL) {
        printf("\nErro ao abrir o arquivo para gravacao!\n");
        return;
    }
    fwrite(contatos, sizeof(Contato), total, fp);
    fclose(fp);
}

int buscarIndicePorNome(Contato contatos[], int total, const char *nome) {
    char alvo[TAM_NOME], atual[TAM_NOME];
    int i;

    paraMinusculo(nome, alvo, TAM_NOME);
    if (alvo[0] == '\0') {
        return -1;
    }
    for (i = 0; i < total; i++) {
        paraMinusculo(contatos[i].nome, atual, TAM_NOME);
        if (strstr(atual, alvo) != NULL) {
            return i;
        }
    }
    return -1;
}

void cadastrarContato(Contato contatos[], int *total) {
    Contato novo;

    if (*total >= MAX_CONTATOS) {
        printf("\nLimite de %d contatos atingido. Nao e possivel cadastrar.\n",
               MAX_CONTATOS);
        return;
    }
    printf("\n--- Cadastrar Contato ---\n");
    lerString(novo.nome, TAM_NOME, "Nome.....: ");
    lerString(novo.email, TAM_EMAIL, "E-mail...: ");
    printf("Telefone:\n");
    lerTelefone(novo.telefone, TAM_TELEFONE, 0);
    lerString(novo.tipo, TAM_TIPO,
              "Tipo (Pessoal/Trabalho/Familia/Cliente/Outro): ");

    contatos[*total] = novo;
    (*total)++;
    printf("\nContato cadastrado com sucesso!\n");
}

void alterarContato(Contato contatos[], int total) {
    char termo[TAM_NOME];
    char bNome[TAM_NOME], bEmail[TAM_EMAIL];
    char bTel[TAM_TELEFONE], bTipo[TAM_TIPO];
    int idx;

    if (total == 0) {
        printf("\nNenhum contato cadastrado.\n");
        return;
    }
    printf("\n--- Alterar Contato ---\n");
    lerString(termo, TAM_NOME, "Nome do contato a alterar: ");

    idx = buscarIndicePorNome(contatos, total, termo);
    if (idx == -1) {
        printf("Contato \"%s\" nao encontrado.\n", termo);
        return;
    }

    printf("\nContato encontrado:");
    exibirContato(&contatos[idx], idx);
    printf("\nDigite os novos dados (Enter para manter o atual):\n");

    lerString(bNome, TAM_NOME, "Novo nome.....: ");
    if (strlen(bNome) > 0) strcpy(contatos[idx].nome, bNome);

    lerString(bEmail, TAM_EMAIL, "Novo e-mail...: ");
    if (strlen(bEmail) > 0) strcpy(contatos[idx].email, bEmail);

    printf("Novo telefone (DDD em branco para manter):\n");
    if (lerTelefone(bTel, TAM_TELEFONE, 1)) {
        strcpy(contatos[idx].telefone, bTel);
    }

    lerString(bTipo, TAM_TIPO, "Novo tipo.....: ");
    if (strlen(bTipo) > 0) strcpy(contatos[idx].tipo, bTipo);

    printf("\nContato alterado com sucesso!\n");
}

void apagarContato(Contato contatos[], int *total) {
    char termo[TAM_NOME];
    int idx, i;

    if (*total == 0) {
        printf("\nNenhum contato cadastrado.\n");
        return;
    }
    printf("\n--- Apagar Contato ---\n");
    lerString(termo, TAM_NOME, "Nome do contato a apagar: ");

    idx = buscarIndicePorNome(contatos, *total, termo);
    if (idx == -1) {
        printf("Contato \"%s\" nao encontrado.\n", termo);
        return;
    }

    printf("\nRemovendo:");
    exibirContato(&contatos[idx], idx);

    for (i = idx; i < *total - 1; i++) {
        contatos[i] = contatos[i + 1];
    }
    (*total)--;
    printf("\nContato removido com sucesso!\n");
}

void procurarContato(Contato contatos[], int total) {
    char termo[TAM_NOME], termoLower[TAM_NOME], nomeLower[TAM_NOME];
    int i, encontrados = 0;

    if (total == 0) {
        printf("\nNenhum contato cadastrado.\n");
        return;
    }
    printf("\n--- Procurar Contato ---\n");
    lerString(termo, TAM_NOME, "Digite o nome a procurar: ");
    paraMinusculo(termo, termoLower, TAM_NOME);

    if (termoLower[0] == '\0') {
        printf("Termo de busca vazio.\n");
        return;
    }
    for (i = 0; i < total; i++) {
        paraMinusculo(contatos[i].nome, nomeLower, TAM_NOME);
        if (strstr(nomeLower, termoLower) != NULL) {
            exibirContato(&contatos[i], i);
            encontrados++;
        }
    }
    if (encontrados == 0) {
        printf("Nenhum contato encontrado com \"%s\".\n", termo);
    }
}

void listarContatos(Contato contatos[], int total) {
    int i;

    if (total == 0) {
        printf("\nNenhum contato cadastrado.\n");
        return;
    }
    printf("\n--- Lista de Contatos (%d/%d) ---\n", total, MAX_CONTATOS);
    for (i = 0; i < total; i++) {
        exibirContato(&contatos[i], i);
    }
}

int exibirMenu(void) {
    char linha[10];

    printf("\n========================================\n");
    printf("   GERENCIADOR DE CONTATOS\n");
    printf("========================================\n");
    printf("  1 - Cadastrar contato\n");
    printf("  2 - Alterar contato\n");
    printf("  3 - Apagar contato\n");
    printf("  4 - Procurar contato\n");
    printf("  5 - Listar contatos\n");
    printf("  6 - Sair\n");
    printf("----------------------------------------\n");
    printf("Escolha uma opcao: ");

    if (fgets(linha, sizeof(linha), stdin) == NULL) {
        return 6;
    }
    return atoi(linha);
}

int main(void) {
    Contato contatos[MAX_CONTATOS];
    int total = 0;
    int opcao;

    carregarContatos(contatos, &total);
    printf("Sistema iniciado. %d contato(s) carregado(s).\n", total);

    do {
        opcao = exibirMenu();

        switch (opcao) {
            case 1:
                cadastrarContato(contatos, &total);
                salvarContatos(contatos, total);
                break;
            case 2:
                alterarContato(contatos, total);
                salvarContatos(contatos, total);
                break;
            case 3:
                apagarContato(contatos, &total);
                salvarContatos(contatos, total);
                break;
            case 4:
                procurarContato(contatos, total);
                break;
            case 5:
                listarContatos(contatos, total);
                break;
            case 6:
                salvarContatos(contatos, total);
                printf("\nDados salvos. Encerrando o programa...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 6);

    return 0;
}
