
TEST(RoundTripTest, Roundtrip) {
  int parsed_ok_count = 0;
  int correct_count = 0; 
  bool debug = true;
  std::cout << "Size:" << cpp2_files->size() << "\n" << std::flush;
  for (const std::string_view filename : *cpp2_files) {
    std::string f(filename);
    cppfront c(f); 
    if (!c.had_no_errors()) {
      c.print_errors();
    } else {
      parsed_ok_count++; //move ++ to the start for efficiency and all that (much good it'll do you)
      const std::unique_ptr<translation_unit_node>& parse_tree = c.get_parse_tree(); 
      if (1 == 0) {
        std::cout << "Parse tree time:" << parse_tree.get() << "\n" << std::flush;
      }
      const fuzzing::translation_unit_node translation_unit_proto = 
          TranslationUnitToProto(*parse_tree);
      std::stringstream out;
      TranslationUnitToCpp2(translationz_unit_proto, out); 
      write_to_file("/tmp/c2.cpp2", out.str());
      if (debug) {   
        std::cout << out.str(); 
      }
      if(debug) { 
        SCOPED_TRACE(testing::Message()
                    << "Cpp2 file: " << filename << ", source from proto:\n"
                    << out.str());
      }
      std::istringstream source_from_proto(out.str());
      cppfront c2(f, source_from_proto); 
      const auto c_contents = translation_unit_to_string(c);
      const auto c2_contents = translation_unit_to_string(c2);
      write_to_file("/tmp/c_contents", c_contents);
      write_to_file("/tmp/c2_contents", c2_contents);
      write_to_file("/tmp/proto_tree", translation_unit_proto.DebugString());
      //rename this to not be retarded
      if (c2.had_no_errors()) {
        
        if (debug) {  
          EXPECT_EQ(c_contents, c2_contents);
        }
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
          std::cout << parsed_ok_count << ". " << filename << "\n";
          ADD_FAILURE() << "Parse error ";
      }
    }
  }
  std::cout << "Correct File Parsing: " << correct_count << " out of " << parsed_ok_count << " :) \n"; 
  // Makes sure files were actually processed.
  EXPECT_GT(parsed_ok_count, 0);
}