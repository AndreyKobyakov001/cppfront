#include "source/fuzzing/ast_to_proto.h"
#include "source/fuzzing/proto_to_cpp2.h"
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
    
static std::vector<std::string_view>* cpp2_files = nullptr;

//use Throw for errors. 

auto translation_unit_to_string(cppfront& c) { 
    std::stringstream out;
    c.parser_debug_print(out);
    return out.str(); 
}

TEST(RoundTripTest, Roundtrip) {
  int parsed_ok_count = 0;
  std::cout << "Hello world\n" << std::flush;
  std::cout << "Size:" << cpp2_files->size() << "\n" << std::flush;
  for (const std::string_view filename : *cpp2_files) {
    std::cout << "Filename:" << filename << "\n" << std::flush;
    std::string f(filename);
    cppfront c(f); 
    std::cout << "Created CPP2 File \n" << std::flush;
    if (c.had_no_errors()) {
      ++parsed_ok_count;
      const std::unique_ptr<translation_unit_node>& parse_tree = c.get_parse_tree(); 
      std::cout << "Parse tree time:" << parse_tree.get() << "\n" << std::flush;
      const fuzzing::translation_unit_node translation_unit_proto = 
          TranslationUnitToProto(*parse_tree); //this line breaks
          //check if not null
      std::cout << "Generated proto from CPP2 \n" << std::flush;
      std::stringstream out;
      TranslationUnitToCpp2(translation_unit_proto, out); 
      std::cout << "Generate CPP2 from proto \n" << std::flush;

      SCOPED_TRACE(testing::Message()
                    << "Cpp2 file: " << filename << ", source from proto:\n"
                    << out.str());
      //rename the out variable :)-|<
      std::istringstream source_from_proto(out.str());
      cppfront c2(f, source_from_proto); 
      //rename this to not be retarded
      if (c2.had_no_errors()) {
        EXPECT_EQ(translation_unit_to_string(c), translation_unit_to_string(c2));
        } else {
          c2.print_errors();
          ADD_FAILURE() << "Parse error ";
      }

      // if (c2.had_no_errors()) {
      //   ASSERT_EQ(translation_unit_to_string(c), translation_unit_to_string(c2));
      //   } 
      // //   else {
      // //     c2.print_errors();
      // //     ADD_FAILURE() << "Parse error ";
      // // }
    }
  }
  // Makes sure files were actually processed.
  EXPECT_GT(parsed_ok_count, 0);
}


} //namespace
} //namespace cpp2

auto main(int argc, char** argv) -> int {
  ::testing::InitGoogleTest(&argc, argv);
  // gtest should remove flags, leaving just input files.
  std::vector<std::string_view> cpp2_files(&argv[1], &argv[argc]);
  cpp2::cpp2_files = &cpp2_files;
  return RUN_ALL_TESTS();
}