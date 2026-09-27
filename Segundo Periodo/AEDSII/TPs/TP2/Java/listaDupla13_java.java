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
      if (i > 0) comb += ";";
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

/* No da lista duplamente encadeada.
 * prox aponta para o proximo no; ant aponta para o anterior. */
class No {
  Veiculo v;
  No prox, ant;
  No(Veiculo v) {
    this.v = v;
    this.prox = null;
    this.ant = null;
  }
}

/* Lista duplamente encadeada de veiculos, com ponteiros para
 * o inicio e para o fim. Insercao  e remocao nas duas pontas. */
class ListaDupla {
  private No inicio, fim;
  private int tamanho;

  public ListaDupla() { inicio = null; fim = null; tamanho = 0; }
  public int getTamanho() { return tamanho; }

  /* Insere veiculo na primeira posicao.
   * O novo no vira o inicio, e seu prox aponta para o antigo inicio. */
  public void inserirInicio(Veiculo v) {
    No novo = new No(v);
    novo.prox = inicio;
    if (inicio != null) { inicio.ant = novo; } 
    else { fim = novo; }
    inicio = novo;
    tamanho++;
  }

  /* Insere veiculo na posicao indicada.*/
  public void inserir(Veiculo v, int pos) {
    if (pos <= 0) { inserirInicio(v); return; }
    if (pos >= tamanho) { inserirFim(v); return; }

    /* Chega ao no que ficara imediatamente antes do novo. */
    No atual = inicio;
    for (int i = 0; i < pos - 1; i++) atual = atual.prox;

    No novo = new No(v);
    novo.prox = atual.prox;      
    novo.ant = atual;            
    atual.prox.ant = novo; 
    atual.prox = novo;           
    tamanho++;
  }

  /* Insere veiculo na ultima posicao.
   * O novo no vira o fim, e seu ant aponta para o antigo fim. */
  public void inserirFim(Veiculo v) {
    No novo = new No(v);
    novo.ant = fim;              /* novo aponta para o antigo fim */
    if (fim != null) { fim.prox = novo; } 
    else { inicio = novo;}
    fim = novo;
    tamanho++;
  }

  /* Remove e retorna o primeiro veiculo.*/
  public Veiculo removerInicio() {
    Veiculo r = inicio.v;
    inicio = inicio.prox;
    if (inicio != null) { inicio.ant = null; } 
    else { fim = null; }
    tamanho--;
    return r;
  }

  /* Remove e retorna o veiculo da posicao indicada.*/
  public Veiculo remover(int pos) {
    if (pos <= 0) return removerInicio();
    if (pos >= tamanho - 1) return removerFim();
    No atual = inicio;
    for (int i = 0; i < pos; i++) atual = atual.prox;
    Veiculo r = atual.v;

    atual.ant.prox = atual.prox; /* antecessor pula o no removido */
    atual.prox.ant = atual.ant;  /* sucessor aponta de volta para o antecessor */
    
    tamanho--;
    return r;
  }

  /* Remove e retorna o ultimo veiculo.
   * O fim passa a ser o no anterior, e seu prox vira null. */
  public Veiculo removerFim() {
    Veiculo r = fim.v;
    fim = fim.ant;
    if (fim != null) { fim.prox = null; } 
    else { inicio = null; }
    tamanho--;
    return r;
  }

  /* Retorna o veiculo da posicao i, vindo do inicio. */
  public Veiculo get(int i) {
    No atual = inicio;
    for (int k = 0; k < i; k++) atual = atual.prox;
    return atual.v;
  }
}

/* Main le os ids iniciais e processa os comandos. */
public class listaDupla13_java {

  /* Busca veiculo por id. Retorna null se nao encontrar. */
  public static Veiculo searchID(Veiculo[] v, int id) {
    int i = 0;
    while (i < v.length && v[i].getId() != id) i++;
    if (i < v.length) return v[i];
    return null;
  }

  public static void main(String[] args) throws Exception {
    Veiculo[] veiculos = reader.readCSV("/tmp/veiculos.csv");
    Scanner sc = new Scanner(System.in);

    ListaDupla lista = new ListaDupla();

    /* ids dos veiculos, inseridos no final da lista */
    int id = 0;
    while (sc.hasNextInt() && id != -1) {
      id = sc.nextInt();
      if (id != -1) {
        Veiculo v = searchID(veiculos, id);
        if (v != null) lista.inserirFim(v);
      }
    }

    /* comandos */
    int n = sc.nextInt();
    for (int k = 0; k < n; k++) {
      String cmd = sc.next();

      if (cmd.equals("II")) {
        int vid = sc.nextInt();
        Veiculo v = searchID(veiculos, vid);
        if (v != null) lista.inserirInicio(v);
      } 

      else if (cmd.equals("I*")) {
        int pos = sc.nextInt();
        int vid = sc.nextInt();
        Veiculo v = searchID(veiculos, vid);
        if (v != null) lista.inserir(v, pos);
      } 

      else if (cmd.equals("IF")) {
        int vid = sc.nextInt();
        Veiculo v = searchID(veiculos, vid);
        if (v != null) lista.inserirFim(v);
      } 

      else if (cmd.equals("RI")) {
        if (lista.getTamanho() > 0) {
          Veiculo r = lista.removerInicio();
          System.out.println("(R)" + r.getMarca() + " " + r.getModelo());
        }
      } 

      else if (cmd.equals("R*")) {
        int pos = sc.nextInt();
        if (lista.getTamanho() > 0) {
          Veiculo r = lista.remover(pos);
          System.out.println("(R)" + r.getMarca() + " " + r.getModelo());
        }
      } 
      
      else if (cmd.equals("RF")) {
        if (lista.getTamanho() > 0) {
          Veiculo r = lista.removerFim();
          System.out.println("(R)" + r.getMarca() + " " + r.getModelo());
        }
      }
    }
    /* Imprime os veiculos do primeiro ao ultimo */
    for (int i = 0; i < lista.getTamanho(); i++) { System.out.println(lista.get(i).formatVeiculo()); }
    sc.close();
  }
}
