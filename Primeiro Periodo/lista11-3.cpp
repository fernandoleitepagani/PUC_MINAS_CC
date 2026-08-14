#include <iostream>
#include <string>
using namespace std;

class Sensor{
private:
    string ambiente;
    int temp;
public:
    Sensor(){
	ambiente = "meuambiente";
	temp = 25;
    }
    void getAmbiente(){
	cout << ambiente << endl;
    }
    void getTemp(){
	cout << temp << endl;
    }
};
int main() {
    Sensor sensor1;
    sensor1.getAmbiente();
    sensor1.getTempo();
    return 0;
}
