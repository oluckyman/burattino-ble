#include <stdio.h>
#include <esp_log.h>
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "./http_request.h"

static const char *TAG = "bur[register-device]";
static EventGroupHandle_t event_group;

BackendResponse register_device_on_backend(const char *endpoint, const char *token, const char *device_id) {
    ESP_LOGI(TAG, ">>>> Send Request to Backend");

    RequestParams *request_params = calloc(1, sizeof(RequestParams));

    asprintf(&request_params->url, "http://%s", endpoint);
    asprintf(&request_params->token, token);
    asprintf(&request_params->body, "{\"device\": \"%s\"}", device_id);

    event_group = xEventGroupCreate();
    BackendResponse response = http_request(event_group, request_params);
    // TODO: release event_group?

    free(request_params->url);
    free(request_params->token);
    free(request_params->body);
    free(request_params);

    ESP_LOGI(TAG, "<<<< Finish Request to Backend");
    return response;
}