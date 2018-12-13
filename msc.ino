#include <LWiFi.h>
#include "MCS.h"
#include "DHT.h"

int t;
int h;

char _lwifi_ssid[] = "HTC";
char _lwifi_pass[] = "00000001";

MCSDevice mcs("DKPVczGi", "GWTcBuvIBr7t6UjW");
MCSDisplayInteger temp("temp");
MCSDisplayInteger humid("humid");

DHT __dht2(4, DHT11);

void setup()
{
  Serial.begin(9600);

  mcs.addChannel(temp);
  mcs.addChannel(humid);
  Serial.println("Wi-Fi const");
  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) { delay(1000); }
  Serial.println("Wi-Fi consuc");
  while(!mcs.connected()) { mcs.connect(); }
  Serial.println("MCS consuc");
  Serial.begin(9600);
  __dht2.begin();
}

void loop()
{
  while (!mcs.connected()) {
    mcs.connect();
    if (mcs.connected()) { Serial.println("MCS 已重新連線"); }
  }
  mcs.process(100);

  t = __dht2.readTemperature();
  h = __dht2.readHumidity();
  temp.set(t);
  humid.set(h);

  Serial.print("攝氏溫度 : ");
  Serial.println(t);
  Serial.print("相對溼度 :");
  Serial.println(h);

  delay(1000);
}
