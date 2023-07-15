#include "source/fuzzing/ast_to_proto.h"
#include "source/fuzzing/cpp2.pb.h" 

#include <gmock/gmock.h> //Doesn't bring in gMock 😎
#include <google/protobuf/descriptor.h>
#include <google/protobuf/util/message_differencer.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <numeric>
#include <set>
#include <variant>
#include <ostream>
#include <sstream>

// #include "parse.h"
#include "source/cppfront.h"

namespace cpp2 {
namespace {
    
//use Throw for errors. 

auto translation_unit_to_string(const cppfront& c) { 
    std::stringstream out;
    c.parser_debug_print(out);
    return out.str(); 
}

analyze_file(std::string const& filename) -> translation_unit_node { 
  cppfront c(filename); 
  const std::unique_ptr<translation_unit_node>& parse_tree = c.get_parse_tree(); 
  //print ast from TUs possibly using a function, though this may have to be used twice
  const fuzzing::translation_unit_node translation_unit_proto = 
      TranslationUnitToProto(*parse_tree);
      //check if not null
  std::stringstream out;
  TranslationUnitToCpp2(translation_unit_proto, out);

  std::istringstream source_from_proto(out.str());
  cppfront c2(filename, source_from_proto);
  const std::unique_ptr<translation_unit_node>& parse_tree_from_proto = c2.get_parse_tree(); 
  //rename this to not be retarded

  EXPECT_EQ(translation_unit_to_string(c), translation_unit_to_string(c2));

}


} //namespace
} //namespace cpp2