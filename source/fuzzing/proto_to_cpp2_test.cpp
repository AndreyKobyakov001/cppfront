#include <gtest/gtest.h>
#include "source/fuzzing/proto_to_cpp2.h"
#include "source/fuzzing/cpp2.pb.h" 
#include "gmock/gmock.h" //Doesn't bring in gMock 😎
#include <sstream>

namespace cpp2 {    
namespace {

TEST(ProtoToCpp2Test, TokenToCpp2) { 
    fuzzing::token t;
    t.set_value("xx");
    std::stringstream out;
    TokenToCpp2(t, out);
    EXPECT_EQ(out.str(), "xx");
}

TEST(ProtoToCpp2Test, LiteralToCpp2) { 
    fuzzing::literal_node lit_proto;
}

TEST(ProtoToCpp2Test, TypeToCpp2) {
    fuzzing::type_node type_proto;
//     type_proto.set_value;
}

TEST(ProtoToCpp2Test, NameToCpp2) { 
    fuzzing::namespace_node name;
}

//messages inside messages behave as if variables in a namespace

} //namespace
} //namespace cpp2
