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

/* Counting Sort usando número de cilindros.*/
void countingSort(Veiculo* v, int n) {

  /* Acha o maior numero de cilindros */
  int maxCilindros = 0, i;
  for (i = 0; i < n; i++) {
    if (v[i].cilindros > maxCilindros) { maxCilindros = v[i].cilindros; }
  }

   /* Tamanho = maxCilindros + 1 (pq tem que incluir o 0). */
  int* count = (int*) malloc((maxCilindros + 1) * sizeof(int));
  for (i = 0; i <= maxCilindros; i++) { count[i] = 0; }

  for (i = 0; i < n; i++) { count[v[i].cilindros]++; }

  /* Soma acumulada */
  for (i = 1; i <= maxCilindros; i++) { count[i] += count[i - 1]; }

  /* Construi o vetor de saida */
  Veiculo* output = (Veiculo*) malloc(n * sizeof(Veiculo));
  for (i = n - 1; i >= 0; i--) {
    int c = v[i].cilindros;
    output[count[c] - 1] = v[i];
    count[c]--;
  }
  for (i = 0; i < n; i++) { v[i] = output[i]; }

  free(count);
  free(output);
}

/* Main le o dataset de veiculos e, para cada id informado realiza pesquisa sequencial
 * e imprime cada veiculo e suas características.
 * A entrada termina quando o id -1 e lido. */
int main(){
  int n;
  Veiculo* veiculos = readCSV("/tmp/veiculos.csv", &n);

  Veiculo selecionados[1000];
  int m = 0;
  int id;

  while (scanf("%d", &id) == 1 && id != -1) {
    int i = 0;
    while (i < n && veiculos[i].id != id && id!=-1) { i++; }
    selecionados[m++] = veiculos[i];
  }

  /* chama funcao do countingSort */
  countingSort(selecionados, m);

  for (int i = 0; i < m; i++) {
    char buffer[1024];
    formatVeiculo(&selecionados[i], buffer);
    printf("%s\n", buffer);
  }

  free(veiculos);
  return 0;
}
