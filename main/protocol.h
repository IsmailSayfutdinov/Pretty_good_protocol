#pragma once
#include <stdint.h>
#include <stdbool.h>

#define PROTOCOL_VERSION 1

typedef enum
{
    MSG_KEY_PRESS,
    MSG_LED_BRIGHTNESS
} msg_type_t;

typedef struct
{
    msg_type_t msgType;
    uint8_t version;
    uint32_t keyId;
    bool isPressed;
    uint32_t msgOrder;
} key_press_t;

typedef struct
{
    msg_type_t msgType;
    uint8_t version;
    uint32_t ledId;
    uint8_t brightness;
    uint32_t color;
    uint32_t msgOrder;
} led_brightness_t;