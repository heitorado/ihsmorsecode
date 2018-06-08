#include <iostream>
#include "./cripto.cpp"

#define dict cripto::dict
using namespace std;

cripto::message test = {".-", "-...",
			"-.-.", "-..",
			".", "..-.",
			"--.", "....",
			"..", ".---",
			"-.-", ".-..",
			"--", "-.",
			"---", ".--.",
			"--.-", ".-.",
			"...", "-",
			"..-", "...-",
			".--", "-..-",
			"-.--", "--.."
};

cripto::message encripted;

int main(void) {
  for (auto t : test) {
    auto c = decript(t, cripto::asciiToMorse);
    cout << c << " ";

    encripted.emplace_back( cripto::encript(c, cripto::rot13) );    
  }

  cout << endl;
  
  for (auto e : encripted) {
    cout << e << " ";
  }
  
  cout << endl;
}
