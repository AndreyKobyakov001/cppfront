cc_library(
    name = "cppfront_lib",  
    srcs = ["cppfront.h"],
    hdrs = ["common.h", "io.h", "lex.h", "parse.h", "reflect.h", "sema.h", "cppfront.h", "build.info"],
    deps = ["//include:cpp2util"],
) 

cc_binary(
    name = "cppfront",
    srcs = ["main.cpp"],
    deps = [":cppfront_lib"],   
)

