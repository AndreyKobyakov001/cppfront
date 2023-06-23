#include <gtest/gtest.h>
#include <google/protobuf/util/message_differencer.h>
#include <google/protobuf/text_format.h>
#include "source/fuzzing/ast_to_proto.h"
#include "source/fuzzing/cpp2.pb.h" 
#include "gmock/gmock.h"  // Brings in gMock.



namespace cpp2 { 
namespace {

bool EqualsProto(const google::protobuf::Message& actual, const std::string &expected) {
    std::unique_ptr<google::protobuf::Message> expected_proto(actual.New());
    if (!google::protobuf::TextFormat::ParseFromString(expected, expected_proto.get())) {
        return false;
    }
    google::protobuf::util::MessageDifferencer differencer;
    std::string diffs;
    differencer.ReportDifferencesToString(&diffs);
    bool equals = differencer.Compare(actual, *expected_proto);
    // return google::protobuf::util::MessageDifferencer::Equals(actual, *expected_proto);
    if (!equals){ 
        std::cerr << "Diffs: " << diffs << "\n";
        // std::cout << "Expected:" << actual << "\n";
    }
    return equals;
}

auto MakeToken(const char* value, lexeme lex = lexeme::Identifier) { 
    source_position pos;
    return token(value, pos, lex);
}

TEST(AstToProtoTest, TokenToProto) { 
    token t = MakeToken("xx");

    fuzzing::token token_proto = TokenToProto(t);
    EXPECT_TRUE(EqualsProto(token_proto, "value: 'Identifier: xx'"));
}

TEST(AstToProtoTest, LiteralToProto) { 
    token int_literal = MakeToken("1", lexeme::DecimalLiteral);
    literal_node lit { .literal = &int_literal };

    fuzzing::literal_node lit_proto = LiteralToProto(lit);
    EXPECT_TRUE(EqualsProto(lit_proto, R"(literal: { value: "DecimalLiteral: 1" })"));
}

TEST(AstToProtoTest, TypeToProto) { 
    token type_token = MakeToken("int", lexeme::BinaryLiteral);
    type_node type(&type_token, false);

    fuzzing::type_node type_proto = TypeToProto(type);
    // EXPECT_TRUE(EqualsProto(type_proto, R"(type: { value: "int" })"));
    EXPECT_TRUE(EqualsProto(type_proto, R"(type: { 
                                             value: "BinaryLiteral: int" 
                                           }
                                           final: false)"));
}

TEST(AstToProtoTest, NamespaceToProto) { 
    token namespace_token = MakeToken("name");
    namespace_node namespace_node(&namespace_token);
    fuzzing::namespace_node namespace_proto = NamespaceToProto(namespace_node);
    EXPECT_TRUE(EqualsProto(namespace_proto, R"(namespace_: { value: "Identifier: name" })"));
}

TEST(AstToProtoTest, PrimaryExpressionToProto) { 
    
}

TEST(AstToProtoTest, PrefixExpressionToProto) { 
    
}

TEST(AstToProtoTest, IsAsExpressionToProto) { 
    
}

TEST(AstToProtoTest, MultiplicativeExpressionToProto) { 
    
}

TEST(AstToProtoTest, AdditiveExpressionToProto) { 
    
}

TEST(AstToProtoTest, ShiftExpressionToProto) { 

}

TEST(AstToProtoTest, CompareExpressionToProto) { 
    
}

TEST(AstToProtoTest, RelationalExpressionToProto) { 
    
}

TEST(AstToProtoTest, EqualityExpressionToProto) { 
    
}

TEST(AstToProtoTest, BitAndExpressionToProto) { 
    
}

TEST(AstToProtoTest, BitXorExpressionToProto) { 

}

TEST(AstToProtoTest, BitOrExpressionToProto) { 
    
}

TEST(AstToProtoTest, LogicalAndExpressionToProto) { 
    
}

TEST(AstToProtoTest, LogicalOrExpressionToProto) { 
    
}

TEST(AstToProtoTest, AssignmentExpressionToProto) { 
    
}

TEST(AstToProtoTest, ExpressionToProto) { 

}

TEST(AstToProtoTest, ExpressionListToProto) { 
    
}

TEST(AstToProtoTest, ExpressionStatementToProto) { 
    
}

TEST(AstToProtoTest, CaptureToProto) { 
    
}

TEST(AstToProtoTest, CaptureGroupToProto) { 
    
}

TEST(AstToProtoTest, PostfixExpressionToProto) { 

}

TEST(AstToProtoTest, UnqualifiedIdToProto) { 
    
}

TEST(AstToProtoTest, QualifiedIdToProto) { 
    
}

TEST(AstToProtoTest, TypeIdToProto) { 
    
}

TEST(AstToProtoTest, IdExpressionToProto) { 
    
}

TEST(AstToProtoTest, CompoundStatementToProto) { 

}

TEST(AstToProtoTest, SelectionStatementToProto) { 
    
}

TEST(AstToProtoTest, IterationStatementToProto) { 
    
}

TEST(AstToProtoTest, ReturnStatementToProto) { 
    
}

TEST(AstToProtoTest, AlternativeToProto) { 
    
}

TEST(AstToProtoTest, InspectExpressionToProto) { 

}

TEST(AstToProtoTest, ContractToProto) { 
    
}

TEST(AstToProtoTest, JumpToProto) { 
    
}

TEST(AstToProtoTest, StatementToProto) { 
    
}

TEST(AstToProtoTest, ModifierToProto) { 
    
}

TEST(AstToProtoTest, ParameterDeclarationToProto) { 

}

TEST(AstToProtoTest, ParameterDeclarationListToProto) { 
    
}

TEST(AstToProtoTest, FunctionTypeToProto) { 
    
}

TEST(AstToProtoTest, AliasToProto) { 
    
}

TEST(AstToProtoTest, DeclarationToProto) { 
    
}

TEST(AstToProtoTest, TranslationUnitToProto) { 
    
}

} //namespace
} //namespace cpp2
