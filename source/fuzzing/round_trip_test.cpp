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

auto write_to_file(const std::string_view filename, const std::string_view contents) { 
  std::ofstream f;
  f.open(filename.data());
  f << contents; 
  f.close(); 
}

TEST(RoundTripTest, Roundtrip) {
  int parsed_ok_count = 0;
  int correct_count = 0; 
  // bool debug = false; 
  bool debug = true;
  // std::cout << "Hello world\n" << std::flush;
  std::cout << "Size:" << cpp2_files->size() << "\n" << std::flush;
  for (const std::string_view filename : *cpp2_files) {
    // std::cout << "Filename: " << filename << "\n" << std::flush;
    std::string f(filename);
    cppfront c(f); 
    if (!c.had_no_errors()) {
      c.print_errors();
      ADD_FAILURE() << "Parse error ";
    } else {
      parsed_ok_count++; //move ++ to the start for efficiency and all that (much good it'll do you)
      const std::unique_ptr<translation_unit_node>& parse_tree = c.get_parse_tree(); 
      if (1 == 0) {
        std::cout << "Parse tree time:" << parse_tree.get() << "\n" << std::flush;
      }
      const fuzzing::translation_unit_node translation_unit_proto = 
          TranslationUnitToProto(*parse_tree); //TODO: check if not null


      //DEBUGGING PURPOSES
      // if (debug) { 
      //   std::cout << "Generated proto from CPP2: \n" << translation_unit_proto.DebugString() << "\n" <<  std::flush;      
      // }
      // std::cout << "Translation Unit:\n" << translation_unit_to_string(c) << "\n"; 
     
     
      std::stringstream out;
      TranslationUnitToCpp2(translation_unit_proto, out); 
      write_to_file("/tmp/c2.cpp2", out.str());
      // if (debug) { 
      //   std::cout << "Generate CPP2 from proto \n" << std::flush;
      // }

      if(debug) { 
        SCOPED_TRACE(testing::Message()
                    << "Cpp2 file: " << filename << ", source from proto:\n"
                    << out.str());
      }
      //rename the out variable :)-|<
      
      std::istringstream source_from_proto(out.str());
      
      cppfront c2(f, source_from_proto); 
      if(debug) { 
        // std::cout << "Errors: \n";
        c2.print_errors();
      }
      //rename this to not be retarded
      if (c2.had_no_errors()) {
        const auto c_contents = translation_unit_to_string(c);
        const auto c2_contents = translation_unit_to_string(c2);
        if (debug) {  
          EXPECT_EQ(c_contents, c2_contents);
        }
        write_to_file("/tmp/c_contents", c_contents);
        write_to_file("/tmp/c2_contents", c2_contents);
        write_to_file("/tmp/proto_tree", translation_unit_proto.DebugString());
        
        const bool same = c_contents == c2_contents;
        if(same) { 
          correct_count++; 
        } else { 
          std::cout << parsed_ok_count << ". " << filename << " Different\n";
        }
        EXPECT_TRUE(same); 
      } else {
          if (debug) { 
            c2.print_errors();
          }
          std::cout << parsed_ok_count << ". " << filename << " HAS ERRORS" << "\n";
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
  std::cout << "Correct File Parsing: " << correct_count << " out of " << parsed_ok_count << " :) \n"; 
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