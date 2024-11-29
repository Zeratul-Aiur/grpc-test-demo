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

# For clangd auto complation.
http_archive(
    name = "com_grail_bazel_compdb",
    sha256 = "0f80f0e46309c489c5fa17f6ad87612eb4011afe972fdcda538430ddfae6ad1a",
    strip_prefix = "bazel-compilation-database-1c14b847c8b8fde1b022dafd41e7afaf5d2086bc",
    urls = ["https://github.com/aqrose-aidi-sdk-team/bazel-compilation-database/archive/1c14b847c8b8fde1b022dafd41e7afaf5d2086bc.zip"],
)

load("@com_grail_bazel_compdb//:config.bzl", "config_compdb")

config_compdb(
    cuda_enable = True,
    global_filter_flags = [
        # clang doesn't understand gcc's -fno-canonical-system-headers.
        # See here for more info:
        # https://github.com/clangd/clangd/issues/1004
        "-fno-canonical-system-headers",
        # nvcc's
        "-ccbin",
        "-gencode",
    ],
)

load("@com_grail_bazel_compdb//:deps.bzl", "bazel_compdb_deps")

bazel_compdb_deps()
