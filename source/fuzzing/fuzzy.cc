#include "fuzztest/fuzztest.h"
#include "gtest/gtest.h"


#include <filesystem>
#include <numeric>
#include <set>
#include <variant>
#include <ostream>
#include <sstream>


#include "source/fuzzing/ast_to_proto.h"
#include "source/fuzzing/proto_to_cpp2.h"
#include "source/fuzzing/cpp2.pb.h" 

// #include "parse.h"
#include "source/cppfront.h"
#include <gmock/gmock.h> //Doesn't bring in gMock 😎
#include <google/protobuf/descriptor.h>
#include <google/protobuf/util/message_differencer.h>
#include <gtest/gtest.h>
// #include "src/libfuzzer/libfuzzer_macro.h"
// #include "source/fuzzing/mutator.h"
// #include "source/fuzzing/mutator.cc"

namespace cpp2 {
namespace {

static std::vector<std::string_view>* cpp2_files = nullptr;

auto write_to_file(const std::string_view filename, const std::string_view contents) { 
  std::ofstream f;
  f.open(filename.data());
  f << contents; 
  f.close(); 
}

// BASIC FUZZER - mostly useless
void Cpp2Basic(const fuzzing::translation_unit_node& c) {
    std::stringstream out;
    TranslationUnitToCpp2(c, out); 
    std::cout << out.str();
    cppfront parsed_c(out.str());
    if (!parsed_c.had_no_errors()) {
      std::cout << "Parsed cpp2 code has errors\n";
    } else { 
      std::cout << "Parsed correctly\n"; 
    }
}



void Cpp2() { 
  
} 

// std::vector<std::tuple<cpp2::fuzzing::translation_unit_node>> GenerateSeeds(std::string_view dir) {
//     std::vector<std::tuple<cpp2::fuzzing::translation_unit_node>> seeds;
//     int parsed_ok_count = 0;
//     for (const auto file : ::fuzztest::ReadFilesFromDirectory(dir)) {
//         std::string f(std::get<0>(file));
//         cppfront c(f);
//         std::stringstream out;

//         if (!c.had_no_errors()) {
//           c.print_errors();
//         } 
        
//         // // c.parser_debug_print(out);
//         // fuzzing::translation_unit_node node;
//         // node.ParseFromString(out.str());
//         // seeds.emplace_back(node);
//         // std::cout << "Added " << f << "\n"; 
//     }

//     return seeds;
// }

FUZZ_TEST(RoundTripTest, Cpp2Basic);
// FUZZ_TEST(RoundTripTest, Cpp2);

} //namespace
} //namespace cpp2


// auto main(int argc, char** argv) -> int {
//   ::testing::InitGoogleTest(&argc, argv);
//   // gtest should remove flags, leaving just input files.
//   std::vector<std::string_view> cpp2_files(&argv[1], &argv[argc]);
//   cpp2::cpp2_files = &cpp2_files;
//   return RUN_ALL_TESTS();
// }


// FUZZ_TEST(RoundTripTest, Cpp2).WithDomains(
//   fuzztest::Arbitrary<fuzzing::translation_unit_node>())
//   .WithSeeds();

// std::vector<std::tuple<std::string>> ReadFilesFromDirectory(std::string_view dir) {
//     std::vector<std::tuple<std::string>> contents;
//     for (const std::string_view file : *cpp2_files) {
//         // file.open(); 
//         std::string f(file);
//         cppfront c(f);
//         std::stringstream out;
//         c.parser_debug_print(out);
//         contents.emplace_back(out.str());
//         // file.close();
//     }

//     return contents;
// }

// std::vector<std::tuple<std::string>> seeds = ReadFilesFromDirectory("/regression-tests:cpp2_files");

// FUZZ_TEST(RoundTripTest, Cpp2).WithDomains(
//     fuzztest::Arbitrary<fuzzing::translation_unit_node>())
//     .WithSeeds(seeds);

    // std::vector<std::string_view> cpp2_files(&argv[1], &argv[argc]);
    // cpp2_files = &cpp2_files;