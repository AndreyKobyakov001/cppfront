#ifndef __CPP2_FUZZING_AST_TO_PROTO
#define __CPP2_FUZZING_AST_TO_PROTO

#include "source/cppfront.h"
#include "source/fuzzing/cpp2.pb.h"

namespace cpp2 {

// Builds a protobuf representation of `ast`.
// auto AstToProto(const translation_unit_node& parse_tree) ->
// fuzzing::translation_unit_node;
auto TokenToProto(const token &t) -> fuzzing::token;

} // namespace cpp2

#endif // __CPP2_FUZZING_AST_TO_PROTO