#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22

const char* ssid = "ESP32_AP";
const char* password = "12345678";

DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

float temperature = 0;
float humidity = 0;

void setup() {
  WiFi.softAP(ssid, password);
  dht.begin();
  server.on("/", handleRoot);
  server.begin();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  server.handleClient();
  webSocket.loop();
  static unsigned long lastSend = 0;
  if (millis() - lastSend > 2000) {
    lastSend = millis();
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
    String data = "{\"temp\":" + String(temperature) + ",\"hum\":" + String(humidity) + "}";
    webSocket.broadcastTXT(data);
  }
}

void handleRoot() {
  server.send(200, "text/html", htmlPage());
}

String htmlPage() {
  return R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <title>DHT22 Dashboard</title>
      <style>
        body { font-family: Arial; text-align: center; padding: 50px; }
        h1 { font-size: 2rem; }
        .reading { font-size: 1.5rem; margin: 10px; }
      </style>
    </head>
    <body>
      <h1>ESP32 DHT22 Dashboard</h1>
      <div class="reading">Temperature: <span id="temp">--</span> °C</div>
      <div class="reading">Humidity: <span id="hum">--</span> %</div>
      <script>
        var gateway = `ws://${location.hostname}:81/`;
        var websocket = new WebSocket(gateway);
        websocket.onmessage = function(event) {
          var data = JSON.parse(event.data);
          document.getElementById('temp').innerText = data.temp;
          document.getElementById('hum').innerText = data.hum;
        };
      </script>
    </body>
    </html>
  )rawliteral";
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {}
