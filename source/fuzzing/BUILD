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
    deps = ["//source:cppfront_lib", 
            ":cpp2_cc_proto"]
    # visibility = ["//visibility:public"],
)

cc_test(
  name = "round_trip_test",
  srcs = ["round_trip_test.cpp"],
  size = "small",
  deps = ["@com_google_googletest//:gtest", 
          ":ast_to_proto",
          ":proto_to_cpp2",
          "//source:cppfront_lib", 
          ":cpp2_cc_proto"],
  args = [
    "$(locations //regression-tests:cpp2_files)",
    ],
  data = [
    "//regression-tests:cpp2_files",
    ],
)

cc_test(
    name = "fuzz_test",
    srcs = ["fuzz_test.cc"],
    size = "small",
    deps = [
        "@com_google_googletest//:gtest",
        ":ast_to_proto",
        ":proto_to_cpp2",
        "//source:cppfront_lib",
        ":cpp2_cc_proto",
        # "fuzz_test.cc",
        "@com_google_fuzztest//fuzztest",
        "@com_google_fuzztest//fuzztest:fuzztest_gtest_main",
        # "@com_google_libprotobuf_mutator//:libprotobuf_mutator",
        # ":mutator", 
    ],
    args = [
        "$(locations //regression-tests:cpp2_files)",
    ],
    data = [
        "//regression-tests:cpp2_files",
    ],
    # corpus = glob(["fuzzer_corpus/*"]),
    # shard_count = 8,
    # tags = ["proto-fuzzer"],
    # What? 
)


# cc_library(
#     name = "mutator",
#     srcs = ["mutator.cc"],
#     hdrs = ["mutator.h"],
#     deps = ["//source:cppfront_lib", 
#             ":cpp2_cc_proto"]
# )

cc_library(
    name = "proto_to_cpp2",
    srcs = ["proto_to_cpp2.cpp"],
    hdrs = ["proto_to_cpp2.h"],
    deps = ["//source:cppfront_lib", 
            ":cpp2_cc_proto"]
)

cc_test(
  name = "ast_to_proto_test",
  size = "small",
  srcs = ["ast_to_proto_test.cpp"],
  deps = ["@com_google_googletest//:gtest_main", 
          ":ast_to_proto", 
          ":cpp2_cc_proto"],
)

cc_test(
    name = "proto_to_cpp2_test",
    size = "small",
    srcs = ["proto_to_cpp2_test.cpp"],
    deps = ["@com_google_googletest//:gtest_main", 
          ":proto_to_cpp2", 
          ":cpp2_cc_proto"],
)
