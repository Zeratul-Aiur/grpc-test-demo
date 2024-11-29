# grpc-test-demo

- 测试 gRPC 的传输性能。

```bash
# 启动服务端
bazelisk run //:service
# 启动客户端，传输 2GB 文件
bazelisk run //:client -- 2gb_file.txt
```
