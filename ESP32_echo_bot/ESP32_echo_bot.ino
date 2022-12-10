#define USE_CLIENTSSL true
#define MYTZ "CET-1CEST,M3.5.0,M10.5.0/3"

// DEFINIÇÃO DAS CREDENCIAIS PARA ACESSO
#define ssid "WIFI_SSID"                                        // NOME DA REDE WIFI
#define pass "WIFI_PASS"                                        // SENHA DA REDE WIFI
#define token "TELEGRAM_BOT_TOKEN"                              // TOKEN DO BOT

#include <AsyncTelegram2.h>
#include <time.h>
#include <WiFi.h>
#include <WiFiClient.h>

#if USE_CLIENTSSL
#include <SSLClient.h>
#include "tg_certificate.h"

WiFiClient base_client;
SSLClient client(base_client, TAs, (size_t)TAs_NUM, A0, 1, SSLClient::SSL_ERROR);
#endif

AsyncTelegram2 myBot(client);

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  // initialize the Serial
  Serial.begin(115200);
  Serial.println("\nStarting TelegramBot...");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  delay(500);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(500);
  }

  // Sync time with NTP
  configTzTime(MYTZ, "time.google.com", "time.windows.com", "pool.ntp.org");
#if USE_CLIENTSSL == false
  client.setCACert(telegram_cert);
#endif

  // Set the Telegram bot properies
  myBot.setUpdateTime(2000);
  myBot.setTelegramToken(token);

  // Check if all things are ok
  Serial.print("\nTest Telegram connection... ");
  myBot.begin() ? Serial.println("OK") : Serial.println("NOK");
}

void loop()
{

  static uint32_t ledTime = millis();
  if (millis() - ledTime > 150)
  {
    ledTime = millis();
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }

  TBMessage msg; // VARIÁVEL LOCAL PARA RECEBER A MENSAGEM

  // SE HOUVER UMA MENSAGEM NOVA
  if (myBot.getNewMessage(msg))
  {
    // A MENSAGEM SERÁ DEVOLVIDA
    myBot.sendMessage(msg, msg.text);
  }
}
