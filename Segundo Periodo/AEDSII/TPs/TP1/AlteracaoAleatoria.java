import java.util.Random;
import java.util.Scanner;

/**
 * TP1 - Questao 2: Alteracao Aleatoria (iterativo).
 * Random e atributo estatico (seed=4, setada 1x) para que o sorteio
 * avance a cada linha e a correcao automatica seja reprodutivel.
 */
public class AlteracaoAleatoria {

    private static Random gerador = new Random();

    /** Sorteia uma letra minuscula ('a'-'z'). */
    private static char sortearLetra() {
        return (char) ('a' + (Math.abs(gerador.nextInt()) % 26));
    }

    /** Sorteia 2 letras e troca a 1a pela 2a na string, retornando o resultado. */
    public static String alterar(String s) {
        char letraOrigem = sortearLetra();
        char letraDestino = sortearLetra();
        String resultado = "";
        int i;
        for (i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c == letraOrigem) {
                resultado = resultado + letraDestino;
            } else {
                resultado = resultado + c;
            }
        }
        return resultado;
    }

    /** Verifica se a linha lida e o marcador "FIM". */
    private static boolean isFim(String linha) {
        boolean resp = true;
        if (linha.length() != 3) {
            resp = false;
        } else if (linha.charAt(0) != 'F' || linha.charAt(1) != 'I' || linha.charAt(2) != 'M') {
            resp = false;
        }
        return resp;
    }

    /** Fixa seed=4, le linhas ate "FIM"/fim da entrada e imprime cada uma alterada. */
    public static void main(String[] args) {
        gerador.setSeed(4);
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNextLine()) {
            String linha = scanner.nextLine();
            if (isFim(linha)) {
                break;
            }
            System.out.println(alterar(linha));
        }
        scanner.close();
    }
}
