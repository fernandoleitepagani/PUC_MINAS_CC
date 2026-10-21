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

/* Classe que implementa o algoritmo Heapsort. */
class Heapsort {

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

  /* Retorna true se o veiculo a for maior que b (co2 e, no empate, transmissao). */
  public static boolean maior(Veiculo a, Veiculo b) {
    if (a.getCo2() > b.getCo2()) return true;
    if (a.getCo2() < b.getCo2()) return false;
    return compararTexto(a.getTransmissao(), b.getTransmissao()) > 0;
  }

  /* Troca dois veiculos de posicao no vetor. */
  private static void trocar(Veiculo[] v, int i, int j) {
    Veiculo temp = v[i];
    v[i] = v[j];
    v[j] = temp;
  }

  /* Ordena o vetor em ordem crescente usando um heap maximo. */
  public static void heapsort(Veiculo[] v, int n) {
    for (int i = 1; i < n; i++) {
      subir(v, i);
    }
    for (int i = n - 1; i > 0; i--) {
      trocar(v, 0, i);
      descer(v, i, 0);
    }
  }

  /* Sobe um elemento ate restaurar a propriedade do heap maximo. */
  private static void subir(Veiculo[] v, int i) {
    while (i > 0) {
      int pai = (i - 1) / 2;
      if (!maior(v[i], v[pai])) break;
      trocar(v, i, pai);
      i = pai;
    }
  }

  /* Restaura a propriedade de heap no no i, considerando n elementos. */
  private static void descer(Veiculo[] v, int n, int i) {
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;
    if (esq < n && maior(v[esq], v[maior])) maior = esq;
    if (dir < n && maior(v[dir], v[maior])) maior = dir;
    if (maior != i) {
      trocar(v, i, maior);
      descer(v, n, maior);
    }
  }
}

/* Classe principal: le os ids, ordena e imprime os veiculos. */
public class OrdenacaoHeapsort {

  /* Pesquisa sequencial por id; retorna null se nao encontrar. */
  public static Veiculo buscar(Veiculo[] v, int id) {
    for (int i = 0; i < v.length; i++) {
      if (v[i].getId() == id) return v[i];
    }
    return null;
  }

  /* Le os ids, seleciona os veiculos, ordena e imprime a saida. */
  public static void main(String[] args) throws Exception {
    Veiculo[] veiculos = LeitorCsv.ler("/tmp/veiculos.csv");
    Scanner sc = new Scanner(System.in);

    Veiculo[] selecionados = new Veiculo[1000];
    int m = 0;
    int id = 0;
    while (sc.hasNextInt() && id != -1) {
      id = sc.nextInt();
      if (id != -1) {
        Veiculo v = buscar(veiculos, id);
        if (v != null) selecionados[m++] = v;
      }
    }

    Heapsort.heapsort(selecionados, m);

    for (int i = 0; i < m; i++) {
      System.out.println(selecionados[i].formatVeiculo());
    }
    sc.close();
  }
}
