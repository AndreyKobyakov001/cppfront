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

auto PrimaryExpressionToProto(const primary_expression_node& primary_expression_) -> fuzzing::primary_expression_node;

auto PrefixExpressionToProto(const prefix_expression_node& prefix_expression_) -> fuzzing::prefix_expression_node;

auto IsAsExpressionToProto(const is_as_expression_node& is_as_expression_) -> fuzzing::is_as_expression_node;

auto MultiplicativeExpressionToProto(const multiplicative_expression_node& multiplicative_expression_) -> fuzzing::multiplicative_expression_node;

auto AdditiveExpressionToProto(const additive_expression_node& additive_expression_) -> fuzzing::additive_expression_node;

auto ShiftExpressionToProto(const shift_expression_node& shift_expression_) -> fuzzing::shift_expression_node;

auto CompareExpressionToProto(const compare_expression_node& compare_expression_) -> fuzzing::compare_expression_node;

auto RelationalExpressionToProto(const relational_expression_node& relational_expression_) -> fuzzing::relational_expression_node;

auto EqualityExpressionToProto(const equality_expression_node& equality_expression_) -> fuzzing::equality_expression_node;

auto BitAndExpressionToProto(const bit_and_expression_node& bit_and_expression_) -> fuzzing::bit_and_expression_node;

auto BitXorExpressionToProto(const bit_xor_expression_node& bit_xor_expression_) -> fuzzing::bit_xor_expression_node;

auto BitOrExpressionToProto(const bit_or_expression_node& bit_or_expression_) -> fuzzing::bit_or_expression_node;

auto LogicalAndExpressionToProto(const logical_and_expression_node& logical_and_expression_) -> fuzzing::logical_and_expression_node;

auto LogicalOrExpressionToProto(const logical_or_expression_node& logical_or_expression_) -> fuzzing::logical_or_expression_node;

auto AssignmentExpressionToProto(const assignment_expression_node& assignment_expression_) -> fuzzing::assignment_expression_node;

auto ExpressionToProto(const expression_node& expression_) -> fuzzing::expression_node;

auto ExpressionListToProto(const expression_list_node& expression_list_) -> fuzzing::expression_list_node;

auto ExpressionStatementToProto(const expression_statement_node& expression_statement_) -> fuzzing::expression_statement_node;

auto CaptureToProto(const capture& capture_) -> fuzzing::capture;

auto CaptureGroupToProto(const capture_group& capture_group_) -> fuzzing::capture_group;

auto PostfixExpressionToProto(const postfix_expression_node& postfix_expression_) -> fuzzing::postfix_expression_node;

auto UnqualifiedIdToProto(const unqualified_id_node& unqualified_id_) -> fuzzing::unqualified_id_node;

auto QualifiedIdToProto(const qualified_id_node& qualified_id_) -> fuzzing::qualified_id_node;

auto TypeIdToProto(const type_id_node& type_id_) -> fuzzing::type_id_node;

auto IdExpressionToProto(const id_expression_node& id_expression_) -> fuzzing::id_expression_node;

auto CompoundStatementToProto(const compound_statement_node& compound_statement_) -> fuzzing::compound_statement_node;

auto SelectionStatementToProto(const selection_statement_node& selection_statement_) -> fuzzing::selection_statement_node;

auto IterationStatementToProto(const iteration_statement_node& iteration_statement_) -> fuzzing::iteration_statement_node;

auto ReturnStatementToProto(const return_statement_node& return_statement_) -> fuzzing::return_statement_node;

auto AlternativeToProto(const alternative_node& alternative_) -> fuzzing::alternative_node;

auto InspectExpressionToProto(const inspect_expression_node& inspect_expression_) -> fuzzing::inspect_expression_node;

auto ContractToProto(const contract_node& contract_) -> fuzzing::contract_node;

auto FunctionDefinitionToProto(const function_definition_node& function_definition_) -> fuzzing::function_definition_node;

auto TopLevelDeclarationToProto(const top_level_declaration_node& top_level_declaration_) -> fuzzing::top_level_declaration_node;

auto TranslationUnitToProto(const translation_unit_node& translation_unit_) -> fuzzing::translation_unit_node;


}// namespace cpp2

#endif // __CPP2_FUZZING_AST_TO_PROTO