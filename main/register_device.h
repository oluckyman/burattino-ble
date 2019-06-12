#ifndef REGISTER_DEVICE_H_INCLUDED
#define REGISTER_DEVICE_H_INCLUDED
#include "./http_request.h"

BackendResponse register_device_on_backend(const char *endpoint, const char *token, const char *device_id);

#endif