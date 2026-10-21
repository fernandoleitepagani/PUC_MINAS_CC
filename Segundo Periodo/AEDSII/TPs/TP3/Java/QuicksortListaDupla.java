import java.io.File;
import java.util.Scanner;

/* Veiculo do dataset. */
class Veiculo {
  private int id, ano, cilindros;
  private double cilindrada, consumoCidade, consumoEstrada, co2;
  private String marca, modelo, categoria, transmissao, tracao, dataRegistro;
  private String[] combustivel;
  private boolean turbo;

  /* Construtor: recebe todos os atributos do veiculo, inclusive a data em ISO. */
  public Veiculo(int id, String marca, String modelo, int ano, String categoria,
                 String[] combustivel, int cilindros, double cilindrada,
                 String transmissao, String tracao,
                 double consumoCidade, double consumoEstrada, double co2,
                 boolean turbo, String dataRegistro) {
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
  public String getDataRegistro() { return dataRegistro; }

  /* Converte a data "AAAA-MM-DD" para o formato DD/MM/AAAA. */
  public static String formatData(String iso) {
    String[] p = iso.split("-");
    return p[2] + "/" + p[1] + "/" + p[0];
  }

  /* Cria um Veiculo a partir de uma linha do CSV. */
  public static Veiculo createVeiculo(String linha) {
    String[] c = linha.split(",");
    return new Veiculo(
      Integer.parseInt(c[0]), c[1], c[2],
      Integer.parseInt(c[3]), c[4], c[5].split(";"),
      Integer.parseInt(c[6]), Double.parseDouble(c[7]),
      c[8], c[9],
      Double.parseDouble(c[10]), Double.parseDouble(c[11]), Double.parseDouble(c[12]),
      Boolean.parseBoolean(c[13]), c[14]);
  }

  /* Retorna o veiculo no formato do enunciado. */
  public String formatVeiculo() {
    String comb = "";
    for (int i = 0; i < combustivel.length; i++) {
      if (i > 0) comb += ",";
      comb += combustivel[i];
    }
    String turboStr = turbo ? "true" : "false";
    return String.format(
      "[%d ## %s ## %s ## %d ## %s ## [%s] ## %d ## %.1f ## %s ## %s ## %.2f ## %.2f ## %.1f ## %s ## %s]",
      id, marca, modelo, ano, categoria, comb,
      cilindros, cilindrada, transmissao, tracao,
      consumoCidade, consumoEstrada, co2, turboStr, formatData(dataRegistro));
  }
}

/* Le o CSV e devolve o vetor de veiculos. */
class LeitorCsv {
  /* Le o arquivo CSV e devolve o vetor de veiculos ja preenchido. */
  public static Veiculo[] ler(String caminho) throws Exception {
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

/* No da lista duplamente encadeada.
 * prox aponta para o proximo no; ant aponta para o anterior. */
class No {
  Veiculo v;
  No ant, prox;
  /* Construtor: cria um no isolado com o veiculo informado. */
  No(Veiculo v) { this.v = v; this.ant = null; this.prox = null; }
}

/* Lista duplamente encadeada de veiculos, com ponteiros para
 * o inicio e para o fim. Insercao  e remocao nas duas pontas. */
class ListaDupla {
  private No inicio, fim;

  /* Construtor: cria a lista vazia. */
  public ListaDupla() { inicio = null; fim = null; }

  /* Insere veiculo na ultima posicao.
   * O novo no vira o fim, e seu ant aponta para o antigo fim. */
  public void inserirFim(Veiculo v) {
    No novo = new No(v);
    novo.ant = fim;              /* novo aponta para o antigo fim */
    if (fim != null) fim.prox = novo;
    else inicio = novo;
    fim = novo;
  }

  /* Retorna o primeiro no da lista. */
  public No getInicio() { return inicio; }
}

/* Classe que implementa o Quicksort sobre a lista duplamente encadeada. */
class QuicksortLista {

  /* Compara duas strings ignorando diferenca entre maiusculas e minusculas. */
  public static int compararTexto(String a, String b) {
    int n = a.length() < b.length() ? a.length() : b.length();
    for (int i = 0; i < n; i++) {
      char ca = a.charAt(i);
      char cb = b.charAt(i);
      if (ca >= 'A' && ca <= 'Z') ca = (char)(ca + ('a' - 'A'));
      if (cb >= 'A' && cb <= 'Z') cb = (char)(cb + ('a' - 'A'));
      if (ca != cb) return ca - cb;
    }
    return a.length() - b.length();
  }

  /* Compara dois veiculos: consumo estrada e, no empate, marca. */
  public static int comparar(Veiculo a, Veiculo b) {
    if (a.getConsumoEstrada() < b.getConsumoEstrada()) return -1;
    if (a.getConsumoEstrada() > b.getConsumoEstrada()) return 1;
    return compararTexto(a.getMarca(), b.getMarca());
  }

  /* Ordena o trecho da lista com Quicksort e dois indices. */
  public static void quicksort(No esq, No dir, int tamanho) {
    if (tamanho < 2) return;

    No meio = esq;
    for (int k = 0; k < (tamanho - 1) / 2; k++) meio = meio.prox;
    Veiculo pivo = meio.v;
    No iNo = esq, jNo = dir;
    int i = 0, j = tamanho - 1;

    while (i <= j) {
      while (comparar(iNo.v, pivo) < 0) { iNo = iNo.prox; i++; }
      while (comparar(jNo.v, pivo) > 0) { jNo = jNo.ant; j--; }
      if (i <= j) {
        Veiculo temp = iNo.v;
        iNo.v = jNo.v;
        jNo.v = temp;
        iNo = iNo.prox;
        jNo = jNo.ant;
        i++;
        j--;
      }
    }

    int tamEsq = j + 1;
    int tamDir = tamanho - i;
    if (tamEsq > 1) quicksort(esq, jNo, tamEsq);
    if (tamDir > 1) quicksort(iNo, dir, tamDir);
  }
}

/* Classe principal: le os ids, ordena e imprime os veiculos. */
public class QuicksortListaDupla {

  /* Pesquisa sequencial por id; retorna null se nao encontrar. */
  public static Veiculo buscar(Veiculo[] v, int id) {
    for (int i = 0; i < v.length; i++) {
      if (v[i].getId() == id) return v[i];
    }
    return null;
  }

  /* Le os ids, insere na lista, ordena e imprime a saida. */
  public static void main(String[] args) throws Exception {
    Veiculo[] veiculos = LeitorCsv.ler("/tmp/veiculos.csv");
    Scanner sc = new Scanner(System.in);

    ListaDupla lista = new ListaDupla();
    int id = 0;
    /* ids dos veiculos, inseridos no final da lista */
    while (sc.hasNextInt() && id != -1) {
      id = sc.nextInt();
      if (id != -1) {
        Veiculo v = buscar(veiculos, id);
        if (v != null) lista.inserirFim(v);
      }
    }

    No inicio = lista.getInicio();
    No fim = inicio;
    int tamanho = 0;
    while (fim != null) { tamanho++; if (fim.prox == null) break; fim = fim.prox; }
    QuicksortLista.quicksort(inicio, fim, tamanho);

    /* Imprime os veiculos do primeiro ao ultimo */
    for (No atual = inicio; atual != null; atual = atual.prox) {
      System.out.println(atual.v.formatVeiculo());
    }
    sc.close();
  }
}
