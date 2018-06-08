#include <iostream>
#include <random>
#include <chrono>
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

int main(void) {
  std::uniform_int_distribution<cripto::ulli> distribution(0, 1000000);
  std::default_random_engine engine;
  cripto::message encripted;
  
  engine.seed( std::chrono::system_clock::now().time_since_epoch().count() );
  cripto::ulli key = distribution(engine);

  cout << "Key: " << key << endl;
  
  for (auto t : test) {
    auto c = decript(t, cripto::asciiToMorse);
    cout << c << " ";

    encripted.emplace_back( cripto::encript(c, cripto::cesar, key) );    
  }

  cout << endl;
  
  for (auto e : encripted) {
    cout << e << " ";
  }
  
  cout << endl;

  for (auto e : encripted) {
    cout << cripto::decript(e, cripto::cesar, key) << " ";
  }
  
  cout << endl;
 
  return 0;
}
