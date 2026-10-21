import java.util.Scanner;

public class questao2{
  static public void main(String[] args){
    Scanner sc = new Scanner(System.in);
    while (sc.hasNextInt()){
      int n = sc.nextInt();
      Pilha prat = new Pilha(n);
      Pilha aux = new Pilha(n);
      for(int i=0;i<n;i++){
	String op = sc.next();
	String item = sc.next();
	if(op.equals("GUARDA")){ prat.empilhar(); }
	else{ 
	  while(!prat.topo().equals(item)){
	    String auxI = prat.desempilhar();
	    aux.empilhar(auxI);
	  }
	  prat.desempilhar();
	  while (!aux.vazia()){
	    String aux1 = aux.desempilhar();
	    prat.empilhar();
	  }
	  prat.imprimir();
	}
      }
    }
  }
}
