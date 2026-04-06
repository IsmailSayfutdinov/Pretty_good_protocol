idf_component_register(SRCS "json_encode.c" "main.c" "tlv_encode.c" "protocol.pb.c" "pb_encode.c" "pb_decode.c" "pb_common.c" "proto_encode.c"
                    INCLUDE_DIRS "."
                    REQUIRES lwip esp_netif esp_event esp_wifi nvs_flash driver json)
