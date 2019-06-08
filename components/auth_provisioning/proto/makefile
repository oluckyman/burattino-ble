all: c_proto swift_proto

c_proto: *.proto
	@export PATH=$PATH:/Users/oluckyman/Projects/esp/protobuf-c/protoc-c
	@protoc --c_out=../proto-c/ *.proto


swift_proto: *.proto
	@protoc --swift_out=/Users/oluckyman/Projects/Burattino/burattino-app/Burattino/Burattino/Shared/Services/Networking/EspressifProvision/proto *.proto