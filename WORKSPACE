workspace(name = "grpc_test_demo")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "rules_proto_grpc",
    sha256 = "2a0860a336ae836b54671cbbe0710eec17c64ef70c4c5a88ccfd47ea6e3739bd",
    strip_prefix = "rules_proto_grpc-4.6.0",
    urls = ["https://github.com/rules-proto-grpc/rules_proto_grpc/releases/download/4.6.0/rules_proto_grpc-4.6.0.tar.gz"],
)

load("@rules_proto_grpc//:repositories.bzl", "rules_proto_grpc_repos", "rules_proto_grpc_toolchains")

rules_proto_grpc_toolchains()

# load package:
# @rules_proto
# @rules_python
# @build_bazel_rules_swift
# @bazel_skylib
# @rules_pkg
# @com_google_protobuf
# @com_github_grpc_grpc
# @zlib
rules_proto_grpc_repos()

load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")

rules_proto_dependencies()

rules_proto_toolchains()

load("@rules_proto_grpc//cpp:repositories.bzl", rules_proto_grpc_cpp_repos = "cpp_repos")

rules_proto_grpc_cpp_repos()

load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")

grpc_deps()

load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")

grpc_extra_deps()
