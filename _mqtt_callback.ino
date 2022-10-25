void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("RECEIVED MESSAGE : ");
  Serial.println(topic);
  String _topic = String(topic);
  String _payload = "";
  for (int i = 0; i < length; i++)
  {
    _payload += (char)payload[i];
    Serial.print((char)payload[i]);
  }
  Serial.println();


  if (_topic == gpioInTopic)
  {
    createGpioApi (_payload);
  }

  if (_topic == gpioDataInTopic)
  {
    createGpioDataApi(_payload);
  }

  if (_topic == deviceInTopic)
  {
    createDeviceApi(_payload);
  }

  if (_topic == gpioTimerInTopic)
  {
    createGpioTimerApi(_payload);
  }

  if (_topic == deviceSensorInTopic)
  {
    createSensorStateApi(_payload);
  }

  if(_topic == fanInTopic)
  {
    createFanApi(_payload);
  }
}
