import java.util.Scanner;

/**
 * TP1 - Questao 3: Is (iterativo).
 * Letras acentuadas nao contam como letra (so 'A'-'Z'/'a'-'z').
 */
public class Is {

    /** True se a string tiver somente vogais (a, e, i, o, u). */
    public static boolean somenteVogais(String s) {
        boolean resp = true;
        int i;
        for (i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c >= 'A' && c <= 'Z') {
                c = (char) (c - 'A' + 'a');
            }
            if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u') {
                resp = false;
            }
        }
        return resp;
    }

    /** True se a string tiver somente consoantes. */
    public static boolean somenteConsoantes(String s) {
        boolean resp = true;
        int i;
        for (i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c >= 'A' && c <= 'Z') {
                c = (char) (c - 'A' + 'a');
            }
            boolean vogal = (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
            if (c < 'a' || c > 'z' || vogal) {
                resp = false;
            }
        }
        return resp;
    }

    /** True se a string for um numero inteiro (sinal opcional + digitos). */
    public static boolean numeroInteiro(String s) {
        boolean resp = true;
        int inicio = (s.length() > 0 && (s.charAt(0) == '+' || s.charAt(0) == '-')) ? 1 : 0;
        if (s.length() == 0 || inicio == s.length()) {
            resp = false;
        }
        int i;
        for (i = inicio; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c < '0' || c > '9') {
                resp = false;
            }
        }
        return resp;
    }

    /** True se a string for um numero real (sinal opcional + digitos.digitos). */
    public static boolean numeroReal(String s) {
        boolean resp = true;
        int inicio = (s.length() > 0 && (s.charAt(0) == '+' || s.charAt(0) == '-')) ? 1 : 0;
        int pontos = 0;
        int digitosAntes = 0;
        int digitosDepois = 0;
        boolean aposPonto = false;
        int i;
        for (i = inicio; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c == '.') {
                pontos++;
                aposPonto = true;
            } else if (c < '0' || c > '9') {
                resp = false;
            } else if (aposPonto) {
                digitosDepois++;
            } else {
                digitosAntes++;
            }
        }
        if (pontos != 1 || digitosAntes == 0 || digitosDepois == 0) {
            resp = false;
        }
        return resp;
    }

    /** Le linhas ate "FIM"/fim da entrada e imprime X1 X2 X3 X4 (SIM/NAO). */
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNextLine()) {
            String linha = scanner.nextLine();
            boolean fim = linha.length() == 3 && linha.charAt(0) == 'F'
                    && linha.charAt(1) == 'I' && linha.charAt(2) == 'M';
            if (fim) {
                break;
            }
            String x1 = somenteVogais(linha) ? "SIM" : "NAO";
            String x2 = somenteConsoantes(linha) ? "SIM" : "NAO";
            String x3 = numeroInteiro(linha) ? "SIM" : "NAO";
            String x4 = numeroReal(linha) ? "SIM" : "NAO";
            System.out.println(x1 + " " + x2 + " " + x3 + " " + x4);
        }
        scanner.close();
    }
}
