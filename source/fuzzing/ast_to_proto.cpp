//this has something to do with the visitor

#include "ast_to_proto.h"
#include "source/fuzzing/cpp2.pb.h" 

namespace cpp2 {

auto TokenToProto(const token& token) -> fuzzing::token {
    fuzzing::token token_proto;
    token_proto.set_value(token.to_string()); 
    return token_proto;
}

auto LiteralToProto(const literal_node& lit) -> fuzzing::literal_node { 
    fuzzing::literal_node lit_proto;
    if (lit.literal != nullptr) { 
        *lit_proto.mutable_literal() = TokenToProto(*lit.literal);
    }
    return lit_proto;
}

auto TypeToProto(const type_node& type) -> fuzzing::type_node {
    fuzzing::type_node type_proto;
    if (type.type != nullptr) {
        *type_proto.mutable_type() = TokenToProto(*type.type);
    }
    type_proto.set_final(type.final);
    return type_proto;
}

auto NamespaceToProto(const namespace_node& namespace_) -> fuzzing::namespace_node { 
    fuzzing::namespace_node namespace_proto;
    if (namespace_.namespace_ != nullptr) {
        *namespace_proto.mutable_namespace_() = TokenToProto(*namespace_.namespace_);
    }
    return namespace_proto;
}

} // namespace cpp2

