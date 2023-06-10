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

// The nasty starts here

auto PrimaryExpressionToProto(const primary_expression_node& primary_expression_) -> fuzzing::primary_expression_node { 
    fuzzing::primary_expression_node primary_expression_;

    return primary_expression_proto;
}

auto PrefixExpressionToProto(const prefix_expression_node& prefix_expression_) -> fuzzing::prefix_expression_node {
    fuzzing::prefix_expression_node prefix_expression_;
    // TODO: Convert prefix_expression_ to fuzzing::prefix_expression_node
    return prefix_expression_proto;
}

auto IsAsExpressionToProto(const is_as_expression_node& is_as_expression_) -> fuzzing::is_as_expression_node {
    fuzzing::is_as_expression_node is_as_expression_;
    // TODO: Convert is_as_expression_ to fuzzing::is_as_expression_node
    return is_as_expression_proto;
}

auto MultiplicativeExpressionToProto(const multiplicative_expression_node& multiplicative_expression_) -> fuzzing::multiplicative_expression_node {
    fuzzing::multiplicative_expression_node multiplicative_expression_;
    // TODO: Convert multiplicative_expression_ to fuzzing::multiplicative_expression_node
    return multiplicative_expression_proto;
}

auto AdditiveExpressionToProto(const additive_expression_node& additive_expression_) -> fuzzing::additive_expression_node {
    fuzzing::additive_expression_node additive_expression_;
    // TODO: Convert additive_expression_ to fuzzing::additive_expression_node
    return additive_expression_proto;
}

auto ShiftExpressionToProto(const shift_expression_node& shift_expression_) -> fuzzing::shift_expression_node {
    fuzzing::shift_expression_node shift_expression_;
    // TODO: Convert shift_expression_ to fuzzing::shift_expression_node
    return shift_expression_proto;
}

auto CompareExpressionToProto(const compare_expression_node& compare_expression_) -> fuzzing::compare_expression_node {
    fuzzing::compare_expression_node compare_expression_;
    // TODO: Convert compare_expression_ to fuzzing::compare_expression_node
    return compare_expression_proto;
}

auto RelationalExpressionToProto(const relational_expression_node& relational_expression_) -> fuzzing::relational_expression_node {
    fuzzing::relational_expression_node relational_expression_;
    // TODO: Convert relational_expression_ to fuzzing::relational_expression_node
    return relational_expression_proto;
}

auto EqualityExpressionToProto(const equality_expression_node& equality_expression_) -> fuzzing::equality_expression_node {
    fuzzing::equality_expression_node equality_expression_;
    // TODO: Convert equality_expression_ to fuzzing::equality_expression_node
    return equality_expression_proto;
}

auto BitAndExpressionToProto(const bit_and_expression_node& bit_and_expression_) -> fuzzing::bit_and_expression_node {
    fuzzing::bit_and_expression_node bit_and_expression_;
    // TODO: Convert bit_and_expression_ to fuzzing::bit_and_expression_node
    return bit_and_expression_proto;
}

auto BitXorExpressionToProto(const bit_xor_expression_node& bit_xor_expression_) -> fuzzing::bit_xor_expression_node {
    fuzzing::bit_xor_expression_node bit_xor_expression_;
    // TODO: Convert bit_xor_expression_ to fuzzing::bit_xor_expression_node
    return bit_xor_expression_proto;
}

auto BitOrExpressionToProto(const bit_or_expression_node& bit_or_expression_) -> fuzzing::bit_or_expression_node {
    fuzzing::bit_or_expression_node bit_or_expression_;
    // TODO: Convert bit_or_expression_ to fuzzing::bit_or_expression_node
    return bit_or_expression_proto;
}

auto LogicalAndExpressionToProto(const logical_and_expression_node& logical_and_expression_) -> fuzzing::logical_and_expression_node {
    fuzzing::logical_and_expression_node logical_and_expression_;
    // TODO: Convert logical_and_expression_ to fuzzing::logical_and_expression_node
    return logical_and_expression_proto;
}

auto LogicalOrExpressionToProto(const logical_or_expression_node& logical_or_expression_) -> fuzzing::logical_or_expression_node {
    fuzzing::logical_or_expression_node logical_or_expression_;
    // TODO: Convert logical_or_expression_ to fuzzing::logical_or_expression_node
    return logical_or_expression_proto;
}

auto AssignmentExpressionToProto(const assignment_expression_node& assignment_expression_) -> fuzzing::assignment_expression_node {
    fuzzing::assignment_expression_node assignment_expression_;
    // TODO: Convert assignment_expression_ to fuzzing::assignment_expression_node
    return assignment_expression_proto;
}

auto ExpressionToProto(const expression_node& expression_) -> fuzzing::expression_node {
    fuzzing::expression_node expression_;
    // TODO: Convert expression_ to fuzzing::expression_node
    return expression_proto;
}

auto ExpressionListToProto(const expression_list_node& expression_list_) -> fuzzing::expression_list_node {
    fuzzing::expression_list_node expression_list_;
    // TODO: Convert expression_list_ to fuzzing::expression_list_node
    return expression_list_proto;
}

auto ExpressionStatementToProto(const expression_statement_node& expression_statement_) -> fuzzing::expression_statement_node {
    fuzzing::expression_statement_node expression_statement_;
    // TODO: Convert expression_statement_ to fuzzing::expression_statement_node
    return expression_statement_proto;
}

auto CaptureToProto(const capture& capture_) -> fuzzing::capture {
    fuzzing::capture capture_;
    // TODO: Convert capture_ to fuzzing::capture
    return capture_proto;
}

auto CaptureGroupToProto(const capture_group& capture_group_) -> fuzzing::capture_group {
    fuzzing::capture_group capture_group_;
    // TODO: Convert capture_group_ to fuzzing::capture_group
    return capture_group_proto;
}

auto PostfixExpressionToProto(const postfix_expression_node& postfix_expression_) -> fuzzing::postfix_expression_node {
    fuzzing::postfix_expression_node postfix_expression_;
    // TODO: Convert postfix_expression_ to fuzzing::postfix_expression_node
    return postfix_expression_proto;
}

auto UnqualifiedIdToProto(const unqualified_id_node& unqualified_id_) -> fuzzing::unqualified_id_node {
    fuzzing::unqualified_id_node unqualified_id_;
    // TODO: Convert unqualified_id_ to fuzzing::unqualified_id_node
    return unqualified_id_proto;
}

auto QualifiedIdToProto(const qualified_id_node& qualified_id_) -> fuzzing::qualified_id_node {
    fuzzing::qualified_id_node qualified_id_;
    // TODO: Convert qualified_id_ to fuzzing::qualified_id_node
    return qualified_id_proto;
}

auto TypeIdToProto(const type_id_node& type_id_) -> fuzzing::type_id_node {
    fuzzing::type_id_node type_id_;
    // TODO: Convert type_id_ to fuzzing::type_id_node
    return type_id_proto;
}

auto IdExpressionToProto(const id_expression_node& id_expression_) -> fuzzing::id_expression_node {
    fuzzing::id_expression_node id_expression_;
    // TODO: Convert id_expression_ to fuzzing::id_expression_node
    return id_expression_proto;
}

auto CompoundStatementToProto(const compound_statement_node& compound_statement_) -> fuzzing::compound_statement_node {
    fuzzing::compound_statement_node compound_statement_;
    // TODO: Convert compound_statement_ to fuzzing::compound_statement_node
    return compound_statement_proto;
}

auto SelectionStatementToProto(const selection_statement_node& selection_statement_) -> fuzzing::selection_statement_node {
    fuzzing::selection_statement_node selection_statement_;
    // TODO: Convert selection_statement_ to fuzzing::selection_statement_node
    return selection_statement_proto;
}

auto IterationStatementToProto(const iteration_statement_node& iteration_statement_) -> fuzzing::iteration_statement_node {
    fuzzing::iteration_statement_node iteration_statement_;
    // TODO: Convert iteration_statement_ to fuzzing::iteration_statement_node
    return iteration_statement_proto;
}

auto ReturnStatementToProto(const return_statement_node& return_statement_) -> fuzzing::return_statement_node {
    fuzzing::return_statement_node return_statement_;
    // TODO: Convert return_statement_ to fuzzing::return_statement_node
    return return_statement_proto;
}

auto AlternativeToProto(const alternative_node& alternative_) -> fuzzing::alternative_node {
    fuzzing::alternative_node alternative_;
    // TODO: Convert alternative_ to fuzzing::alternative_node
    return alternative_proto;
}

auto InspectExpressionToProto(const inspect_expression_node& inspect_expression_) -> fuzzing::inspect_expression_node {
    fuzzing::inspect_expression_node inspect_expression_;
    // TODO: Convert inspect_expression_ to fuzzing::inspect_expression_node
    return inspect_expression_proto;
}

auto ContractToProto(const contract_node& contract_) -> fuzzing::contract_node {
    fuzzing::contract_node contract_;
    // TODO: Convert contract_ to fuzzing::contract_node
    return contract_proto;
}

auto FunctionDefinitionToProto(const function_definition_node& function_definition_) -> fuzzing::function_definition_node {
    fuzzing::function_definition_node function_definition_;
    // TODO: Convert function_definition_ to fuzzing::function_definition_node
    return function_definition_proto;
}

auto TopLevelDeclarationToProto(const top_level_declaration_node& top_level_declaration_) -> fuzzing::top_level_declaration_node {
    fuzzing::top_level_declaration_node top_level_declaration_;
    // TODO: Convert top_level_declaration_ to fuzzing::top_level_declaration_node
    return top_level_declaration_proto;
}

auto TranslationUnitToProto(const translation_unit_node& translation_unit_) -> fuzzing::translation_unit_node {
    fuzzing::translation_unit_node translation_unit_;
    // TODO: Convert translation_unit_ to fuzzing::translation_unit_node
    return translation_unit_proto;
}

} // namespace cpp2

