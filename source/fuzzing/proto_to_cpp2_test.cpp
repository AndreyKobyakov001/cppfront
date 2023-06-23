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

TEST(ProtoToCpp2Test, PrimaryExpressionToProto) { 
    
}

TEST(ProtoToCpp2Test, PrefixExpressionToProto) { 
    
}

TEST(ProtoToCpp2Test, IsAsExpressionToProto) { 
    
}

TEST(ProtoToCpp2Test, MultiplicativeExpressionToProto) { 
    
}

TEST(ProtoToCpp2Test, AdditiveExpressionToProto) { 
    
}

TEST(ProtoToCpp2Test, ShiftExpressionToProto) { 

}

TEST(ProtoToCpp2Test, CompareExpressionToProto) { 
    
}

TEST(ProtoToCpp2Test, RelationalExpressionToProto) { 
    
}

TEST(ProtoToCpp2Test, EqualityExpressionToProto) { 
    
}

TEST(ProtoToCpp2Test, BitAndExpressionToProto) { 
    
}

TEST(ProtoToCpp2Test, BitXorExpressionToProto) { 

}

TEST(ProtoToCpp2Test, BitOrExpressionToProto) { 
    
}

TEST(ProtoToCpp2Test, LogicalAndExpressionToProto) { 
    
}

TEST(ProtoToCpp2Test, LogicalOrExpressionToProto) { 
    
}

TEST(ProtoToCpp2Test, AssignmentExpressionToProto) { 
    
}

TEST(ProtoToCpp2Test, ExpressionToProto) { 

}

TEST(ProtoToCpp2Test, ExpressionListToProto) { 
    
}

TEST(ProtoToCpp2Test, ExpressionStatementToProto) { 
    
}

TEST(ProtoToCpp2Test, CaptureToProto) { 
    
}

TEST(ProtoToCpp2Test, CaptureGroupToProto) { 
    
}

TEST(ProtoToCpp2Test, PostfixExpressionToProto) { 

}

TEST(ProtoToCpp2Test, UnqualifiedIdToProto) { 
    
}

TEST(ProtoToCpp2Test, QualifiedIdToProto) { 
    
}

TEST(ProtoToCpp2Test, TypeIdToProto) { 
    
}

TEST(ProtoToCpp2Test, IdExpressionToProto) { 
    
}

TEST(ProtoToCpp2Test, CompoundStatementToProto) { 

}

TEST(ProtoToCpp2Test, SelectionStatementToProto) { 
    
}

TEST(ProtoToCpp2Test, IterationStatementToProto) { 
    
}

TEST(ProtoToCpp2Test, ReturnStatementToProto) { 
    
}

TEST(ProtoToCpp2Test, AlternativeToProto) { 
    
}

TEST(ProtoToCpp2Test, InspectExpressionToProto) { 

}

TEST(ProtoToCpp2Test, ContractToProto) { 
    
}

TEST(ProtoToCpp2Test, JumpToProto) { 
    
}

TEST(ProtoToCpp2Test, StatementToProto) { 
    
}

TEST(ProtoToCpp2Test, ModifierToProto) { 
    
}

TEST(ProtoToCpp2Test, ParameterDeclarationToProto) { 

}

TEST(ProtoToCpp2Test, ParameterDeclarationListToProto) { 
    
}

TEST(ProtoToCpp2Test, FunctionTypeToProto) { 
    
}

TEST(ProtoToCpp2Test, AliasToProto) { 
    
}

TEST(ProtoToCpp2Test, DeclarationToProto) { 
    
}

TEST(ProtoToCpp2Test, TranslationUnitToProto) { 
    
}

} //namespace
} //namespace cpp2
