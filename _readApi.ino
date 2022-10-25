
void readApi()
{
  if (SPIFFS.begin())
  {
    size_t n = sizeof(pin) / sizeof(pin[0]);

    if (shouldReadFanApi)
    {
      String fileName = "/fan.json";

      if (SPIFFS.exists(fileName))
      {
        File configFile = SPIFFS.open(fileName, "r");
        if (configFile)
        {
          Serial.println("OPEN GPIOS FILE CONFIG" + fileName);
          size_t size = configFile.size();
          std::unique_ptr<char[]> buf(new char[size]);
          configFile.readBytes(buf.get(), size);
          DynamicJsonDocument json(256);

          DeserializationError error = deserializeJson(json, buf.get());
          if (error)
          {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
          }

          bool tmp_fan = json["fan"];
          if (!error)
          {
            fan = tmp_fan;
          }
          if (!configFile)
          {
            Serial.println("failed to open config file for writing");
          }
          serializeJsonPretty(json, Serial);

          configFile.close();
        }
      }
      shouldReadFanApi = false;
    }

    if (shouldReadDeviceApi)
    {
      String fileName = "/device.json";

      if (SPIFFS.exists(fileName))
      {
        File configFile = SPIFFS.open(fileName, "r");
        if (configFile)
        {
          Serial.println("OPEN GPIOS FILE CONFIG" + fileName);
          size_t size = configFile.size();
          std::unique_ptr<char[]> buf(new char[size]);
          configFile.readBytes(buf.get(), size);
          DynamicJsonDocument json(256);

          DeserializationError error = deserializeJson(json, buf.get());
          if (error)
          {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
          }

          bool tmp_auto = json["auto"];
          if (!error)
          {
            strcpy( device_name, json["name"]);
            Auto = tmp_auto;
          }
          if (!configFile)
          {
            Serial.println("failed to open config file for writing");
          }
          serializeJsonPretty(json, Serial);

          configFile.close();
        }
      }
      shouldReadDeviceApi = false;
    }/* END READ DEVICE */


    if (shouldReadGpioApi)
    {
      for (int i = 0 ; i < n ; i++)
      {
        String fileName = "/gpio" + String(pin[i]) + ".json";

        if (SPIFFS.exists(fileName))
        {
          File configFile = SPIFFS.open(fileName, "r");
          if (configFile)
          {
            Serial.println("OPEN GPIOS FILE CONFIG" + fileName);
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

            int index = json["index"];
            bool tmp_title = json["title"];
            bool tmp_state = json["state"];

            if (!error)
            {
              state[index] = tmp_state;
              strcpy(pinName[index], json["title"]);
            }
            if (!configFile)
            {
              Serial.println("failed to open config file for writing");
            }
            serializeJsonPretty(json, Serial);

            configFile.close();
          }
        }
      }
      shouldReadGpioApi = false;

    }/* END GPIO STATE READ */


    if (shouldReadGpioDataApi)
    {
      for (int i = 0 ; i < n ; i++)
      {
        String fileName = "/gpioData" + String(pin[i]) + ".json";

        if (SPIFFS.exists(fileName))
        {
          File configFile = SPIFFS.open(fileName, "r");
          if (configFile)
          {
            Serial.println("OPEN GPIOS FILE CONFIG" + fileName);
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

            int index = json["index"];
            bool tmp_phState = json["phState"];
            bool tmp_ecState = json["ecState"];
            bool tmp_timerState = json["timerState"];
            bool tmp_sclState = json["sclState"];
            bool tmp_bclState = json["bclState"];

            float tmp_maxEc = json["maxEc"];
            float tmp_minEc = json["minEc"];
            float tmp_maxPh = json["maxPh"];
            float tmp_minPh = json["minPh"];
            if (!error)
            {
              phState[index] = tmp_phState;
              ecState[index] = tmp_ecState;
              timerState[index] = tmp_timerState;
              maxEc[index] = tmp_maxEc;
              minEc[index] = tmp_minEc;
              maxPh[index] = tmp_maxPh;
              minPh[index] = tmp_minPh;
              sclState[index] = tmp_sclState;
              bclState[index] = tmp_bclState;
            }
            if (!configFile)
            {
              Serial.println("failed to open config file for writing");
            }
            serializeJsonPretty(json, Serial);

            configFile.close();
          }
        }
      }
      shouldReadGpioDataApi = false;
    }/* END GPIO DATA READ */

    if (shouldReadGpioTimerApi)
    {
      for (int i = 0 ; i < n ; i++)
      {
        String fileName = "/gpioTimer" + String(pin[i]) + ".json";

        if (SPIFFS.exists(fileName))
        {
          File configFile = SPIFFS.open(fileName, "r");
          if (configFile)
          {
            Serial.println("OPEN GPIOS FILE CONFIG" + fileName);
            size_t size = configFile.size();
            std::unique_ptr<char[]> buf(new char[size]);
            configFile.readBytes(buf.get(), size);
            DynamicJsonDocument json(3072);

            DeserializationError error = deserializeJson(json, buf.get());
            if (error)
            {
              Serial.print(F("deserializeJson() failed: "));
              Serial.println(error.f_str());
            }



            if (!error)
            {
              for (int j = 0 ; j < json["timers"].size() ; j++)
              {
                String tmp_start = json["timers"][j]["start"];
                tStart[i][j] = tmp_start;
                String tmp_stop = json["timers"][j]["stop"];
                tStop[i][j] = tmp_stop;

                for (int k = 0 ; k < json["timers"][j]["days"].size(); k++)
                {
                  String tmp_day = json["timers"][j]["days"][k]["day"];
                  tDays[i][j][k] = tmp_day;
                }
              }
            }
            if (!configFile)
            {
              Serial.println("failed to open config file for writing");
            }
            serializeJsonPretty(json, Serial);

            configFile.close();
          }
        }
      }
      shouldReadGpioTimerApi = false;
    }/* END READ TIMER */

    if (shouldReadSensorStateApi)
    {
      for (int i = 0; i < 7; i++)
      {
        String fileName = "/sensor" + String(i) + ".json";

        if (SPIFFS.exists(fileName))
        {
          File configFile = SPIFFS.open(fileName, "r");
          if (configFile)
          {
            Serial.println("OPEN GPIOS FILE CONFIG" + fileName);
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

            int index = json["index"];
            bool tmp_state = json["state"];
            String tmp_name = json["name"];

            if (!error)
            {
              if (index == 1)
              {
                phInputState = tmp_state;
              }

              if (index == 2)
              {
                ecInputState = tmp_state;
              }

              if (index == 3)
              {
                waterInputState = tmp_state;
              }

              if (index == 5)
              {
                tempHumInputState = tmp_state;
              }
              if (index == 6)
              {
                ultraSonicInputState = tmp_state;
              }

            }
            if (!configFile)
            {
              Serial.println("failed to open config file for writing");
            }
            serializeJsonPretty(json, Serial);

            configFile.close();
          }
        }
      }
      shouldReadSensorStateApi = false;
    }/* END SENSOR READ */

  }
}
