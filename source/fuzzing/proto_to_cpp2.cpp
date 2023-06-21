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

void PrimaryExpressionToCpp2(const fuzzing::primary_expression_node& primary_expression, std::ostream& out) {
    if (primary_expression.has_identifier()) {
        TokenToCpp2(primary_expression.identifier(), out);
    } else if (primary_expression.has_expression_list()) {
        ExpressionListToCpp2(primary_expression.expression_list(), out);
    } else if (primary_expression.has_id_expression()) {
        IdExpressionToCpp2(primary_expression.id_expression(), out);
    } else if (primary_expression.has_declaration()) {
        DeclarationToCpp2(primary_expression.declaration(), out);
    } else if (primary_expression.has_inspect()) {
        InspectExpressionToCpp2(primary_expression.inspect(), out);
    } else if (primary_expression.has_literal()) {
        LiteralToCpp2(primary_expression.literal(), out);
    }
}

void PrefixExpressionToCpp2(const fuzzing::prefix_expression_node& prefix_expression, std::ostream& out) { 
    TokenToCpp2(prefix_expression.literal(), out);
    PostfixExpressionToCpp2(prefix_expression.suffix(), out);
}

void IsAsExpressionToCpp2(const fuzzing::is_as_expression_node& is_as_expression, std::ostream& out) {
    PrefixExpressionToCpp2(is_as_expression.expr(), out);
    
    for (const auto& term : is_as_expression.ops()) {
        if (term.has_op()) {
            TokenToCpp2(term.op(), out);//these have been left as if-statements for a bootleg switch-case-like thing, but they could be removed *probably*. 
        }
        if (term.has_type()) {
            TypeToCpp2(term.type(), out);
        }
        if (term.has_expr()) {
            ExpressionToCpp2(term.expr(), out);
        }
    }
}


void MultiplicativeExpressionToCpp2(const fuzzing::multiplicative_expression_node& multiplicative_expression, std::ostream& out) { 
    IsAsExpressionToCpp2(multiplicative_expression.expr(), out);
    
    for (const auto& term : multiplicative_expression.terms()) {
        if (term.has_op()) {
            TokenToCpp2(term.op(), out);
        }
        if (term.has_expr()) {
            IsAsExpressionToCpp2(term.expr(), out);
        }
    }
}


void AdditiveExpressionToCpp2(const fuzzing::additive_expression_node& additive_expression, std::ostream& out) { 
    MultiplicativeExpressionToCpp2(additive_expression.expr(), out);
    
    for (const auto& term : additive_expression.terms()) {
        if (term.has_op()) {
            TokenToCpp2(term.op(), out);
        }
        if (term.has_expr()) {
            MultiplicativeExpressionToCpp2(term.expr(), out);
        }
    }
}

void ShiftExpressionToCpp2(const fuzzing::shift_expression_node& shift_expression, std::ostream& out) { 
    AdditiveExpressionToCpp2(shift_expression.expr(), out);
    
    for (const auto& term : shift_expression.terms()) {
        if (term.has_op()) {
            TokenToCpp2(term.op(), out);
        }
        if (term.has_expr()) {
            AdditiveExpressionToCpp2(term.expr(), out);
        }
    }
}

void CompareExpressionToCpp2(const fuzzing::compare_expression_node& compare_expression, std::ostream& out) { 
    ShiftExpressionToCpp2(compare_expression.expr(), out);
    
    for (const auto& term : compare_expression.terms()) {
        if (term.has_op()) {
            TokenToCpp2(term.op(), out);
        }
        if (term.has_expr()) {
            ShiftExpressionToCpp2(term.expr(), out);
        }
    }
}

void RelationalExpressionToCpp2(const fuzzing::relational_expression_node& relational_expression, std::ostream& out) { 
    CompareExpressionToCpp2(relational_expression.expr(), out);
    
    for (const auto& term : relational_expression.terms()) {
        if (term.has_op()) {
            TokenToCpp2(term.op(), out);
        }
        if (term.has_expr()) {
            CompareExpressionToCpp2(term.expr(), out);
        }
    }
}

void EqualityExpressionToCpp2(const fuzzing::equality_expression_node& equality_expression, std::ostream& out) { 
    RelationalExpressionToCpp2(equality_expression.expr(), out);
    
    for (const auto& term : equality_expression.terms()) {
        if (term.has_op()) {
            TokenToCpp2(term.op(), out);
        }
        if (term.has_expr()) {
            RelationalExpressionToCpp2(term.expr(), out);
        }
    }
}

void BitAndExpressionToCpp2(const fuzzing::bit_and_expression_node& bit_and_expression, std::ostream& out) { 
    EqualityExpressionToCpp2(bit_and_expression.expr(), out);
    
    for (const auto& term : bit_and_expression.terms()) {
        if (term.has_op()) {
            TokenToCpp2(term.op(), out);
        }
        if (term.has_expr()) {
            EqualityExpressionToCpp2(term.expr(), out);
        }
    }
}

void BitXorExpressionToCpp2(const fuzzing::bit_xor_expression_node& bit_xor_expression, std::ostream& out) { 
    BitAndExpressionToCpp2(bit_xor_expression.expr(), out);
    
    for (const auto& term : bit_xor_expression.terms()) {
        if (term.has_op()) {
            TokenToCpp2(term.op(), out);
        }
        if (term.has_expr()) {
            BitAndExpressionToCpp2(term.expr(), out);
        }
    }
}

void BitOrExpressionToCpp2(const fuzzing::bit_or_expression_node& bit_or_expression, std::ostream& out) { 
    BitXorExpressionToCpp2(bit_or_expression.expr(), out);
    
    for (const auto& term : bit_or_expression.terms()) {
        if (term.has_op()) {
            TokenToCpp2(term.op(), out);
        }
        if (term.has_expr()) {
            BitXorExpressionToCpp2(term.expr(), out);
        }
    }
}

void LogicalAndExpressionToCpp2(const fuzzing::logical_and_expression_node& logical_and_expression, std::ostream& out) { 
    BitOrExpressionToCpp2(logical_and_expression.expr(), out);
    
    for (const auto& term : logical_and_expression.terms()) {
        if (term.has_op()) {
            TokenToCpp2(term.op(), out);
        }
        if (term.has_expr()) {
            BitOrExpressionToCpp2(term.expr(), out);
        }
    }
}

void LogicalOrExpressionToCpp2(const fuzzing::logical_or_expression_node& logical_or_expression, std::ostream& out) { 
    LogicalAndExpressionToCpp2(logical_or_expression.expr(), out);
    
    for (const auto& term : logical_or_expression.terms()) {
        if (term.has_op()) {
            TokenToCpp2(term.op(), out);
        }
        if (term.has_expr()) {
            LogicalAndExpressionToCpp2(term.expr(), out);
        }
    }
}

void AssignmentExpressionToCpp2(const fuzzing::assignment_expression_node& assignment_expression, std::ostream& out) { 
    LogicalOrExpressionToCpp2(assignment_expression.expr(), out);
    
    for (const auto& term : assignment_expression.terms()) {
        if (term.has_op()) {
            TokenToCpp2(term.op(), out);
        }
        if (term.has_expr()) {
            LogicalOrExpressionToCpp2(term.expr(), out);
        }
    }
}

void ExpressionToCpp2(const fuzzing::expression_node& expression, std::ostream& out);

void ExpressionListToCpp2(const fuzzing::expression_list_node& expression_list, std::ostream& out);

void ExpressionStatementToCpp2(const fuzzing::expression_statement_node& expression_statement, std::ostream& out);

void CaptureToCpp2(const fuzzing::capture& capture, std::ostream& out);

void CaptureGroupToCpp2(const fuzzing::capture_group& capture_group, std::ostream& out);

void PostfixExpressionToCpp2(const fuzzing::postfix_expression_node& postfix_expression, std::ostream& out);

void UnqualifiedIdToCpp2(const fuzzing::unqualified_id_node& unqualified_id, std::ostream& out);

void QualifiedIdToCpp2(const fuzzing::qualified_id_node& qualified_id, std::ostream& out);

void TypeIdToCpp2(const fuzzing::type_id_node& type_id, std::ostream& out);

void IdExpressionToCpp2(const fuzzing::id_expression_node& id_expression, std::ostream& out);

void CompoundStatementToCpp2(const fuzzing::compound_statement_node& compound_statement, std::ostream& out);

void SelectionStatementToCpp2(const fuzzing::selection_statement_node& selection_statement, std::ostream& out);

void IterationStatementToCpp2(const fuzzing::iteration_statement_node& iteration_statement, std::ostream& out);

void ReturnStatementToCpp2(const fuzzing::return_statement_node& return_statement, std::ostream& out);

void AlternativeToCpp2(const fuzzing::alternative_node& alternative, std::ostream& out);

void InspectExpressionToCpp2(const fuzzing::inspect_expression_node& inspect_expression, std::ostream& out);

void ContractToCpp2(const fuzzing::contract_node& contract, std::ostream& out);

void JumpToCpp2(const fuzzing::jump_statement_node& jump_statement, std::ostream& out);

void StatementToCpp2(const fuzzing::statement_node& statement, std::ostream& out);

void ParameterDeclarationNodeToCpp2(const fuzzing::parameter_declaration_node& parameter_declaration, std::ostream& out);

void ParameterDeclarationListToCpp2(const fuzzing::parameter_declaration_list_node& parameter_declaration_list, std::ostream& out);

void FunctionTypeToCpp2(const fuzzing::function_type_node& function_type, std::ostream& out);

void AliasToCpp2(const fuzzing::alias_node& alias, std::ostream& out);

void DeclarationToCpp2(const fuzzing::declaration_node& declaration, std::ostream& out);

void TranslationUnitToCpp2(const fuzzing::translation_unit_node& translation_unit, std::ostream& out);

} // namespace cpp2

// #endif // __CPP2_FUZZING_PROTO_TO_CPP2
