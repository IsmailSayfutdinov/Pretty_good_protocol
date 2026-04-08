#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "lwip/sockets.h"
#include "driver/gpio.h"

#include "protocol.h"
#include "json_encode.h"
#include "tlv_encode.h"
#include "proto_encode.h"

#define AP_SSID "nano-net"
#define AP_PASSWORD "12345678"
#define UDP_PORT 3333
#define LED_GPIO 7

static const char *TAG = "sender";

void wifi_init_softap(void)
{
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = AP_SSID,
            .ssid_len = strlen(AP_SSID),
            .password = AP_PASSWORD,
            .max_connection = 4,
            .authmode = WIFI_AUTH_WPA2_PSK,
        },
    };

    esp_wifi_set_mode(WIFI_MODE_AP);
    esp_wifi_set_config(WIFI_IF_AP, &wifi_config);
    esp_wifi_start();

    ESP_LOGI(TAG, "SoftAP started. SSID: %s  Password: %s", AP_SSID, AP_PASSWORD);
    ESP_LOGI(TAG, "My IP: 192.168.4.1");
}

void udp_send_task(void *pvParameters)
{
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    int broadcast = 1;
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));

    struct sockaddr_in dest_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(UDP_PORT),
    };
    inet_pton(AF_INET, "192.168.4.255", &dest_addr.sin_addr);

    while (1)
    {
        // JSON
        key_press_t test_msg = {
            .msgType = MSG_KEY_PRESS,
            .version = PROTOCOL_VERSION,
            .keyId = 1,
            .isPressed = true,
            .msgOrder = 1};

        char *json = encode_key_press_json(&test_msg);
        sendto(sock, json, strlen(json), 0,
               (struct sockaddr *)&dest_addr, sizeof(dest_addr));
        ESP_LOGI(TAG, "JSON sent, %d bytes", strlen(json));
        free(json);
        vTaskDelay(pdMS_TO_TICKS(1000));

        // TLV
        uint16_t tlv_len = 0;
        uint8_t *tlv = encode_key_press_tlv(&test_msg, &tlv_len);
        sendto(sock, tlv, tlv_len, 0,
               (struct sockaddr *)&dest_addr, sizeof(dest_addr));
        ESP_LOGI(TAG, "TLV sent, %d bytes", tlv_len);
        free(tlv);
        vTaskDelay(pdMS_TO_TICKS(1000));

        // PROTOBUF
        uint8_t proto_buf[64];
        size_t proto_len = 0;
        bool ok = encode_key_press_proto(&test_msg, proto_buf, sizeof(proto_buf), &proto_len);
        if (ok)
        {
            sendto(sock, proto_buf, proto_len, 0,
                   (struct sockaddr *)&dest_addr, sizeof(dest_addr));
            ESP_LOGI(TAG, "Proto sent, %d bytes", proto_len);
        }
        else
        {
            ESP_LOGE(TAG, "Proto encoding failed");
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    close(sock);
    vTaskDelete(NULL);
}

void app_main(void)
{
    nvs_flash_init();
    esp_netif_init();
    esp_event_loop_create_default();
    wifi_init_softap();
    xTaskCreate(udp_send_task, "udp_send", 4096, NULL, 5, NULL);
}
