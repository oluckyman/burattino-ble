# Protobuf files for defining auth config-data packet structures

This is an example proto file defining auth configuration related data packet structures, namely -
1. AuthConfigRequest - for sending configuration data consisting of various fields
2. AuthConfigResponse - for receiving configuration status (fail/success)

Note : These proto files are not automatically compiled during the build process.

Run "make" (Optional) to generate the respective C and Python files. The generated C files are used by protocomm itself to create, delete and manipulate transaction packets. The generated Python files can be used by python based applications for implementing client side interface to protocomm layer.

Compilation requires protoc (Protobuf Compiler) and protoc-c (Protobuf C Compiler) installed. Since the generated files are to remain the same, as long as the proto files are not modified, therefore the generated files are already available under "protocomm/proto-c" and "protocomm/python" directories, and thus running make (and installing the Protobuf compilers) is optional.
