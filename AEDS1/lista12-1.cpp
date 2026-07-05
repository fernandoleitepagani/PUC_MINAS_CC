#include <iostream>
#include <string>
using namespace std;

class Veiculo{
    public:
	string modelo;
	void ligar(){
	    cout << "ligado" << endl;
	}
};
class Carro:Veiculo{
    private:
	int portas;
    public:
	Carro(int p, string m){
	    portas = p;
	    modelo = m;
	}
	void abrirPortaMalas(){
	    cout << "porta malas aberto" << endl;
	}
};
int main() {
    Carro carro(4,"ford");
    ligar();
    abrirPortaMalas();
    return 0;
}
