import java.util.Scanner;

public class CifraDeCesar {
    /** Cifra a string com chave 3 (pula 3 pra frente), mantendo caracteres não letras. */
  public static String cifrar(String s) {
    int CHAVE = 3;
    String resultado = "";
    int i;
    for (i = 0; i < s.length(); i++) {
      char c = s.charAt(i);
      char novo = (char) (c + CHAVE);
      resultado = resultado + novo;
    }
    return resultado;
  }
    
    /** Le linhas ate "FIM"/fim da entrada e imprime cada uma cifrada. */
    public static void main(String[] args) {
      Scanner scanner = new Scanner(System.in);
      while (scanner.hasNextLine()) {
	String linha = scanner.nextLine();
	if (linha.length() == 3 && linha.charAt(0) == 'F' && linha.charAt(1) == 'I' && linha.charAt(2) == 'M') { scanner.close(); return; }
	System.out.println(cifrar(linha));
      }
      scanner.close();
    }
}
