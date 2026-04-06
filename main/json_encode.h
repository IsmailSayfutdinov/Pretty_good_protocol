#pragma once
#include "protocol.h"

char *encode_key_press_json(const key_press_t *msg);
char *encode_led_brightness_json(const led_brightness_t *msg);