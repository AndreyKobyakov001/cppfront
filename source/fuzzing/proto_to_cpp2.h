#ifndef __CPP2_FUZZING_PROTO_TO_CPP2
#define __CPP2_FUZZING_PROTO_TO_CPP2

#include <ostream>
#include "source/fuzzing/cpp2.pb.h"

namespace cpp2 {

void TokenToCpp2(const fuzzing::token &t, std::ostream& out);

void LiteralToCpp2(const fuzzing::literal_node &lit, std::ostream& out);

void TypeToCpp2(const fuzzing::type_node& type, std::ostream& out);

void NameToCpp2(const fuzzing::namespace_node& namespace_, std::ostream& out);

} // namespace cpp2

#endif // __CPP2_FUZZING_PROTO_TO_CPP2