#include <fstream>
#include <string>

#include "grpcpp/server.h"
#include "grpcpp/server_builder.h"
#include "grpcpp/server_context.h"
#include "transfer.grpc.pb.h"
#include "transfer.pb.h"

#define CHUNK_SIZE 3 * 1024 * 1024 // 3MB

class FileTransferServiceImpl final : public FileTransferService::Service {
public:
  grpc::Status upload(grpc::ServerContext *context,
                      grpc::ServerReader<FileChunk> *reader,
                      UploadStatus *status) override {
    const auto start = std::chrono::high_resolution_clock::now();

    std::ofstream outfile;
    outfile.open("output.bin",
                 std::ios::binary | std::ios::out | std::ios::trunc);
    if (!outfile.is_open()) {
      std::cerr << "Error: Failed to open file." << std::endl;
      return grpc::Status::CANCELLED;
    }

    const char *data;
    FileChunk chunk;
    while (reader->Read(&chunk)) {
      data = chunk.content().c_str();
      outfile.write(data, chunk.content().length());
    }

    auto pos = outfile.tellp();
    status->set_length(pos);
    outfile.close();

    const auto end = std::chrono::high_resolution_clock::now();
    const auto duration =
        std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(
            end - start);

    std::cout << "Total transmission time: " << duration.count() << " ms"
              << std::endl;
    std::cout << "Total data transmitted: " << pos << " bytes" << std::endl;
    std::cout << "Transmission rate: "
              << (pos * 1000.0 / duration.count()) / 1024 / 1024 << " MB/s"
              << std::endl;

    return grpc::Status::OK;
  }
};

void run_server() {
  std::string server_address("0.0.0.0:50051");
  FileTransferServiceImpl service;

  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}

int main() {
  run_server();
  return 0;
}