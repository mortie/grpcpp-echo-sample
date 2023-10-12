#include "proto/sample.grpc.pb.h"

#include <grpcpp/grpcpp.h>
#include <iostream>
#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " <server address>";
		return 1;
	}

	auto channel = grpc::CreateChannel(argv[1], grpc::InsecureChannelCredentials());
	auto stub = EchoService::NewStub(channel);

	while (true) {
		grpc::ClientContext ctx;
		EchoResponse resp;
		EchoRequest req;
		req.set_msg("Hello");
		grpc::Status status = stub->Echo(&ctx, req, &resp);

		if (status.ok()) {
			std::cout << "Response message: " << resp.msg() << '\n';
		} else {
			std::cout << "Error: " << status.error_message() << ": " << status.error_details() << '\n';
		}

		sleep(1);
	}
}
