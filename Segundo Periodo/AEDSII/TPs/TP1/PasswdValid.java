import java.util.Scanner;

public class PasswdValid {

  public static boolean passwd_check(String s) {
    int validOrNot = 0; // pontuações para definir se é valida ou não
    if (s.length() < 8) return false; // checa se tem pelo menos 8 caracteres

    // booleans para checar se tem pelo menos 1 de cada
    boolean hasUpper = false;
    boolean hasLower = false;
    boolean hasNumber = false;
    boolean hasSpecial = false;

    for (int i = 0; i < s.length(); i++) {
      char tmp = s.charAt(i);

      boolean isUpper = (tmp >= 'A' && tmp <= 'Z');
      boolean isLower = (tmp >= 'a' && tmp <= 'z');
      boolean isNumber = (tmp == '0' || tmp == '1' || tmp == '2' || tmp == '3' || tmp == '4' ||
	  tmp == '5' || tmp == '6' || tmp == '7' || tmp == '8' || tmp == '9');

      if (isUpper) hasUpper = true; //marca que achou letra maiuscula
      if (isLower) hasLower = true; //marca que achou letra minuscula
      if (isNumber) hasNumber = true; //marca que achou numero
      if (!isUpper && !isLower && !isNumber) hasSpecial = true; //não é letra nem numero, logo é especial
    }

    if (!hasUpper) validOrNot++; //se não houver nenhuma letra maiuscula
    if (!hasLower) validOrNot++; //se não houver nenhuma letra minuscula
    if (!hasNumber) validOrNot++; //se não houver nenhum numero
    if (!hasSpecial) validOrNot++; //se não houver nenhum caractere especial

    if (validOrNot > 0) return false; // se pontuação maior que 0, então false
    else return true;
  }

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    while (sc.hasNextLine()) {
      String passwd = sc.nextLine();
      // le ate ler FIM
      if (passwd.length() == 3 && passwd.charAt(0) == 'F' && passwd.charAt(1) == 'I' && passwd.charAt(2) == 'M') { sc.close(); return; }
     if(passwd_check(passwd)==true)System.out.println("SIM");
     else System.out.println("NAO");
    }
    sc.close();
  }
}
