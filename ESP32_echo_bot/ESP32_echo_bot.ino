#define USE_CLIENTSSL true  //editar melhor no vscode
#include <AsyncTelegram2.h> //BIBLIOTECA PARA INTERFACE COM A API DO TELEGRAM
#include <time.h> //
#define MYTZ "CET-1CEST,M3.5.0,M10.5.0/3"
#include <WiFi.h>
#include <WiFiClient.h>
// #if USE_CLIENTSSL
// #include <SSLClient.h>  
// #include "tg_certificate.h"
// #endif

WiFiClient base_client;
// SSLClient client(base_client, TAs, (size_t)TAs_NUM, A0, 1, SSLClient::SSL_ERROR);

AsyncTelegram2 myBot(base_client);

#define ssid  "yout_ssid"     // SSID WiFi network
#define pass  "Your_pass"     // Password  WiFi network
#define token "your_token_here"  // Telegram token

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  // initialize the Serial
  Serial.begin(115200);
  Serial.println("\nStarting TelegramBot...");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  delay(500);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }


  // configTzTime(MYTZ, "time.google.com", "time.windows.com", "pool.ntp.org");
  // #if USE_CLIENTSSL == false
  //   client.setCACert(telegram_cert);
  // #endif  
  // Set the Telegram bot properies
  myBot.setUpdateTime(2000);
  myBot.setTelegramToken(token);

  // Check if all things are ok
  Serial.print("\nTest Telegram connection... ");
  myBot.begin() ? Serial.println("OK") : Serial.println("NOK");
}

void loop() {
  
  static uint32_t ledTime = millis();
  if (millis() - ledTime > 150) {
    ledTime = millis();
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }

  TBMessage msg;

  // if there is an incoming message...
  if (myBot.getNewMessage(msg)) {    
    // Send a message to your public channel
    // String message ;
    // message += "Message from @";
    // message += myBot.getBotName();
    // message += ":\n";
    // message += msg.text;
    // Serial.println(message);

    // echo the received message
    myBot.sendMessage(msg, msg.text);
  }
}