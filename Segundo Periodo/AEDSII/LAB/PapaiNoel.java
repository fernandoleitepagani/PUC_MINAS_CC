import java.util.Scanner;

public class PapaiNoel {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int good = 0, bad = 0, N;
    char behavior;
    String[] array = new String[100];
    N = sc.nextInt();

    for (int i = 0; i < N; i++) {
      behavior = sc.next().charAt(0);
      array[i] = sc.next();

      if (behavior == '+')good++;
      else bad++;
    }

    for (int i = 0; i < N; i++) {
      for (int j = i + 1; j < N; j++) {
	if (array[i].compareTo(array[j]) > 0) {
	  String tmp = array[i];
	  array[i] = array[j];
	  array[j] = tmp;
	}
      }
    }
    for (int i = 0; i < N; i++)System.out.println(array[i]);
    System.out.println("Se comportaram: " + good + " | Nao se comportaram: " + bad);
    sc.close();
  }
}
