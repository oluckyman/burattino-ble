# Protobuf files for defining auth config-data packet structures

Note: These proto files are not automatically compiled during the build process.

To compile the respective C and Swift files update the paths in `makefile` and run `make`.

The generated C files are used by protocomm itself to create, delete and manipulate transaction packets. The generated Swift files are used by ios app for implementing client side interface to protocomm layer.

Compilation requires protoc (Protobuf Compiler) and protoc-c (Protobuf C Compiler) installed. Since the generated files are to remain the same, as long as the proto files are not modified, therefore the generated files are already available under "protocomm/proto-c" directory, and thus running make (and installing the Protobuf compilers) is optional.
