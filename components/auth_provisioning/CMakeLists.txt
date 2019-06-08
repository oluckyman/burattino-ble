set(COMPONENT_ADD_INCLUDEDIRS include)
set(COMPONENT_PRIV_INCLUDEDIRS proto-c)
set(COMPONENT_SRCS  "src/auth_config.c"
                    "proto-c/auth_config.pb-c.c")

set(COMPONENT_PRIV_REQUIRES protobuf-c)

register_component()
