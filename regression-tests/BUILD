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
#  - regression-tests\mixed-function-expression-with-repeated-capture.cpp2: 
        # std::ranges::for_each( view, callback ); becomes std::ranges::for_each( view, callback );; 
        # - with 2 semicolons. See L4626 in parse.h
#  - missing semicolons at end of if declarations for no reason: 
     # - regression-tests\mixed-initialization-safety-3.cpp2 & others. Also missing ; in L6.
    #  Specifically in cases of if { ... or SOMECODE = { ... .  - see L6099 in parse.h
#  - 
#  - 
#  - 
#  - 
#  - 