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
	
	cout << "binary: " << binary << endl;

  return binary;
}

// int main() {

//   string bin = decimalToBinary(8);
//   cout << bin << endl;

//   int n = 2 % 4;
//   cout << n << endl;

//   return 0;
// }
