#pragma once
#include "protocol.h"
#include "protocol.pb.h"

bool encode_key_press_proto(const key_press_t *msg, uint8_t *buf, size_t buf_size, size_t *out_len);
bool encode_led_brightness_proto(const led_brightness_t *msg, uint8_t *buf, size_t buf_size, size_t *out_len);