#include "BluetoothSerial.h" 
BluetoothSerial ESP_BT; 
int incoming;
int LED_BUILTIN = 2; // on-board LED pin number

void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param){
  if(event == ESP_SPP_SRV_OPEN_EVT){
    Serial.println("Client Connected");
  }
}

void setup() {
  Serial.begin(115200); //serial monitor at 115200
  ESP_BT.register_callback(callback);
  ESP_BT.begin("ESP32"); //name of Bluetooth
  Serial.println("Bluetooth Device is Ready to Pair");
  pinMode (LED_BUILTIN, OUTPUT);
}
void loop() {
  
  if (ESP_BT.available()) // checking if we receive data from Bluetooth
  {
    incoming = ESP_BT.read(); // check what we recevived
    Serial.write(incoming); // print on Bluetooth serial
    Serial.print("Received:"); Serial.println(incoming);
    if (incoming == 49)
        {
        digitalWrite(LED_BUILTIN, HIGH);
        ESP_BT.println("LED turned ON");
        }
        
    if (incoming == 48)
        {
        digitalWrite(LED_BUILTIN, LOW);
        ESP_BT.println("LED turned OFF");
        }     
  }
  delay(20);
}
