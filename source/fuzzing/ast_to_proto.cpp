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

auto PrimaryExpressionToProto(const primary_expression_node& primary_expression) -> fuzzing::primary_expression_node { 
    fuzzing::primary_expression_node primary_expression_proto;
    const auto& e = primary_expression.expr;
    if (std::holds_alternative<std::monostate>(e)) { 
    } else if (std::holds_alternative<const token*>(e)) { 
        *primary_expression_proto.mutable_identifier() = TokenToProto(*std::get<const token*>(e));
    } else if (std::holds_alternative<std::unique_ptr<expression_list_node>>(e)) { 
        *primary_expression_proto.mutable_expression_list() = 
          ExpressionListToProto(*std::get<std::unique_ptr<expression_list_node>>(e));
    } else if (std::holds_alternative<std::unique_ptr<id_expression_node>>(e)) { 
        *primary_expression_proto.mutable_id_expression() = 
          IdExpressionToProto(*std::get<std::unique_ptr<id_expression_node>>(e));
    } else if (std::holds_alternative<std::unique_ptr<declaration_node>>(e)) { 
        *primary_expression_proto.mutable_declaration() = 
          DeclarationToProto(*std::get<std::unique_ptr<declaration_node>>(e));
    } else if (std::holds_alternative<std::unique_ptr<inspect_expression_node>>(e)) { 
        *primary_expression_proto.mutable_inspect() = 
          InspectExpressionToProto(*std::get<std::unique_ptr<inspect_expression_node>>(e));
    } else if (std::holds_alternative<std::unique_ptr<literal_node>>(e)) { 
        *primary_expression_proto.mutable_literal() = 
          LiteralToProto(*std::get<std::unique_ptr<literal_node>>(e));
    }
    return primary_expression_proto;
}

auto PrefixExpressionToProto(const prefix_expression_node& prefix_expression) -> fuzzing::prefix_expression_node {
    fuzzing::prefix_expression_node prefix_expression_proto;
    // TODO: Convert prefix_expression_ to fuzzing::prefix_expression_node
    return prefix_expression_proto;
}

auto IsAsExpressionToProto(const is_as_expression_node& is_as_expression) -> fuzzing::is_as_expression_node {
    fuzzing::is_as_expression_node is_as_expression_proto;
    // TODO: Convert is_as_expression_ to fuzzing::is_as_expression_node
    return is_as_expression_proto;
}

auto MultiplicativeExpressionToProto(const multiplicative_expression_node& multiplicative_expression) -> fuzzing::multiplicative_expression_node {
    fuzzing::multiplicative_expression_node multiplicative_expression_proto;
    // TODO: Convert multiplicative_expression_ to fuzzing::multiplicative_expression_node
    return multiplicative_expression_proto;
}

auto AdditiveExpressionToProto(const additive_expression_node& additive_expression) -> fuzzing::additive_expression_node {
    fuzzing::additive_expression_node additive_expression_proto;
    // TODO: Convert additive_expression_ to fuzzing::additive_expression_node
    return additive_expression_proto;
}

auto ShiftExpressionToProto(const shift_expression_node& shift_expression) -> fuzzing::shift_expression_node {
    fuzzing::shift_expression_node shift_expression_proto;
    // TODO: Convert shift_expression_ to fuzzing::shift_expression_node
    return shift_expression_proto;
}

auto CompareExpressionToProto(const compare_expression_node& compare_expression) -> fuzzing::compare_expression_node {
    fuzzing::compare_expression_node compare_expression_proto;
    // TODO: Convert compare_expression_ to fuzzing::compare_expression_node
    return compare_expression_proto;
}

auto RelationalExpressionToProto(const relational_expression_node& relational_expression) -> fuzzing::relational_expression_node {
    fuzzing::relational_expression_node relational_expression_proto;
    // TODO: Convert relational_expression_ to fuzzing::relational_expression_node
    return relational_expression_proto;
}

auto EqualityExpressionToProto(const equality_expression_node& equality_expression) -> fuzzing::equality_expression_node {
    fuzzing::equality_expression_node equality_expression_proto;
    // TODO: Convert equality_expression_ to fuzzing::equality_expression_node
    return equality_expression_proto;
}

auto BitAndExpressionToProto(const bit_and_expression_node& bit_and_expression) -> fuzzing::bit_and_expression_node {
    fuzzing::bit_and_expression_node bit_and_expression_proto;
    // TODO: Convert bit_and_expression_ to fuzzing::bit_and_expression_node
    return bit_and_expression_proto;
}

auto BitXorExpressionToProto(const bit_xor_expression_node& bit_xor_expression) -> fuzzing::bit_xor_expression_node {
    fuzzing::bit_xor_expression_node bit_xor_expression_proto;
    // TODO: Convert bit_xor_expression_ to fuzzing::bit_xor_expression_node
    return bit_xor_expression_proto;
}

auto BitOrExpressionToProto(const bit_or_expression_node& bit_or_expression) -> fuzzing::bit_or_expression_node {
    fuzzing::bit_or_expression_node bit_or_expression_proto;
    // TODO: Convert bit_or_expression_ to fuzzing::bit_or_expression_node
    return bit_or_expression_proto;
}

auto LogicalAndExpressionToProto(const logical_and_expression_node& logical_and_expression) -> fuzzing::logical_and_expression_node {
    fuzzing::logical_and_expression_node logical_and_expression_proto;
    // TODO: Convert logical_and_expression_ to fuzzing::logical_and_expression_node
    return logical_and_expression_proto;
}

auto LogicalOrExpressionToProto(const logical_or_expression_node& logical_or_expression) -> fuzzing::logical_or_expression_node {
    fuzzing::logical_or_expression_node logical_or_expression_proto;
    // TODO: Convert logical_or_expression_ to fuzzing::logical_or_expression_node
    return logical_or_expression_proto;
}

auto AssignmentExpressionToProto(const assignment_expression_node& assignment_expression) -> fuzzing::assignment_expression_node {
    fuzzing::assignment_expression_node assignment_expression_proto;
    // TODO: Convert assignment_expression_ to fuzzing::assignment_expression_node
    return assignment_expression_proto;
}

auto ExpressionToProto(const expression_node& expression) -> fuzzing::expression_node {
    fuzzing::expression_node expression_proto;
    // TODO: Convert expression_ to fuzzing::expression_node
    return expression_proto;
}

auto ExpressionListToProto(const expression_list_node& expression_list) -> fuzzing::expression_list_node {
    fuzzing::expression_list_node expression_list_proto;
    // TODO: Convert expression_list_ to fuzzing::expression_list_node
    return expression_list_proto;
}

auto ExpressionStatementToProto(const expression_statement_node& expression_statement) -> fuzzing::expression_statement_node {
    fuzzing::expression_statement_node expression_statement_proto;
    // TODO: Convert expression_statement_ to fuzzing::expression_statement_node
    return expression_statement_proto;
}

auto CaptureToProto(const capture& capture) -> fuzzing::capture {
    fuzzing::capture capture_proto;
    // TODO: Convert capture_ to fuzzing::capture
    return capture_proto;
}

auto CaptureGroupToProto(const capture_group& capture_group) -> fuzzing::capture_group {
    fuzzing::capture_group capture_group_proto;
    // TODO: Convert capture_group_ to fuzzing::capture_group
    return capture_group_proto;
}

auto PostfixExpressionToProto(const postfix_expression_node& postfix_expression) -> fuzzing::postfix_expression_node {
    fuzzing::postfix_expression_node postfix_expression_proto;
    // TODO: Convert postfix_expression_ to fuzzing::postfix_expression_node
    return postfix_expression_proto;
}

auto UnqualifiedIdToProto(const unqualified_id_node& unqualified_id) -> fuzzing::unqualified_id_node {
    fuzzing::unqualified_id_node unqualified_id_proto;
    // TODO: Convert unqualified_id_ to fuzzing::unqualified_id_node
    return unqualified_id_proto;
}

auto QualifiedIdToProto(const qualified_id_node& qualified_id) -> fuzzing::qualified_id_node {
    fuzzing::qualified_id_node qualified_id_proto;
    // TODO: Convert qualified_id_ to fuzzing::qualified_id_node
    return qualified_id_proto;
}

auto TypeIdToProto(const type_id_node& type_id) -> fuzzing::type_id_node {
    fuzzing::type_id_node type_id_proto;
    // TODO: Convert type_id_ to fuzzing::type_id_node
    return type_id_proto;
}

auto IdExpressionToProto(const id_expression_node& id_expression) -> fuzzing::id_expression_node {
    fuzzing::id_expression_node id_expression_proto;
    // TODO: Convert id_expression_ to fuzzing::id_expression_node
    return id_expression_proto;
}

auto CompoundStatementToProto(const compound_statement_node& compound_statement) -> fuzzing::compound_statement_node {
    fuzzing::compound_statement_node compound_statement_proto;
    // TODO: Convert compound_statement_ to fuzzing::compound_statement_node
    return compound_statement_proto;
}

auto SelectionStatementToProto(const selection_statement_node& selection_statement) -> fuzzing::selection_statement_node {
    fuzzing::selection_statement_node selection_statement_proto;
    // TODO: Convert selection_statement_ to fuzzing::selection_statement_node
    return selection_statement_proto;
}

auto IterationStatementToProto(const iteration_statement_node& iteration_statement) -> fuzzing::iteration_statement_node {
    fuzzing::iteration_statement_node iteration_statement_proto;
    // TODO: Convert iteration_statement_ to fuzzing::iteration_statement_node
    return iteration_statement_proto;
}

auto ReturnStatementToProto(const return_statement_node& return_statement) -> fuzzing::return_statement_node {
    fuzzing::return_statement_node return_statement_proto;
    // TODO: Convert return_statement_ to fuzzing::return_statement_node
    return return_statement_proto;
}

auto AlternativeToProto(const alternative_node& alternative) -> fuzzing::alternative_node {
    fuzzing::alternative_node alternative_proto;
    // TODO: Convert alternative_ to fuzzing::alternative_node
    return alternative_proto;
}

auto InspectExpressionToProto(const inspect_expression_node& inspect_expression) -> fuzzing::inspect_expression_node {
    fuzzing::inspect_expression_node inspect_expression_proto;
    // TODO: Convert inspect_expression_ to fuzzing::inspect_expression_node
    return inspect_expression_proto;
}

auto ContractToProto(const contract_node& contract) -> fuzzing::contract_node {
    fuzzing::contract_node contract_proto;
    // TODO: Convert contract_ to fuzzing::contract_node
    return contract_proto;
}

auto JumpToProto(const jump_statement_node& jump_statement) -> fuzzing::jump_statement_node { 
    fuzzing::jump_statement_node jump_statement_proto;

    return jump_statement_proto;
}

auto StatementToProto(const statement_node& statement) -> fuzzing::statement_node {
    fuzzing::statement_node statement_proto;
    // TODO: Convert statement_ to fuzzing::statement_node
    return statement_proto;
}

auto ParameterDeclarationNodeToProto(const parameter_declaration_node& parameter_declaration) -> fuzzing::parameter_declaration_node {
    fuzzing::parameter_declaration_node parameter_declaration_proto;
    // TODO: Convert parameter_declaration_ to fuzzing::parameter_declaration_node
    return parameter_declaration_proto;
}

auto ParameterDeclarationListToProto(const parameter_declaration_list_node& parameter_declaration_list) -> fuzzing::parameter_declaration_list_node {
    fuzzing::parameter_declaration_list_node parameter_declaration_list_proto;
    // TODO: Convert parameter_declaration_list_ to fuzzing::parameter_declaration_list_node
    return parameter_declaration_list_proto;
}

auto FunctionTypeToProto(const function_type_node& function_type) -> fuzzing::function_type_node {
    fuzzing::function_type_node function_type_proto;
    // TODO: Convert function_type_ to fuzzing::function_type_node
    return function_type_proto;
}

auto AliasToProto(const alias_node& alias) -> fuzzing::alias_node {
    fuzzing::alias_node alias_proto;
    // TODO: Convert alias_ to fuzzing::alias_node
    return alias_proto;
}

auto DeclarationToProto(const declaration_node& declaration) -> fuzzing::declaration_node {
    fuzzing::declaration_node declaration_proto;
    // TODO: Convert declaration_ to fuzzing::declaration_node
    return declaration_proto;
}

auto TranslationUnitToProto(const translation_unit_node& translation_unit) -> fuzzing::translation_unit_node {
    fuzzing::translation_unit_node translation_unit_proto;
    // TODO: Convert translation_unit_ to fuzzing::translation_unit_node
    return translation_unit_proto;
}

} // namespace cpp2

