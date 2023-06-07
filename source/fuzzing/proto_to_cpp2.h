#ifndef __CPP2_FUZZING_PROTO_TO_CPP2
#define __CPP2_FUZZING_PROTO_TO_CPP2

#include <ostream>
#include "source/fuzzing/cpp2.pb.h"

namespace cpp2 {

void TokenToCpp2(const fuzzing::token &t, std::ostream& out);

} // namespace cpp2

#endif // __CPP2_FUZZING_PROTO_TO_CPP2