#ifndef __CPP2_FUZZING_AST_TO_PROTO
#define __CPP2_FUZZING_AST_TO_PROTO

#include "source/cppfront.h"
#include "source/fuzzing/cpp2.pb.h"

namespace cpp2 {

// Builds a protobuf representation of `ast`.
// auto AstToProto(const translation_unit_node& parse_tree) ->
// fuzzing::translation_unit_node;
auto TokenToProto(const token& t) -> fuzzing::token;

auto LiteralToProto(const literal_node& lit) -> fuzzing::literal_node; 

auto TypeToProto(const type_node& type) -> fuzzing::type_node;

auto NamespaceToProto(const namespace_node& namespace_) -> fuzzing::namespace_node;

//the complexities are hereafter

auto DeclarationToProto(const declaration_node& declaration) -> fuzzing::declaration_node;

auto PrimaryExpressionToProto(const primary_expression_node& primary_expression) -> fuzzing::primary_expression_node;

auto PrefixExpressionToProto(const prefix_expression_node& prefix_expression) -> fuzzing::prefix_expression_node;

auto IsAsExpressionToProto(const is_as_expression_node& is_as_expression) -> fuzzing::is_as_expression_node;

auto MultiplicativeExpressionToProto(const multiplicative_expression_node& multiplicative_expression) -> fuzzing::multiplicative_expression_node;

auto AdditiveExpressionToProto(const additive_expression_node& additive_expression) -> fuzzing::additive_expression_node;

auto ShiftExpressionToProto(const shift_expression_node& shift_expression) -> fuzzing::shift_expression_node;

auto CompareExpressionToProto(const compare_expression_node& compare_expression) -> fuzzing::compare_expression_node;

auto RelationalExpressionToProto(const relational_expression_node& relational_expression) -> fuzzing::relational_expression_node;

auto EqualityExpressionToProto(const equality_expression_node& equality_expression) -> fuzzing::equality_expression_node;

auto BitAndExpressionToProto(const bit_and_expression_node& bit_and_expression) -> fuzzing::bit_and_expression_node;

auto BitXorExpressionToProto(const bit_xor_expression_node& bit_xor_expression) -> fuzzing::bit_xor_expression_node;

auto BitOrExpressionToProto(const bit_or_expression_node& bit_or_expression) -> fuzzing::bit_or_expression_node;

auto LogicalAndExpressionToProto(const logical_and_expression_node& logical_and_expression) -> fuzzing::logical_and_expression_node;

auto LogicalOrExpressionToProto(const logical_or_expression_node& logical_or_expression) -> fuzzing::logical_or_expression_node;

auto AssignmentExpressionToProto(const assignment_expression_node& assignment_expression) -> fuzzing::assignment_expression_node;

auto ParameterDeclarationToProto(const parameter_declaration_node& parameter_declaration) -> fuzzing::parameter_declaration_node;

auto ParameterDeclarationListToProto(const parameter_declaration_list_node& parameter_declaration_list) -> fuzzing::parameter_declaration_list_node;

auto ExpressionToProto(const expression_node& expression) -> fuzzing::expression_node;

auto ExpressionListToProto(const expression_list_node& expression_list) -> fuzzing::expression_list_node;

auto ExpressionStatementToProto(const expression_statement_node& expression_statement) -> fuzzing::expression_statement_node;

auto CaptureToProto(const capture& capture) -> fuzzing::capture;

auto CaptureGroupToProto(const capture_group& capture_group) -> fuzzing::capture_group;

auto PostfixExpressionToProto(const postfix_expression_node& postfix_expression) -> fuzzing::postfix_expression_node;

auto UnqualifiedIdToProto(const unqualified_id_node& unqualified_id) -> fuzzing::unqualified_id_node;

auto QualifiedIdToProto(const qualified_id_node& qualified_id) -> fuzzing::qualified_id_node;

auto TypeIdToProto(const type_id_node& type_id) -> fuzzing::type_id_node;

auto IdExpressionToProto(const id_expression_node& id_expression) -> fuzzing::id_expression_node;

auto CompoundStatementToProto(const compound_statement_node& compound_statement) -> fuzzing::compound_statement_node;

auto SelectionStatementToProto(const selection_statement_node& selection_statement) -> fuzzing::selection_statement_node;

auto IterationStatementToProto(const iteration_statement_node& iteration_statement) -> fuzzing::iteration_statement_node;

auto ReturnStatementToProto(const return_statement_node& return_statement) -> fuzzing::return_statement_node;

auto StatementToProto(const statement_node& statement) -> fuzzing::statement_node;

auto AlternativeToProto(const alternative_node& alternative) -> fuzzing::alternative_node;

auto InspectExpressionToProto(const inspect_expression_node& inspect_expression) -> fuzzing::inspect_expression_node;

auto ContractToProto(const contract_node& contract) -> fuzzing::contract_node;

auto TranslationUnitToProto(const translation_unit_node& translation_unit) -> fuzzing::translation_unit_node;


}// namespace cpp2

#endif // __CPP2_FUZZING_AST_TO_PROTO