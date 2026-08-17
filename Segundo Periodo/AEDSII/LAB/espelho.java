import java.util.Scanner;
 
public class espelho {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while (sc.hasNextInt()) {
            int a = sc.nextInt();
            int b = sc.nextInt();
            int N = 0;
            for (int n = a; n <= b; n++) {
                int temp = n;
                if (temp == 0) {
                    N += 1;
                } else {
                    while (temp > 0) {
                        N++;
                        temp /= 10;
                    }
                }
            }
            int i = 0, j = 0, z = 0;
            int[] both = new int[N];
            int[] invert = new int[N];
            while (a <= b) {
                int temp = a;
                int nd = 0;
                if (temp == 0) {
                    nd = 1;
                } else {
                    while (temp > 0) {
                        nd++;
                        temp /= 10;
                    }
                }
                int potencia = 1;
                for (int k = 1; k < nd; k++) potencia *= 10;
                int num = a;
                for (int k = 0; k < nd; k++) {
                    both[i] = num / potencia;
                    num = num % potencia;
                    potencia /= 10;
                    i++;
                }
                a++;
            }
            z = N - 1;
            while (z >= 0) {
                invert[j] = both[z];
                z--;
                j++;
            }
            for (int k = 0; k < N; k++) { System.out.print(both[k]); }
            for (int k = 0; k < N; k++) { System.out.print(invert[k]); }
            System.out.println();
        }
        sc.close();
    }
}
 

