# ArdunioLog
This library is used to implement log output on the Arduino platform.

## Use

```c++
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
// output
//  Run...
// [log] Info 5 file: src\main.cpp line: 13 level: D
// [log] Info 1 file: src\main.cpp line: 14 level: D
// [log] Info 9.90 file: src\main.cpp line: 15 level: E
// [log] Info true file: src\main.cpp line: 16 level: E
// Log library by NingQing,time: 2021-5-7, version:1.00  
}

void loop()
{
  // put your main code here, to run repeatedly:
}
```
### Controllable output
Output achieved by modifying the log level grade.
```c++
#define LOG_LEVEL LOG_OFF       // no output
#define LOG_LEVEL LOG_DEBUG     // can output: debug error info
#define LOG_LEVEL LOG_TEST      // can output: error info
#define LOG_LEVEL LOG_RUN       // can output: error

```
### Bind output object
Logger can be bound to class objects that inherit Print to achieve output
```c++
Logger log(&Serial);
```
