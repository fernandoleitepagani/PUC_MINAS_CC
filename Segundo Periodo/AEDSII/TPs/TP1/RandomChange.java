import java.util.Scanner;
import java.util.Random;

public class RandomChange {
  public static String random(String s, Random g){

    // change the Chracters
    char change1 = (char) ('a' + (Math.abs(g.nextInt()) % 26));
    char change2  = (char) ('a' + (Math.abs(g.nextInt()) % 26));

    String fv = ""; //string vazia
		    
    for (int i = 0; i < s.length(); i++) {
      char tmp = s.charAt(i);
      if (tmp == change1) tmp = change2;
      fv += tmp;
    }
    return fv; //fv == final version
  } 

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in); //scanners 
    Random generator = new Random(); //gerador aleatório
    generator.setSeed(4);
    
    while (sc.hasNextLine()) {
      String line = sc.nextLine();
      if (line.length() == 3 && line.charAt(0) == 'F' && line.charAt(1) == 'I' && line.charAt(2) == 'M') { sc.close(); return; 
      }
      System.out.println(random(line, generator));
    }
    sc.close();
  }
}
