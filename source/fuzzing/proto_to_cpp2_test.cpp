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

} //namespace
} //namespace cpp2
