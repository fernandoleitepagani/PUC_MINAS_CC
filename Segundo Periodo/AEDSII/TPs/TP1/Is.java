import java.util.Scanner;


public class Is {
  public static boolean isVogals(String s) { //verifica se é só vogal
    for (int i = 0; i < s.length(); i++) {
      char tmp = s.charAt(i);

      //se algum não for vogal, false
      if (tmp != 'a' && tmp != 'e' && tmp != 'i' && tmp != 'o' && tmp != 'u' &&
	  tmp != 'A' && tmp != 'E' && tmp != 'I' && tmp != 'O' && tmp != 'U') { return false; }
    }
    return true;
  }

  public static boolean notVogals(String s) { //verifica se é só consoante
    for (int i = 0; i < s.length(); i++) {
      char tmp = s.charAt(i);

      // checa se é uma letra
      boolean TrueFalseLetter = (tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z');
      if (!TrueFalseLetter) return false;

      // checa se é vogal
      if (tmp == 'a' || tmp == 'e' || tmp == 'i' || tmp == 'o' || tmp == 'u' || tmp == 'A' || tmp == 'E' || tmp == 'I' || tmp == 'O' || tmp == 'U') { return false; }
    }
    return true;
  }

  public static boolean intNumber(String s) { //verifica se é numero int
    for (int i = 0; i < s.length(); i++) {
      char tmp = s.charAt(i);

      //se algum nao for numero, false
      if (tmp != '0' && tmp != '1' && tmp != '2' && tmp != '3' && tmp != '4' &&
	  tmp != '5' && tmp != '6' && tmp != '7' && tmp != '8' && tmp != '9') { return false; }
    }
    return true;
  }

  public static boolean realNumber(String s) { // verifica se é numero real
    int dotComma = 0;          // conta quantos '.' ou ',' apareceram
    for (int i = 0; i < s.length(); i++) {
      char tmp = s.charAt(i);
      if (tmp == '.' || tmp == ','){dotComma++;
	if (dotComma > 1) return false;   // mais de um ponto ou virgula -> false
      }
      // charactere que não é dígito nem ponto e virgula 
      else if (tmp < '0' || tmp > '9'){return false;}
    }
    if (dotComma == s.length()) return false; // string só com '.' ou ',' 
    return true;
  }

  public static void main(String[] args) {

    //scanner
    Scanner sc = new Scanner(System.in);
    
    while (sc.hasNextLine()) {
      String scanned = sc.nextLine();

      //Acaba se ler FIM
      if (scanned.length() == 3 && scanned.charAt(0) == 'F' && scanned.charAt(1) == 'I' && scanned.charAt(2) == 'M') { sc.close(); return; }

      //imprime resposta baseado no Boolean Value dos métodos
      if(isVogals(scanned)==true) System.out.print("SIM");
      else System.out.print("NAO");

      if(notVogals(scanned)==true) System.out.print(" SIM");
      else System.out.print(" NAO");
      
      if(intNumber(scanned)==true) System.out.print(" SIM");
      else System.out.print(" NAO");

      if(realNumber(scanned)==true) System.out.print(" SIM");
      else System.out.print(" NAO");

      System.out.println();
    }
    sc.close();
  }
}
