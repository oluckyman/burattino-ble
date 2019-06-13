/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: auth_config.proto */

#ifndef PROTOBUF_C_auth_5fconfig_2eproto__INCLUDED
#define PROTOBUF_C_auth_5fconfig_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003001 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _AuthConfigRequest AuthConfigRequest;
typedef struct _AuthConfigResponse AuthConfigResponse;


/* --- enums --- */

typedef enum _AuthConfigStatus {
  AUTH_CONFIG_STATUS__ConfigSuccess = 0,
  AUTH_CONFIG_STATUS__ConfigFail = 1
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(AUTH_CONFIG_STATUS)
} AuthConfigStatus;

/* --- messages --- */

struct  _AuthConfigRequest
{
  ProtobufCMessage base;
  char *endpoint;
  char *token;
};
#define AUTH_CONFIG_REQUEST__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&auth_config_request__descriptor) \
    , (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string }


struct  _AuthConfigResponse
{
  ProtobufCMessage base;
  AuthConfigStatus status;
  char *deviceid;
  char *backendmessage;
};
#define AUTH_CONFIG_RESPONSE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&auth_config_response__descriptor) \
    , AUTH_CONFIG_STATUS__ConfigSuccess, (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string }


/* AuthConfigRequest methods */
void   auth_config_request__init
                     (AuthConfigRequest         *message);
size_t auth_config_request__get_packed_size
                     (const AuthConfigRequest   *message);
size_t auth_config_request__pack
                     (const AuthConfigRequest   *message,
                      uint8_t             *out);
size_t auth_config_request__pack_to_buffer
                     (const AuthConfigRequest   *message,
                      ProtobufCBuffer     *buffer);
AuthConfigRequest *
       auth_config_request__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   auth_config_request__free_unpacked
                     (AuthConfigRequest *message,
                      ProtobufCAllocator *allocator);
/* AuthConfigResponse methods */
void   auth_config_response__init
                     (AuthConfigResponse         *message);
size_t auth_config_response__get_packed_size
                     (const AuthConfigResponse   *message);
size_t auth_config_response__pack
                     (const AuthConfigResponse   *message,
                      uint8_t             *out);
size_t auth_config_response__pack_to_buffer
                     (const AuthConfigResponse   *message,
                      ProtobufCBuffer     *buffer);
AuthConfigResponse *
       auth_config_response__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   auth_config_response__free_unpacked
                     (AuthConfigResponse *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*AuthConfigRequest_Closure)
                 (const AuthConfigRequest *message,
                  void *closure_data);
typedef void (*AuthConfigResponse_Closure)
                 (const AuthConfigResponse *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCEnumDescriptor    auth_config_status__descriptor;
extern const ProtobufCMessageDescriptor auth_config_request__descriptor;
extern const ProtobufCMessageDescriptor auth_config_response__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_auth_5fconfig_2eproto__INCLUDED */
