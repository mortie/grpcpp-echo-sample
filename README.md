# gRPC++ Echo Sample

This is a sample application which implements a gRPC echo server and client.

## Usage

To compile the server and client, run:

    make

To start the server, run `./server <listen address>`, for example `./server localhost:3044`.

To start the client, run `./client <server address>`, for example `./client localhost:3044`.

## Dependencies

In addition to a C++ compiler, this project depends on the `grpc++` library, the `protobuf` library,
the `protoc` protobuf compiler and the gRPC C++ plug-in `grpc_cpp_plugin`.

On macOS, I believe `brew install grpc protoc` should be sufficient.
