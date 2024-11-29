
#include <chrono>
#include <fstream>
#include <memory>

#include "grpcpp/channel.h"
#include "grpcpp/client_context.h"
#include "grpcpp/create_channel.h"
#include "transfer.grpc.pb.h"
#include "transfer.pb.h"

#define CHUNK_SIZE 3 * 1024 * 1024 // 3MB

class TransferClient {
public:
  TransferClient(std::shared_ptr<grpc::Channel> channel)
      : stub_(FileTransferService::NewStub(channel)) {}

  void upload_file(const std::string &filename) {
    const auto start = std::chrono::high_resolution_clock::now();

    std::ifstream input_file;
    input_file.open(filename, std::ios::binary | std::ios::in);
    if (!input_file.is_open()) {
      std::cerr << "Error: File not found." << std::endl;
      return;
    }

    grpc::ClientContext context;
    UploadStatus upload_status;
    std::unique_ptr<grpc::ClientWriter<FileChunk>> writer(
        stub_->upload(&context, &upload_status));

    FileChunk chunk;
    char *buffer = new char[CHUNK_SIZE];
    size_t len = 0;
    while (!input_file.eof()) {
      input_file.read(buffer, CHUNK_SIZE);
      chunk.set_content(buffer, input_file.gcount());
      if (!writer->Write(chunk)) {
        std::cerr << "Error: Failed to write chunk." << std::endl;
        break;
      }
      len += input_file.gcount();
    }

    input_file.close();
    delete[] buffer;

    writer->WritesDone();
    auto status = writer->Finish();
    if (status.ok() && len != upload_status.length()) {
      const auto end = std::chrono::high_resolution_clock::now();
      const auto duration =
          std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(
              end - start);
      std::cout << "File uploaded successfully." << std::endl;
      std::cout << "Time taken: " << duration.count() << "ms" << std::endl;
      std::cout << "File size: " << len << " bytes" << std::endl;
      std::cout << "Speed: " << (len * 1000 / duration.count()) / 1024 / 1024
                << " MB/s" << std::endl;
    } else {
      std::cerr << "Error: " << status.error_message() << "len: " << len
                << " status.length(): " << upload_status.length() << std::endl;
    }
  }

private:
  std::unique_ptr<FileTransferService::Stub> stub_;
};

int main(int argc, char **argv) {
  std::string filename(argv[1]);
  std::string server_ip = "localhost";

  TransferClient client(grpc::CreateChannel(
      server_ip + ":50051", grpc::InsecureChannelCredentials()));
  client.upload_file(filename);

  return 0;
}