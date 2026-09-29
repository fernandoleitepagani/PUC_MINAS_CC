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

/*Ordena por um digito do ano*/
void countingSortDigito(Veiculo* v, int n, int exp) {
  Veiculo* output = (Veiculo*) malloc(n * sizeof(Veiculo));
  int count[10] = {0};
  int i;

  /* Conta ocorrencias do digito atual */
  for (i = 0; i < n; i++) {
    int digito = (v[i].ano / exp) % 10;
    count[digito]++;
  }

  /* Soma acumulada*/
  for (i = 1; i < 10; i++) { count[i] += count[i - 1]; }

  /* faz o output*/ 
  for (i = n - 1; i >= 0; i--) {
    int digito = (v[i].ano / exp) % 10;
    output[count[digito] - 1] = v[i];
    count[digito]--;
  }

  /* Copia de volta para o vetor original */
  for (i = 0; i < n; i++) { v[i] = output[i]; }

  free(output);
}

/* Radixsort por ano */
void radixSort(Veiculo* v, int n) {

  /* Acha o maior ano para saber quantos digitos processar */
  int maxAno = v[0].ano;
  int i;
  for (i = 1; i < n; i++) { if (v[i].ano > maxAno) { maxAno = v[i].ano; } }
  int exp;
  for (exp = 1; maxAno / exp > 0; exp *= 10) { countingSortDigito(v, n, exp); }
}

/* Main le o dataset de veiculos e, para cada id informado realiza pesquisa sequencial
 * e imprime cada veiculo e suas características.
 * A entrada termina quando o id -1 e lido. */
int main() {
  int n, m = 0, id;
  Veiculo* veiculos = readCSV(ARQUIVO_CSV, &n);
  Veiculo selecionados[1000];

  while (scanf("%d", &id) == 1 && id != -1) {
    int i = 0;
    while (i < n && veiculos[i].id != id) { i++; }
    if (i < n) { selecionados[m++] = veiculos[i]; }
  }

  /* radixSort */
  radixSort(selecionados, m);

  for (int i = 0; i < m; i++) {
    char buffer[1024];
    formatVeiculo(&selecionados[i], buffer);
    printf("%s\n", buffer);
  }

  free(veiculos);
  return 0;
}
