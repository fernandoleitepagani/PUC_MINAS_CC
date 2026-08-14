#include <iostream>
#include <string>
using namespace std;

class Funcionario{
public:
    string nome;
    double salario;
    void mostrarFuncionario(){
	cout << nome << endl;
	cout << salario << endl;
    }
};
class Gerente: public Funcionario{
    private:
	string setor;
    public:
	Gerente(string s,string n,int sa){
	    nome = n;
	    setor = s;
	    salario = sa;
	}
	void mostrarGerente(){
	    cout << setor << endl; 
	}
};

int main() {
    int sa;
    string s,n;
    cin >> sa;
    cin >> s ;
    cin >> n ;
    Gerente gerente1(s,n,sa);
    gerente1.mostrarFuncionario();
    gerente1.mostrarGerente();
    return 0;
}
