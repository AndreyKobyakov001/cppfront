package(
    default_visibility = ["//visibility:public"]
)
cc_library(
    name = "cppfront_lib",  
    srcs = ["parse.cpp", "common.cpp", "cppfront.cpp"],
    hdrs = ["common.h", "io.h", "lex.h", "parse.h", "reflect.h", "sema.h", "cppfront.h", "build.info"],
    deps = ["//include:cpp2util"],
) 
#make each header and source have its own build target :)


cc_binary(
    name = "cppfront",
    srcs = ["main.cpp"],
    deps = [":cppfront_lib"],  
    # visibility = ["//visibility:public"], 
)

