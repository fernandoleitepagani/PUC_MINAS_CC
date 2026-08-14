#include <iostream>
#include <string>

using namespace std;

class Lampada{
Private:
    string Estado; 
    int intensidade;
Public:
   Lampada(){
       Estado = "desligado";
       intensidade = 0;
    } 
   void getestado(){
	return Estado;
   }
   void getintensidade(){
	return intensidade;
   }
};

int main() {
    Lampada lampadasala;
    cout << lampadasala.getestado() << endl;
    cout << lampadasala.getintensidade() << endl;
    return 0;
}
