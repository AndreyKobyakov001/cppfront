#include "proto_to_cpp2.h"
#include "source/fuzzing/cpp2.pb.h" 
#include <ostream>

namespace cpp2 {

void TokenToCpp2(const fuzzing::token& token, std::ostream& out) {
    out << token.value();
}

void LiteralToCpp2(const fuzzing::literal_node& lit, std::ostream& out) { 
    TokenToCpp2(lit.literal(), out);
    
    if (lit.has_suffix()) { 
        TokenToCpp2(lit.suffix(), out);
    }
    // else { 
        //suffix generator; featuring one-off lexemes  
    // }
    
    // redo to add default values
    //if not has literal, give it fake literal :)
}

void TypeToCpp2(const fuzzing::type_node& type, std::ostream& out) { 
    TokenToCpp2(type.type(), out);
}

void NameToCpp2(const fuzzing::namespace_node& namespace_, std::ostream& out){ 
    //should the name be changed to have _proto?
    TokenToCpp2(namespace_.namespace_(), out);
}

} // namespace cpp2

