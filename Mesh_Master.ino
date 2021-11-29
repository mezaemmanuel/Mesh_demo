#include <painlessMesh.h>
#define   MESH_PREFIX     "SSID"
#define   MESH_PASSWORD   "PASSWORD"
#define   MESH_PORT       5555
painlessMesh  mesh;
Scheduler userScheduler;

uint8_t WIFIChannel=13;

void receivedCallback( uint32_t from, String &msg ) {
  Serial.println(msg);
}

void setup() {
  Serial.begin(115200);
  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT, WIFI_AP_STA, WIFIChannel);
  mesh.onReceive(&receivedCallback);
  Serial.println("Mi indentificador de nodo en es:" + String(mesh.getNodeId()));
}

void loop() {
  // it will run the user scheduler as well
  if (Serial.available()){
    String Reading = Serial.readString();  
    Serial.println("Sending:"+Reading);  
    mesh.sendBroadcast(Reading);
  }
  mesh.update();
}
