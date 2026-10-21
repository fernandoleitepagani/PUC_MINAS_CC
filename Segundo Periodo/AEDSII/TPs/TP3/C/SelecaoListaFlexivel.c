#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMBUSTIVEL 3
#define TAM_COMBUSTIVEL 20

/* Estrutura que representa o veiculo do dataset. */
typedef struct {
  /* Para turbo, 0 = false, 1 = true */
  int id, ano, cilindros, numCombustivel, turbo;
  char marca[50], modelo[100], categoria[50];
  char combustivel[MAX_COMBUSTIVEL][TAM_COMBUSTIVEL];
  char transmissao[30], tracao[50], dataRegistro[11];
  double cilindrada, consumoCidade, consumoEstrada, co2;
} Veiculo;

/* Nó da lista simplesmente encadeada. */
typedef struct No {
  Veiculo v;
  struct No* prox;
} No;

/* Converte a data "AAAA-MM-DD" para o formato DD/MM/AAAA. */
void formatData(char* dataIso, char* saida) {
  int ano, mes, dia;
  sscanf(dataIso, "%d-%d-%d", &ano, &mes, &dia);
  sprintf(saida, "%02d/%02d/%04d", dia, mes, ano);
}

/* Cria um Veiculo a partir de uma linha do CSV. */
Veiculo createVeiculo(char* linha) {
  Veiculo v;
  char* campos[15];
  int i;

  campos[0] = strtok(linha, ",");
  for (i = 1; i < 15; i++) campos[i] = strtok(NULL, ",");

  sscanf(campos[0], "%d", &v.id);
  sprintf(v.marca, "%s", campos[1]);
  sprintf(v.modelo, "%s", campos[2]);
  sscanf(campos[3], "%d", &v.ano);
  sprintf(v.categoria, "%s", campos[4]);

  v.numCombustivel = 0;
  char* tipo = strtok(campos[5], ";");
  while (tipo != NULL && v.numCombustivel < MAX_COMBUSTIVEL) {
    sprintf(v.combustivel[v.numCombustivel], "%s", tipo);
    v.numCombustivel++;
    tipo = strtok(NULL, ";");
  }

  sscanf(campos[6], "%d", &v.cilindros);
  sscanf(campos[7], "%lf", &v.cilindrada);
  sprintf(v.transmissao, "%s", campos[8]);
  sprintf(v.tracao, "%s", campos[9]);
  sscanf(campos[10], "%lf", &v.consumoCidade);
  sscanf(campos[11], "%lf", &v.consumoEstrada);
  sscanf(campos[12], "%lf", &v.co2);
  v.turbo = (strcmp(campos[13], "true") == 0);
  sprintf(v.dataRegistro, "%s", campos[14]);

  return v;
}

/* Formata um Veiculo no padrao do enunciado. */
void formatVeiculo(Veiculo* v, char* buffer) {
  char data[11];
  formatData(v->dataRegistro, data);

  int pos = sprintf(buffer, "[%d ## %s ## %s ## %d ## %s ## [",
                    v->id, v->marca, v->modelo, v->ano, v->categoria);
  for (int i = 0; i < v->numCombustivel; i++) {
    if (i > 0) pos += sprintf(buffer + pos, ",");
    pos += sprintf(buffer + pos, "%s", v->combustivel[i]);
  }
  sprintf(buffer + pos,
          "] ## %d ## %.1f ## %s ## %s ## %.2f ## %.2f ## %.1f ## %s ## %s]",
          v->cilindros, v->cilindrada, v->transmissao, v->tracao,
          v->consumoCidade, v->consumoEstrada, v->co2,
          v->turbo ? "true" : "false", data);
}

/* Le o CSV e devolve o vetor de veiculos (quantidade em *n). */
Veiculo* lerCsv(char* caminho, int* n) {
  FILE* f = fopen(caminho, "r");
  if (!f) { *n = 0; return NULL; }

  char linha[1024];
  fgets(linha, sizeof(linha), f); /* cabecalho */

  int cap = 1000;
  Veiculo* veiculos = (Veiculo*) malloc(cap * sizeof(Veiculo));
  *n = 0;

  while (fgets(linha, sizeof(linha), f)) {
    if (linha[0] == '\n' || linha[0] == '\0') continue;
    if (*n == cap) {
      cap *= 2;
      veiculos = (Veiculo*) realloc(veiculos, cap * sizeof(Veiculo));
    }
    veiculos[*n] = createVeiculo(linha);
    (*n)++;
  }

  fclose(f);
  return veiculos;
}

/* Compara dois modelos ignorando diferenca entre maiusculas e minusculas.*/
int comparaTexto(const char* a, const char* b) {
  int i = 0;
  while (a[i] != '\0' && b[i] != '\0') {
    char ca = a[i], cb = b[i];
    /* Converte para minusculo se for letra maiuscula */
    if (ca >= 'A' && ca <= 'Z') ca = ca + ('a' - 'A');
    if (cb >= 'A' && cb <= 'Z') cb = cb + ('a' - 'A');
    if (ca != cb) return ca - cb;
    i++;
  }
  return (unsigned char)a[i] - (unsigned char)b[i];
}

/* Insere um veiculo no fim da lista. */
No* inserirFim(No* inicio, Veiculo v) {
  No* novo = (No*) malloc(sizeof(No));
  novo->v = v;
  novo->prox = NULL;
  if (inicio == NULL) return novo;
  No* atual = inicio;
  while (atual->prox != NULL) atual = atual->prox;
  atual->prox = novo;
  return inicio;
}

// funcao selection sort usando "modelo" como chave da pesquisa
void selecaoLista(No* inicio) {
  for (No* i = inicio; i != NULL; i = i->prox) {
    No* menor = i;
    for (No* j = i->prox; j != NULL; j = j->prox) {
      if (comparaTexto(j->v.modelo, menor->v.modelo) < 0) menor = j;
    }
    if (menor != i) {
      Veiculo temporario = i->v;
      i->v = menor->v;
      menor->v = temporario;
    }
  }
}

/* Main le o dataset de veiculos e, para cada id informado realiza pesquisa sequencial
 * e imprime cada veiculo e suas características.
 * A entrada termina quando o id -1 e lido. */
int main() {
  int n;
  Veiculo* veiculos = lerCsv("/tmp/veiculos.csv", &n);

  No* inicio = NULL;
  int id = 0;

  while (scanf("%d", &id) == 1 && id != -1) {
    int i = 0;
    while (i < n && veiculos[i].id != id) i++;
    if (i < n) inicio = inserirFim(inicio, veiculos[i]);
  }

  /* chama funcao selection sort */
  selecaoLista(inicio);

  /* imprime buffer */
  for (No* atual = inicio; atual != NULL; atual = atual->prox) {
    char buffer[1024];
    formatVeiculo(&atual->v, buffer);
    printf("%s\n", buffer);
  }

  free(veiculos);
  return 0;
}
