//***MESH**//
#include <painlessMesh.h>
#define   MESH_PREFIX     "SSID"
#define   MESH_PASSWORD   "PASSWORD"
#define   MESH_PORT       5555

Scheduler userScheduler;
painlessMesh  mesh;

void sendMessage() ; 
Task taskSendMessage( TASK_SECOND * 1 , TASK_FOREVER, &sendMessage );

void sendMessage() {
  
 String Mensaje = "Hola";
  Serial.println("El mensaje que voy a enviar es : " + Mensaje);
  Serial.println(Mensaje);
  mesh.sendBroadcast(Mensaje);
  //mesh.sendSingle(nodeidMaster, Mensaje);
}

// Needed for painless library-----------opcional.
void receivedCallback( uint32_t from, String &msg ) {
  Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
}
void newConnectionCallback(uint32_t nodeId) {
    Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}
void changedConnectionCallback() {
  Serial.printf("Changed connections\n");
}
void nodeTimeAdjustedCallback(int32_t offset) {
    Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
}
void setup() {
  Serial.begin(115200);
  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT, WIFI_AP_STA, 13);
  mesh.onReceive(&receivedCallback);

  taskSendMessage.setInterval( TASK_SECOND * 10);
  userScheduler.addTask(taskSendMessage);
  taskSendMessage.enable();

}

void loop() {
   mesh.update();

}
