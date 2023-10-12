PROTOC ?= $(shell which protoc)
GRPC_CPP_PLUGIN ?= $(shell which grpc_cpp_plugin)

PKGS := grpc++ protobuf
PKG_CFLAGS := $(shell pkg-config --cflags $(PKGS))
PKG_LIBS := $(shell pkg-config --libs $(PKGS))

ifeq ($(PROTOC),)
$(error Missing program: protoc)
endif

ifeq ($(GRPC_CPP_PLUGIN),)
$(error Missing program: grpc_cpp_plugin)
endif

CFLAGS := $(CFLAGS) -std=c++17 $(PKG_CFLAGS)
LDFLAGS := $(LDFLAGS) $(PKG_LIBS)

.PHONY: all
all: server client

server: server.o proto/sample.grpc.pb.o proto/sample.pb.o
	$(CXX) -o $@ $(LDFLAGS) $^

client: client.o proto/sample.grpc.pb.o proto/sample.pb.o
	$(CXX) -o $@ $(LDFLAGS) $^

%.o: %.cc proto/.sample.proto.stamp
	$(CXX) -c $(CFLAGS) -o $@ $<

proto/.sample.proto.stamp: sample.proto
	mkdir -p proto
	$(PROTOC) --cpp_out=proto --grpc_out=proto --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN) $<
	touch $@

.PHONY: clean
clean:
	rm -rf proto
	rm -f server server.o client client.o
