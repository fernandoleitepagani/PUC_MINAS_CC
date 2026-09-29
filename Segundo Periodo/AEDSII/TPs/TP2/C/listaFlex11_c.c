#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMBUSTIVEL 3
#define TAM_COMBUSTIVEL 20
#define ARQUIVO_CSV "/tmp/veiculos.csv"

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

/* Nó da lista simplesmente encadeada. */
typedef struct No {
  Veiculo v;
  struct No* prox;
} No;

/* Lista com ponteiros para inicio e fim. */
typedef struct {
  No* inicio;
  No* fim;
  int tamanho;
} Lista;

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

/* Inicializa a lista vazia. */
void startLista(Lista* l) {
  l->inicio = NULL;
  l->fim = NULL;
  l->tamanho = 0;
}

/* Insere um veiculo no inicio da lista. */
void inserirInicio(Lista* l, Veiculo v) {
  No* novo = (No*) malloc(sizeof(No));
  novo->v = v;
  novo->prox = l->inicio;
  l->inicio = novo;
  if (l->tamanho == 0) { l->fim = novo; }
  l->tamanho++;
}

/* Insere um veiculo no fim da lista. */
void inserirFim(Lista* l, Veiculo v) {
  No* novo = (No*) malloc(sizeof(No));
  novo->v = v;
  novo->prox = NULL;
  if (l->tamanho == 0) { l->inicio = novo; } 
  else { l->fim->prox = novo; }
  l->fim = novo;
  l->tamanho++;
}

/* Insere um veiculo na posicao indicada. */
void inserirPosicao(Lista* l, Veiculo v, int pos) {
  if (pos <= 0) { inserirInicio(l, v); return; }
  if (pos >= l->tamanho) { inserirFim(l, v); return; }
  No* atual = l->inicio;
  for (int i = 0; i < pos - 1; i++) { atual = atual->prox; }
  No* novo = (No*) malloc(sizeof(No));
  novo->v = v;
  novo->prox = atual->prox;
  atual->prox = novo;
  l->tamanho++;
}

/* Remove o primeiro veiculo da lista e retorna. */
Veiculo removerInicio(Lista* l) {
  No* temp = l->inicio;
  Veiculo v = temp->v;
  l->inicio = temp->prox;
  if (l->inicio == NULL) { l->fim = NULL; }
  free(temp);
  l->tamanho--;
  return v;
}

/* Remove o ultimo veiculo da lista e retorna. */
Veiculo removerFim(Lista* l) {
  Veiculo v;
  if (l->tamanho == 1) {
    v = l->inicio->v;
    l->inicio = NULL;
    l->fim = NULL;
  } 
  else {
    No* atual = l->inicio;
    while (atual->prox != l->fim) { atual = atual->prox; }
    v = l->fim->v;
    free(l->fim);
    atual->prox = NULL;
    l->fim = atual;
  }
  l->tamanho--;
  return v;
}

/* Remove o veiculo da posicao e retorna. */
Veiculo removerPosicao(Lista* l, int pos) {
  if (pos <= 0) { return removerInicio(l); }
  if (pos >= l->tamanho - 1) { return removerFim(l); }
  No* atual = l->inicio;
  for (int i = 0; i < pos - 1; i++) { atual = atual->prox; }
  No* temp = atual->prox;
  Veiculo v = temp->v;
  atual->prox = temp->prox;
  l->tamanho--;
  return v;
}

/* Main insere os ids iniciais e processa os comandos. */
int main() {
  int n;
  Veiculo* veiculos = readCSV(ARQUIVO_CSV, &n);
  Lista lista;

  startLista(&lista);

  /* ids dos veiculos, postos ao final da lista */
  int id;
  while (scanf("%d", &id) == 1 && id != -1) {
    Veiculo* v = searchID(veiculos, n, id);
    if (v != NULL) { inserirFim(&lista, *v); }
  }

  /* comandos */
  int qtd;
  scanf("%d", &qtd);

  char comando[10];
  for (int i = 0; i < qtd; i++) {
    scanf("%s", comando);
    if (strcmp(comando, "II") == 0) {
      int vid;
      scanf("%d", &vid);
      Veiculo* v = searchID(veiculos, n, vid);
      if (v != NULL) { inserirInicio(&lista, *v); }
    } 
    else if (strcmp(comando, "I*") == 0) {
      int pos, vid;
      scanf("%d %d", &pos, &vid);
      Veiculo* v = searchID(veiculos, n, vid);
      if (v != NULL) { inserirPosicao(&lista, *v, pos); }
    } 
    else if (strcmp(comando, "IF") == 0) {
      int vid;
      scanf("%d", &vid);
      Veiculo* v = searchID(veiculos, n, vid);
      if (v != NULL) { inserirFim(&lista, *v); }
    } 
    else if (strcmp(comando, "RI") == 0) {
      if (lista.tamanho > 0) {
        Veiculo r = removerInicio(&lista);
        printf("(R)%s %s\n", r.marca, r.modelo);
      }
    } 
    else if (strcmp(comando, "R*") == 0) {
      int pos;
      scanf("%d", &pos);
      if (lista.tamanho > 0) {
        Veiculo r = removerPosicao(&lista, pos);
        printf("(R)%s %s\n", r.marca, r.modelo);
      }
    } 
    else if (strcmp(comando, "RF") == 0) {
      if (lista.tamanho > 0) {
        Veiculo r = removerFim(&lista);
        printf("(R)%s %s\n", r.marca, r.modelo);
      }
    }
  }

  /* Imprime os elementos da lista do primeiro ao ultimo */
  No* atual = lista.inicio;
  while (atual != NULL) {
    char buffer[1024];
    formatVeiculo(&atual->v, buffer);
    printf("%s\n", buffer);
    atual = atual->prox;
  }

  free(veiculos);
  return 0;
}
