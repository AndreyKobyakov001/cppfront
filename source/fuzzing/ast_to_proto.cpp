//this has something to do with the visitor

#include "ast_to_proto.h"
#include "source/fuzzing/cpp2.pb.h" 

namespace cpp2 {

//UNDER REVIEW
auto PassingStyleToProto(passing_style style) -> fuzzing::passing_style::en {
    switch (style) {
        case passing_style::in:
            return fuzzing::passing_style::in;
        case passing_style::copy:
            return fuzzing::passing_style::copy;
        case passing_style::inout:
            return fuzzing::passing_style::inout;
        case passing_style::out:
            return fuzzing::passing_style::out;
        case passing_style::move:
            return fuzzing::passing_style::move;
        case passing_style::forward:
            return fuzzing::passing_style::forward;
        case passing_style::invalid:
            return fuzzing::passing_style::invalid;
    }
    return fuzzing::passing_style::invalid;  // Default case
}

auto TokenToProto(const token& token) -> fuzzing::token {
    fuzzing::token token_proto;

    if (token.start != nullptr && token.count > 0) {
        token_proto.set_value(std::string{token.start, static_cast<unsigned>(token.count)});
    } 
    // else {
    //     token_proto.set_value("0");
    // }

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
    // for oneofs
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
    if (prefix_expression.expr != nullptr) {
        *prefix_expression_proto.mutable_expr() = PostfixExpressionToProto(*prefix_expression.expr);
    }
    return prefix_expression_proto;
}

//FOR REVIEW:

auto IsAsExpressionToProto(const is_as_expression_node& is_as_expression) -> fuzzing::is_as_expression_node {
    fuzzing::is_as_expression_node is_as_expression_proto;
    if (is_as_expression.expr != nullptr) { 
        *is_as_expression_proto.mutable_expr() = PrefixExpressionToProto(*is_as_expression.expr);
    }
    for (const auto& term : is_as_expression.ops) {
        auto& op_proto = *is_as_expression_proto.add_ops();
        if (term.op != nullptr) {
            *op_proto.mutable_op() = TokenToProto(*term.op);
        }
        if (term.type != nullptr) {
            *op_proto.mutable_type() = TypeIdToProto(*term.type);    
        }
        if (term.expr != nullptr) {
            *op_proto.mutable_expr() = ExpressionToProto(*term.expr); 
        }
        // *op_proto.mutable_op() = TokenToProto(*term.op);
        // *op_proto.mutable_type() = TypeIdToProto(*term.type);
        // *op_proto.mutable_expr() = ExpressionToProto(*term.expr);
    }

    return is_as_expression_proto;
}

auto MultiplicativeExpressionToProto(const multiplicative_expression_node& multiplicative_expression) -> fuzzing::multiplicative_expression_node {
    fuzzing::multiplicative_expression_node multiplicative_expression_proto;
    if (multiplicative_expression.expr != nullptr) { 
        *multiplicative_expression_proto.mutable_expr() = IsAsExpressionToProto(*multiplicative_expression.expr);
    }
    
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

//FOR REVIEW, 15/6/23

auto ExpressionToProto(const expression_node& expression) -> fuzzing::expression_node {
    fuzzing::expression_node expression_proto;
    if (expression.expr != nullptr) {
        *expression_proto.mutable_expr() = AssignmentExpressionToProto(*expression.expr);
    }
    return expression_proto;
}

auto ExpressionListToProto(const expression_list_node& expression_list) -> fuzzing::expression_list_node {
    fuzzing::expression_list_node expression_list_proto;
    *expression_list_proto.mutable_open_paren() = TokenToProto(*expression_list.open_paren);
    *expression_list_proto.mutable_close_paren() = TokenToProto(*expression_list.close_paren);
    // *expression_list_proto.mutable_inside_initializer = set_inside_initializer(*expression_list.inside_initializer); 
    // bool?
    for (const auto& term : expression_list.expressions) {
        auto term_proto = expression_list_proto.add_expressions();
        term_proto->set_pass(PassingStyleToProto(term.pass));
        *term_proto->mutable_expr() = ExpressionToProto(*term.expr);
    }
    return expression_list_proto;
}

auto ExpressionStatementToProto(const expression_statement_node& expression_statement) -> fuzzing::expression_statement_node {
    fuzzing::expression_statement_node expression_statement_proto;
    *expression_statement_proto.mutable_expr() = ExpressionToProto(*expression_statement.expr);
    expression_statement_proto.set_has_semicolon(expression_statement.has_semicolon);
    return expression_statement_proto;
}

auto CaptureToProto(const capture& capture) -> fuzzing::capture {
    fuzzing::capture capture_proto;
    *capture_proto.mutable_capture_expr() = PostfixExpressionToProto(*capture.capture_expr);
    return capture_proto;
}

auto CaptureGroupToProto(const capture_group& capture_group) -> fuzzing::capture_group {
    fuzzing::capture_group capture_group_proto;
    for(const auto& member : capture_group.members) { 
        *capture_group_proto.add_members() = CaptureToProto(member);
    }
    return capture_group_proto;
}

auto PostfixExpressionToProto(const postfix_expression_node& postfix_expression) -> fuzzing::postfix_expression_node {
    fuzzing::postfix_expression_node postfix_expression_proto;
    if (postfix_expression.expr != nullptr) {
        *postfix_expression_proto.mutable_expr() = PrimaryExpressionToProto(*postfix_expression.expr);
    }
    for (const auto& term : postfix_expression.ops) {
        auto term_proto = postfix_expression_proto.add_ops();
        if(term.op != nullptr) {
            *term_proto->mutable_op() = TokenToProto(*term.op);
        }
        if(term.id_expr != nullptr) {
            *term_proto->mutable_id_expr() = IdExpressionToProto(*term.id_expr);
        }
        if(term.expr_list != nullptr) {
            *term_proto->mutable_expr_list() = ExpressionListToProto(*term.expr_list);
        }
        if(term.op_close != nullptr) {
            *term_proto->mutable_op_close() = TokenToProto(*term.op_close);
        }
    }
    return postfix_expression_proto;
}

auto UnqualifiedIdToProto(const unqualified_id_node& unqualified_id) -> fuzzing::unqualified_id_node {
    fuzzing::unqualified_id_node unqualified_id_proto;
    if (unqualified_id.identifier != nullptr) {
        *unqualified_id_proto.mutable_identifier() = TokenToProto(*unqualified_id.identifier);
    }
    for (const auto& term : unqualified_id.template_args) {
        
        struct converter { 
            fuzzing::unqualified_id_node::term* s;
            explicit converter(fuzzing::unqualified_id_node::term& s_param): s(&s_param) {}
            void operator() (const std::monostate&) { }
            void operator() (const std::unique_ptr<expression_node>& e) { 
                if (e != nullptr) {
                    *s->mutable_expression() = ExpressionToProto(*e);
                }
            }
            void operator() (const std::unique_ptr<type_id_node>& e) { 
                if (e != nullptr) {
                    *s->mutable_type_id() = TypeIdToProto(*e);
                }
            }    
        };
        std::visit(converter(*unqualified_id_proto.add_template_args()), term.arg);
    }
    return unqualified_id_proto;
}

auto QualifiedIdToProto(const qualified_id_node& qualified_id) -> fuzzing::qualified_id_node {
    fuzzing::qualified_id_node qualified_id_proto;
    for (const auto& term : qualified_id.ids) {
        auto term_proto = qualified_id_proto.add_ids();
        if (term.scope_op != nullptr) {
             *term_proto->mutable_scope_op() = TokenToProto(*term.scope_op);
        }
        if (term.id != nullptr) {
        *term_proto->mutable_id() = UnqualifiedIdToProto(*term.id);
        }
    }
    return qualified_id_proto;
}

auto TypeIdToProto(const type_id_node& type_id) -> fuzzing::type_id_node {
    fuzzing::type_id_node type_id_proto;
    for (const auto& pc_qualifier : type_id.pc_qualifiers) {
        *type_id_proto.add_pc_qualifiers() = TokenToProto(*pc_qualifier);
    }
    if (type_id.address_of != nullptr) {
        *type_id_proto.mutable_address_of() = TokenToProto(*type_id.address_of);
    }
    if (type_id.dereference_of != nullptr) {
        *type_id_proto.mutable_dereference_of() = TokenToProto(*type_id.dereference_of);
    }
    type_id_proto.set_dereference_cnt(type_id.dereference_cnt); 
    

    if(type_id.suspicious_initialization != nullptr) {
    *type_id_proto.mutable_suspicious_initialization() = TokenToProto(*type_id.suspicious_initialization);
    }
    // const auto& e = type_id.id;
    struct converter {
        fuzzing::type_id_node* s;
        explicit converter(fuzzing::type_id_node& s_param): s(&s_param) {}

        void operator()(const std::monostate&) {
            
        }        
        void operator()(const std::unique_ptr<qualified_id_node>& e) {
            if (e != nullptr) { 
                *s->mutable_qualified() = QualifiedIdToProto(*e);
            }
        }
        void operator()(const std::unique_ptr<unqualified_id_node>& e) {
            if (e != nullptr) { 
                *s->mutable_unqualified() = UnqualifiedIdToProto(*e);
            }
        }
        void operator()(const token* e) {
            if (e != nullptr) { 
                *s->mutable_keyword() = TokenToProto(*e);
            }
        }
    };

    std::visit(converter(type_id_proto), type_id.id);
    return type_id_proto;
}


auto IdExpressionToProto(const id_expression_node& id_expression) -> fuzzing::id_expression_node {
    fuzzing::id_expression_node id_expression_proto;

    struct converter {
        fuzzing::id_expression_node* s;
        explicit converter(fuzzing::id_expression_node& s_param): s(&s_param) {}

        void operator()(const std::monostate&) { 
        } 
        void operator() (const std::unique_ptr<qualified_id_node>& e) {
            if(e != nullptr) {
                *s->mutable_qualified() = QualifiedIdToProto(*e);
            }

        } 
        void operator() (const std::unique_ptr<unqualified_id_node>& e) {
            if(e != nullptr) {
                *s->mutable_unqualified() = UnqualifiedIdToProto(*e);
            } 
        }
    };
    std::visit(converter(id_expression_proto), id_expression.id);
    return id_expression_proto;
}

auto CompoundStatementToProto(const compound_statement_node& compound_statement) -> fuzzing::compound_statement_node {
    fuzzing::compound_statement_node compound_statement_proto;
    for (const auto& statement : compound_statement.statements) {
        auto* statement_proto = compound_statement_proto.add_statements();
        *statement_proto = StatementToProto(*statement);
        // *compound_statement_proto.mutable_statements() = StatementToProto(*statement); --deprecated
    }
    compound_statement_proto.set_body_indent(compound_statement.body_indent);
    
    return compound_statement_proto;
}

auto SelectionStatementToProto(const selection_statement_node& selection_statement) -> fuzzing::selection_statement_node {
    fuzzing::selection_statement_node selection_statement_proto;
    selection_statement_proto.set_is_constexpr(selection_statement.is_constexpr);
    *selection_statement_proto.mutable_identifier() = TokenToProto(*selection_statement.identifier);
    *selection_statement_proto.mutable_expression() = LogicalOrExpressionToProto(*selection_statement.expression);
    *selection_statement_proto.mutable_true_branch() = CompoundStatementToProto(*selection_statement.true_branch);
    *selection_statement_proto.mutable_false_branch() = CompoundStatementToProto(*selection_statement.false_branch);
    selection_statement_proto.set_has_source_false_branch(selection_statement.has_source_false_branch);
    return selection_statement_proto;
}

auto IterationStatementToProto(const iteration_statement_node& iteration_statement) -> fuzzing::iteration_statement_node {
    fuzzing::iteration_statement_node iteration_statement_proto;
    if (iteration_statement.label != nullptr) {
        *iteration_statement_proto.mutable_label() = TokenToProto(*iteration_statement.label);
        }
    if (iteration_statement.identifier != nullptr) {
        *iteration_statement_proto.mutable_identifier() = TokenToProto(*iteration_statement.identifier);
        }
    if (iteration_statement.next_expression != nullptr) {
        *iteration_statement_proto.mutable_next_expression() = AssignmentExpressionToProto(*iteration_statement.next_expression);
        }
    if (iteration_statement.condition != nullptr) {
        *iteration_statement_proto.mutable_condition() = LogicalOrExpressionToProto(*iteration_statement.condition);
        }
    if (iteration_statement.statements != nullptr) {
        *iteration_statement_proto.mutable_statements() = CompoundStatementToProto(*iteration_statement.statements);
        }
    if (iteration_statement.range != nullptr) {
        *iteration_statement_proto.mutable_range() = ExpressionToProto(*iteration_statement.range);
        }
    if (iteration_statement.parameter != nullptr) {
        *iteration_statement_proto.mutable_parameter() = ParameterDeclarationToProto(*iteration_statement.parameter);
        }
    if (iteration_statement.body != nullptr) {
        *iteration_statement_proto.mutable_body() = StatementToProto(*iteration_statement.body);
        }
        iteration_statement_proto.set_for_with_in(iteration_statement.for_with_in);
    return iteration_statement_proto;
}


auto ReturnStatementToProto(const return_statement_node& return_statement) -> fuzzing::return_statement_node {
    fuzzing::return_statement_node return_statement_proto;
    if(return_statement.identifier != nullptr) { 
        *return_statement_proto.mutable_identifier() = TokenToProto(*return_statement.identifier);
    }
    if(return_statement.expression != nullptr) { 
        *return_statement_proto.mutable_expression() = ExpressionToProto(*return_statement.expression);
    }
    return return_statement_proto;
}

auto AlternativeToProto(const alternative_node& alternative) -> fuzzing::alternative_node {
    fuzzing::alternative_node alternative_proto;
    if(alternative.name != nullptr) {
        *alternative_proto.mutable_name() = UnqualifiedIdToProto(*alternative.name);
    }
    if(alternative.is_as_keyword != nullptr) {
        *alternative_proto.mutable_is_as_keyword() = TokenToProto(*alternative.is_as_keyword);
    }
    if(alternative.type_id != nullptr) {
        *alternative_proto.mutable_type_id() = TypeIdToProto(*alternative.type_id);
    }
    if(alternative.value != nullptr) {
        *alternative_proto.mutable_value() = PostfixExpressionToProto(*alternative.value);
    }
    if(alternative.statement != nullptr) {
        *alternative_proto.mutable_statement() = StatementToProto(*alternative.statement);
    }
    return alternative_proto;
}

auto InspectExpressionToProto(const inspect_expression_node& inspect_expression) -> fuzzing::inspect_expression_node {
    fuzzing::inspect_expression_node inspect_expression_proto;
    inspect_expression_proto.set_is_constexpr(inspect_expression.is_constexpr);
    if(inspect_expression.identifier != nullptr) { 
        *inspect_expression_proto.mutable_identifier() = TokenToProto(*inspect_expression.identifier);
    }
    if(inspect_expression.expression != nullptr) { 
        *inspect_expression_proto.mutable_expression() = ExpressionToProto(*inspect_expression.expression);
    }
    if(inspect_expression.result_type != nullptr) { 
        *inspect_expression_proto.mutable_result_type() = TypeIdToProto(*inspect_expression.result_type);
    }
    for (const auto& alternative : inspect_expression.alternatives) {
        auto* e = inspect_expression_proto.add_alternatives();
        if(e != nullptr) {
            *e = AlternativeToProto(*alternative);
        }
        // *e = AlternativeToProto(*alternative);
        }
    return inspect_expression_proto;
}

auto ContractToProto(const contract_node& contract) -> fuzzing::contract_node {
    fuzzing::contract_node contract_proto;
    // if(contract.captures != nullptr) {
    //     *contract_proto.mutable_captures() = CaptureGroupToProto(contract.captures);
    // }
    *contract_proto.mutable_captures() = CaptureGroupToProto(contract.captures);
    
    if(contract.kind != nullptr) {
        *contract_proto.mutable_kind() = TokenToProto(*contract.kind);
    }
    if(contract.group != nullptr) {
        *contract_proto.mutable_group() = IdExpressionToProto(*contract.group);
    }
    if(contract.condition != nullptr) {
        *contract_proto.mutable_condition() = LogicalOrExpressionToProto(*contract.condition);
    }
    if(contract.message != nullptr) {
        *contract_proto.mutable_message() = TokenToProto(*contract.message);
    }
    return contract_proto;
}

auto JumpToProto(const jump_statement_node& jump_statement) -> fuzzing::jump_statement_node { 
    fuzzing::jump_statement_node jump_statement_proto;
    *jump_statement_proto.mutable_keyword() = TokenToProto(*jump_statement.keyword);
    *jump_statement_proto.mutable_label() = TokenToProto(*jump_statement.label);
    return jump_statement_proto;
}

auto StatementToProto(const statement_node& statement) -> fuzzing::statement_node {
    fuzzing::statement_node statement_proto;
    if(statement.parameters != nullptr) {
        *statement_proto.mutable_parameters() = ParameterDeclarationListToProto(*statement.parameters);
    }
    // const auto& e = statement.statement;
    
    //visitor
    struct converter { 
        fuzzing::statement_node* s;
        explicit converter(fuzzing::statement_node& s_param): s(&s_param) {}
        
        void operator()(const std::unique_ptr<expression_statement_node>& e) { 
            if (e != nullptr) {
                *s->mutable_expression() = ExpressionStatementToProto(*e);
            }
        }
        void operator()(const std::unique_ptr<compound_statement_node>& e) { 
            if (e != nullptr) {
                *s->mutable_compound() = CompoundStatementToProto(*e);
            }
        } 
        void operator()(const std::unique_ptr<selection_statement_node>& e) { 
            if (e != nullptr) {
                *s->mutable_selection() = SelectionStatementToProto(*e);
        }
            }
        void operator()(const std::unique_ptr<declaration_node>& e) { 
            if (e != nullptr) {
                *s->mutable_declaration() = DeclarationToProto(*e);
            }
        } 
        void operator()(const std::unique_ptr<return_statement_node>& e) { 
            if (e != nullptr) {
                *s->mutable_return_() = ReturnStatementToProto(*e);
            }
        } 
        void operator()(const std::unique_ptr<iteration_statement_node>& e) { 
            if (e != nullptr) {
                *s->mutable_iteration() = IterationStatementToProto(*e);
            }
        }
        void operator()(const std::unique_ptr<contract_node>& e) { 
            if (e != nullptr) {
                *s->mutable_contract() = ContractToProto(*e);
            }
        } 
        void operator()(const std::unique_ptr<inspect_expression_node>& e) { 
            if (e != nullptr) {
                *s->mutable_inspect() = InspectExpressionToProto(*e);
            }
        } 
        void operator()(const std::unique_ptr<jump_statement_node>& e) { 
            if (e != nullptr) {
                *s->mutable_jump() = JumpToProto(*e);
            }
        }
    };
    
    std::visit(converter(statement_proto), statement.statement);
    
    statement_proto.set_emitted(statement.emitted);

    return statement_proto;
}

auto ModifierToProto(const parameter_declaration_node::modifier mod) { 
    switch (mod) {
        case parameter_declaration_node::modifier::none:
            return fuzzing::parameter_declaration_node::none;
        case parameter_declaration_node::modifier::implicit:
            return fuzzing::parameter_declaration_node::implicit;
        case parameter_declaration_node::modifier::virtual_:
            return fuzzing::parameter_declaration_node::virtual_;
        case parameter_declaration_node::modifier::override_:
            return fuzzing::parameter_declaration_node::override_;
        case parameter_declaration_node::modifier::final_:
            return fuzzing::parameter_declaration_node::final_;
    }
    return fuzzing::parameter_declaration_node::none;
}

auto ParameterDeclarationToProto(const parameter_declaration_node& parameter_declaration) -> fuzzing::parameter_declaration_node {
    fuzzing::parameter_declaration_node parameter_declaration_proto;
    //proto2cpp2 not working for this one. 
    parameter_declaration_proto.set_mod(ModifierToProto(parameter_declaration.mod));
    *parameter_declaration_proto.mutable_declaration() = DeclarationToProto(*parameter_declaration.declaration);
    return parameter_declaration_proto;
}

auto ParameterDeclarationListToProto(const parameter_declaration_list_node& parameter_declaration_list) -> fuzzing::parameter_declaration_list_node {
    fuzzing::parameter_declaration_list_node parameter_declaration_list_proto;
    if(parameter_declaration_list.open_paren != nullptr) {
        *parameter_declaration_list_proto.mutable_open_paren() = TokenToProto(*parameter_declaration_list.open_paren);
    }
    if(parameter_declaration_list.close_paren != nullptr) {
        *parameter_declaration_list_proto.mutable_close_paren() = TokenToProto(*parameter_declaration_list.close_paren);
    }

    for (const auto& parameter : parameter_declaration_list.parameters) {
        if (parameter != nullptr) {
            *parameter_declaration_list_proto.add_parameters() = ParameterDeclarationToProto(*parameter);
        }
        else {
            parameter_declaration_list_proto.add_parameters(); 
        }
        // auto* e = parameter_declaration_list_proto.add_parameters();
        // *e = ParameterDeclarationToProto(*parameter);
    }

    return parameter_declaration_list_proto;
}

auto FunctionTypeToProto(const function_type_node& function_type) -> fuzzing::function_type_node {
    fuzzing::function_type_node function_type_proto;
    if (!function_type.my_decl) {
        std::cerr << "Error: function_type.my_decl is nullptr!" << std::endl;
    }
    // if (function_type.my_decl) {
    //     *function_type_proto.mutable_my_decl() = DeclarationToProto(*function_type.my_decl);
    // }
    if(function_type.parameters != nullptr) {
        *function_type_proto.mutable_parameters() = ParameterDeclarationListToProto(*function_type.parameters);
    }
    function_type_proto.set_throws(function_type.throws);
    
    //visitor
    struct converter { 
        fuzzing::function_type_node* s;
        explicit converter(fuzzing::function_type_node& s_param): s(&s_param) {}
        
        void operator()(const std::monostate& e) { 
            //hello :)
        }
        void operator()(const function_type_node::single_type_id& e) { 
            if (e.type) {
                if(e.type != nullptr) {
                s->mutable_id()->mutable_type()->CopyFrom(TypeIdToProto(*e.type));
                }
                s->mutable_id()->set_pass(PassingStyleToProto(e.pass));
            } 
        }
        void operator()(const std::unique_ptr<parameter_declaration_list_node>& e) { 
            *s->mutable_list() = ParameterDeclarationListToProto(*e);
        } 
    };
    
    std::visit(converter(function_type_proto), function_type.returns);
    
    for (const auto& contract : function_type.contracts) {
        *function_type_proto.add_contracts() = ContractToProto(*contract);
    }
    
    return function_type_proto;
}


auto AliasToProto(const alias_node& alias) -> fuzzing::alias_node {
    fuzzing::alias_node alias_proto;
    *alias_proto.mutable_type() = TokenToProto(*alias.type);
    //oneof

    struct converter { 
        fuzzing::alias_node* s;
        explicit converter(fuzzing::alias_node& s_param): s(&s_param) {}
        
        void operator()(const std::unique_ptr<type_id_node>& e) { 
            assert(e != nullptr);
            *s->mutable_a_type() = TypeIdToProto(*e);
        }
        void operator()(const std::unique_ptr<id_expression_node>& e) { 
            assert(e != nullptr);
            *s->mutable_a_namespace() = IdExpressionToProto(*e);
        } 
        void operator()(const std::unique_ptr<expression_node>& e) { 
            assert(e != nullptr);
            *s->mutable_an_object() = ExpressionToProto(*e);
        }
    };
    
    std::visit(converter(alias_proto), alias.initializer);

    return alias_proto;
}

auto DeclarationToProto(const declaration_node& declaration) -> fuzzing::declaration_node {
    fuzzing::declaration_node declaration_proto;
    *declaration_proto.mutable_captures() = CaptureGroupToProto(declaration.captures);
    if (declaration.identifier != nullptr) { 
        *declaration_proto.mutable_identifier() = UnqualifiedIdToProto(*declaration.identifier);
    }
    // const auto& e = declaration_proto.type;

    struct converter { 
        fuzzing::declaration_node* s;
        explicit converter(fuzzing::declaration_node& s_param): s(&s_param) {}
        
        void operator()(const std::unique_ptr<function_type_node>& e) { 
            if (e != nullptr) { 
                *s->mutable_a_function() = FunctionTypeToProto(*e);
            }
        }
        void operator()(const std::unique_ptr<type_id_node>& e) { 
            if (e != nullptr) { 
                *s->mutable_an_object() = TypeIdToProto(*e);
            }
        } 
        void operator()(const std::unique_ptr<type_node>& e) { 
            if (e != nullptr) { 
                *s->mutable_a_type() = TypeToProto(*e);
            }
        }
        void operator()(const std::unique_ptr<namespace_node>& e) { 
            if (e != nullptr) { 
                *s->mutable_a_namespace() = NamespaceToProto(*e);
            }
        } 
        void operator()(const std::unique_ptr<alias_node>& e) { 
            if (e != nullptr) { 
                *s->mutable_an_alias() = AliasToProto(*e);
            }
        } 
       
    };
    
    std::visit(converter(declaration_proto), declaration.type);

    for (const auto& meta_function : declaration.meta_functions) {
        *declaration_proto.add_meta_functions() = IdExpressionToProto(*meta_function);
    }
    if (declaration.template_parameters != nullptr) {
        *declaration_proto.mutable_template_parameters() = ParameterDeclarationListToProto(*declaration.template_parameters);
    }
    if (declaration.requires_clause_expression != nullptr) {
        *declaration_proto.mutable_requires_clause_expression() = ExpressionToProto(*declaration.requires_clause_expression);
    }
    if (declaration.initializer != nullptr) {
        *declaration_proto.mutable_initializer() = StatementToProto(*declaration.initializer);
    }

    return declaration_proto;
}

auto TranslationUnitToProto(const translation_unit_node& translation_unit) -> fuzzing::translation_unit_node {
    fuzzing::translation_unit_node translation_unit_proto;
    for (const auto& declaration : translation_unit.declarations) {
        *translation_unit_proto.add_declarations() = DeclarationToProto(*declaration);
    }
    return translation_unit_proto;
}

} // namespace cpp2

