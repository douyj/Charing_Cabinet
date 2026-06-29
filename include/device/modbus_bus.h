#ifndef MODEBUS_BUS_H
#define MODEBUS_BUS_H

#include <modbus.h>

/*
 * 初始化 Modbus RTU 总线
 * dev: 串口设备，例如 "/dev/ttyUSB0" 或 "/dev/ttymxc2"
 * baud: 波特率，例如 9600
 * 返回值：0 成功，-1 失败
 */
int modbus_bus_init(const char *dev, int baud);

/*
 * 设置当前要通信的从机地址
 * slave_id: 从机地址，一般 1~247
 * 返回值：0 成功，-1 失败
 */
int modbus_bus_set_slave(int slave_id);

/*
 * 获取全局 modbus_t 指针
 * 其他设备模块通过它调用 modbus_read_registers 等函数
 */
modbus_t *modbus_bus_get_ctx(void);

/*
 * 设置调试开关
 * enable: 1 开启，0 关闭
 */
void modbus_bus_set_debug(int enable);

/*
 * 关闭并释放 Modbus 总线
 */
void modbus_bus_close(void);

#endif