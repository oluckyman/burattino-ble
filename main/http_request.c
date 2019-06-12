#include <string.h>
#include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#include "esp_http_client.h"
// #include "lwip/err.h"
// #include "lwip/sockets.h"
// #include "lwip/sys.h"
// #include "lwip/netdb.h"
// #include "lwip/dns.h"
#include "./http_request.h"

static EventGroupHandle_t event_group;
static const char *TAG = "bur[http-request]";

BackendResponse backend_response;


esp_err_t _http_event_handler(esp_http_client_event_t *evt) {
    switch(evt->event_id) {
        case HTTP_EVENT_ERROR:
            ESP_LOGV(TAG, "HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGV(TAG, "HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_HEADER_SENT:
            ESP_LOGV(TAG, "HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:
            ESP_LOGV(TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
            break;
        case HTTP_EVENT_ON_DATA:
            if (!esp_http_client_is_chunked_response(evt->client)) {
                ESP_LOGI(TAG, "HTTP_EVENT_ON_DATA:\n%.*s\n", evt->data_len, (char *)evt->data);
                snprintf(backend_response.message, sizeof(backend_response.message), "%.*s", evt->data_len, (char *)evt->data);
            }
            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGV(TAG, "HTTP_EVENT_ON_FINISH");
            break;
        case HTTP_EVENT_DISCONNECTED:
            ESP_LOGV(TAG, "HTTP_EVENT_DISCONNECTED");
            break;
        default:
            ESP_LOGW(TAG, "Unknown event id: %d", evt->event_id);
            break;
    }
    return ESP_OK;
}


void http_request_task(void *pvParameters) {
    RequestParams *params = (RequestParams *)pvParameters;
    esp_http_client_config_t config = {
        .url = params->url,
        .method = HTTP_METHOD_PUT,
        .event_handler = _http_event_handler,
        .buffer_size = 2 * 1024,
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);

    char *header_buf = NULL;
    asprintf(&header_buf, "Token %s", params->token);
    esp_http_client_set_header(client, "Authorization", header_buf);
    esp_http_client_set_header(client, "Content-Type", "application/json");
    esp_http_client_set_post_field(client, params->body, strlen(params->body));

    esp_err_t err = esp_http_client_perform(client);

    if (err == ESP_OK) {
        ESP_LOGI(TAG, "HTTP PUT Status = %d, content_length = %d",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
        backend_response.status_code = esp_http_client_get_status_code(client);
    } else {
        ESP_LOGE(TAG, "HTTP PUT request failed: %s", esp_err_to_name(err));
        backend_response.status_code = 500;
    }

    esp_http_client_cleanup(client);
    free(header_buf);
    xEventGroupSetBits(event_group, HTTP_REQUEST_DONE_BIT);
    vTaskDelete(NULL);
}


BackendResponse http_request(EventGroupHandle_t _event_group, RequestParams *params) {
    event_group = _event_group;

    xEventGroupClearBits(event_group, HTTP_REQUEST_DONE_BIT);
    xTaskCreate(&http_request_task, "http_request_task", 4096, params, 5, NULL);
    xEventGroupWaitBits(event_group, HTTP_REQUEST_DONE_BIT, true, false, portMAX_DELAY);
    return backend_response;
}