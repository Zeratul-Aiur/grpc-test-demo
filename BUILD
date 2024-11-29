load("@com_grail_bazel_compdb//:defs.bzl", "compilation_database")
load("@com_grail_bazel_output_base_util//:defs.bzl", "OUTPUT_BASE")
load("@rules_proto//proto:defs.bzl", "proto_library")
load("@rules_proto_grpc//cpp:defs.bzl", "cpp_proto_library")

proto_library(
    name = "transfer_proto",
    srcs = ["transfer.proto"],
    deps = ["@com_google_protobuf//:any_proto"],
)

cpp_proto_library(
    name = "transfer_proto_lib",
    protos = [":transfer_proto"],
)

cc_binary(
    name = "client",
    srcs = ["client.cpp"],
    deps = [
        ":transfer_proto_lib",
        "@com_github_grpc_grpc//:grpc",
    ],
)

cc_binary(
    name = "service",
    srcs = ["service.cpp"],
    deps = [
        ":transfer_proto_lib",
        "@com_github_grpc_grpc//:grpc",
    ],
)

compilation_database(
    name = "compdb",
    testonly = True,
    # OUTPUT_BASE is a dynamic value that will vary for each user workspace.
    # If you would like your build outputs to be the same across users, then
    # skip supplying this value, and substitute the default constant value
    # "__OUTPUT_BASE__" through an external tool like `sed` or `jq` (see
    # below shell commands for usage).
    output_base = OUTPUT_BASE,
    targets = [
        ":client",
        ":service",
    ],
)
