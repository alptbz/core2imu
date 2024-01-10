#include "networking.h"

WiFiClient espClient;
PubSubClient client(espClient);

char *macAddress;

std::vector<const char *> subscriptions;

void setup_wifi()
{
  Serial.println("Connecting to " + String(ssid));
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, passphrase);
  String macAddressS = WiFi.macAddress();
  macAddress = (char *)malloc((macAddressS.length() + 1) * sizeof(char));
  strcpy(macAddress, (macAddressS.c_str()));

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println(".");
  }
  Serial.println("\nSuccess\n");
}

void mqtt_loop()
{
  if (!client.connected())
  {
    mqtt_re_connect();
  }
  client.loop();
}

void mqtt_init(MQTT_CALLBACK_SIGNATURE)
{
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  mqtt_re_connect();
}

void mqtt_publish(const char *topic, const char *payload)
{
  client.publish(topic, payload);
}

void mqtt_re_connect()
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection, ClientID = ");
    Serial.println(macAddress);
    if (client.connect(macAddress))
    {
      for (const char *sub : subscriptions)
      {
        client.subscribe(sub);
      }
      Serial.println("Connected!");
    }
    else
    {
      Serial.println("failed, rc=");
      Serial.println(client.state());
      Serial.println("try again in 5 seconds");
    }
  }
}

void mqtt_subscribe(const char *topic)
{
  subscriptions.push_back(topic);
}
