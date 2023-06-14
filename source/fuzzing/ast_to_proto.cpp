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
    for (const auto* op : prefix_expression.ops) {
        *prefix_expression_proto.add_ops() = TokenToProto(*op);
    }
    *prefix_expression_proto.mutable_expr() = PostfixExpressionToProto(*prefix_expression.expr);
    return prefix_expression_proto;
}

//FOR REVIEW:

auto IsAsExpressionToProto(const is_as_expression_node& is_as_expression) -> fuzzing::is_as_expression_node {
    fuzzing::is_as_expression_node is_as_expression_proto;
    *is_as_expression_proto.mutable_expr() = PrefixExpressionToProto(*is_as_expression.expr);
    for (const auto& term : is_as_expression.ops) {
        auto& op_proto = *is_as_expression_proto.add_ops();
        *op_proto.mutable_op() = TokenToProto(*term.op);
        *op_proto.mutable_type() = TypeIdToProto(*term.type);
        *op_proto.mutable_expr() = ExpressionToProto(*term.expr);
    }

    return is_as_expression_proto;
}

auto MultiplicativeExpressionToProto(const multiplicative_expression_node& multiplicative_expression) -> fuzzing::multiplicative_expression_node {
    fuzzing::multiplicative_expression_node multiplicative_expression_proto;
    *multiplicative_expression_proto.mutable_expr() = IsAsExpressionToProto(*multiplicative_expression.expr);
    
    for (const auto& term : multiplicative_expression.terms) {
        // auto& op_proto = *multiplicative_expression.add_ops();
        // auto& op_proto = TokenToProto(*multiplicative_expression.ops);
        // *op_proto.mutable_op() = TokenToProto(*term.op);
        // *op_proto.mutable_expr() = IsAsExpressionToProto(*term.type);
        // *term.mutable_op() = TokenToProto(*term.op);
        // *term.mutable_expr() = IsAsExpressionToProto(*term.type);
        // *multiplicative_expression.mutable_op() = TokenToProto(*term.op);
        // *multiplicative_expression.mutable_expr() = IsAsExpressionToProto(*term.type);
        auto term_proto = multiplicative_expression_proto.add_terms();
        *term_proto->mutable_op() = TokenToProto(*term.op);
        *term_proto->mutable_expr() = IsAsExpressionToProto(*term.expr);
    }

    return multiplicative_expression_proto;
}

auto AdditiveExpressionToProto(const additive_expression_node& additive_expression) -> fuzzing::additive_expression_node {
    fuzzing::additive_expression_node additive_expression_proto;
     
    *additive_expression_proto.mutable_expr() = MultiplicativeExpressionToProto(*additive_expression.expr);
    
    for (const auto& term : additive_expression.terms) {
        // auto& op_proto = *additive_expression.add_ops();
        // *op_proto.mutable_op() = TokenToProto(*term.op);
        // *op_proto.mutable_expr() = MultiplicativeExpressionToProto(*term.type);
        auto term_proto = additive_expression_proto.add_terms();
        *term_proto->mutable_op() = TokenToProto(*term.op);
        *term_proto->mutable_expr() = MultiplicativeExpressionToProto(*term.expr);
    }

    return additive_expression_proto;
}

auto ShiftExpressionToProto(const shift_expression_node& shift_expression) -> fuzzing::shift_expression_node {
    fuzzing::shift_expression_node shift_expression_proto;
    
    *shift_expression_proto.mutable_expr() = AdditiveExpressionToProto(*shift_expression.expr);
    for (const auto& term : shift_expression.terms) {
        // auto& op_proto = *shift_expression.add_ops();
        // *op_proto.mutable_op() = TokenToProto(*term.op);
        // *op_proto.mutable_expr() = AdditiveExpressionToProto(*term.type);
        auto term_proto = shift_expression_proto.add_terms();
        *term_proto->mutable_op() = TokenToProto(*term.op);
        *term_proto->mutable_expr() = AdditiveExpressionToProto(*term.expr);
    }

    return shift_expression_proto;
}

auto CompareExpressionToProto(const compare_expression_node& compare_expression) -> fuzzing::compare_expression_node {
    fuzzing::compare_expression_node compare_expression_proto;
    
    *compare_expression_proto.mutable_expr() = ShiftExpressionToProto(*compare_expression.expr);
    for (const auto& term : compare_expression.terms) {
        // auto& op_proto = *compare_expression.add_ops();
        // *op_proto.mutable_op() = TokenToProto(*term.op);
        // *op_proto.mutable_expr() = ShiftExpressionToProto(*term.type);
        auto term_proto = compare_expression_proto.add_terms();
        *term_proto->mutable_op() = TokenToProto(*term.op);
        *term_proto->mutable_expr() = ShiftExpressionToProto(*term.expr);
    }

    return compare_expression_proto;
}

auto RelationalExpressionToProto(const relational_expression_node& relational_expression) -> fuzzing::relational_expression_node {
    fuzzing::relational_expression_node relational_expression_proto;
    
    *relational_expression_proto.mutable_expr() = CompareExpressionToProto(*relational_expression.expr);
    for (const auto& term : relational_expression.terms) {
        // auto& op_proto = *relational_expression.add_ops();
        // *op_proto.mutable_op() = TokenToProto(*term.op);
        // *op_proto.mutable_expr() = CompareExpressionToProto(*term.type);
        auto term_proto = relational_expression_proto.add_terms();
        *term_proto->mutable_op() = TokenToProto(*term.op);
        *term_proto->mutable_expr() = CompareExpressionToProto(*term.expr);
    }

    return relational_expression_proto;
}

auto EqualityExpressionToProto(const equality_expression_node& equality_expression) -> fuzzing::equality_expression_node {
    fuzzing::equality_expression_node equality_expression_proto;
    *equality_expression_proto.mutable_expr() = RelationalExpressionToProto(*equality_expression.expr);
    for (const auto& term : equality_expression.terms) {
        // auto& op_proto = *equality_expression.add_ops();
        // *op_proto.mutable_op() = TokenToProto(*term.op);
        // *op_proto.mutable_expr() = RelationalExpressionToProto(*term.type);
        auto term_proto = equality_expression_proto.add_terms();
        *term_proto->mutable_op() = TokenToProto(*term.op);
        *term_proto->mutable_expr() = RelationalExpressionToProto(*term.expr);
    }
    
    return equality_expression_proto;
}

auto BitAndExpressionToProto(const bit_and_expression_node& bit_and_expression) -> fuzzing::bit_and_expression_node {
    fuzzing::bit_and_expression_node bit_and_expression_proto;
    
    *bit_and_expression_proto.mutable_expr() = EqualityExpressionToProto(*bit_and_expression.expr);
    for (const auto& term : bit_and_expression.terms) {
        // auto& op_proto = *bit_and_expression.add_ops();
        // *op_proto.mutable_op() = TokenToProto(*term.op);
        // *op_proto.mutable_expr() = EqualityExpressionToProto(*term.type);
        auto term_proto = bit_and_expression_proto.add_terms();
        *term_proto->mutable_op() = TokenToProto(*term.op);
        *term_proto->mutable_expr() = EqualityExpressionToProto(*term.expr);
    }

    return bit_and_expression_proto;
}

auto BitXorExpressionToProto(const bit_xor_expression_node& bit_xor_expression) -> fuzzing::bit_xor_expression_node {
    fuzzing::bit_xor_expression_node bit_xor_expression_proto;
    
    *bit_xor_expression_proto.mutable_expr() = BitAndExpressionToProto(*bit_xor_expression.expr);
    for (const auto& term : bit_xor_expression.terms) {
        // auto& op_proto = *bit_xor_expression.add_ops(); 
        // *op_proto.mutable_op() = TokenToProto(*term.op);
        // *op_proto.mutable_expr() = BitAndExpressionToProto(*term.type);
        auto term_proto = bit_xor_expression_proto.add_terms();
        *term_proto->mutable_op() = TokenToProto(*term.op);
        *term_proto->mutable_expr() = BitAndExpressionToProto(*term.expr);
    }
    
    return bit_xor_expression_proto;
}

auto BitOrExpressionToProto(const bit_or_expression_node& bit_or_expression) -> fuzzing::bit_or_expression_node {
    fuzzing::bit_or_expression_node bit_or_expression_proto;
    
    *bit_or_expression_proto.mutable_expr() = BitXorExpressionToProto(*bit_or_expression.expr);
    for (const auto& term : bit_or_expression.terms) {
        // auto& op_proto = *bit_or_expression.add_ops();
        // *op_proto.mutable_op() = TokenToProto(*term.op);
        // *op_proto.mutable_expr() = BitXorExpressionToProto(*term.type);
        auto term_proto = bit_or_expression_proto.add_terms();
        *term_proto->mutable_op() = TokenToProto(*term.op);
        *term_proto->mutable_expr() = BitXorExpressionToProto(*term.expr);
    }

    return bit_or_expression_proto;
}

auto LogicalAndExpressionToProto(const logical_and_expression_node& logical_and_expression) -> fuzzing::logical_and_expression_node {
    fuzzing::logical_and_expression_node logical_and_expression_proto;
    
    *logical_and_expression_proto.mutable_expr() = BitOrExpressionToProto(*logical_and_expression.expr);
    for (const auto& term : logical_and_expression.terms) {
        // auto& op_proto = *logical_and_expression.add_ops();
        // *op_proto.mutable_op() = TokenToProto(*term.op);
        // *op_proto.mutable_expr() = BitOrExpressionToProto(*term.type);
        auto term_proto = logical_and_expression_proto.add_terms();
        *term_proto->mutable_op() = TokenToProto(*term.op);
        *term_proto->mutable_expr() = BitOrExpressionToProto(*term.expr);
    }

    return logical_and_expression_proto;
}

auto LogicalOrExpressionToProto(const logical_or_expression_node& logical_or_expression) -> fuzzing::logical_or_expression_node {
    fuzzing::logical_or_expression_node logical_or_expression_proto;
    
    *logical_or_expression_proto.mutable_expr() = LogicalAndExpressionToProto(*logical_or_expression.expr);
    for (const auto& term : logical_or_expression.terms) {
        // auto& op_proto = *logical_or_expression.add_ops();
        // *op_proto.mutable_op() = TokenToProto(*term.op);
        // *op_proto.mutable_expr() = LogicalAndExpressionToProto(*term.type);
        auto term_proto = logical_or_expression_proto.add_terms();
        *term_proto->mutable_op() = TokenToProto(*term.op);
        *term_proto->mutable_expr() = LogicalAndExpressionToProto(*term.expr);
    }

    return logical_or_expression_proto;
}

auto AssignmentExpressionToProto(const assignment_expression_node& assignment_expression) -> fuzzing::assignment_expression_node {
    fuzzing::assignment_expression_node assignment_expression_proto;
    
    *assignment_expression_proto.mutable_expr() = LogicalOrExpressionToProto(*assignment_expression.expr);
    for (const auto& term : assignment_expression.terms) {
        // auto& op_proto = *assignment_expression.add_ops();
        // *op_proto.mutable_op() = TokenToProto(*term.op);
        // *op_proto.mutable_expr() = LogicalOrExpressionToProto(*term.type);
        auto term_proto = assignment_expression_proto.add_terms();
        *term_proto->mutable_op() = TokenToProto(*term.op);
        *term_proto->mutable_expr() = LogicalOrExpressionToProto(*term.expr);
    }

    return assignment_expression_proto;
}

auto ExpressionToProto(const expression_node& expression) -> fuzzing::expression_node {
    fuzzing::expression_node expression_proto;
    *expression_proto.mutable_expr() = AssignmentExpressionToProto(*expression.expr);
    return expression_proto;
}

auto ExpressionListToProto(const expression_list_node& expression_list) -> fuzzing::expression_list_node {
    fuzzing::expression_list_node expression_list_proto;
    // *expression_list_proto.mutable_open_paren = TokenToProto(*expression_list.open_paren);
    // *expression_list_proto.mutable_close_paren = TokenToProto(*expression_list.close_paren);
    // // *expression_list_proto.mutable_bool
    // //the above line has been left blank, because I have no idea as to how to mute a bool
    // //and similarly, problems with the nested message have arisen
    // // *expression_list_proto.mutable_pass = I have no idea what this is
    // *expression_list_proto.mutable_expr = ExpressionToProto(*expression_list.expr);
    // for (const auto* term : expression_list.expressions) {
    //     //do something, I guess
    // }
    return expression_list_proto;
}

auto ExpressionStatementToProto(const expression_statement_node& expression_statement) -> fuzzing::expression_statement_node {
    fuzzing::expression_statement_node expression_statement_proto;
    // *expression_statement_proto.mutable_expr() = ExpressionListToProto(expression_statement.expr);
    // *expression.mutable_has_semicolon = bool...? - what to do with bools? 
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

