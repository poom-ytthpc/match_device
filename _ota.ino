String getChipId()
{
  String ChipIdHex = String((uint32_t)(ESP.getEfuseMac() >> 32), HEX);
  ChipIdHex += String((uint32_t)ESP.getEfuseMac(), HEX);
  return ChipIdHex;
}

void updateVersion()
{
  if (pingTest && (WiFi.status() == WL_CONNECTED))
  {
    Serial.println("///////////////////////////////////////");
    Serial.print("SIZE : ");
    Serial.println(SPIFFS.usedBytes());
    Serial.println("///////////////////////////////////////");

    String bid = "";
    bid.concat(device_id);
    String url = SERVER_OTA_IP + "/getFile?";
    url += "v=" + ver;
    url += "&bid=" + bid;
    url += "&cid=" + getChipId();

    WiFiClient client;
    httpUpdate.update(client, url, ver);
  }
}
