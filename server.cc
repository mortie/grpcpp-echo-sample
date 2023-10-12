#include "proto/sample.grpc.pb.h"

#include <grpcpp/grpcpp.h>
#include <iostream>
#include <string>

class EchoServiceImpl: public EchoService::Service {
	grpc::Status Echo(grpc::ServerContext *ctx, const EchoRequest *req, EchoResponse *res)
	{
		std::string msg = req->msg();
		msg += ' ';
		msg += std::to_string(n++);
		std::cerr << "Responding to 'echo' request with message: '" << msg << "'\n";
		res->set_msg(std::move(msg));
		return grpc::Status::OK;
	}

	int n = 0;
};

int main(int argc, char **argv)
{
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " <listen address>";
		return 1;
	}

	EchoServiceImpl service;

	grpc::ServerBuilder builder;
	builder.AddListeningPort(argv[1], grpc::InsecureServerCredentials());
	builder.RegisterService(&service);
	auto server = builder.BuildAndStart();
	if (!server) {
		std::cerr << "failed to create server.\n";
		return 1;
	}

	std::cerr << "Started server on: " << argv[1] << '\n';
	server->Wait();
}
