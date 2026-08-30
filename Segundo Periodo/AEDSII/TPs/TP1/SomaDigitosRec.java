import java.util.Scanner;

public class SomaDigitosRec{

  //contador 
  public static int sum(int num){
    return sumRec(num);
  }
  //funcao recursiva que realiza a soma
  public static int sumRec(int num){
    int soma;
    if (num == 0) soma = 0;
    else{ 
      // Soma o ultimo digito e chama a funçao novamente.
      soma = (num%10) + sumRec(num/10);
    }
    return soma;
  }
  // Le os numeros e mostra a soma dos seus digitos.
  public static void main(String[] args){
    Scanner sc = new Scanner(System.in);

    while(sc.hasNextInt()){ //ate EOF
      int scan = sc.nextInt();
      System.out.println(sum(scan)); 
    }

    sc.close();
  }
}
