#include <errno.h>
#include <stdio.h>
#include <modbus.h>

#include "device/modbus_bus.h"

static modbus_t *g_ctx = NULL;

int modbus_bus_init(const char *dev, int baud)
{
    if(g_ctx != NULL){
        printf("Modbus bus already initialized\n");
        return 0;
    }

    /*创建对象*/
    g_ctx = modbus_new_rtu(dev, baud, 'N', 8, 1);
    if(g_ctx == NULL){
        printf("Failed to create modbus context\n");
        return -1;
    }

    /*超时响应 1s*/
    modbus_set_response_timeout(g_ctx, 1, 0);

    /*调试阶段开，正式阶段关*/
    modbus_bus_set_debug(1);

    /*打开串口*/
    if(modbus_connect(g_ctx) == -1){
        printf("Failed to connect modbus bus\n");
        modbus_free(g_ctx);
        g_ctx = NULL;
        return -1;
    }

    printf("Modbus bus initialized successfully\n");

    return 0;
}


int modbus_bus_set_slave(int slave_id)
{
    if(g_ctx == NULL){
        printf("Modbus bus not initialized\n");
        return -1;
    }

    if(modbus_set_slave(g_ctx, slave_id) == -1){
        printf("set slave %d failed: %s\n\n", slave_id, modbus_strerror(errno));
        return -1;
    }

    return 0;
}

modbus_t *modbus_bus_get_ctx(void)
{
    return g_ctx;
}


void modbus_bus_set_debug(int enable)
{
    if (g_ctx != NULL) {
        modbus_set_debug(g_ctx, enable);
    }
}

void modbus_bus_close(void)
{
    if (g_ctx != NULL) {
        modbus_close(g_ctx);
        modbus_free(g_ctx);
        g_ctx = NULL;
        printf("[modbus_bus] closed\n");
    }
}



