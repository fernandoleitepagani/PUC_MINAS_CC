#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMBUSTIVEL 3
#define TAM_COMBUSTIVEL 20
#define ARQUIVO_CSV "/tmp/veiculos.csv"
#define TAM_FILA 5

typedef struct { int ano, mes, dia; } Data;

typedef struct {
  /* Para turbo, 0 = false, 1 = true */
  int id, ano, cilindros, numCombustivel, turbo;
  char marca[50], modelo[100], categoria[50];
  char combustivel[MAX_COMBUSTIVEL][TAM_COMBUSTIVEL];
  char transmissao[30], tracao[50];
  double cilindrada, consumoCidade, consumoEstrada, co2;
  Data dataRegistro;
} Veiculo;

/* Fila circular de veiculos com capacidade fixa. */
typedef struct {
  Veiculo elementos[TAM_FILA];
  int inicio, fim, tamanho;
} Fila;

/* Converte "AAAA-MM-DD" para Data. */
Data convertData(char* s) {
  Data d;
  sscanf(s, "%d-%d-%d", &d.ano, &d.mes, &d.dia);
  return d;
}

/* Cria um Veiculo a partir de uma linha do CSV. */
Veiculo* createVeiculo(char* s) {
  Veiculo* v = (Veiculo*) malloc(sizeof(Veiculo));
  char* campos[15];
  int i;

  campos[0] = strtok(s, ",");
  for (i = 1; i < 15; i++) campos[i] = strtok(NULL, ",");

  sscanf(campos[0], "%d", &v->id);
  sprintf(v->marca, "%s", campos[1]);
  sprintf(v->modelo, "%s", campos[2]);
  sscanf(campos[3], "%d", &v->ano);
  sprintf(v->categoria, "%s", campos[4]);

  v->numCombustivel = 0;
  char* tipo = strtok(campos[5], ";");
  while (tipo != NULL && v->numCombustivel < MAX_COMBUSTIVEL) {
    sprintf(v->combustivel[v->numCombustivel], "%s", tipo);
    v->numCombustivel++;
    tipo = strtok(NULL, ";");
  }

  sscanf(campos[6], "%d", &v->cilindros);
  sscanf(campos[7], "%lf", &v->cilindrada);
  sprintf(v->transmissao, "%s", campos[8]);
  sprintf(v->tracao, "%s", campos[9]);
  sscanf(campos[10], "%lf", &v->consumoCidade);
  sscanf(campos[11], "%lf", &v->consumoEstrada);
  sscanf(campos[12], "%lf", &v->co2);
  v->turbo = (strcmp(campos[13], "true") == 0);
  v->dataRegistro = convertData(campos[14]);

  return v;
}

/* Formata um Veiculo no padrao do enunciado. */
void formatVeiculo(Veiculo* v, char* buffer) {
  char data[11];
  sprintf(data, "%02d/%02d/%04d",
          v->dataRegistro.dia, v->dataRegistro.mes, v->dataRegistro.ano);

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
Veiculo* readCSV(char* caminho, int* n) {
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
    Veiculo* v = createVeiculo(linha);
    veiculos[*n] = *v;
    free(v);
    (*n)++;
  }

  fclose(f);
  return veiculos;
}

/* Busca veiculo por id. Retorna ponteiro ou NULL. */
Veiculo* searchID(Veiculo* veiculos, int n, int id) {
  int i = 0;
  while (i < n && veiculos[i].id != id) { i++; }
  if (i < n) { return &veiculos[i]; }
  return NULL;
}

/* Inicializa a fila circular vazia. */
void startFila(Fila* f) {
  f->inicio = 0;
  f->fim = 0;
  f->tamanho = 0;
}

/* Verifica se a fila esta vazia. */
int filaVazia(Fila* f) { return f->tamanho == 0; }

/* Verifica se a fila esta cheia. */
int filaCheia(Fila* f) { return f->tamanho == TAM_FILA; }

/* Remove o primeiro elemento da fila e retorna. */
Veiculo desenfileirar(Fila* f) {
  Veiculo v = f->elementos[f->inicio];
  f->inicio = (f->inicio + 1) % TAM_FILA;
  f->tamanho--;
  return v;
}

/* Enfileira um registro. Se a fila estiver cheia, remove o primeiro antes. */
void enfileirar(Fila* f, Veiculo v) {
  if (filaCheia(f)) {
    Veiculo r = desenfileirar(f);
    printf("(R)%s %s\n", r.marca, r.modelo);
  }
  f->elementos[f->fim] = v;
  f->fim = (f->fim + 1) % TAM_FILA; /* avanca o inicio de forma circular */
  f->tamanho++;
}

/* Main enfileira os ids iniciais e processa os comandos Inserir e Remover. */
int main() {
  int n;
  Veiculo* veiculos = readCSV(ARQUIVO_CSV, &n);

  Fila fila;
  startFila(&fila);

  /* ids dos veiculos, enfileirados um a um */
  int id;
  while (scanf("%d", &id) == 1 && id != -1) {
    Veiculo* v = searchID(veiculos, n, id);
    if (v != NULL) { enfileirar(&fila, *v); }
  }

  /* comandos I (inserir) e R (remover) */
  int qtd;
  scanf("%d", &qtd);

  char comando[10];
  for (int i = 0; i < qtd; i++) {
    scanf("%s", comando);
    if (strcmp(comando, "I") == 0) {
      int vid;
      scanf("%d", &vid);
      Veiculo* v = searchID(veiculos, n, vid);
      if (v != NULL) { enfileirar(&fila, *v); }
    } 
    else if (strcmp(comando, "R") == 0) {
      if (!filaVazia(&fila)) {
        Veiculo r = desenfileirar(&fila);
        printf("(R)%s %s\n", r.marca, r.modelo);
      }
    }
  }

  /* Imprime os registros da fila do primeiro ao ultimo */
  int i = fila.inicio;
  for (int k = 0; k < fila.tamanho; k++) {
    char buffer[1024];
    formatVeiculo(&fila.elementos[i], buffer);
    printf("%s\n", buffer);
    i = (i + 1) % TAM_FILA; /* Avanca o indice de forma circular. */
  }

  free(veiculos);
  return 0;
}
