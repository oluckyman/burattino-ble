PATH := /Users/oluckyman/Projects/esp/protobuf-c/protoc-c:$(PATH)

all: c_proto swift_proto

c_proto: *.proto
	@protoc --c_out=../proto-c/ *.proto

swift_proto: *.proto
	@protoc --swift_out=/Users/oluckyman/Projects/Burattino/burattino-app/Burattino/Burattino/Shared/Services/Networking/EspressifProvision/proto *.proto
