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
    }
    return equals;
}

TEST(AstToProtoTest, TokenToProto) { 
    
    source_position pos;
    token t("xx", pos, lexeme::Identifier);

    fuzzing::token token_proto = TokenToProto(t);
    EXPECT_TRUE(EqualsProto(token_proto, "value: 'Identifier: xx'"));
}

} //namespace
} //namespace cpp2
