#include <Arduino.h>
#include "view.h"
#include "networking.h"
#include "sideled.h"


void event_handler_checkbox(struct _lv_obj_t * obj, lv_event_t event);
void event_handler_button(struct _lv_obj_t * obj, lv_event_t event);
void init_image_roller();
void mqtt_callback(char* topic, byte* payload, unsigned int length);

unsigned long next_lv_task = 0;

void event_handler_button(struct _lv_obj_t * obj, lv_event_t event) {
  
}

lv_obj_t * label_x;
lv_obj_t * label_y;
lv_obj_t * label_z;
lv_obj_t * label_state;

void init_gui() {
  add_label("accel:", 30, 10);
  label_x = add_label("0", 90, 10);
  label_y = add_label("0", 150, 10);
  label_z = add_label("0", 210, 10);
  label_state = add_label("", 90, 50);
}

// ----------------------------------------------------------------------------
// MQTT callback
// ----------------------------------------------------------------------------

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  // Parse Payload into String
  char * buf = (char *)malloc((sizeof(char)*(length+1)));
  memcpy(buf, payload, length);
  buf[length] = '\0';
  String payloadS = String(buf);
  payloadS.trim();

  Serial.println(topic);
  Serial.println(payloadS);
}


// ----------------------------------------------------------------------------
// UI event handlers
// ----------------------------------------------------------------------------

String buffer = "";
lv_obj_t * mbox;


// ----------------------------------------------------------------------------
// MAIN LOOP
// ----------------------------------------------------------------------------
unsigned long next_data_send = 0;
unsigned long next_data_get = 0;

float acc_raw_x = 0, acc_raw_y = 0, acc_raw_z = 0;
float acc_buf_x = 0, acc_buf_y = 0, acc_buf_z = 0;

bool isOpenGarageDoor = false;

void updateSideLeds() {
  set_sideled_state(0, 10, SIDELED_STATE_ON);
  if(isOpenGarageDoor) {
    set_sideled_color(0, 10, CRGB::Green);
  }else{
    set_sideled_color(0, 10, CRGB::Red);
  }
}

void updateGui() {
  lv_label_set_text(label_x, String(acc_buf_x).c_str());
  lv_label_set_text(label_y, String(acc_buf_y).c_str());
  lv_label_set_text(label_z, String(acc_buf_z).c_str());
  lv_label_set_text(label_state, isOpenGarageDoor ? "Garage door is open" :"Garage door is closed");
}

void loop_accel() {
  M5.IMU.getAccelData(&acc_raw_x, &acc_raw_y, &acc_raw_z);
  acc_buf_x = (acc_buf_x * 4 + acc_raw_x) / 5;
  acc_buf_y = (acc_buf_y * 4 + acc_raw_y) / 5;
  acc_buf_z = (acc_buf_z * 4 + acc_raw_z) / 5;

  if(acc_buf_y > 0.8) isOpenGarageDoor = false;
  else if(acc_buf_z < -0.8) isOpenGarageDoor = true;
  updateSideLeds();
  updateGui();
}

void loop_publish_data() {
  char buf[30];
  snprintf (buf, 32, "%.2f,%.2f,%.2f", acc_buf_x,acc_buf_y,acc_buf_z);
  mqtt_publish("m5core2/accel", buf);
}

void loop() {
  if(next_lv_task < millis()) {
    lv_task_handler();
    next_lv_task = millis() + 5;
  }
  if(next_data_send < millis()) {
    loop_publish_data();
    next_data_send = millis() + 1000;
  }
  if(next_data_get < millis()) {
    loop_accel();
    next_data_get = millis() + 250;
  }
  // Uncomment the following lines to enable MQTT
  mqtt_loop();
} 

// ----------------------------------------------------------------------------
// MAIN SETUP
// ----------------------------------------------------------------------------

void init_networking() {
  lv_obj_t * wifiConnectingBox = show_message_box_no_buttons("Connecting to WiFi...");
  lv_task_handler();
  delay(5);
  setup_wifi();
  mqtt_init(mqtt_callback);
  close_message_box(wifiConnectingBox);
}

void init_sensors() {
  Wire.begin(); 
  M5.IMU.Init();
}

void setup() {
  init_m5();
  init_display();
  Serial.begin(115200);
  
  // Uncomment the following lines to enable MQTT
  init_networking();


  init_gui();
  init_sideled();
  init_sensors();
}