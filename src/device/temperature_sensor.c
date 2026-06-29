#include <stdio.h>
#include <modbus.h>
#include <errno.h>

#include "device/modbus_bus.h"
#include "device/temperature_sensor.h"



int temperature_sensor_read(int slave_id, temperature_sensor_data_t *data){

    if(data == NULL){
        return -1;
    }

    modbus_t *ctx = modbus_bus_get_ctx();
    if(ctx == NULL){
        printf("Modbus bus not initialized\n");
        return -1;
    }

    if(modbus_bus_set_slave(slave_id)!=0){
        return -1;
    }

    uint16_t reg[4];
    int rc = modbus_read_registers(ctx, 0, 2, reg);
    if(rc == -1){
        printf("Failed to read registers from slave %d: %s\n", slave_id, modbus_strerror(errno));
        return -1;
    }

    data->temperature = reg[0] / 10.0f;
    data->humidity = reg[1] / 10.0f;

    return 0;
}
