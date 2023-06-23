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

void ExpressionToCpp2(const fuzzing::expression_node& expression, std::ostream& out) { 
    AssignmentExpressionToCpp2(expression.expr(), out);
}


//FOR REVIEW
void ExpressionListToCpp2(const fuzzing::expression_list_node& expression_list, std::ostream& out) { 
    TokenToCpp2(expression_list.open_paren(), out); 
    TokenToCpp2(expression_list.close_paren(), out); 
    // optional bool inside_initializer = 3; 
    for (const auto& expression : expression_list.expressions()) {
        if (expression.has_pass()) {
            // PassToCpp2(expression.pass(), out);
            //make
        }
        if (expression.has_expr()) {
            ExpressionToCpp2(expression.expr(), out);
        }
    }
}

void ExpressionStatementToCpp2(const fuzzing::expression_statement_node& expression_statement, std::ostream& out) { 
    ExpressionToCpp2(expression_statement.expr(), out);
    //optional bool has_semicolon = 2; 
}

void CaptureToCpp2(const fuzzing::capture& capture, std::ostream& out) { 
    PostfixExpressionToCpp2(capture.capture_expr(), out);
    // optional string cap_sym = 2;
    // optional string str = 3;
    // optional string str_suppressed_move = 4;
}

void CaptureGroupToCpp2(const fuzzing::capture_group& capture_group, std::ostream& out) { 
    for (const auto& member : capture_group.members()) {
        CaptureToCpp2(member.member(), out);

    }
}

void PostfixExpressionToCpp2(const fuzzing::postfix_expression_node& postfix_expression, std::ostream& out) { 
    PrimaryExpressionToCpp2(postfix_expression.expr(), out); 
    for (const auto& op : postfix_expression.ops()) {
        if (op.has_op()) {
            TokenToCpp2(op.op(), out);
        }
        if (op.has_id_expr()) {
            IdExpressionToCpp2(op.id_expr(), out);
        }
        if (op.has_expr_list()) {
            ExpressionListToCpp2(op.expr_list(), out);
        }
        if (op.has_op_close()) {
            TokenToCpp2(op.op_close(), out);
        }
    }
    CaptureGroupToCpp2(postfix_expression.cap_grp(), out);
}

void UnqualifiedIdToCpp2(const fuzzing::unqualified_id_node& unqualified_id, std::ostream& out) { 
    TokenToCpp2(unqualified_id.identifier(), out); 
    for (const auto& id : unqualified_id.ids()) {
        if (id.has_expression()) {
            ExpressionToCpp2(id.expression(), out);
        }
        if (id.has_type_id()) {
            TypeIdToCpp2(id.type_id(), out);
        }
    }
    //correct to use template_args  as in proto file
}

void QualifiedIdToCpp2(const fuzzing::qualified_id_node& qualified_id, std::ostream& out) { 
    for (const auto& id : qualified_id.ids()) {
        if (id.has_scope_op()) {
            TokenToCpp2(id.scope_op (), out);
        }
        if (id.has_id()) {
            UnqualifiedIdToCpp2(id.id(), out);
        }
    }
}

void TypeIdToCpp2(const fuzzing::type_id_node& type_id, std::ostream& out) { 
    for (const auto& pc_qualifier : type_id.pc_qualifiers()) {
        TokenToCpp2(pc_qualifier.pc_qualifier(), out);
        //make sure this is coprrect. 
    }
    TokenToCpp2(type_id.address_of(), out);
    TokenToCpp2(type_id.dereference_of(), out);
    // optional int32 dereference_cnt = 5;
    TokenToCpp2(type_id.suspicious_initialization(), out);

   //TODO: MAKE THE ONEOF WORK, PROBABLY WITH SWITCH CASE 
    // oneof id { 
    //     qualified_id_node qualified = 7;
    //     unqualified_id_node unqualified = 8;
    //     token keyword = 9; 
    // }
}

void IdExpressionToCpp2(const fuzzing::id_expression_node& id_expression, std::ostream& out) { 
    // oneof id { 
    //     qualified_id_node qualified = 2;
    //     unqualified_id_node unqualified = 3;
    // }
    // // make the oneof work, again with a switch case
}

void CompoundStatementToCpp2(const fuzzing::compound_statement_node& compound_statement, std::ostream& out) { 
    for (const auto& statement : compound_statement.statement()) {
        StatementToCpp2(statement.statement(), out);
        //make sure this is coprrect - the statement.statement bit in particular
    }
    // optional int32 body_indent - basic set conversion? 
}

void SelectionStatementToCpp2(const fuzzing::selection_statement_node& selection_statement, std::ostream& out) { 
    // optional bool is_constexpr = 1;
    TokenToCpp2(selection_statement.identifier(), out);
    LogicalOrExpressionToCpp2(selection_statement.expression(), out); 
    CompoundStatementToCpp2(selection_statement.true_branch(), out);
    CompoundStatementToCpp2(selection_statement.false_branch(), out);
    // optional bool has_source_false_branch = 7;
    // make bool setters throughout where appropriate 
}

void IterationStatementToCpp2(const fuzzing::iteration_statement_node& iteration_statement, std::ostream& out) { 
    TokenToCpp2(iteration_statement.label(), out); 
    TokenToCpp2(iteration_statement.identifier(), out); 
    AssignmentExpressionToCpp2(iteration_statement.next_expression(), out); 
    LogicalOrExpressionToCpp2(iteration_statement.condition(), out); 
    CompoundStatementToCpp2(iteration_statement.statements(), out); 
    ExpressionToCpp2(iteration_statement.range(), out); 
    ParameterDeclarationNodeToCpp2(iteration_statement.parameter(), out); 
    StatementToCpp2(iteration_statement.body(), out); 
    // optional bool for_with_in = 9;
    // again with the set function or something of the sort :)
}

void ReturnStatementToCpp2(const fuzzing::return_statement_node& return_statement, std::ostream& out) { 
    TokenToCpp2(return_statement.identifier(), out);
    ExpressionToCpp2(return_statement.expression(), out); 
}

void AlternativeToCpp2(const fuzzing::alternative_node& alternative, std::ostream& out) { 
    UnqualifiedIdToCpp2(alternative.name(), out);
    TokenToCpp2(alternative.name(), out); 
    TypeIdToCpp2(alternative.type_id(), out); 
    PostfixExpressionToCpp2(alternative.value(), out);
    StatementToCpp2(alternative.statement(), out); 
}

void InspectExpressionToCpp2(const fuzzing::inspect_expression_node& inspect_expression, std::ostream& out) { 
    // optional bool is_constexpr = 1;
    TokenToCpp2(inspect_expression.identifier(), out);
    ExpressionToCpp2(inspect_expression.expression(), out); 
    TypeIdToCpp2(inspect_expression.result_type(), out); 

    for (const auto& alternative : inspect_expression.alternatives()) {
        AlternativeToCpp2(alternative.alternative(), out);
        //make sure this is coprrect, as with all for-loops for repeated singular terms. 
    }
}

void ContractToCpp2(const fuzzing::contract_node& contract, std::ostream& out) { 
    CaptureGroupToCpp2(contract.captures(), out); 
    TokenToCpp2(contract.kind(), out); 
    IdExpressionToCpp2(contract.group(), out); 
    LogicalOrExpressionToCpp2(contract.condition(), out); 
    TokenToCpp2(contract.message(), out); 
}

void JumpToCpp2(const fuzzing::jump_statement_node& jump_statement, std::ostream& out) { 
    TokenToCpp2(jump_statement.keyword(), out);
    TokenToCpp2(jump_statement.label(), out);
}

void StatementToCpp2(const fuzzing::statement_node& statement, std::ostream& out) { 
    ParameterDeclarationListToCpp2(statement.parameters(), out);
    if (statement.has_expression()) {
        ExpressionStatementToCpp2(statement.expression(), out);
    } else if (statement.has_compound()) {
        CompoundStatementToCpp2(statement.compound(), out);
    } else if (statement.has_selection()) {
        SelectionStatementToCpp2(statement.selection(), out);
    } else if (statement.has_declaration()) {
        DeclarationToCpp2(statement.declaration(), out);
    } else if (statement.has_return_()) {
        ReturnStatementToCpp2(statement.return_(), out);
    } else if (statement.has_iteration()) {
        IterationStatementToCpp2(statement.iteration(), out);
    } else if (statement.has_contract()) {
        ContractToCpp2(statement.contract(), out);
    } else if (statement.has_inspect()) {
        InspectExpressionToCpp2(statement.inspect(), out);
    } else if (statement.has_jump()) {
        JumpToCpp2(statement.jump(), out);
    }
    // optional bool emitted = 11;
}

void ParameterDeclarationNodeToCpp2(const fuzzing::parameter_declaration_node& parameter_declaration, std::ostream& out) { 
    // optional passing_style.en pass = 2;
    //make passing style

    // enum modifier { 
    //     none = 0;
    //     implicit = 1;
    //     virtual_ = 2;
    //     override_ = 3;
    //     final_ = 4;
    // }
    // optional modifier mod = 3;
    //make enum work, probably with ChadGPT

    DeclarationToCpp2(parameter_declaration.declaration(), out); 
}

void ParameterDeclarationListToCpp2(const fuzzing::parameter_declaration_list_node& parameter_declaration_list, std::ostream& out) { 
    TokenToCpp2(parameter_declaration_list.open_paren(), out); 
    TokenToCpp2(parameter_declaration_list.close_paren(), out); 
     
    for (const auto& parameter : parameter_declaration_list.parameters()) {
        ParameterDeclarationNodeToCpp2(parameter.parameter(), out);
        //make sure this is coprrect - the statement.statement bit in particular
    }
}

void FunctionTypeToCpp2(const fuzzing::function_type_node& function_type, std::ostream& out) { 
    DeclarationToCpp2(function_type.my_decl(), out); 
    ParameterDeclarationListToCpp2(function_type.parameters(), out); 
    // optional bool throws = 3;
    
    //in single_type_id message, which is broken in cpp2_to_proto also because single_type_id does not specify a type (FIX!)
    // this could be rearranged  in a structure where if the type is single_type_id, the case loads up both type_id_node and passing_style, and otherwise does the list_node? 

    TypeIdToCpp2(function_type.type(), out); 
    // optional passing_style.en pass = 2;
    //make passing_style to cpp2
    
    if (function_type.has_id()) {
    // TypeIdToCpp2(function_type.type(), out); 
    // // optional passing_style.en pass = 2;
        ExpressionStatementToCpp2(function_type.id(), out);
    } else if (function_type.has_id()) {
        ParameterDeclarationListToCpp2(function_type.id(), out);
    }

    for (const auto& contract : function_type.contracts()) {
        ContractToCpp2(contract.contract(), out);
        //make sure this is coprrect - the statement.statement bit in particular
    }

}

void AliasToCpp2(const fuzzing::alias_node& alias, std::ostream& out) { 
    TokenToCpp2(alias.type(), out); 

    if (alias.has_a_type()) {
        TypeIdToCpp2(alias.a_type(), out);
    } else if (alias.has_a_namespace()) {
        IdExpressionToCpp2(alias.a_namespace(), out);
    } else if (alias.has_an_object()) {
        ExpressionToCpp2(alias.an_object(), out);
    } 
}

void DeclarationToCpp2(const fuzzing::declaration_node& declaration, std::ostream& out) { 
    CaptureGroupToCpp2(declaration.captutres(), out); 
    UnqualifiedIdToCpp2(declaration.identifier(), out); 

    if (declaration.has_a_function()) {
        FunctionTypeToCpp2(declaration.a_function(), out);
    } else if (declaration.has_an_object()) {
        TypeIdToCpp2(declaration.an_object(), out);
    } else if (declaration.has_a_type()) {
        TypeToCpp2(declaration.a_type(), out);
    } else if (declaration.has_a_namespace()) {
        NameToCpp2(declaration.a_namespace(), out);
    } else if (declaration.has_an_alias()) {
        AliasToCpp2(declaration.an_alias(), out);
    } 

    for (const auto& meta_function : declaration.meta_function()) {
        IdExpressionToCpp2(meta_function.meta_function(), out);
        //make sure this is coprrect 
    }

    ParameterDeclarationListToCpp2(declaration.template_parameters(), out); 
    ExpressionToCpp2(declaration.requires_clause_expression(), out);
    StatementToCpp2(declaration.initializer(), out); 
    DeclarationToCpp2(declaration.parent_declaration(), out); 
}

void TranslationUnitToCpp2(const fuzzing::translation_unit_node& translation_unit, std::ostream& out) { 
    for (const auto& declaration : translation_unit.declaration()) {
        DeclarationToCpp2(declaration.declaration(), out);
        //make sure this is coprrect 
    }
}

} // namespace cpp2

// #endif // __CPP2_FUZZING_PROTO_TO_CPP2