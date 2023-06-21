#include <homekit/homekit.h>
#include <homekit/characteristics.h>

homekit_characteristic_t remote_switch = HOMEKIT_CHARACTERISTIC_(ON, false);
homekit_characteristic_t name = HOMEKIT_CHARACTERISTIC_(NAME, "Remote Desktop Switch");

void my_accessory_identify(homekit_value_t _value) {
	printf("accessory identify\n");
}

homekit_accessory_t *accessories[] = {
    HOMEKIT_ACCESSORY(.id=1, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Remote Desktop Switch"),
            HOMEKIT_CHARACTERISTIC(MANUFACTURER, "NitroStudio"),
            HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "NS_RDS_001"),
            HOMEKIT_CHARACTERISTIC(MODEL, "NodeMCU"),
            HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.0"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify),
            NULL
        }),
		HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]){
			&remote_switch,
			&name,
			NULL
		}),
        NULL
    }),
    NULL
};

homekit_server_config_t config = {
		.accessories = accessories,
		.password = "123-45-678"
};


