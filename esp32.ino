#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <PubSubClient.h>

// Configurações WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Configurações MQTT
const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;
const char* mqttClientId = "YGC_mqtt";
const char* mqttTopic = "FIAP/GS/Dicas";

// Definições de hardware
#define BTN_PIN 5
#define TFT_DC 2
#define TFT_CS 15
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

// Dicas de relaxamento
const char* relaxationTips[] = {
  "Inspire profundamente, segure a respiração por alguns segundos e expire lentamente.",
  "Feche os olhos e imagine um lugar tranquilo, prestando atenção aos detalhes ao seu redor.",
  "Ouça sua música calma favorita e concentre-se nas melodias relaxantes.",
  "Reserve 5 minutos para praticar meditação mindfulness, focando na sua respiração e no momento presente.",
  "Faça alongamentos suaves para liberar a tensão muscular, começando pela cabeça e pescoço até os pés.",
  "Desconecte-se de dispositivos eletrônicos por pelo menos 15 minutos. Respire fundo e aproveite o silêncio.",
  "Prepare uma xícara de chá de ervas, saboreando cada gole e permitindo-se relaxar.",
  "Escreva em um diário sobre seus pensamentos, sentimentos e gratidões do dia.",
  "Dedique alguns minutos para praticar a atenção plena, focando no presente e deixando de lado preocupações futuras.",
  "Sorria, encontre algo bonito ao seu redor e aprecie os pequenos momentos positivos da vida."
};

int currentTipIndex = 0;

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  // Callback para lidar com mensagens recebidas
  // (pode ser implementado conforme necessário)
}

void connectToMQTT() {
  while (!client.connected()) {
    Serial.println("Conectando ao servidor MQTT...");
    if (client.connect(mqttClientId)) {
      Serial.println("Conectado ao servidor MQTT");
      client.subscribe(mqttTopic);
    } else {
      Serial.print("Falha na conexão com o servidor MQTT, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BTN_PIN, INPUT_PULLUP);

  Serial.begin(115200);

  tft.begin();
  tft.setRotation(1);

  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.print("Conectando ao WiFi");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    tft.print(".");
  }

  tft.print("\nOK! IP=");
  tft.println(WiFi.localIP());

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  connectToMQTT();
}

void loop() {
  if (!client.connected()) {
    connectToMQTT();
  }
  client.loop();

  if (digitalRead(BTN_PIN) == LOW) {
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(0, 0);

    // Publica a próxima dica ao pressionar o botão
    String jsonTip = "{\"tip\": \"" + String(relaxationTips[currentTipIndex]) + "\"}";
    client.publish(mqttTopic, jsonTip.c_str());

    // Exibe a dica no LCD
    tft.setTextColor(ILI9341_BLUE);
    tft.println(relaxationTips[currentTipIndex]);

    currentTipIndex = (currentTipIndex + 1) % (sizeof(relaxationTips) / sizeof(relaxationTips[0]));

    delay(1000); // Atraso de debounce para evitar pressionamentos múltiplos do botão
  }

  delay(100);
}
