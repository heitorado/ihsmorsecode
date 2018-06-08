#pragma once
#include "./cripto.hpp"
#include <functional>

namespace cripto {

  inline element _identity(const element& in, const ulli& key) {
    return in;
  };

  bool isUpperChar(const char& c) {
    if (c >= 'A' && c <= 'Z')
      return true;
    else
      return false;
  }
  
  inline element _morseToAscii(const element& morse, const ulli& key) {
    return asciiToMorseDict.getKeyByValue(morse);
  }

  inline element _asciiToMorse(const element& ascii, const ulli& key) {
    return asciiToMorseDict.getValueByKey(ascii);
  }

  element _cesar(const element& ascii, const ulli& key) {
    auto lowerBound = 'A';
    auto range = 'Z' - 'A';
    auto c = ascii[0];
    
    if (c == ' ')
      return " ";
    else if (c == 0)
      return 0;
    else if (c == sep[0])
      return sep;
    else if ( isUpperChar(c) )
      return element(1, lowerBound + ( (c - 'A' + key) % range ) ); // char constructor of std::string<char>(int n, char c), fill char 'c' n times 
    else
      return element("Matching error at _cesar with input: " + ascii);
  }

  inline element _uncesar(const element& ascii, const ulli& key) {
    return _cesar(ascii, ('A' - 'Z') - key + 9);
  }
  
  inline element _rot13(const element& ascii, const ulli& key) {
    return _cesar(ascii, 13);
  }

  inline element _unrot13(const element& ascii, const ulli& key) {
    return _uncesar(ascii, 13);
  }
  
  using functionMethod = std::function< element(const element& in, const ulli& key) >;
  // criptoMethods (enum) identifier to criptography function itself
  std::map< ulli, functionMethod > criptoImplementation {
							 {identity, _identity},
							 {morseToAscii, _morseToAscii},
							 {asciiToMorse, _asciiToMorse},
							 {cesar, _cesar},
							 {rot13, _rot13}
  };

  std::map< ulli, functionMethod > decriptoImplementation {
							 {identity, _identity},
							 {morseToAscii, _asciiToMorse},
							 {asciiToMorse, _morseToAscii},
							 {cesar, _uncesar},
							 {rot13, _unrot13}
  };
  
  
  inline element encript(const element& in, const criptoMethods& method, const ulli& key) {
    return criptoImplementation.at(method)(in, key);
  }

  inline element decript(const element& in, const criptoMethods& method, const ulli& key) {
    return decriptoImplementation.at(method)(in, key);
  }
  
};
