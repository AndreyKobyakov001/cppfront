//test.cc
#include <gtest/gtest.h>
#include <google/protobuf/util/message_differencer.h>
#include <google/protobuf/text_format.h>

#include "source/fuzzing/ast_to_proto.h"
#include "source/fuzzing/cpp2.pb.h" 
// #include "testing/base/public/gmock.h"
#include "gmock/gmock.h"  // Brings in gMock.
#include "gtest/gtest.h"


namespace cpp2 { 
namespace {
void EqualsProto(const google::protobuf::Message& actual, std_string_view expected) { 
    google::protobuf::TextFormat::Parser
}

TEST(AstToProtoTest, TokenToProto) { 
    
    source_position pos;
    token t("xx", pos, lexeme::Identifier);

    fuzzing::token token_proto = TokenToProto(t);

    // EXPECT_EQ(token_proto.DebugString(), "xx");
    // expected output (second position):  "value: \"Identifier: xx\"\n"

    // EXPECT_THAT(token_proto.DebugString(), "value: \"Identifier: xx\"\n");
    EXPECT_THAT(token_proto.DebugString(), ::testing::EqualsProto("value: \"Identifier: xx\"\n"));
}

} //namespace
} //namespace cpp2