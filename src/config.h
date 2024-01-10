#ifndef CONFIG_H_
#define CONFIG_H_

extern const char *  mqtt_server;
extern const char *  username;
extern const char *  password;
extern const char * ssid;
extern const char * passphrase;

#define MQTT_TOPIC_ACCEL "haus3/tor"
#define SENSOR_SMOOTHING_FACTOR 4


#endif // BASE_H