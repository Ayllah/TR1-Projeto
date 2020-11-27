#include <iostream>
#include <string>

using namespace std;

string decimalToBinary(int number) {
  string binary = "";

  while(number > 0) {
    binary = to_string(number % 2) + binary;
    number /= 2;
  }

	int restante = 8 - binary.length();

	for (int i = 0; i < restante; i++){
    binary = "0" + binary;
	}
	
	// cout << "binary: " << binary << endl;

  return binary;
}