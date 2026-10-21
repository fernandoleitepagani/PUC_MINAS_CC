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

/* Compara consumo estrada e, no empate, marca. */
int comparaVeiculo(Veiculo a, Veiculo b) {
  if (a.consumoEstrada < b.consumoEstrada) return -1;
  if (a.consumoEstrada > b.consumoEstrada) return 1;
  return strcmp(a.marca, b.marca);
}

/* Troca dois veiculos de posicao no vetor. */
void trocar(Veiculo* a, Veiculo* b) {
  Veiculo temporario = *a;
  *a = *b;
  *b = temporario;
}

/* Devolve o indice da mediana entre tres posicoes. */
int medianaDeTres(Veiculo* v, int a, int b, int c) {
  if (comparaVeiculo(v[a], v[b]) <= 0) {
    if (comparaVeiculo(v[b], v[c]) <= 0) return b;
    if (comparaVeiculo(v[a], v[c]) <= 0) return c;
    return a;
  } else {
    if (comparaVeiculo(v[a], v[c]) <= 0) return a;
    if (comparaVeiculo(v[b], v[c]) <= 0) return c;
    return b;
  }
}

/* Particiona o trecho com pivô mediano e devolve os limites das metades. */
int particionar(Veiculo* v, int esq, int dir, int* fimEsq) {
  int meio = (esq + dir) / 2;
  int m = medianaDeTres(v, esq, meio, dir);
  trocar(&v[m], &v[meio]);
  Veiculo pivo = v[meio];
  int i = esq;
  int j = dir;
  while (i <= j) {
    while (comparaVeiculo(v[i], pivo) < 0) i++;
    while (comparaVeiculo(v[j], pivo) > 0) j--;
    if (i <= j) {
      trocar(&v[i], &v[j]);
      i++;
      j--;
    }
  }
  *fimEsq = j;
  return i;
}

/* Ordena o vetor recursivamente com Quicksort e mediana de tres. */
void quicksort(Veiculo* v, int esq, int dir) {
  if (esq < dir) {
    int fimEsq;
    int inicioDir = particionar(v, esq, dir, &fimEsq);
    quicksort(v, esq, fimEsq);
    quicksort(v, inicioDir, dir);
  }
}

/* Main le o dataset de veiculos e, para cada id informado realiza pesquisa sequencial
 * e imprime cada veiculo e suas características.
 * A entrada termina quando o id -1 e lido. */
int main() {
  int n;
  Veiculo* veiculos = lerCsv("/tmp/veiculos.csv", &n);

  /* array para os veiculos selecionados */
  Veiculo selecionados[1000];
  int m = 0;
  int id = 0;

  while (scanf("%d", &id) == 1 && id != -1) {
    int i = 0;
    while (i < n && veiculos[i].id != id) i++;
    if (i < n) selecionados[m++] = veiculos[i];
  }

  quicksort(selecionados, 0, m - 1);

  /* imprime buffer */
  for (int i = 0; i < m; i++) {
    char buffer[1024];
    formatVeiculo(&selecionados[i], buffer);
    printf("%s\n", buffer);
  }

  free(veiculos);
  return 0;
}
