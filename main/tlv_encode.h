#pragma once
#include "protocol.h"

uint8_t *encode_key_press_tlv(const key_press_t *msg, uint16_t *out_len);
uint8_t *encode_led_brightness_tlv(const led_brightness_t *msg, uint16_t *out_len);