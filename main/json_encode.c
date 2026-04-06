#include "json_encode.h"
#include "cJSON.h"

const char *msg_type_to_string(msg_type_t type)
{
    switch (type)
    {
    case MSG_KEY_PRESS:
        return "KEY_PRESS";
    case MSG_LED_BRIGHTNESS:
        return "LED_BRIGHTNESS";
    default:
        return "UNKNOWN";
    }
}

char *encode_key_press_json(const key_press_t *msg)
{
    cJSON *root = cJSON_CreateObject();

    cJSON_AddStringToObject(root, "msgType", msg_type_to_string(msg->msgType));
    cJSON_AddNumberToObject(root, "version", msg->version);
    cJSON_AddNumberToObject(root, "keyId", msg->keyId);
    cJSON_AddBoolToObject(root, "isPressed", msg->isPressed);
    cJSON_AddNumberToObject(root, "msgOrder", msg->msgOrder);

    char *json_str = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    return json_str;
}
char *encode_led_brightness_json(const led_brightness_t *msg)
{
    cJSON *root = cJSON_CreateObject();

    cJSON_AddStringToObject(root, "msgType", msg_type_to_string(msg->msgType));
    cJSON_AddNumberToObject(root, "version", msg->version);
    cJSON_AddNumberToObject(root, "ledId", msg->ledId);
    cJSON_AddNumberToObject(root, "brightness", msg->brightness);
    cJSON_AddNumberToObject(root, "color", msg->color);
    cJSON_AddNumberToObject(root, "msgOrder", msg->msgOrder);

    char *json_str = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    return json_str;
}