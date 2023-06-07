#include "proto_to_cpp2.h"
#include "source/fuzzing/cpp2.pb.h" 
#include <ostream>

namespace cpp2 {

void TokenToCpp2(const fuzzing::token& token, std::ostream& out) {
    out << token.value();
}

} // namespace cpp2

