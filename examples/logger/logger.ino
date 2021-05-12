#include <Logger.h>

#define LOG_LEVEL LOG_DEBUG

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    continue;
  Serial.println(F("Run..."));
  Logger log(&Serial);
  log.setPrefix("[log]");
  log.debug("Info %d",5);
  log.debug("Info %c",'1');
  log.error("Info %f",9.9);
  log.error("Info %t",true);
  log.info("Log library by NingQing,time: %s, version:%f \n","2021-5-7",1.0);
}

void loop()
{
  // put your main code here, to run repeatedly:
}