#include "proto_encode.h"
#include "pb_encode.h"

bool encode_key_press_proto(const key_press_t *msg, uint8_t *buf, size_t buf_size, size_t *out_len)
{
    Packet packet = Packet_init_zero;
    KeyPress kp = KeyPress_init_zero;

    kp.keyId = msg->keyId;
    kp.isPressed = msg->isPressed;
    kp.msgOrder = msg->msgOrder;
    kp.version = msg->version;

    packet.which_msgType = Packet_keyPress_tag;
    packet.msgType.keyPress = kp;

    pb_ostream_t stream = pb_ostream_from_buffer(buf, buf_size);
    bool status = pb_encode(&stream, Packet_fields, &packet);
    *out_len = stream.bytes_written;
    return status;
}

bool encode_led_brightness_proto(const led_brightness_t *msg, uint8_t *buf, size_t buf_size, size_t *out_len)
{
    Packet packet = Packet_init_zero;
    LedBrightness kp = LedBrightness_init_zero;

    kp.ledId = msg->ledId;
    kp.brightness = msg->brightness;
    kp.color = msg->color;
    kp.msgOrder = msg->msgOrder;
    kp.version = msg->version;

    packet.which_msgType = Packet_ledBrightness_tag;
    packet.msgType.ledBrightness = kp;

    pb_ostream_t stream = pb_ostream_from_buffer(buf, buf_size);
    bool status = pb_encode(&stream, Packet_fields, &packet);
    *out_len = stream.bytes_written;
    return status;
}
