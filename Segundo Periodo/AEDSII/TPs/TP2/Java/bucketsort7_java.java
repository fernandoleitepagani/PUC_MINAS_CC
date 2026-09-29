import java.io.File;
import java.util.Scanner;

/* Data no formato ano-mes-dia. */
class Data {
  private int ano, mes, dia;

  public Data(int ano, int mes, int dia) { this.ano = ano; this.mes = mes; this.dia = dia; }

  public int getAno() { return ano; }
  public int getMes() { return mes; }
  public int getDia() { return dia; }

  /* Converte "AAAA-MM-DD" para Data. */
  public static Data convertData(String s) {
    String[] p = s.split("-");
    return new Data(Integer.parseInt(p[0]), Integer.parseInt(p[1]), Integer.parseInt(p[2]));
  }

  public String format() { return String.format("%02d/%02d/%04d", dia, mes, ano); }
}

/* Veiculo do dataset. */
class Veiculo {
  private int id, ano, cilindros;
  private double cilindrada, consumoCidade, consumoEstrada, co2;
  private String marca, modelo, categoria, transmissao, tracao;
  private String[] combustivel;
  private boolean turbo;
  private Data dataRegistro;

  public Veiculo(int id, String marca, String modelo, int ano, String categoria,
                 String[] combustivel, int cilindros, double cilindrada,
                 String transmissao, String tracao,
                 double consumoCidade, double consumoEstrada, double co2,
                 boolean turbo, Data dataRegistro) {
    this.id = id;
    this.marca = marca;
    this.modelo = modelo;
    this.ano = ano;
    this.categoria = categoria;
    this.combustivel = combustivel;
    this.cilindros = cilindros;
    this.cilindrada = cilindrada;
    this.transmissao = transmissao;
    this.tracao = tracao;
    this.consumoCidade = consumoCidade;
    this.consumoEstrada = consumoEstrada;
    this.co2 = co2;
    this.turbo = turbo;
    this.dataRegistro = dataRegistro;
  }

  /* getters */
  public int getId() { return id; }
  public String getMarca() { return marca; }
  public String getModelo() { return modelo; }
  public int getAno() { return ano; }
  public String getCategoria() { return categoria; }
  public String[] getCombustivel() { return combustivel; }
  public int getCilindros() { return cilindros; }
  public double getCilindrada() { return cilindrada; }
  public String getTransmissao() { return transmissao; }
  public String getTracao() { return tracao; }
  public double getConsumoCidade() { return consumoCidade; }
  public double getConsumoEstrada() { return consumoEstrada; }
  public double getCo2() { return co2; }
  public boolean isTurbo() { return turbo; }
  public Data getDataRegistro() { return dataRegistro; }

  /* Cria um Veiculo a partir de uma linha do CSV. */
  public static Veiculo createVeiculo(String s) {
    String[] c = s.split(",");
    return new Veiculo(
      Integer.parseInt(c[0]), c[1], c[2],
      Integer.parseInt(c[3]), c[4], c[5].split(";"),
      Integer.parseInt(c[6]), Double.parseDouble(c[7]),
      c[8], c[9],
      Double.parseDouble(c[10]), Double.parseDouble(c[11]), Double.parseDouble(c[12]),
      Boolean.parseBoolean(c[13]), Data.convertData(c[14]));
  }

  /* Retorna o veiculo no formato do enunciado. */
  public String formatVeiculo() {
    String comb = "";
    for (int i = 0; i < combustivel.length; i++) {
      if (i > 0) comb += ",";
      comb += combustivel[i];
    }

    String turboStr;
    if (turbo) turboStr = "true";
    else turboStr = "false";

    return String.format(
      "[%d ## %s ## %s ## %d ## %s ## [%s] ## %d ## %.1f ## %s ## %s ## %.2f ## %.2f ## %.1f ## %s ## %s]",
      id, marca, modelo, ano, categoria, comb,
      cilindros, cilindrada, transmissao, tracao,
      consumoCidade, consumoEstrada, co2,
      turboStr, dataRegistro.format());
  }
}

/* Le o CSV e devolve o vetor de veiculos. */
class reader {
  public static Veiculo[] readCSV(String caminho) throws Exception {
    Veiculo[] v = new Veiculo[1000];
    int n = 0;
    Scanner sc = new Scanner(new File(caminho));
    sc.nextLine(); /* cabecalho */
    while (sc.hasNextLine()) {
      String linha = sc.nextLine();
      if (linha.length() > 0) {
        if (n == v.length) {
          Veiculo[] maior = new Veiculo[v.length * 2];
          for (int i = 0; i < n; i++) maior[i] = v[i];
          v = maior;
        }
        v[n++] = Veiculo.createVeiculo(linha);
      }
    }
    sc.close();

    Veiculo[] resp = new Veiculo[n];
    for (int i = 0; i < n; i++) resp[i] = v[i];
    return resp;
  }
}

class BucketSort {

  /* Ordena por cilindrada normalizada. Usa 10 buckets e Insertion Sort dentro de cada bucket. */
  public static void bucketsort(Veiculo[] v, int n) {

    /* 10 buckets, cada um com capacidade maxima n */
    Veiculo[][] buckets = new Veiculo[10][n];
    int[] tam = new int[10];

    /* Distribui cada veiculo no bucket correspondente */
    for (int i = 0; i < n; i++) {
      double norm = v[i].getCilindrada() / 8.1;
      int idx = (int)(norm * 10);
      if (idx >= 10) idx = 9; /* seguranca para cilindrada == 8.1 */
      if (idx < 0) idx = 0;
      buckets[idx][tam[idx]] = v[i];
      tam[idx]++;
    }

    /* Ordena cada bucket com Insertion Sort */
    for (int b = 0; b < 10; b++) { insertion(buckets[b], tam[b]); }

    /* buckets de volta no vetor original */
    int k = 0;
    for (int b = 0; b < 10; b++) {
      for (int i = 0; i < tam[b]; i++) { v[k] = buckets[b][i]; k++; }
    }
  }

  /* Insertion Sort por cilindrada. */
  private static void insertion(Veiculo[] v, int n) {
    for (int i = 1; i < n; i++) {
      Veiculo temp = v[i];
      int j = i - 1;
      while (j >= 0 && v[j].getCilindrada() > temp.getCilindrada()) {
        v[j + 1] = v[j];
        j--;
      }
      v[j + 1] = temp;
    }
  }
}

/* Main le o csv para cada id na entrada. A entrada termina quando o id -1 é lido. */
public class bucketsort7_java {
  public static void main(String[] args) throws Exception {
    Veiculo[] veiculos = reader.readCSV("/tmp/veiculos.csv");
    Scanner sc = new Scanner(System.in);

    Veiculo[] selecionados = new Veiculo[1000];
    int m = 0;
    int id = 0;

    while (sc.hasNextInt()) {
      id = sc.nextInt();
      if (id == -1) break;

      int i = 0;
      while (i < veiculos.length && veiculos[i].getId() != id) { i++; }
      selecionados[m++] = veiculos[i];
    }
    /* chama funcao do bucketsort */
    BucketSort.bucketsort(selecionados, m);

    for (int i = 0; i < m; i++) { System.out.println(selecionados[i].formatVeiculo()); }
    sc.close();
  }
}
