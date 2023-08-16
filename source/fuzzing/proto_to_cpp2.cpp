#include "proto_to_cpp2.h"
#include "source/parse.h"
#include "source/fuzzing/cpp2.pb.h" 
#include <ostream>

namespace cpp2 {

class ListSeparator {
  bool first = true;
  std::string sep_;
 
public:
  ListSeparator(std::string sep = ", ") : sep_(sep) {}
  friend std::ostream& operator<<(std::ostream& os, ListSeparator& sep) {
    if (sep.first) {
      sep.first = false;
    } else {
        os << sep.sep_; 
    }
    return os;
  }
};

// void TokenToCpp2(const fuzzing::token& token, std::ostream& out) {
//     out << token.value();
// }

// void TokenToCpp2(const fuzzing::token& token, std::ostream& out) {
//     const std::string& value = token.value();
//     if (value == ", " || value == ": " || value == ";") {
//         out << value;
//     } else {
//         out << token.value();
//     }
// }

bool debug_colon = true;
// bool debug_colon = false;

bool IsAssignmentOperator(const std::string& value) { 
    return value == "=" || value == "*="  || value == "/="  || value == "%="  || 
    value == "+=" || value ==  "-=" || value ==  ">>=" || value ==  "<<=" || value ==  "&=" || 
    value ==  "^="  || value == "|=";
}

bool IsPostfixOperator(const std::string& value) { 
    return value == "++" || value == "--" || value == "*" || value == "&" || value == "~" || value == "$";
}

bool IsPrefixOperator(const std::string& value) { 
    return value == "!" || value == "-" || value == "+";
}

bool IsLogicalOperator(const std::string& value) {
    return value == "&&" || value == "||";
}

bool IsMathOperator(const std::string& value) {
    return value == "<=" || value == ">=" || value == "==" || value == "!=" ||
           value == "+" || value == "-" || value == "/";
        //    || value == "*" MAKES PROBLEMS WITH POINTERS - what to do with multiplication? 
}

void TokenToCpp2(const fuzzing::token& token, std::ostream& out) {
    const std::string& value = token.value();
    if (IsLogicalOperator(value) || IsMathOperator(value)) {
        out << " " << value << " ";
    } else {
        out << token.value();
    }
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
    TokenToCpp2(namespace_.namespace_(), out);
}

void PrimaryExpressionToCpp2(const fuzzing::primary_expression_node& primary_expression, std::ostream& out) {
    //TODO: make into switch case; do so for other if-else PODs. 
    if (primary_expression.has_identifier()) {
        TokenToCpp2(primary_expression.identifier(), out);
    } else if (primary_expression.has_expression_list()) {
        if(!primary_expression.expression_list().expressions().empty()) { 
            TokenToCpp2(primary_expression.expression_list().open_paren(), out); 
            // out << "(";
            ExpressionListToCpp2(primary_expression.expression_list(), out);
            TokenToCpp2(primary_expression.expression_list().close_paren(), out);
            // out << ")";
        }
        else { 
            out << "()"; //This should be correct
        } 
    } else if (primary_expression.has_id_expression()) {
        IdExpressionToCpp2(primary_expression.id_expression(), out);
    } else if (primary_expression.has_declaration()) {
        DeclarationToCpp2(primary_expression.declaration(), false, out);
    } else if (primary_expression.has_inspect()) {
        InspectExpressionToCpp2(primary_expression.inspect(), out);
    } else if (primary_expression.has_literal()) {
        LiteralToCpp2(primary_expression.literal(), out);
    }
}

void PrefixExpressionToCpp2(const fuzzing::prefix_expression_node& prefix_expression, std::ostream& out) { 
    for (const auto& op : prefix_expression.ops()) {
        TokenToCpp2(op, out);
    }
    
    PostfixExpressionToCpp2(prefix_expression.expr_prefix(), out);
}

void IsAsExpressionToCpp2(const fuzzing::is_as_expression_node& is_as_expression, std::ostream& out) {
    // if (is_as_expression.has_expr_is_as()) {
    //     PrefixExpressionToCpp2(is_as_expression.expr_is_as(), out);
    // }
    PrefixExpressionToCpp2(is_as_expression.expr_is_as(), out);
    for (const auto& term : is_as_expression.ops()) {
        //TODO: make into switch case. 
        if (term.has_op()) {
            out << " ";
            TokenToCpp2(term.op(), out);//these have been left as if-statements for a bootleg switch-case-like thing, but they could be removed *probably*. 
            out << " "; 
        }
        if (term.has_type()) {
            TypeIdToCpp2(term.type(), out);
        }
        if (term.has_expr()) {
            ExpressionToCpp2(term.expr(), out);
        }
    }
}


void MultiplicativeExpressionToCpp2(const fuzzing::multiplicative_expression_node& multiplicative_expression, std::ostream& out) { 
    IsAsExpressionToCpp2(multiplicative_expression.expr_multiplicative(), out);
    
    for (const auto& term : multiplicative_expression.terms()) {
        if (term.has_op()) {
            out << " "; 
            TokenToCpp2(term.op(), out);
            out << " "; 
        }
        if (term.has_expr()) {
            IsAsExpressionToCpp2(term.expr(), out);
        }
    }
}


void AdditiveExpressionToCpp2(const fuzzing::additive_expression_node& additive_expression, std::ostream& out) { 
    MultiplicativeExpressionToCpp2(additive_expression.expr_additive(), out);
    
    for (const auto& term : additive_expression.terms()) {
        if (term.has_op()) {
            // out << " "; //not necessary with modifications to token; to be reviewed. 
            TokenToCpp2(term.op(), out);
            // out << " ";
        }
        if (term.has_expr()) {
            MultiplicativeExpressionToCpp2(term.expr(), out);
        }
    }
}

void ShiftExpressionToCpp2(const fuzzing::shift_expression_node& shift_expression, std::ostream& out) { 
    AdditiveExpressionToCpp2(shift_expression.expr_shift(), out);
    
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
    ShiftExpressionToCpp2(compare_expression.expr_compare(), out);
    
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
    CompareExpressionToCpp2(relational_expression.expr_relational(), out);
    
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
    RelationalExpressionToCpp2(equality_expression.expr_equality(), out);
    
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
    EqualityExpressionToCpp2(bit_and_expression.expr_bit_and(), out);
    
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
    BitAndExpressionToCpp2(bit_xor_expression.expr_bit_xor(), out);
    
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
    BitXorExpressionToCpp2(bit_or_expression.expr_bit_or(), out);
    
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
    BitOrExpressionToCpp2(logical_and_expression.expr_logical_and(), out);
    
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
    LogicalAndExpressionToCpp2(logical_or_expression.expr_logical_or(), out);
    
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
    LogicalOrExpressionToCpp2(assignment_expression.expr_assignment(), out);
    for (const auto& term : assignment_expression.terms()) {
        if (term.has_op()) {
            TokenToCpp2(term.op(), out);
            // out << "\n";
        }
        // out << "\n";
        if (term.has_expr()) {
            LogicalOrExpressionToCpp2(term.expr(), out);
        }
    }
}

void ExpressionToCpp2(const fuzzing::expression_node& expression, std::ostream& out) { 
    AssignmentExpressionToCpp2(expression.expr_expression(), out);
}

auto ProtoToPassingStyle(fuzzing::passing_style::en style_proto, 
    fuzzing::passing_style::en default_passing_style = fuzzing::passing_style::in) -> std::string_view {
    //TODO: Review this mess.
    if (style_proto == default_passing_style) { 
        return ""; 
    } 
    switch (style_proto) {
        case fuzzing::passing_style::in:
            return "in";
            
        case fuzzing::passing_style::copy:
            return "copy"; 

        case fuzzing::passing_style::inout:
            return "inout"; 

        case fuzzing::passing_style::out:
            return "out"; 

        case fuzzing::passing_style::move:
            return "move"; 

        case fuzzing::passing_style::forward:
            return "forward";

        case fuzzing::passing_style::invalid:            
        default: 
            return ""; 
    }
}

void ExpressionListToCpp2(const fuzzing::expression_list_node& expression_list, std::ostream& out) { 
    // TokenToCpp2(expression_list.open_paren(), out); 
    // TokenToCpp2(expression_list.close_paren(), out); 
    // // optional bool inside_initializer = 3; bool inside_initializer = expression_statement_proto.has_semicolon(); - not in the other one. 
    if(!expression_list.expressions().empty()) { 
        // out << "(";
        // TokenToCpp2(expression_list.open_paren(), out); 
        ListSeparator sep; 
        for (const auto& expression : expression_list.expressions()) {
            out << sep; 
            const auto passing_style = ProtoToPassingStyle(expression.pass(), fuzzing::passing_style::in);
            if(!passing_style.empty()) {
                // out << "(";
                out << passing_style << " "; 
            }
            if (expression.has_expr()) {
                ExpressionToCpp2(expression.expr(), out);
            }
            if(!passing_style.empty()) { 
                // out << ")";
            }
        }
        // out << ")";
        // TokenToCpp2(expression_list.close_paren(), out); 
    }
}

void CaptureToCpp2(const fuzzing::capture& capture, std::ostream& out) { 
    // PostfixExpressionToCpp2(capture.capture_expr(), out);
    //THIS HAS BEEN COMMENTED OUT FOR THE TIME BEING, PERHAPS INCORRECTLY - TODO: REVIEW!!!
    // The following is not in ast2proto, but perhaps it should be; REVIEW 
    // optional string cap_sym = 2;
    // optional string str = 3;
    // optional string str_suppressed_move = 4;
}

void CaptureGroupToCpp2(const fuzzing::capture_group& capture_group, std::ostream& out) { 
    for (const auto& member : capture_group.members()) {
        CaptureToCpp2(member, out);

    }
}

void PostfixExpressionToCpp2(const fuzzing::postfix_expression_node& postfix_expression, std::ostream& out) { 
    PrimaryExpressionToCpp2(postfix_expression.expr_postfix(), out); 
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
    if(!unqualified_id.template_args().empty()) {
        out << "<";
        ListSeparator sep; 
        for (const auto& id : unqualified_id.template_args()) {
            out << sep; 
            if (id.has_expression()) {
                ExpressionToCpp2(id.expression(), out);
            }
            if (id.has_type_id()) {
                TypeIdToCpp2(id.type_id(), out);
            }
        }
        out << ">";
    }

}

void QualifiedIdToCpp2(const fuzzing::qualified_id_node& qualified_id, std::ostream& out) { 
    for (const auto& id : qualified_id.ids()) {
        if (id.has_scope_op()) {
            TokenToCpp2(id.scope_op(), out);
        }
        if (id.has_id()) {
            UnqualifiedIdToCpp2(id.id(), out);
        }
    }
}

void IdExpressionToCpp2(const fuzzing::id_expression_node& id_expression, std::ostream& out) { 
    if (id_expression.has_qualified()) {
        QualifiedIdToCpp2(id_expression.qualified(), out);
    } else if (id_expression.has_unqualified()) {
        UnqualifiedIdToCpp2(id_expression.unqualified(), out);
    }
}

void SelectionStatementToCpp2(const fuzzing::selection_statement_node& selection_statement, std::ostream& out) { 
    // optional bool is_constexpr = 1; REVIEW
    // bool is_constexpr = selection_statement.is_constexpr(); 
    // if(is_constexpr) { 
    //     out << is_constexpr;
    // }
    TokenToCpp2(selection_statement.identifier(), out);
    out << " "; 
    LogicalOrExpressionToCpp2(selection_statement.expression(), out); 
    // out << ")";
    CompoundStatementToCpp2(selection_statement.true_branch(), out);
    if (selection_statement.has_false_branch()) { 
        out << " else "; 
        CompoundStatementToCpp2(selection_statement.false_branch(), out);
    } 
}

void IterationStatementToCpp2(const fuzzing::iteration_statement_node& iteration_statement, std::ostream& out) { 
    
    // std::cout << "***Iteration Statement Value***" << iteration_statement.identifier().value() << "\n"; 
    if(iteration_statement.identifier().value() == "for") { 
        out << "for "; 
        ExpressionToCpp2(iteration_statement.range(), out); 
        // out << "\n";
        if(iteration_statement.has_next_expression()) { 
            out << "\nnext "; 
            AssignmentExpressionToCpp2(iteration_statement.next_expression(), out); 
            out << "\n";
        }
        out << " do (";
        ParameterDeclarationNodeToCpp2(iteration_statement.parameter(), out); 
        out << ") \n";
        // out << ") {\n";
        StatementToCpp2(iteration_statement.body(), false, out); 
        // out << "}\n";
    } else if(iteration_statement.identifier().value() == "while") { 
        // label? 'while' logical-or-expression next-clause? compound-statement
        out << "while ";
        ExpressionToCpp2(iteration_statement.range(), out);
        // out << " "; 
        LogicalOrExpressionToCpp2(iteration_statement.condition(), out);
        if(iteration_statement.has_next_expression()) { 
            out << " next "; 
            AssignmentExpressionToCpp2(iteration_statement.next_expression(), out); 
            // out << "\n";
        }
        CompoundStatementToCpp2(iteration_statement.statements(), out);  
        out << "\n";

    } else if(iteration_statement.identifier().value() == "do") { 
        out << "do"; 
        ParameterDeclarationNodeToCpp2(iteration_statement.parameter(), out);
        LogicalOrExpressionToCpp2(iteration_statement.condition(), out); 
        CompoundStatementToCpp2(iteration_statement.statements(), out);  
        out << ") \n";
        // out << ") {\n";
        // out << "}\n";

    }
    // else{ 
    // //TODO: finish logic for while/do
    //    TokenToCpp2(iteration_statement.label(), out); 
    //     TokenToCpp2(iteration_statement.identifier(), out); 
    //     AssignmentExpressionToCpp2(iteration_statement.next_expression(), out); 
    //     LogicalOrExpressionToCpp2(iteration_statement.condition(), out); 
    //     CompoundStatementToCpp2(iteration_statement.statements(), out); 
    //     ExpressionToCpp2(iteration_statement.range(), out); 
    //     ParameterDeclarationNodeToCpp2(iteration_statement.parameter(), out); 
    //     StatementToCpp2(iteration_statement.body(), out); 
    // }
    // bool for_with_in = iteration_statement.for_with_in(); 
    // if(for_with_in) { 
    //     out << for_with_in; 
    // }
    // optional bool for_with_in = 9; - REVIEW
    // again with the set function or something of the sort :)
}

void AlternativeToCpp2(const fuzzing::alternative_node& alternative, std::ostream& out) { 
    UnqualifiedIdToCpp2(alternative.name(), out);
    TokenToCpp2(alternative.is_as_keyword(), out); 
    out << " "; 
    TypeIdToCpp2(alternative.type_id(), out); 
    PostfixExpressionToCpp2(alternative.value(), out);
    out << " = "; 

    StatementToCpp2(alternative.statement(), false, out); 
}

void InspectExpressionToCpp2(const fuzzing::inspect_expression_node& inspect_expression, std::ostream& out) { 
    // optional bool is_constexpr = 1; REVIEW
    bool is_constexpr = inspect_expression.is_constexpr(); 
    if(is_constexpr) { 
        out << is_constexpr; 
    }
    TokenToCpp2(inspect_expression.identifier(), out);
    out << " "; 
    ExpressionToCpp2(inspect_expression.expression(), out); 
    out << " -> ";
    TypeIdToCpp2(inspect_expression.result_type(), out); 
    ListSeparator sep; 
    out << " {"; 
    for (const auto& alternative : inspect_expression.alternatives()) {
        out << "    "; //indent may be unnecessary, but who knows? 
        AlternativeToCpp2(alternative, out);
        // out << sep; 
        out << " "; 
    }
    out << "}"; 
}

void ContractToCpp2(const fuzzing::contract_node& contract, std::ostream& out) { 
    CaptureGroupToCpp2(contract.captures(), out); 
    TokenToCpp2(contract.kind(), out); 
    out << " "; 
    IdExpressionToCpp2(contract.group(), out); 
    out << ": "; 
    LogicalOrExpressionToCpp2(contract.condition(), out); 
    if(contract.has_message()) {
    out << ", ";//this might be wrong. 
    TokenToCpp2(contract.message(), out); 
    }    
}
    

void JumpToCpp2(const fuzzing::jump_statement_node& jump_statement, std::ostream& out) { 
    TokenToCpp2(jump_statement.keyword(), out);
    TokenToCpp2(jump_statement.label(), out);
    //semicolons pls
}

auto ProtoToModifier(const fuzzing::parameter_declaration_node::modifier mod) -> std::string_view {
    switch (mod) {
        case fuzzing::parameter_declaration_node::none:
            return "";
        case fuzzing::parameter_declaration_node::implicit:
            return "implicit";
        case fuzzing::parameter_declaration_node::virtual_:
            return "virtual";
        case fuzzing::parameter_declaration_node::override_:
            return "override";
        case fuzzing::parameter_declaration_node::final_:
            return "final";
        default:
            return ""; 
    }
    // return "";
}

void ParameterDeclarationNodeToCpp2(const fuzzing::parameter_declaration_node& parameter_declaration, std::ostream& out) { 
    // optional modifier mod = 3;
    // modifier mod = parameter_declaration.mod();
    // if(mod) { 
    //     out << mod; 
    // }
    //make enum work, probably with ChadGPT
    // ModifierToProto(parameter_declaration.mod(), out); 
    const auto passing_style = ProtoToPassingStyle(parameter_declaration.pass(), fuzzing::passing_style::in);
    if(!passing_style.empty()) {
        out << passing_style << " "; 
    }
    DeclarationToCpp2(parameter_declaration.declaration(), true, out); 
}

void ParameterDeclarationListToCpp2(const fuzzing::parameter_declaration_list_node& parameter_declaration_list, std::ostream& out) { 
    TokenToCpp2(parameter_declaration_list.open_paren(), out); 
     
    ListSeparator sep; 
    for (const auto& parameter : parameter_declaration_list.parameters()) {
        out << sep; 
        ParameterDeclarationNodeToCpp2(parameter, out);
    }
    TokenToCpp2(parameter_declaration_list.close_paren(), out);
}

void FunctionTypeToCpp2(const fuzzing::function_type_node& function_type, std::ostream& out) { 
    ParameterDeclarationListToCpp2(function_type.parameters(), out); 
    if(function_type.throws()) { 
        out << " throws"; 
    }
    switch (function_type.returns_case()) {
        case fuzzing::function_type_node::kId:{
            out << " -> ";
            const auto passing_style = ProtoToPassingStyle(function_type.id().pass(), fuzzing::passing_style::move);
            if(!passing_style.empty()) {
                out << passing_style << " "; 
            }
            TypeIdToCpp2(function_type.id().type(), out); 
        } break;
        case fuzzing::function_type_node::kList:
            out << " -> ";
            ParameterDeclarationListToCpp2(function_type.list(), out);
            break;
        case fuzzing::function_type_node::RETURNS_NOT_SET: 
            //FIGURE SOMETHING OUT
            break;
    }
    // out << "\n";
    for (const auto& contract : function_type.contracts()) {
        out << "[[";
        ContractToCpp2(contract, out);
        out << "]]";
    }

}

void AliasToCpp2(const fuzzing::alias_node& alias, std::ostream& out) { 
    TokenToCpp2(alias.type(), out); 
    if (alias.has_a_type()) {
        out << " == ";
        TypeIdToCpp2(alias.a_type(), out);
        out << ";\n"; 
    } else if (alias.has_a_namespace()) {
        IdExpressionToCpp2(alias.a_namespace(), out);
    } else if (alias.has_an_object()) {
        ExpressionToCpp2(alias.an_object(), out);

    } 
}

void DeclarationToCpp2(const fuzzing::declaration_node& declaration, bool is_parameter, std::ostream& out) { 
    CaptureGroupToCpp2(declaration.captures(), out); 
    // std::cout << "***DeclarationToCpp2 - Identifier: " << declaration.identifier() << "*** \n";
    bool colon = true; 
    UnqualifiedIdToCpp2(declaration.identifier(), out); 
    ParameterDeclarationListToCpp2(declaration.template_parameters(), out); 
    if (declaration.identifier().identifier().value() != "this" &&  
        declaration.identifier().identifier().value() != "that" && 
        declaration.identifier().identifier().value() != "_") { 
        out << ": ";//move
        for (const auto& meta_function : declaration.meta_functions()) {
            out << "@";
            IdExpressionToCpp2(meta_function, out);
            out << " "; 
        } 
        if (declaration.has_a_function()) {
            FunctionTypeToCpp2(declaration.a_function(), out);
            colon = false;
        } else if (declaration.has_an_object()) {
            //This bit specifically needs a lot of work and is responsible for a lot of failed semicolons. 
            TypeIdToCpp2(declaration.an_object(), out);
            colon = !is_parameter;  
        } else if (declaration.has_a_type()) {
            // colon = false; 
            TypeToCpp2(declaration.a_type(), out);
        } else if (declaration.has_a_namespace()) {
            NameToCpp2(declaration.a_namespace(), out);
        } else if (declaration.has_an_alias()) {
            AliasToCpp2(declaration.an_alias(), out);
        } 
    }
    ExpressionToCpp2(declaration.requires_clause_expression(), out);
    if (declaration.has_initializer()) { 
        out << " = ";
        colon = false; 
        StatementToCpp2(declaration.initializer(), declaration.has_a_function(), out); 
    } 
    if (colon) { 
        if (debug_colon) { 
            out << ";//DECLARATION\n";
        }
        else { 
            out << ";\n";
        }
    }
}

void TranslationUnitToCpp2(const fuzzing::translation_unit_node& translation_unit, std::ostream& out) { 
    // ListSeparator sep; 
    for (const auto& declaration : translation_unit.declarations()) {
        DeclarationToCpp2(declaration, false, out);
        // out << sep;
    }
}

void ExpressionStatementToCpp2(const fuzzing::expression_statement_node& expression_statement, 
    bool is_function_initializer, std::ostream& out) { 
    if(expression_statement.has_expr_statement()) { 
        ExpressionToCpp2(expression_statement.expr_statement(), out);
    } 
    bool has_semicolon = expression_statement.has_semicolon();
    if (has_semicolon && !is_function_initializer) {
        if (debug_colon) { 
            out << ";//EXPRESSIONSTATEMENT\n";     
        } else {
            out << ";\n"; 
        }
    } else {
        out << "\n";
    }
}

void StatementToCpp2(const fuzzing::statement_node& statement, bool is_function_initializer, std::ostream& out) { 
    ParameterDeclarationListToCpp2(statement.parameters(), out);
    if (statement.has_expression()) {
        ExpressionStatementToCpp2(statement.expression(), is_function_initializer, out);
        // bool has_semicolon = statement.expression().has_semicolon();
        // if (has_semicolon) {//moved to experiment with avoiding double semicolons as in mised-function-expression-and-std-for-each. 
        //     out << ";//EXPRESSIONSTATEMENT\n";   
        // }
    } else if (statement.has_compound()) {
        CompoundStatementToCpp2(statement.compound(), out);
    } else if (statement.has_selection()) {
        SelectionStatementToCpp2(statement.selection(), out);
    } else if (statement.has_declaration()) {
        DeclarationToCpp2(statement.declaration(), false, out);
    } else if (statement.has_return_()) {
        ReturnStatementToCpp2(statement.return_(), out);
    } else if (statement.has_iteration()) {
        IterationStatementToCpp2(statement.iteration(), out);
    } else if (statement.has_contract()) {
        out << "[[";
        ContractToCpp2(statement.contract(), out);
        out << "]]";//2 sets of square braces good? 
    } else if (statement.has_inspect()) {
        InspectExpressionToCpp2(statement.inspect(), out);
    } else if (statement.has_jump()) {
        JumpToCpp2(statement.jump(), out);
    }
    // if (!statement.has_parameters() && !statement.has_expression() && 
    //     !statement.has_compound() && !statement.has_selection() && 
    //     !statement.has_return_() && !statement.has_contract() && 
    //     !statement.has_inspect() && !statement.has_jump()) {
    //         out << ";\n"; 
    //     }
    // bool emitted = statement.emitted();
}

void ReturnStatementToCpp2(const fuzzing::return_statement_node& return_statement, std::ostream& out) { 
    TokenToCpp2(return_statement.identifier(), out);
    if(return_statement.has_expression()) { 
        out << " "; 
        ExpressionToCpp2(return_statement.expression(), out); 
    }
    if (debug_colon) {
        out << ";//RETURN\n";
    }// 
    else { 
        out << ";\n";  
    }
    // ><> fish (very important)
}

void TypeIdToCpp2(const fuzzing::type_id_node& type_id, std::ostream& out) { 
    for (const auto& pc_qualifier : type_id.pc_qualifiers()) {
        TokenToCpp2(pc_qualifier, out); 
        out << " ";
    }
    TokenToCpp2(type_id.address_of(), out);
    TokenToCpp2(type_id.dereference_of(), out);
    if (type_id.has_dereference_cnt()) {
        // out << ":=";
        // TokenToCpp2(type_id.dereference_cnt, out);
    }

   if (type_id.has_qualified()) {
        QualifiedIdToCpp2(type_id.qualified(), out);
    } else if (type_id.has_unqualified()) {
        UnqualifiedIdToCpp2(type_id.unqualified(), out);
        // out << ";\n";//NOT WORKING. 
    } else if (type_id.has_keyword()) {
        TokenToCpp2(type_id.keyword(), out);
    } 
}

void CompoundStatementToCpp2(const fuzzing::compound_statement_node& compound_statement, std::ostream& out) { 
    out << "{\n";
    for (const auto& statement : compound_statement.statements()) {
        out << "    "; //indent may be unnecessary, but who knows? 
        StatementToCpp2(statement, false, out);
    }
    out << "}\n";
    //Is this necessary? 
    int32_t body_indent = compound_statement.body_indent();
    for (int i = 0; i <= body_indent; i++) { 
    }
}

} // namespace cpp2

// #endif // __CPP2_FUZZING_PROTO_TO_CPP2