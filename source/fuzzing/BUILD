load("@rules_proto//proto:defs.bzl", "proto_library")

proto_library(
    name = "cpp2_proto",
    srcs = ["cpp2.proto"], 
    visibility = ["//visibility:public"],
)

cc_proto_library(
    name = "cpp2_cc_proto",
    deps = [":cpp2_proto"], 
    visibility = ["//visibility:public"],
)

cc_library(
    name = "ast_to_proto",
    srcs = ["ast_to_proto.cpp"],
    hdrs = ["ast_to_proto.h"],
    deps = ["//source:cppfront", 
            ":cpp2_cc_proto"]
    # visibility = ["//visibility:public"],
)

cc_test(
  name = "ast_to_proto_test",
  size = "small",
  srcs = ["ast_to_proto_test.cpp"],
  deps = ["@com_google_googletest//:gtest_main", 
          ":ast_to_proto", 
          ":cpp2_cc_proto"],
#   hdrs = ["ast_to_proto.h"],
)