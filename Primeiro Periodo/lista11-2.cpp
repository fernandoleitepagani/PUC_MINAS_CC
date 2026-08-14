#include <iosteam>
#include <string>
using namespace std;

class celular{
private:
    string nome;
    int volume;
public:
    initialize(){
	nome = "celular1";
	volume = 0;
    }
    void setNome(string m){
	nome = m;
    }
    void setVolume(int n){
	if (n>0 && n<100)volume=n;
    }
    void getVolume(){
	cout << volume << endl;
    }
    void getNome() {
	cout << nome << endl;
    }
};

int main() {
    celular celular1;
    cout << getVolume() << endl;
    cout << getNome() << endl;
    return 0;
}
