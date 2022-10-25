void wifi_init()
{


  if (SPIFFS.begin()) {
    if (!SPIFFS.exists("/wifiConfiger.json")) {
      wifiManager.resetSettings(); /* REMOVE OLD SETTING */
      String bname = "";
      bname.concat(device_name);
      tft.fillScreen(TFT_BLACK);
      tft.setTextFont(2);
      tft.setTextSize(2);             // Select the font
      tft.drawString("AP START CONFIG", 160, 90, 2);// Print the string name of the font
      tft.drawString("AP NAME: \n" + bname, 160, 140, 2);
      wifiManager.setSaveConfigCallback(saveConfigCallback);
      WiFiManagerParameter custom_board_id("DEVICE", "DEVICE_ID", device_id, 30);
      WiFiManagerParameter custom_line_token("LINE_TOKEN", "LINE_TOKEN", LINE_TOKEN, 50);
      wifiManager.addParameter(&custom_board_id);
      wifiManager.addParameter(&custom_line_token);
      //    wifiManager.setConfigPortalTimeout(30);
      if (!wifiManager.autoConnect(device_name, "12345678")) {
        Serial.println("failed to connect and hit timeout");


      }

      strcpy(device_id, custom_board_id.getValue());
      strcpy(LINE_TOKEN, custom_line_token.getValue());
    }
  }
  /* WIFI EVENT */
  WiFi.onEvent(WiFiStationConnected, SYSTEM_EVENT_STA_CONNECTED);
  WiFi.onEvent(WiFiGotIP, SYSTEM_EVENT_STA_GOT_IP);
  WiFi.onEvent(WiFiStationDisconnected, SYSTEM_EVENT_STA_DISCONNECTED);
  /* END WIFI EVENT */


  if (ssid == "" || pass == "")
  {
    if (SPIFFS.exists("/wifiConfiger.json"))
    {
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/wifiConfiger.json", "r");
      if (configFile)
      {
        Serial.println("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);

        DynamicJsonDocument json(512);
        DeserializationError error = deserializeJson(json, buf.get());
        serializeJsonPretty(json, Serial);

        if (!error)
        {
          Serial.println("\nparsed json");
          strcpy(ssid , json["ssid"]);
          strcpy(pass , json["pass"]);
        }


        configFile.close();
      }
    }

  }

  if (shouldSaveConfig) {
    Serial.println("saving config");


    if (SPIFFS.begin())
    {

      File configFile = SPIFFS.open("/config.json", "w");

      if (!configFile) {
        Serial.println("failed to open config file for writing");
      }

      if (configFile)
      {
        size_t size = configFile.size();
        std::unique_ptr<char[]> buf(new char[size]);
        configFile.readBytes(buf.get(), size);

        DynamicJsonDocument json(512);

        DeserializationError error = deserializeJson(json, configFile);
        if (error)
        {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.f_str());
        }


        json["device_id"] = device_id;
        json["LINE_TOKEN"] = LINE_TOKEN;

        serializeJsonPretty(json, Serial);
        serializeJson(json, configFile);


        configFile.close();
      }


      File wifiConfig = SPIFFS.open("/wifiConfiger.json" , "w");

      if (!wifiConfig) {
        Serial.println("failed to open config file for writing");

      }

      if (wifiConfig)
      {
        size_t size = wifiConfig.size();
        std::unique_ptr<char[]> buf(new char[size]);
        wifiConfig.readBytes(buf.get(), size);

        DynamicJsonDocument json2(512);

        DeserializationError error = deserializeJson(json2, wifiConfig);
        if (error)
        {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.f_str());
        }


        json2["ssid"] = WiFi.SSID();
        json2["pass"] = WiFi.psk();

        serializeJsonPretty(json2, Serial);
        serializeJson(json2, wifiConfig);


        wifiConfig.close();
      }


      //end save
      shouldSaveConfig = false;
    }
  }

  if (LINE_TOKEN != "") {
    LINE.setToken(LINE_TOKEN);
    LINE.notify("CONNECTED BOARD");
    LINE.notify(device_name);
  }


}


void setupSpiffs() {
  //clean FS, for testing
  //  SPIFFS.format();

  //read configuration from FS json
  Serial.println("mounting FS...");

  if (SPIFFS.begin()) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");

        size_t size = configFile.size();
        std::unique_ptr<char[]> buf(new char[size]);
        configFile.readBytes(buf.get(), size);
        DynamicJsonDocument json(512);

        DeserializationError error = deserializeJson(json, buf.get());
        if (error)
        {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.f_str());
        }

        if (!error)
        {
          serializeJsonPretty(json, Serial);
          Serial.println("\nparsed json");

          strcpy(device_id, json["device_id"]);
          strcpy(LINE_TOKEN, json["LINE_TOKEN"]);
        }



        configFile.close();
      }
    }

    if (SPIFFS.exists("/wifiConfiger.json")) {
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/wifiConfiger.json", "r");
      if (configFile) {
        Serial.println("opened config file");

        size_t size = configFile.size();
        std::unique_ptr<char[]> buf(new char[size]);
        configFile.readBytes(buf.get(), size);
        DynamicJsonDocument json2(512);

        DeserializationError error = deserializeJson(json2, buf.get());
        if (error)
        {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.f_str());
        }

        serializeJsonPretty(json2, Serial);
        if (!error)
        {
          Serial.println("\nparsed json");
          strcpy(ssid , json2["ssid"]);
          strcpy(pass, json2["pass"]);
        }


        configFile.close();
      }
    }
  } else {
    Serial.println("failed to mount FS");
  }
  //end read
}

void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
  Serial.println("Connected to AP successfully!");

  if (stuCount >= 1)
  {
    onlineCheck();
  }

}

void WiFiGotIP(WiFiEvent_t event, WiFiEventInfo_t info)
{
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
  if (time_recon_count > 5) {
    Serial.println("Disconnected from WiFi access point");
    Serial.print("WiFi lost connection. Reason: ");
    Serial.println(info.disconnected.reason);
    Serial.println("Trying to Reconnect");
    WiFi.begin(ssid , pass);
    time_recon_count = 0;
  }


  time_recon_count += 1;

  Serial.print("RECONNECT COUNT : ");
  Serial.println(time_recon_count);
}

void reConect() {
  String ts = "";
  String tp = "";
  ts.concat(ssid);
  tp.concat(pass);

  if (ts == "" || tp == "") {
    Serial.println("SSID AND PASSWORD NOT SAVED RESETART");
    ESP.restart();
  }

  if ((WiFi.status() != WL_CONNECTED)) {

    Serial.print("SSID: ");
    Serial.println(ts);
    Serial.print("PASSWORD: ");
    Serial.println(tp);

    if (ts == "" || tp == "") {
      Serial.println("SSID AND PASSWORD NOT SAVED RESETART");
      ESP.restart();
    }


    if (SPIFFS.exists("/wifiConfiger.json")) {

      if (ts == "" || tp == "") {
        ESP.restart();
      }


    } else {

      ESP.restart();
    }
  }
}

void clearAll() {

  Serial.println("PUSH");
  strcpy(ssid, "");
  strcpy(pass, "");
  SPIFFS.format();
  shouldSaveConfig = false;
  ESP.restart();

}

void resetWifi() {

  Serial.println("PUSH");
  strcpy(ssid, "");
  strcpy(pass, "");
  SPIFFS.remove("/wifiConfiger.json");
  SPIFFS.remove("/TouchCalData");
  //  shouldSaveConfig = false;
  ESP.restart();


  //    SPIFFS.format();



}
