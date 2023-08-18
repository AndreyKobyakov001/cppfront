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
#  - mixed-lifetime-safety-and-null-contracts: *= pointer parsed as multiplicative identity
#  - mixed-lifetime-safety-pointer-init: unexpected end of source file? 
#  - mixed-multiple-return-values: unexpected end of source file -> no final semicolon due to false object bool
#  - bunch of tests having problems with an-object declaration semicolon, as above. 
#  - 
#  - 
#  - 