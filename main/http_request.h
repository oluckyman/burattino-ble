#ifndef HTTP_REQUEST_H_INCLUDED
#define HTTP_REQUEST_H_INCLUDED

// #include "freertos/FreeRTOS.h"
// #include "freertos/event_groups.h"

static const int HTTP_REQUEST_DONE_BIT = BIT2;

typedef struct RequestParams {
    char *url;
    char *token;
    char *body;
} RequestParams;

int http_request(EventGroupHandle_t _event_group, RequestParams *params);

#endif