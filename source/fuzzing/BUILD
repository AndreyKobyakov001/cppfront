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
