void readSensor ()
{

  if (ultraSonicInputState)
  {
    read_serial_count += 1;
    delay(20);
    ReadUsSensor ();
  }
  else
  {
    if (client.connected())
    {
      client.publish(sensorStatusOutTopic.c_str(), createSensorStatusPayload(6, false).c_str());
    }
    SCL_TANK = 0;
    BCL_TANK = 0;
  }

  if (phInputState)
  {
    delay(20);
    ReadPhSensor ();
  }
  else
  {
    if (client.connected())
    {
      client.publish(sensorStatusOutTopic.c_str(), createSensorStatusPayload(1, false).c_str());
    }
    PostPH = 0;
    PostPHTEMP = 0;
  }
  if (ecInputState)
  {
    delay(20);
    ReadEcSensor ();
  }
  else
  {
    if (client.connected())
    {
      client.publish(sensorStatusOutTopic.c_str(), createSensorStatusPayload(2, false).c_str());
    }
    PostEC = 0;
  }
  if (tempHumInputState)
  {
    delay(20);
    ReadTHSensor ();
  }
  else
  {
    if (client.connected())
    {
      client.publish(sensorStatusOutTopic.c_str(), createSensorStatusPayload(5, false).c_str());
    }
    if (RTC.begin())
    {
      PostBOARDTEMP = RTC.getTemperature();
      PostBOARDHUM = 0;
    }
    else
    {
      PostBOARDTEMP = 0;
      PostBOARDHUM = 0;
    }
  }
  //  }
}

void ReadUsSensor ()
{
  if (ultrasonic_count <= 15)
  {
    int16_t result;
    node.begin(6, Serial2);
    result = node.readHoldingRegisters(0, 2);
    if (result == node.ku8MBSuccess)
    {
      if (client.connected())
      {
        client.publish(sensorStatusOutTopic.c_str(), createSensorStatusPayload(6, true).c_str());
      }
      SCL_TANK = node.getResponseBuffer(0);
      BCL_TANK = node.getResponseBuffer(1);
      ultrasonic_count = 0;
    }
    else
    {
      //      if (client.connected())
      //      {
      //        client.publish(sensorStatusOutTopic.c_str(), createSensorStatusPayload(6, false).c_str());
      //      }
      Serial.println("MODBUS CAN'T CONNECT");
      Serial.println(6, HEX);
    }
  }
  if (ultrasonic_count > 20)
  {
    if (client.connected())
    {
      client.publish(sensorStatusOutTopic.c_str(), createSensorStatusPayload(6, false).c_str());
    }
    SCL_TANK = 0;
    BCL_TANK = 0;
  }
  if (ultrasonic_count > 23)
  {
    ultrasonic_count = 9;
  }
  ultrasonic_count += 1;

  Serial.print("ULTRASONIC COUNT ->");
  Serial.println(ultrasonic_count);
}

void ReadPhSensor ()
{
  if (phCount <= 3)
  {
    int16_t result;
    node.begin(1, Serial2);
    result = node.readHoldingRegisters(0, 2);
    if (result == node.ku8MBSuccess)
    {
      if (client.connected())
      {
        client.publish(sensorStatusOutTopic.c_str(), createSensorStatusPayload(1, true).c_str());
      }
      PostPH = (node.getResponseBuffer(1) / 10.0);
      PostPHTEMP = (node.getResponseBuffer(0) / 10.0);
      phCount = 0;
    }
    else
    {
      if (client.connected())
      {
        client.publish(sensorStatusOutTopic.c_str(), createSensorStatusPayload(1, false).c_str());
      }
      Serial.println("MODBUS CAN'T CONNECT");
      Serial.println(1, HEX);
    }
  }
  if (phCount > 5)
  {
    if (client.connected())
    {
      client.publish(sensorStatusOutTopic.c_str(), createSensorStatusPayload(1, false).c_str());
    }
    PostPH = 0;
    PostPHTEMP = 0;
  }
  if (phCount > 10)
  {
    phCount = 2;
  }
  phCount += 1;

  Serial.print("PH COUNT ->");
  Serial.println(phCount);

}

void ReadEcSensor ()
{
  if (ecCount <= 3)
  {
    int16_t result;
    node.begin(2, Serial2);
    result = node.readHoldingRegisters(1, 1);
    if (result == node.ku8MBSuccess)
    {
      if (client.connected())
      {
        client.publish(sensorStatusOutTopic.c_str(), createSensorStatusPayload(2, true).c_str());
      }
      PostEC = (node.getResponseBuffer(0) / 10.0);
      ecCount = 0;
    }
    else
    {
      if (client.connected())
      {
        client.publish(sensorStatusOutTopic.c_str(), createSensorStatusPayload(2, false).c_str());
      }
      Serial.println("MODBUS CAN'T CONNECT");
      Serial.println(2, HEX);
    }
  }
  if (ecCount > 5)
  {
    PostEC = 0;
    if (client.connected())
    {
      client.publish(sensorStatusOutTopic.c_str(), createSensorStatusPayload(2, false).c_str());
    }
  }
  if (ecCount > 10)
  {
    ecCount = 2;
  }
  ecCount += 1;
  Serial.print("EC COUNT ->");
  Serial.println(ecCount);
}

void ReadTHSensor ()
{
  if (thCount <= 3)
  {
    int16_t result;
    node.begin(5, Serial2);
    result = node.readInputRegisters(1, 2);
    if (result == node.ku8MBSuccess)
    {
      if (client.connected())
      {
        client.publish(sensorStatusOutTopic.c_str(), createSensorStatusPayload(5, true).c_str());
      }
      PostBOARDTEMP = (node.getResponseBuffer(0) / 10.0);
      PostBOARDHUM = (node.getResponseBuffer(1) / 10.0);
      thCount = 0;
    }
    else
    {
      if (client.connected())
      {
        client.publish(sensorStatusOutTopic.c_str(), createSensorStatusPayload(5, false).c_str());
      }
      Serial.println("MODBUS CAN'T CONNECT");
      Serial.println(2, HEX);
    }
  }
  if (thCount > 5)
  {
    if (client.connected())
    {
      client.publish(sensorStatusOutTopic.c_str(), createSensorStatusPayload(5, false).c_str());
    }
    if (RTC.begin())
    {
      PostBOARDTEMP = RTC.getTemperature();
      PostBOARDHUM = 0;

    }
    else
    {
      PostBOARDTEMP = 0;
      PostBOARDHUM = 0;
    }
  }
  if (thCount > 10)
  {
    thCount = 2;
  }
  thCount += 1;
  Serial.print("TH COUNT ->");
  Serial.println(thCount);
}

String createSensorStatusPayload (int i , int s)
{
  String txt;
  txt += "{";
  txt += "\"device_id\":\"";
  txt += String(device_id);
  txt += "\",";
  txt += "\"";
  txt += "index\":";
  txt += String(i);
  txt +=  ",";
  txt += "\"" ;
  txt += "status\":";
  txt +=  String(s);
  txt += "}";
  return txt;
}
