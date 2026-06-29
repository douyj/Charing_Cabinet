#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

typedef struct{
    float temperature;
    float humidity;
}temperature_sensor_data_t;

int temperature_sensor_read(int slave_id, temperature_sensor_data_t *data);

#endif