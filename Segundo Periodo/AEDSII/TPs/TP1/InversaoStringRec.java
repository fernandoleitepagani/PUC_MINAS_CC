import java.util.Scanner;

public class InversaoStringRec{
  //contador inicializa a função recursiva 
  public static String invert(String s){
    return invertRec(s, 0);
  }
  // funcao recursiva --> faz a string invertida
  public static String invertRec(String s, int i){
    String result;
    if (i == s.length()) { result = ""; } //indica fim da função/string
    
    // Inverte resto e põe o caractere atual no final
    else { result = invertRec(s, i + 1) + s.charAt(i); }
    return result;
  }

  public static void main(String[] args){
    Scanner sc = new Scanner(System.in);
    while (sc.hasNextLine()) {
      String line = sc.nextLine();
      
      // Para se ler FIM
	if (line.length() == 3 && line.charAt(0) == 'F' && line.charAt(1) == 'I' && line.charAt(2) == 'M') { sc.close(); return; }
      
      System.out.println(invert(line));
    }
    sc.close();
  }
}
