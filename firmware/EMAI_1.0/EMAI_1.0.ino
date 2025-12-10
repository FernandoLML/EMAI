#include <WiFi.h>
#include <Wire.h>
#include <Firebase_ESP_Client.h> // Biblioteca do Mobizt
#include "bsec.h" // Biblioteca do Sensor

// --- 1. CREDENCIAIS DO USUÁRIO ---
#define WIFI_SSID "Seu WI-FI"
#define WIFI_PASSWORD "Sua Senha"

// --- 2. CREDENCIAIS DO FIREBASE ---
#define API_KEY "Insira a chave da API"
#define DATABASE_URL "Insira a URL do banco de dados" // URL completa
#define USER_EMAIL "esp32@emai.com" // Usuário que você criou na etapa 1
#define USER_PASSWORD "12345678"

// --- OBJETOS GLOBAIS ---
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
Bsec iaqSensor;
const int ledPin = 2;
unsigned long sendDataPrevMillis = 0;

// --- FUNÇÕES AUXILIARES ---
void checkIaqSensorStatus(void);

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  Wire.begin(21, 22);
  
  // 1. Conexão Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println("\nConectado!");

  // 2. Configuração Firebase
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  
  // Autenticação com Email/Senha
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

 fbdo.setBSSLBufferSize(4096 /* Rx */, 1024 /* Tx */);

  // 2. Limita o tamanho da resposta para economizar RAM
  fbdo.setResponseSize(2048);

  // Inicializa Firebase
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  // 3. Inicializa Sensor BME680
  iaqSensor.begin(BME68X_I2C_ADDR_HIGH, Wire); // Use 0x77 ou 0x76 conforme seu teste anterior
  
  bsec_virtual_sensor_t sensorList[10] = {
    BSEC_OUTPUT_IAQ,
    BSEC_OUTPUT_STATIC_IAQ,
    BSEC_OUTPUT_CO2_EQUIVALENT,
    BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE,
    BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY,
    BSEC_OUTPUT_RAW_PRESSURE,
  };
  iaqSensor.updateSubscription(sensorList, 6, BSEC_SAMPLE_RATE_LP);
}

void loop() {
  // Roda lógica do sensor
  if (iaqSensor.run()) {
    
    // Envia para o Firebase a cada 10 segundos (para não estourar cota grátis)
    if (millis() - sendDataPrevMillis > 10000 || sendDataPrevMillis == 0) {
      sendDataPrevMillis = millis();
      
      digitalWrite(ledPin, HIGH); // Pisca ao enviar
      
      // Caminho no banco: /emai/sensor/temperatura, etc.
      // Usamos setFloat para números quebrados e setInt para inteiros
      
      if (Firebase.ready()) {
        Firebase.RTDB.setFloat(&fbdo, "/emai/temperatura", iaqSensor.temperature);
        Firebase.RTDB.setFloat(&fbdo, "/emai/umidade", iaqSensor.humidity);
        Firebase.RTDB.setFloat(&fbdo, "/emai/pressao", iaqSensor.pressure / 100.0);
        Firebase.RTDB.setInt(&fbdo, "/emai/iaq", (int)iaqSensor.iaq);
        Firebase.RTDB.setInt(&fbdo, "/emai/co2", (int)iaqSensor.co2Equivalent);
        
        // Atualiza timestamp (opcional, útil para o site saber quando atualizou)
        Firebase.RTDB.setTimestamp(&fbdo, "/emai/timestamp");
        
        Serial.println("Dados enviados para a nuvem! ☁️");
      } else {
        Serial.println("Erro no Firebase: " + fbdo.errorReason());
      }
      
      digitalWrite(ledPin, LOW);
    }
  } else {
    checkIaqSensorStatus();
  }
}

// Mantenha a função checkIaqSensorStatus original do exemplo BSEC aqui embaixo
void checkIaqSensorStatus(void) {
  if (iaqSensor.bsecStatus != BSEC_OK) {
    if (iaqSensor.bsecStatus < BSEC_OK) {
      Serial.println("BSEC error code : " + String(iaqSensor.bsecStatus));
    } else {
      Serial.println("BSEC warning code : " + String(iaqSensor.bsecStatus));
    }
  }
}