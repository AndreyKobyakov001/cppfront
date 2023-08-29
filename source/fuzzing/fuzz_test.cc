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

#include <filesystem>
namespace fs = std::filesystem;

namespace cpp2 {
namespace {

auto write_to_file(const std::string_view filename, const std::string_view contents) { 
  std::ofstream f;
  f.open(filename.data());
  f << contents; 
  f.close(); 
}

void Cpp2(const fuzzing::translation_unit_node& c) {
    std::stringstream out;
    TranslationUnitToCpp2(c, out); 
    std::cout << out.str();
    std::cout << "Size: " << c.ByteSize() << "\n";
    cppfront parsed_c(out.str());
    // if (!parsed_c.had_no_errors()) {
    //   std::cout << "Parsed cpp2 code has errors\n";
    // } else { 
    //   std::cout << "Parsed correctly\n"; 
    // }
}


// static std::vector<std::string_view>* cpp2_files = nullptr;

std::vector<std::tuple<cpp2::fuzzing::translation_unit_node>> GenerateSeeds(std::string_view dir) {
    std::vector<std::tuple<cpp2::fuzzing::translation_unit_node>> seeds;
    std::cerr << "Current Directory: " << std::filesystem::current_path() << "\n"; 
    auto files = ::fuzztest::ReadFilesFromDirectory(dir);
    std::cout << "FOUND: " << files.size() << " files\n";
    for (const auto& file_contents : files) {
        std::stringstream f(std::get<0>(file_contents));
        cppfront c("fuzz.cpp2", f);
        std::stringstream out;
        const std::unique_ptr<translation_unit_node>& parse_tree = c.get_parse_tree(); 
        if (parse_tree != nullptr) {
          seeds.push_back(TranslationUnitToProto(*parse_tree));
          std::cerr << "Added file\n"; 
        }
    }
    // std::cout << "HELLO\n"; 
    return seeds;
}

FUZZ_TEST(RoundTripTest, Cpp2).WithDomains(
  fuzztest::Arbitrary<fuzzing::translation_unit_node>())
    // .WithSeeds(seeds);
    .WithSeeds(GenerateSeeds("regression-tests"));

} //namespace
} //namespace cpp2
