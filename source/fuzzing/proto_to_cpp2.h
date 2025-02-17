#ifndef __CPP2_FUZZING_PROTO_TO_CPP2
#define __CPP2_FUZZING_PROTO_TO_CPP2

#include <ostream>
#include "source/fuzzing/cpp2.pb.h"

namespace cpp2 {

auto ProtoToPassingStyle(fuzzing::passing_style::en style_proto) -> std::string_view; 

void TokenToCpp2(const fuzzing::token &t, std::ostream& out);

void LiteralToCpp2(const fuzzing::literal_node &lit, std::ostream& out);

void TypeToCpp2(const fuzzing::type_node& type, std::ostream& out);

void NameToCpp2(const fuzzing::namespace_node& namespace_, std::ostream& out);

void PrimaryExpressionToCpp2(const fuzzing::primary_expression_node& primary_expression, std::ostream& out);

void PrefixExpressionToCpp2(const fuzzing::prefix_expression_node& prefix_expression, std::ostream& out);

void IsAsExpressionToCpp2(const fuzzing::is_as_expression_node& is_as_expression, std::ostream& out);

void MultiplicativeExpressionToCpp2(const fuzzing::multiplicative_expression_node& multiplicative_expression, std::ostream& out);

void AdditiveExpressionToCpp2(const fuzzing::additive_expression_node& additive_expression, std::ostream& out);

void ShiftExpressionToCpp2(const fuzzing::shift_expression_node& shift_expression, std::ostream& out);

void CompareExpressionToCpp2(const fuzzing::compare_expression_node& compare_expression, std::ostream& out);

void RelationalExpressionToCpp2(const fuzzing::relational_expression_node& relational_expression, std::ostream& out);

void EqualityExpressionToCpp2(const fuzzing::equality_expression_node& equality_expression, std::ostream& out);

void BitAndExpressionToCpp2(const fuzzing::bit_and_expression_node& bit_and_expression, std::ostream& out);

void BitXorExpressionToCpp2(const fuzzing::bit_xor_expression_node& bit_xor_expression, std::ostream& out);

void BitOrExpressionToCpp2(const fuzzing::bit_or_expression_node& bit_or_expression, std::ostream& out);

void LogicalAndExpressionToCpp2(const fuzzing::logical_and_expression_node& logical_and_expression, std::ostream& out);

void LogicalOrExpressionToCpp2(const fuzzing::logical_or_expression_node& logical_or_expression, std::ostream& out);

void AssignmentExpressionToCpp2(const fuzzing::assignment_expression_node& assignment_expression, std::ostream& out);

void ExpressionToCpp2(const fuzzing::expression_node& expression, std::ostream& out);

void ExpressionListToCpp2(const fuzzing::expression_list_node& expression_list, std::ostream& out);

void ExpressionStatementToCpp2(const fuzzing::expression_statement_node& expression_statement, bool is_function_initializer, std::ostream& out);

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

void StatementToCpp2(const fuzzing::statement_node& statement, bool is_function_initializer, std::ostream& out);

void ParameterDeclarationNodeToCpp2(const fuzzing::parameter_declaration_node& parameter_declaration, std::ostream& out);

void ParameterDeclarationListToCpp2(const fuzzing::parameter_declaration_list_node& parameter_declaration_list, std::ostream& out);

void FunctionTypeToCpp2(const fuzzing::function_type_node& function_type, std::ostream& out);

void AliasToCpp2(const fuzzing::alias_node& alias, std::ostream& out);

void DeclarationToCpp2(const fuzzing::declaration_node& declaration, bool is_parameter, std::ostream& out);

void TranslationUnitToCpp2(const fuzzing::translation_unit_node& translation_unit, std::ostream& out);

} // namespace cpp2

#endif // __CPP2_FUZZING_PROTO_TO_CPP2