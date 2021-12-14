// #include <Arduino.h>
// #include <WiFiClient.h>
// #include <WiFi.h>
// #include <WiFiMulti.h>
// #include <WebServer.h>
// #include <ESPAsyncWebServer.h>
// #include <AsyncTCP.h>
// #include <time.h>
// #include <FS.h>
// #include <SPIFFS.h>
// #include <DHT.h>
// #include "sensor.hpp"
// #include "filesystem.hpp"
// #include "utilities.hpp"

// #define CAPACITIVE_SOIL_SENSOR 34
// #define DHT11_PIN 27
// #define SOLENOID_VALVE 32
// #define ACTION_LED 18
// #define ON_LED 19
// #define NUMBER_OF_SENSORS 3

// DHT dht(DHT11_PIN, DHT11);
// WiFiClient client;
// WiFiMulti wifiMulti;
// AsyncWebServer server(80);

// // Network
// const char *ssid = "SubSolo";      // Wifi name
// const char *password = "cocacola"; // Wifi password

// // WAN Acess
// const char *username = "admin";
// const char *serverPass = "ADM88088$horta";

// // Set your Static IP address
// IPAddress local_IP(10, 0, 0, 50);
// IPAddress gateway(10, 0, 0, 1);
// IPAddress subnet(255, 255, 0, 0);
// IPAddress primaryDNS(1, 1, 1, 1);   // optional
// IPAddress secondaryDNS(8, 8, 8, 8); // optional

// // Setup server parameters
// const char *url = "hortaInteligente";        // URL to access localy ex: http://smartGarden.local/
// const char *logFileName = "/sensorData.csv"; // Name of the file to store the sensors data

// // Time server
// const char *ntpServer = "pool.ntp.org";  // ntp url
// const long gmtOffset_sec = 60 * 60 * -3; // -3 hours

// // Irrigation time
// const uint8_t morningIrrigationHour = 11;           // Hour to verify irrigate in the morning 0 - 12
// const uint8_t eveningIrrigationHour = 17;           // Hour to verify irrigate in the evening 12 - 23
// uint8_t nextIrrigationHour = morningIrrigationHour; // The next hour to verify the irrigation
// time_t irrigationEndTime = 0;                       // Time to end the irrigation UNIX epoch
// const uint16_t irrigationDurationPerPercent = 5;    // Seconds to multiply by missing %humidity
// const float dryValue = 3100.0;                      // the value when sensor placed in air
// const float waterValue = 2700.0;                    // the value when sensor placed in water
// float soilReading;

// //  Time variables
// time_t currentTime;          // Current time in UNIX epoch
// struct tm *currentLocalTime; // Current time struct

// // Create sensors
// Sensor *humidity;
// Sensor *temperature;
// Sensor *soilHumidity;

// // Sensors reading intervals
// const uint16_t readingInterval = 300; // Interval between readings in seconds
// time_t nextSensorsReading = 0;        // Time of next reading UNIX epoch

// // Local Functions header
// void startWifiConnection();
// void startSensors();
// void startNTP();
// void startWebServer();
// void startFileSystem();
// // void startMDNS();
// void irrigate();
// void logDataToFile(String &data);

// void setup()
// {
//   // Initialize pins
//   pinMode(ACTION_LED, OUTPUT);
//   pinMode(ON_LED, OUTPUT);
//   pinMode(SOLENOID_VALVE, OUTPUT);
//   pinMode(CAPACITIVE_SOIL_SENSOR, INPUT);

//   // Initialize all the services
//   startWifiConnection();
//   startFileSystem();
//   // startMDNS();
//   startNTP();
//   startSensors();
//   startWebServer();

//   digitalWrite(ON_LED, HIGH);
// }

// void loop()
// {
//   // Update time
//   time(&currentTime);
//   currentLocalTime = localtime(&currentTime);

//   // Keep wifi connected
//   if (wifiMulti.run() != WL_CONNECTED)
//   {
//     digitalWrite(ON_LED, LOW);
//     ESP.restart();
//   }

//   // Average the soil sensor readings across 100 * 10 samples
//   soilReading = ((99.0 * soilReading) + ADCRead(CAPACITIVE_SOIL_SENSOR)) / 100.0;

//   if (currentTime >= nextSensorsReading)
//   {
//     // Update sensors value
//     updateSensorValue(humidity, dht.readHumidity());
//     updateSensorValue(temperature, dht.readTemperature());
//     updateSensorValue(soilHumidity, constrain(map(soilReading, dryValue, waterValue, 0, 100), 0.0, 100.0));

//     Sensor *sensors[NUMBER_OF_SENSORS] = {humidity, temperature, soilHumidity};

//     String sensorsCSV = updatedSensorsToCSV(sensors, NUMBER_OF_SENSORS);

//     // Append changes to the csv file
//     if (sensorsCSV.length() && currentTime > 1600000000)
//     {
//       sensorsCSV += ",";
//       sensorsCSV += String(currentTime);
//       sensorsCSV += "\n";
//       logDataToFile(sensorsCSV);
//     }
//     nextSensorsReading = currentTime + readingInterval;
//     blinkActionLed(ACTION_LED);
//   }

//   // Verify if it needs irrigation when the irrigation hour comes
//   if (currentLocalTime->tm_hour == nextIrrigationHour)
//   {
//     if (getSensorValue(soilHumidity) <= 80.0)
//       irrigate();

//     configTime(gmtOffset_sec, 0, ntpServer);
//     if (nextIrrigationHour == morningIrrigationHour)
//       nextIrrigationHour = eveningIrrigationHour;
//     else
//       nextIrrigationHour = morningIrrigationHour;
//   }

//   // Verify if the irrigation ended
//   if (currentTime >= irrigationEndTime && digitalRead(SOLENOID_VALVE) == HIGH)
//   {
//     digitalWrite(SOLENOID_VALVE, LOW);
//     digitalWrite(ACTION_LED, LOW);
//   }

//   delay(500);
// }

// void startWifiConnection()
// {
//   WiFi.mode(WIFI_STA); // Change wifi mode to station
//   WiFi.disconnect();   // Clear wifi config
//                        // Configures static IP address
//   WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS);

//   wifiMulti.addAP(ssid, password);
//   uint8_t wifiCount = 0;
//   while (wifiMulti.run() != WL_CONNECTED)
//   {
//     blinkActionLed(ACTION_LED);
//     wifiCount += 1;

//     if (wifiCount >= 30)
//       ESP.restart();
//   }
// }

// void startFileSystem()
// {
//   if (!SPIFFS.begin(true))
//     ESP.restart();
// }

// void startWebServer()
// {
//   // Server the static files
//   server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html").setAuthentication(username, serverPass);
//   server.serveStatic(logFileName, SPIFFS, logFileName).setCacheControl("max-age=60"); // For the sensor log file keep in cache for only 60 seconds

//   server.on("/irrigate", [](AsyncWebServerRequest *request)
//             {
//               irrigate();
//               String jsonResponse = "{\"irrigationEndTime\":";
//               jsonResponse += String(irrigationEndTime);
//               jsonResponse += "}";
//               request->send(200, "application/json", jsonResponse); });

//   server.on("/stopIrrigation", [](AsyncWebServerRequest *request)
//             {
//               irrigationEndTime = currentTime;

//               request->send(200, "text/plain", "ok"); });

//   server.onNotFound([](AsyncWebServerRequest *request)
//                     { request->send(404, "text/plain", "FileNotFound"); });
//   server.begin();
// }

// void startNTP()
// {
//   configTime(gmtOffset_sec, 0, ntpServer);
//   time(&currentTime);
//   blinkActionLed(ACTION_LED);
//   delay(1000);
//   nextSensorsReading = currentTime + readingInterval;
// }

// void startSensors()
// {
//   dht.begin();
//   humidity = initSensor(1);
//   temperature = initSensor(2);
//   soilHumidity = initSensor(3);
//   soilReading = ADCRead(CAPACITIVE_SOIL_SENSOR);
// }

// void irrigate()
// {
//   irrigationEndTime = currentTime + (irrigationDurationPerPercent * (100 - getSensorValue(soilHumidity)));
//   digitalWrite(ACTION_LED, HIGH);
//   digitalWrite(SOLENOID_VALVE, HIGH);
// }

// void logDataToFile(String &data)
// {
//   digitalWrite(ACTION_LED, HIGH);
//   if (SPIFFS.usedBytes() < (SPIFFS.totalBytes() * 0.4))
//   {
//     appendFile(SPIFFS, logFileName, data.c_str());
//   }
//   else
//   {
//     removeInitialLines(SPIFFS, logFileName, 8192);
//     appendFile(SPIFFS, logFileName, data.c_str());
//   }
//   digitalWrite(ACTION_LED, LOW);
// }
