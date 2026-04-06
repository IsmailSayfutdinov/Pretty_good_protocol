#include <stdlib.h>
#include "tlv_encode.h"

uint8_t *encode_key_press_tlv(const key_press_t *msg, uint16_t *out_len)
{
    uint8_t *buf = malloc(21);
    // msgType
    buf[0] = 0x01;                  // Type
    buf[1] = 0x01;                  // Length
    buf[2] = (uint8_t)msg->msgType; // Value

    // msgOrder
    buf[3] = 0x02;
    buf[4] = 0x04;
    buf[5] = (msg->msgOrder >> 24) & 0xFF;
    buf[6] = (msg->msgOrder >> 16) & 0xFF;
    buf[7] = (msg->msgOrder >> 8) & 0xFF;
    buf[8] = msg->msgOrder & 0xFF;

    // keyId
    buf[9] = 0x03;
    buf[10] = 0x04;
    buf[11] = (msg->keyId >> 24) & 0xFF;
    buf[12] = (msg->keyId >> 16) & 0xFF;
    buf[13] = (msg->keyId >> 8) & 0xFF;
    buf[14] = msg->keyId & 0xFF;

    // isPressed
    buf[15] = 0x04;
    buf[16] = 0x01;
    buf[17] = (uint8_t)msg->isPressed;

    // version
    buf[18] = 0x08;
    buf[19] = 0x01;
    buf[20] = (uint8_t)msg->version;

    *out_len = 21;
    return buf;
}
uint8_t *encode_led_brightness_tlv(const led_brightness_t *msg, uint16_t *out_len)
{
    uint8_t *buf = malloc(27);
    // msgType
    buf[0] = 0x01;                  // Type
    buf[1] = 0x01;                  // Length
    buf[2] = (uint8_t)msg->msgType; // Value

    // msgOrder
    buf[3] = 0x02;
    buf[4] = 0x04;
    buf[5] = (msg->msgOrder >> 24) & 0xFF;
    buf[6] = (msg->msgOrder >> 16) & 0xFF;
    buf[7] = (msg->msgOrder >> 8) & 0xFF;
    buf[8] = msg->msgOrder & 0xFF;

    // ledId
    buf[9] = 0x05;
    buf[10] = 0x04;
    buf[11] = (msg->ledId >> 24) & 0xFF;
    buf[12] = (msg->ledId >> 16) & 0xFF;
    buf[13] = (msg->ledId >> 8) & 0xFF;
    buf[14] = msg->ledId & 0xFF;

    // brightness
    buf[15] = 0x06;
    buf[16] = 0x01;
    buf[17] = (uint8_t)msg->brightness;

    // color
    buf[18] = 0x07;
    buf[19] = 0x04;
    buf[20] = (msg->color >> 24) & 0xFF;
    buf[21] = (msg->color >> 16) & 0xFF;
    buf[22] = (msg->color >> 8) & 0xFF;
    buf[23] = msg->color & 0xFF;

    // version
    buf[24] = 0x08;
    buf[25] = 0x01;
    buf[26] = (uint8_t)msg->version;

    *out_len = 27;
    return buf;
}