workspace(name = "cpp2")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

rules_proto_version = "5.3.0-21.7"

http_archive(
    name = "rules_proto",
    sha256 = "dc3fb206a2cb3441b485eb1e423165b231235a1ea9b031b4433cf7bc1fa460dd",
    strip_prefix = "rules_proto-{0}".format(rules_proto_version), 
    urls = [
        "https://github.com/bazelbuild/rules_proto/archive/refs/tags/{0}.tar.gz".format(rules_proto_version),
    ],
)
load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")
rules_proto_dependencies()
rules_proto_toolchains()

