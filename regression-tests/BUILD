# filegroup(
#     name = "cpp2_file",
#     srcs = glob(["**/curr_test.cpp2"]),
#     visibility = ["//visibility:public"],
# )

filegroup(
    name = "cpp2_files",
    # srcs = glob(["**/curr_test.cpp2"]),
    srcs = glob(["**/*.cpp2"]),
    visibility = ["//visibility:public"],
)
# //CURRENT FAILS: 
#  -bunch of tests have double semicolons - See L4626 in parse.h
#  - missing semicolons at end of if declarations for no reason: 
     # -  missing Specifically in cases of uninitialized things like points. 
#  - mixed-type-safety1.cpp2: print("\ns* is Shape?  ", s* is Shape  ); breaks over  unexpected text 
# - ( is not properly matched by ) (at 'Shape') atL3798 in parse.h. 
#  - uninitialized things have no semicolon, per x:std::string//;// in 
# mixed-initialization-safety-3-contract-violation. Perhaps it should fail - who knows? 
#  - mixed-lifetime-safety-and-null-contracts: *= dereference pointer reading as multiplicative
#   resulting in unequal proto trees
#  - 
