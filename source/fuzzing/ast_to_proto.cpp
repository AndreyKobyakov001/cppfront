//this has something to do with the visitor

#include "ast_to_proto.h"
#include "source/fuzzing/cpp2.pb.h" 

namespace cpp2 {

auto TokenToProto(const token& token) -> fuzzing::token {
    fuzzing::token token_proto;
    token_proto.set_value(token.to_string()); 
    return token_proto;
}

} // namespace cpp2

