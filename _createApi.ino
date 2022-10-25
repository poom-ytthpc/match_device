void createGpioDataApi(String _payload)
{
  shouldReadGpioDataApi = true;
  DynamicJsonDocument doc(1024);
  Serial.print("GPIO DATA -> ");
  Serial.print(_payload);

  DeserializationError error = deserializeJson(doc, _payload);
  String index = doc["index"];
  String fileName = "/gpioData" + index + ".json";
  Serial.print("INDEX : ");
  Serial.println(index);
  if (error)
  {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
  }
  if (!error)
  {
    if (SPIFFS.begin())
    {

      Serial.println("MOUNT FILE SYSTEM" );
      if (SPIFFS.exists(fileName))
      {
        //        SPIFFS.remove(fileName);
        Serial.print("REMOVE OLD FILE : ");
        Serial.println(fileName);
      }
      File configFile = SPIFFS.open(fileName, "w");
      if (configFile)
      {
        Serial.println("CREATE GPIOS FILE CONFIG : " + fileName);
        size_t size = configFile.size();
        std::unique_ptr<char[]> buf(new char[size]);
        configFile.readBytes(buf.get(), size);
        DynamicJsonDocument json(512);

        json["index"] = doc["index"];
        json["phState"] = doc["gpio_datum"]["phState"];
        json["ecState"] = doc["gpio_datum"]["ecState"];
        json["timerState"] = doc["gpio_datum"]["timerState"];
        json["sclState"] = doc["gpio_datum"]["sclState"];
        json["bclState"] = doc["gpio_datum"]["bclState"];
        json["maxEc"] = doc["gpio_datum"]["maxEc"];
        json["minEc"] = doc["gpio_datum"]["minEc"];
        json["maxPh"] = doc["gpio_datum"]["maxPh"];
        json["minPh"] = doc["gpio_datum"]["minPh"];

        if (!configFile)
        {
          Serial.println("failed to open config file for writing");
        }
        serializeJsonPretty(json, Serial);
        serializeJson(json, configFile);

        configFile.close();
      }
    }
  }
}

void createGpioApi (String _payload)
{
  shouldReadGpioApi = true;

  DynamicJsonDocument doc(1024);

  Serial.print("GPIO STATE -> ");
  Serial.println(_payload);

  DeserializationError error = deserializeJson(doc, _payload);

  if (error)
  {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
  }
  String index = doc["index"];
  String fileName = "/gpio" + index + ".json";
  Serial.print("INDEX : ");
  Serial.println(index);
  if (!error)
  {
    if (SPIFFS.begin())
    {

      Serial.println("MOUNT FILE SYSTEM" );
      if (SPIFFS.exists(fileName))
      {
        //        SPIFFS.remove(fileName);
        Serial.print("REMOVE OLD FILE : ");
        Serial.println(fileName);
      }
      File configFile = SPIFFS.open(fileName, "w");
      if (configFile)
      {
        Serial.println("CREATE GPIOS FILE CONFIG : " + fileName);
        size_t size = configFile.size();
        std::unique_ptr<char[]> buf(new char[size]);
        configFile.readBytes(buf.get(), size);
        DynamicJsonDocument json(256);

        int tmp_index = doc["index"];
        int tmp_state = doc["state"];

        if (state_check_online && pinCheckCount <= 4 && (WiFi.status() == WL_CONNECTED))
        {
          if (state[tmp_index] != tmp_state)
          {
            //            updatePinState(tmp_index , pinName[tmp_index] , state[tmp_index]); /* pin title state */
            if (client.connected() && (WiFi.status() == WL_CONNECTED))
            {
              client.publish(gpioOutTopic.c_str(), createGpioPayload(tmp_index, pinName[tmp_index], state[tmp_index]).c_str());
            }
          }
          pinCheckCount += 1;
        }
        else
        {
          state_check_online = false;
          if (!configFile)
          {
            Serial.println("failed to open config file for writing");
          }

          json["index"] = doc["index"];
          json["title"] = doc["title"];
          json["state"] = doc["state"];

          serializeJsonPretty(json, Serial);
          serializeJson(json, configFile);

        }







        configFile.close();
      }
    }
  }
}

void createDeviceApi (String _payload)
{
  shouldReadDeviceApi = true;
  DynamicJsonDocument doc(1024);

  Serial.print("DEVICE -> ");
  Serial.println(_payload);

  DeserializationError error = deserializeJson(doc, _payload);

  if (error)
  {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
  }
  String fileName = "/device.json";

  if (!error)
  {
    if (SPIFFS.begin())
    {

      Serial.println("MOUNT FILE SYSTEM" );
      if (SPIFFS.exists(fileName))
      {
        //        SPIFFS.remove(fileName);
        Serial.print("REMOVE OLD FILE : ");
        Serial.println(fileName);
      }
      File configFile = SPIFFS.open(fileName, "w");
      if (configFile)
      {
        Serial.println("CREATE DEVICE FILE CONFIG : " + fileName);
        size_t size = configFile.size();
        std::unique_ptr<char[]> buf(new char[size]);
        configFile.readBytes(buf.get(), size);
        DynamicJsonDocument json(256);

        bool tmp_auto = doc["auto"];
        bool tmp_fan = doc["fan"];
        if (auto_check_online)
        {
          if (Auto != tmp_auto || fan != tmp_fan)
          {
            if (client.connected() && (WiFi.status() == WL_CONNECTED))
            {
              client.publish(autoOutTopic.c_str() , createDevicePayload(String(device_name), Auto , fan).c_str());
              client.publish(fanOutTopic.c_str() , createDevicePayload(String(device_name), Auto , fan).c_str());

              //            updateAutoState(Auto);
              auto_check_online = false;
            }
          }
        } else {
          json["name"] = doc["name"];
          json["auto"] = doc["auto"];
          json["fan"] = doc["fan"];
        }



        if (!configFile)
        {
          Serial.println("failed to open config file for writing");
        }
        serializeJsonPretty(json, Serial);
        serializeJson(json, configFile);

        configFile.close();
      }
    }
  }
}

void createGpioTimerApi (String _payload)
{
  shouldReadGpioTimerApi = true;
  DynamicJsonDocument doc(3072);

  Serial.print("GPIO TIMER -> ");
  Serial.println(_payload);

  DeserializationError error = deserializeJson(doc, _payload);

  if (error)
  {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
  }
  String index = doc["index"];
  String fileName = "/gpioTimer" + index + ".json";
  Serial.print("INDEX : ");
  Serial.println(index);
  if (!error)
  {
    if (SPIFFS.begin())
    {

      Serial.println("MOUNT FILE SYSTEM" );
      if (SPIFFS.exists(fileName))
      {
        //        SPIFFS.remove(fileName);
        Serial.print("REMOVE OLD FILE : ");
        Serial.println(fileName);
      }
      File configFile = SPIFFS.open(fileName, "w");
      if (configFile)
      {
        Serial.println("CREATE GPIOS FILE CONFIG : " + fileName);
        size_t size = configFile.size();
        std::unique_ptr<char[]> buf(new char[size]);
        configFile.readBytes(buf.get(), size);
        DynamicJsonDocument json(3072);
        JsonArray timers = json.createNestedArray("timers");

        for (int i = 0 ; i < doc["timers"].size(); i++)
        {
          JsonObject timer = timers.createNestedObject();
          JsonArray timer_days = timer.createNestedArray("days");

          timer["start"] = doc["timers"][i]["start"];
          timer["stop"] = doc["timers"][i]["stop"];

          for (int j = 0 ; j < doc["timers"][i]["days"].size() ; j++)
          {
            JsonObject timer_day = timer_days.createNestedObject();

            timer_day["day"] = doc["timers"][i]["days"][j]["day"];
          }

        }

        if (!configFile)
        {
          Serial.println("failed to open config file for writing");
        }
        serializeJsonPretty(json, Serial);
        serializeJson(json, configFile);

        configFile.close();
      }
    }
  }
}

void createSensorStateApi (String _payload)
{
  shouldReadSensorStateApi = true;
  DynamicJsonDocument doc(1024);

  Serial.print("GPIO STATE -> ");
  Serial.println(_payload);

  DeserializationError error = deserializeJson(doc, _payload);

  if (error)
  {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
  }
  String index = doc["index"];
  String fileName = "/sensor" + index + ".json";
  Serial.print("INDEX : ");
  Serial.println(index);
  if (!error)
  {
    if (SPIFFS.begin())
    {

      Serial.println("MOUNT FILE SYSTEM" );
      if (SPIFFS.exists(fileName))
      {
        //        SPIFFS.remove(fileName);
        Serial.print("REMOVE OLD FILE : ");
        Serial.println(fileName);
      }
      File configFile = SPIFFS.open(fileName, "w");
      if (configFile)
      {
        Serial.println("CREATE GPIOS FILE CONFIG : " + fileName);
        size_t size = configFile.size();
        std::unique_ptr<char[]> buf(new char[size]);
        configFile.readBytes(buf.get(), size);
        DynamicJsonDocument json(512);

        int tmp_index = doc["index"];
        bool tmp_state = doc["state"];

        if (input_check_online && inputCheckCount <= 3 && (WiFi.status() == WL_CONNECTED))
        {
          if (tmp_index == 1)
          {
            if (phInputState != tmp_state)
            {
              if (client.connected() && (WiFi.status() == WL_CONNECTED))
              {
                client.publish(sensorOutTopic.c_str(), createSensorPayload(1, phInputState).c_str());
              }
            }
          }

          if (tmp_index == 2)
          {
            if (ecInputState != tmp_state)
            {
              if (client.connected() && (WiFi.status() == WL_CONNECTED))
              {
                client.publish(sensorOutTopic.c_str(), createSensorPayload(2, ecInputState).c_str());
              }
            }
          }

          if (tmp_index == 5)
          {
            if (tempHumInputState != tmp_state)
            {
              if (client.connected() && (WiFi.status() == WL_CONNECTED))
              {
                client.publish(sensorOutTopic.c_str(), createSensorPayload(5, tempHumInputState).c_str());
              }
            }
          }

          if (tmp_index == 6)
          {
            if (ultraSonicInputState != tmp_state)
            {
              if (client.connected() && (WiFi.status() == WL_CONNECTED))
              {
                client.publish(sensorOutTopic.c_str(), createSensorPayload(6, ultraSonicInputState).c_str());
              }
            }
          }
          inputCheckCount += 1;
        }
        else
        {
          input_check_online = false;
          json["index"] = doc["index"];
          json["state"] = doc["state"];
          json["name"] = doc["name"];

          if (!configFile)
          {
            Serial.println("failed to open config file for writing");
          }
          serializeJsonPretty(json, Serial);
          serializeJson(json, configFile);

        }



        configFile.close();
      }
    }
  }
}

void createFanApi (String _payload)
{
  shouldReadFanApi = true;
  DynamicJsonDocument doc(1024);

  Serial.print("DEVICE -> ");
  Serial.println(_payload);

  DeserializationError error = deserializeJson(doc, _payload);

  if (error)
  {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
  }
  String fileName = "/fan.json";

  if (!error)
  {
    if (SPIFFS.begin())
    {

      Serial.println("MOUNT FILE SYSTEM" );
      if (SPIFFS.exists(fileName))
      {
        //        SPIFFS.remove(fileName);
        Serial.print("REMOVE OLD FILE : ");
        Serial.println(fileName);
      }
      File configFile = SPIFFS.open(fileName, "w");
      if (configFile)
      {
        Serial.println("CREATE DEVICE FILE CONFIG : " + fileName);
        size_t size = configFile.size();
        std::unique_ptr<char[]> buf(new char[size]);
        configFile.readBytes(buf.get(), size);
        DynamicJsonDocument json(256);

        bool tmp_fan = doc["fan"];
        if (auto_check_online && (WiFi.status() == WL_CONNECTED))
        {
          if (fan != tmp_fan )
          {
            if (client.connected() && (WiFi.status() == WL_CONNECTED))
            {
              client.publish(fanOutTopic.c_str() , createDevicePayload(String(device_name), Auto , fan).c_str());
              //            updateAutoState(Auto);
              auto_check_online = false;
            }
          }
        } else {
          json["fan"] = doc["fan"];
        }



        if (!configFile)
        {
          Serial.println("failed to open config file for writing");
        }
        serializeJsonPretty(json, Serial);
        serializeJson(json, configFile);

        configFile.close();
      }
    }
  }
}
