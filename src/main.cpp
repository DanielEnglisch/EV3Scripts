#include <iostream>
#include <unistd.h>
using namespace std;

int main(){

	cout << "123;42;54" << endl;
	usleep(1000000);
	cout << "42;142;234" << endl;
	usleep(1000000);
	cout << "52;4;5" << endl;
	usleep(1000000);
	cout << "84;158;200" << endl;

	return 0;
}	
