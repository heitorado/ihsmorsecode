#pragma once

#include <vector>
#include <string>
#include <functional>
#include <map>
#include "./Bimap.cpp"

namespace cripto {

  using element = std::string;       // contains a single morse/ascii character
  using message = std::vector< element >;  // constians a entire morse / ascii message
  using ulli = unsigned long long int;

  enum criptoMethods : ulli {              // methods of cryptography
			     identity = 0x0,
			     morseToAscii = 0x1,
			     asciiToMorse = 0x2,
			     cesar = 0x3,
			     rot13 = 0x4			    
  };
  
  element encript(const element& in, const criptoMethods& method, const ulli& key = 0);  // cript a single morse/ascii character (interface)
  element decript(const element& in, const criptoMethods& method, const ulli& key = 0);  // deCript a single morse/ascii character (interface)

  /*
    message encript(const message& in, const ulli& key, const criptoMethods& method);  // cript a single morse/ascii message (interface)
    message decript(const message& in, const ulli& key, const criptoMethods& method);  // deCript a single morse/ascii message (interface)

    std::string stringifyMsg(const message& in);
    message normalize(const std::string& str, bool morse = true); // if morse=true convert Morse message of type string to Message pattern (one morse char to )
  */

  const element sep = ","; // separator
  const std::map<element, element> __dict = {
						{ " " , " "     },
						{ sep , sep     },
					  
						{ "A" , ".-"    },
						{ "B" , "-..."  },
						{ "C" , "-.-."  },
						{ "D" , "-.."   },
						{ "E" , "."     },
						{ "F" , "..-."  },
						{ "G" , "--."   },
						{ "H" , "...."  },
						{ "I" , ".."    },
						{ "J" , ".---"  },
						{ "K" , "-.-"   },
						{ "L" , ".-.."  },
						{ "M" , "--"    },
						{ "N" , "-."    },
						{ "O" , "---"   },
						{ "P" , ".--."  },
						{ "Q" , "--.-"  },
						{ "R" , ".-."   },
						{ "S" , "..."   },
						{ "T" , "-"     },
						{ "U" , "..-"   },
						{ "V" , "...-"  },
						{ "W" , ".--"   },
						{ "X" , "-..-"  },
						{ "Y" , "-.--"  },
						{ "Z" ,  "--.." },
  };

  const Bimap<element, element> asciiToMorseDict(__dict);
  
};
