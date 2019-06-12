// Copyright 2018 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <stdio.h>
#include <string.h>
#include <esp_log.h>
#include <esp_err.h>
#include <esp_system.h>

#include <auth_provisioning/auth_config.h>

#include "auth_config.pb-c.h"

static const char *TAG = "auth_config";

esp_err_t get_device_id(char *device_id) {
    uint8_t mac_addr[6] = {0};
    esp_err_t ret = esp_efuse_mac_get_default(mac_addr);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Get base MAC address from BLK0 of EFUSE error (%s)", esp_err_to_name(ret));
        return ret;
    }
	sprintf(device_id, "%02X:%02X:%02X:%02X:%02X:%02X",
            mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    return ESP_OK;
}

int auth_prov_config_data_handler(uint32_t session_id, const uint8_t *inbuf, ssize_t inlen, uint8_t **outbuf, ssize_t *outlen, void *priv_data)
{
    AuthConfigRequest *req;
    AuthConfigResponse resp;
    auth_prov_config_handler_t app_handler_auth_config = (auth_prov_config_handler_t) priv_data;

    req = auth_config_request__unpack(NULL, inlen, inbuf);
    if (!req) {
        ESP_LOGE(TAG, "Unable to unpack config data");
        return ESP_ERR_INVALID_ARG;
    }

    auth_config_response__init(&resp);
    resp.status = AUTH_CONFIG_STATUS__ConfigFail;

    char device_id[(2 + 1) * 6];
    if (app_handler_auth_config && get_device_id(device_id) == ESP_OK) {
        auth_config_t config;
        strlcpy(config.endpoint, req->endpoint, sizeof(config.endpoint));
        strlcpy(config.token, req->token, sizeof(config.token));

        esp_err_t err = app_handler_auth_config(&config, device_id);
        // TODO: get the message from the handler and put it into the status
        // TODO: add "message" field to the status
        resp.status = (err == ESP_OK) ? AUTH_CONFIG_STATUS__ConfigSuccess :
                                        AUTH_CONFIG_STATUS__ConfigFail;
        resp.deviceid = device_id;
    }
    auth_config_request__free_unpacked(req, NULL);

    ESP_LOGI(TAG, "Auth Config Response with Device ID:\n\t%s", resp.deviceid);

    *outlen = auth_config_response__get_packed_size(&resp);
    if (*outlen <= 0) {
        ESP_LOGE(TAG, "Invalid encoding for response");
        return ESP_FAIL;
    }

    *outbuf = (uint8_t *) malloc(*outlen);
    if (*outbuf == NULL) {
        ESP_LOGE(TAG, "System out of memory");
        return ESP_ERR_NO_MEM;
    }

    auth_config_response__pack(&resp, *outbuf);
    return ESP_OK;
}