//includes
  #include <WiFiManager.h>
  #include <strings_en.h>
  #include <wm_consts_en.h>
  #include <wm_strings_en.h>

  #include <Arduino.h>
  #include <NonBlockingRtttl.h>

  //https://www.reddit.com/r/diyelectronics/comments/xpqu12/esp32s2_pinout_for_those_of_you_who_are_looking/
  //still don't entirely understand fspi, but it's working now at least https://www.reddit.com/r/esp32/comments/qbil1g/how_do_i_access_spi2_and_spi3_on_an_esp32s2saola/

  /*************old enail stuff**************/
  #include <SPI.h>
  #include "Adafruit_MAX31855.h"
  #include <PID_v2.h>
  // //ota lol
  // #include <WiFi.h>
  // #include <AsyncTCP.h>
  // #include <ESPAsyncWebServer.h>
  // #include <AsyncElegantOTA.h>
  // #include "wificred.h"

  // //server input lol
  // #include <SPIFFS.h>

  //lvgl
  #include <lvgl.h>
  #include "ui.h"
  #include "ui_helpers.h"
  #include "lvgl.h"

  //display driver, Arduino_GFX
  #include <Arduino_GFX_Library.h>

  //rotary encoder
  #include "AiEsp32RotaryEncoder.h"



  #include "Arduino.h"  //i feel like this probably doesn't need to be here...
//

//pin definitions
  #define RELAY_PIN 3

  //pot pin for testing
  #define PIN_INPUT 6

  //thermocouple amp
  #define MAXDO 37
  #define MAXCS 39
  #define MAXCLK 40

  //rotary encoder
  #define ROTARY_ENCODER_A_PIN 2
  #define ROTARY_ENCODER_B_PIN 1
  #define ROTARY_ENCODER_BUTTON_PIN 4
  #define ROTARY_ENCODER_VCC_PIN -1 /* 27 put -1 of Rotary encoder Vcc is connected directly to 3,3V; else you can use declared output pin for powering rotary encoder */

  //Arduino_GFX
  #define GFX_BL DF_GFX_BL  // default backlight pin, you may replace DF_GFX_BL to actual backlight pin

  //rtttl
  #define BUZZER_PIN 18
//

//notes for thermocouple amp
  // noisy readings https://forums.adafruit.com/viewtopic.php?f=22&t=34978
  //slow readings https://forum.arduino.cc/t/thermocouple-time-response-assistance/439218/6
  //https://github.com/adafruit/Adafruit-MAX31855-library/issues/27
  //https://forums.ni.com/t5/LabVIEW-Interface-for-Arduino/Reading-SPI-of-MAX31855/td-p/3392471
//

//arduinoGFX
  /* Arduino_GFX try to find the settings depends on selected board in Arduino IDE
  * ESP32-S2 various dev board  : CS: 34, DC: 38, RST: 33, BL: 21, SCK: 36, MOSI: 35, MISO: nil
  ******************************************************************************/

  /* More data bus class: https://github.com/moononournation/Arduino_GFX/wiki/Data-Bus-Class */
  Arduino_DataBus* bus = create_default_Arduino_DataBus();

  /* More display class: https://github.com/moononournation/Arduino_GFX/wiki/Display-Class */

  //this one works for the bigger colour display
  //my turn THIS ONE BAYBEEE
  // Arduino_GFX *gfx = new Arduino_ST7735(
  //   bus, 33 /* RST */, 0 /* rotation */, false /* IPS */,
  //   128 /* width */, 160 /* height */,
  //   0 /* col offset 1 */, 0 /* row offset 1 */,
  //   0 /* col offset 2 */, 0 /* row offset 2 */,
  //   false /* BGR */);

  //for the 240*240, finally got it, needed to set the colour to 16 bit swap

  // Arduino_GFX *gfx = new Arduino_ST7789(
  //   bus,33 /* RST */, 0 /* rotation */, true /* IPS */,
  //   240 /* width */, 240 /* height */,
  //   0 /* col offset 1 */, 0 /* row offset 1 */);

  //Arduino_GFX* gfx = new Arduino_ST7789(bus, 33, 1 /*rot.*/, true, 240, 240);

  Arduino_GFX* gfx = new Arduino_GC9A01(
    bus, 33 /* RST */, 0 /* rotation */, true /* IPS */);
  //rotation seems to be a 90 deg multiplier
//

/* Change to your screen resolution */
  //set in lvgl.h
  //I FEEL LIKE I DON'T NEED THIS SCREEN RESOLUTION PART...
  static uint32_t screenWidth;
  static uint32_t screenHeight;
//

//LVGL
  static lv_disp_draw_buf_t draw_buf;
  static lv_color_t* disp_draw_buf;
  static lv_disp_drv_t disp_drv;
  //
  /* Display flushing */
  void my_disp_flush(lv_disp_drv_t* disp, const lv_area_t* area, lv_color_t* color_p) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

  #if (LV_COLOR_16_SWAP != 0)
    gfx->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t*)&color_p->full, w, h);
  #else
    gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t*)&color_p->full, w, h);
  #endif
    lv_disp_flush_ready(disp);
  }
//

//rotary encoder stuff

  //depending on your encoder - try 1,2 or 4 to get expected behaviour
  //#define ROTARY_ENCODER_STEPS 1
  //#define ROTARY_ENCODER_STEPS 2
  //4 seems to work best for the encoder att'd to the small screen
  #define ROTARY_ENCODER_STEPS 4
  //variable to hold a button click so that the read_encoder function can catch it
  bool buttonClickWaiting = 0;
  //initialize the rotary encoder
  AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);
//

//more encoder stuff, not sure if lvgl or encoder encoder...
  void rotary_onButtonClick() {
    static unsigned long lastTimePressed = 0;
    //ignore multiple press in that time milliseconds
    if (millis() - lastTimePressed < 500) {
      return;
    }
    lastTimePressed = millis();
    // Serial.print("button pressed ");
    // Serial.print(millis());
    // Serial.println(" milliseconds after restart");
    buttonClickWaiting = 1;
  }

  void rotary_loop() {
    //dont print anything unless value changed
    // if (rotaryEncoder.encoderChanged()) {
    //   // Serial.print("Value: ");
    //   // Serial.println(rotaryEncoder.readEncoder());
    // }
    if (rotaryEncoder.isEncoderButtonClicked()) {
      rotary_onButtonClick();
    }
  }

  void IRAM_ATTR readEncoderISR() {
    rotaryEncoder.readEncoder_ISR();
  }


  bool enc_pressed() {
    return rotaryEncoder.isEncoderButtonClicked();
  }

  long enc_chango_amount = 0;

  long enc_chango() {
    enc_chango_amount = rotaryEncoder.encoderChanged();
    return enc_chango_amount;
  }
//

//rtttl
  const char* dammit = "dammit:d=4,o=6,b=200:c7,8c7,d7,8d7,e7,g,8g,d7,8d7,e7,a,8a,d7,8d7,e7,f,8f,e7,8e7,d7,c7,d7,8d7,e7,g,8g,d7,8d7,e7,a,8a,d7,8d7,e7,f,8f,e7,8e7,d7";
  const char* kimPossible = "kimPossible:d=16,o=5,b=200:d6,8p,d6,8p,f6,32p,d6";
//

lv_group_t* g;

//wifi manager
  WiFiManager wm;
  
// 

//pid
  // Specify the links and initial tuning parameters
  double Kp = 3, Ki = 0.1, Kd = 0.0000001;
  PID_v2 myPID(Kp, Ki, Kd, PID::Direct);
  double pee = 0;
  const int WindowSize = 100;
  unsigned long windowStartTime;
//

//thermocouple
  Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);
  //tried to initialize with just the chip select to use hwspi, but that didn't work
  //Adafruit_MAX31855 thermocouple(MAXCS);
//


//pid
  double temp = 0;
  double setpoint = 265;
  //wtf is this for???
  double printOutput = 0;
//
//server v1
  //ota lol
    // AsyncWebServer server(80);
  //

  // server_input lol
    // const char* PARAM_STRING = "inputString";
    // const char* PARAM_INT = "inputInt";
    // const char* PARAM_FLOAT = "inputFloat";
  //

  //v1 server stuff
    // // HTML web page to handle 3 input fields (inputString, inputInt, inputFloat)
    // const char index_html[] PROGMEM = R"rawliteral(
    // <!DOCTYPE HTML><html><head>
    //   <title>ESP Input Form</title>
    //   <meta name="viewport" content="width=device-width, initial-scale=1">
    //   <script>
    //     function submitMessage() {
          
    //       setTimeout(function(){ document.location.reload(false); }, 500);  
    // <!--      alert("Saved value to ESP SPIFFS"); -->
    //     }
    //   </script></head><body>
    // <!--  <form action="/get" target="hidden-form">
    //     inputString (current value %inputString%): <input type="text" name="inputString">
    //     <input type="submit" value="Submit" onclick="submitMessage()">
    //   </form><br> 
    // -->
    //   <form action="/get" target="hidden-form">
    //     setpoint (current value %inputInt%): <input type="number " name="inputInt">
    //     <input type="submit" value="Submit" onclick="submitMessage()">
    //   </form><br>
    // <!--  <form action="/get" target="hidden-form">
    //     inputFloat (current value %inputFloat%): <input type="number " name="inputFloat">
    //     <input type="submit" value="Submit" onclick="submitMessage()">
    //   </form>
    //   <iframe style="display:none" name="hidden-form"></iframe>
    //   -->
    //   "do this show?"
    // </body></html>)rawliteral";

    // void notFound(AsyncWebServerRequest* request) {
    //   request->send(404, "text/plain", "Not found");
    // }


    // String readFile(fs::FS& fs, const char* path) {
    //   //  Serial.printf("Reading file: %s\r\n", path);
    //   File file = fs.open(path, "r");
    //   if (!file || file.isDirectory()) {
    //     Serial.println("- empty file or failed to open file");
    //     return String();
    //   }
    //   //  Serial.println("- read from file:");
    //   String fileContent;
    //   while (file.available()) {
    //     fileContent += String((char)file.read());
    //   }
    //   file.close();
    //   //  Serial.println(fileContent);
    //   return fileContent;
    // }

    // void writeFile(fs::FS& fs, const char* path, const char* message) {
    //   Serial.printf("Writing file: %s\r\n", path);
    //   File file = fs.open(path, "w");
    //   if (!file) {
    //     Serial.println("- failed to open file for writing");
    //     return;
    //   }
    //   if (file.print(message)) {
    //     Serial.println("- file written");
    //   } else {
    //     Serial.println("- write failed");
    //   }
    //   file.close();
    // }

    // // Replaces placeholder with stored values
    // String processor(const String& var) {
    //   //Serial.println(var);
    //   if (var == "inputString") {
    //     return readFile(SPIFFS, "/inputString.txt");
    //   } else if (var == "inputInt") {
    //     return readFile(SPIFFS, "/inputInt.txt");
    //   } else if (var == "inputFloat") {
    //     return readFile(SPIFFS, "/inputFloat.txt");
    //   }
    //   return String();
    // }
//

double readThermo() {
  // basic readout test, just print the current temp
  // Serial.print("Internal Temp = ");
  // Serial.println(thermocouple.readInternal());

  double c = thermocouple.readCelsius();

  if (isnan(c)) {
    Serial.println("Thermocouple fault(s) detected!");
    uint8_t e = thermocouple.readError();
    if (e & MAX31855_FAULT_OPEN) Serial.println("FAULT: Thermocouple is open - no connections.");
    if (e & MAX31855_FAULT_SHORT_GND) Serial.println("FAULT: Thermocouple is short-circuited to GND.");
    if (e & MAX31855_FAULT_SHORT_VCC) Serial.println("FAULT: Thermocouple is short-circuited to VCC.");
    return 0;
  } else {

    // Serial.print("C = ");
    // Serial.println(c);

    return c;
  }
}


void encoder_read(lv_indev_drv_t* drv, lv_indev_data_t* data) {
  //have to use the rotaryEncoder.encoderChanged() instead of rotaryEncoder.readEncoder()
  data->enc_diff = rotaryEncoder.encoderChanged();
  //i thought i needed to reset the change amount, but it actually gets reset every time that you call the rotaryEncoder.encoderChanged() function
  //enc_chango_amount = 0;
  // Serial.print("enc_diff:");
  // Serial.println(data->enc_diff);

  if (buttonClickWaiting) {
    data->state = LV_INDEV_STATE_PRESSED;
    //reset the click waiting now that it's been processed
    buttonClickWaiting = 0;
  } else data->state = LV_INDEV_STATE_RELEASED;
}

/***************************** S E T U P ****************************/
void setup() {
  //serial
    Serial.begin(115200);
    // Serial.setDebugOutput(true);
   // while(!Serial);
  //  

  //set pin modes
    //buzzer  
    pinMode(15, OUTPUT);
    digitalWrite(15, HIGH);
    //relay
    pinMode(3, OUTPUT);
    digitalWrite(3, LOW);
  //

  //arduinoGFX setup
    #ifdef GFX_EXTRA_PRE_INIT
      GFX_EXTRA_PRE_INIT();
    #endif

    // Init Display
    gfx->begin();
    gfx->fillScreen(BLACK);

    #ifdef GFX_BL
      pinMode(GFX_BL, OUTPUT);
      digitalWrite(GFX_BL, HIGH);
    #endif
  //

  //lvgl setup
    lv_init();

    screenWidth = gfx->width();
    screenHeight = gfx->height();
    #ifdef ESP32
      disp_draw_buf = (lv_color_t*)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * 32, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    #else
      disp_draw_buf = (lv_color_t*)malloc(sizeof(lv_color_t) * screenWidth * 32);
    #endif
    if (!disp_draw_buf) {
      Serial.println("LVGL disp_draw_buf allocate failed!");
    } else {
      lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * 32);
    }
      /* Initialize the display */
      lv_disp_drv_init(&disp_drv);
      /* Change the following line to your display resolution */
      disp_drv.hor_res = screenWidth;
      disp_drv.ver_res = screenHeight;
      disp_drv.flush_cb = my_disp_flush;
      disp_drv.draw_buf = &draw_buf;
      lv_disp_drv_register(&disp_drv);
  //

  //create the input device for the rotary encoder

      static lv_indev_drv_t indev_drv;
      lv_indev_drv_init(&indev_drv); /*Basic initialization*/
      indev_drv.type = LV_INDEV_TYPE_ENCODER;
      indev_drv.read_cb = encoder_read;
      /*Register the driver in LVGL and save the created input device object*/
      lv_indev_t* my_indev = lv_indev_drv_register(&indev_drv);

      //this really messed me up. you need to create the group after creating the display
      lv_group_t* g = lv_group_create();
      lv_group_set_default(g);
      lv_indev_set_group(my_indev, g);
  //

  // Init SquareLine prepared UI 
    ui_init();
  //
  //can't add the obj to the group until the ui is initialized
    lv_group_add_obj(g, ui_tempArc1);
    //i think what i gotta do is add the objs of the setting screen when switching to the setting screen, then vice versa, actually maybe just the roller and slider?
  //

  //wifimanager
    //wm.resetSettings();
    wm.setConfigPortalBlocking(false);
    wm.setConfigPortalTimeout(60);
    //automatically connect using saved credentials if they exist
    //If connection fails it starts an access point with the specified name
    if(wm.autoConnect("octo-nail wifi setup")){
        Serial.println("connected...yeey :D");
    }
    else {
        Serial.println("Configportal running");
    }
  //

  //thermocouple setup
      if (!thermocouple.begin()) {
        Serial.println("ERROR.");
        while (1) delay(10);
      }
  //

  //pid setup
    windowStartTime = millis();

    // tell the PID to range between 0 and the full window size
    myPID.SetOutputLimits(0, WindowSize);

    // turn the PID on
    myPID.Start(20,         // input
                0,          // current output
                setpoint);  // setpoint
  //

  /*
  //connect to wifi TRYING TO REMOVE
      WiFi.mode(WIFI_STA);
      WiFi.begin(ssid, password);

      // Wait for connection
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
      Serial.println("");
      Serial.print("Connected to ");
      Serial.println(ssid);
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
  //
  */

  //all v1 server stuff
    // //AsyncElegantOTA
    //     AsyncElegantOTA.begin(&server);  // Start ElegantOTA
    //     server.begin();
    //     Serial.println("HTTP server started");
    // //


    // //server input lol I THINK THIS MIGHT ALL BE DEPRECIATED BY WIFIMANAGER

    //   if (!SPIFFS.begin(true)) {
    //     Serial.println("An Error has occurred while mounting SPIFFS");
    //     return;
    //   }

    //   // Send web page with input fields to client
    //   server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    //     request->send_P(200, "text/html", index_html, processor);
    //   });

    //     // Send a GET request to <ESP_IP>/get?inputString=<inputMessage>
    //     server.on("/get", HTTP_GET, [](AsyncWebServerRequest* request) {
    //       String inputMessage;
    //       // GET inputString value on <ESP_IP>/get?inputString=<inputMessage>
    //       if (request->hasParam(PARAM_STRING)) {
    //         inputMessage = request->getParam(PARAM_STRING)->value();
    //         writeFile(SPIFFS, "/inputString.txt", inputMessage.c_str());
    //       }
    //       // GET inputInt value on <ESP_IP>/get?inputInt=<inputMessage>
    //       else if (request->hasParam(PARAM_INT)) {
    //         inputMessage = request->getParam(PARAM_INT)->value();
    //         writeFile(SPIFFS, "/inputInt.txt", inputMessage.c_str());
    //       }
    //       // GET inputFloat value on <ESP_IP>/get?inputFloat=<inputMessage>
    //       else if (request->hasParam(PARAM_FLOAT)) {
    //         inputMessage = request->getParam(PARAM_FLOAT)->value();
    //         writeFile(SPIFFS, "/inputFloat.txt", inputMessage.c_str());
    //       } else {
    //         inputMessage = "No message sent";
    //       }
    //       Serial.println(inputMessage);
    //       request->send(200, "text/text", inputMessage);
    //     });
    //     server.onNotFound(notFound);
    //   }
  // //

  //rotary encoder
    //we must initialize rotary encoder
    rotaryEncoder.begin();
    rotaryEncoder.setup(readEncoderISR);
    //set boundaries and if values should cycle or not
    //in this example we will set possible values between 0 and 1000;
    bool circleValues = false;
    //i think i haven't really been using the rotary encoder value, just the changes, having the max/min seemed to interfere with setting the arc/slider values
    //rotaryEncoder.setBoundaries(180, 360, circleValues);  //minValue, maxValue, circleValues true|false (when max go to min and vice versa)

    /*Rotary acceleration introduced 25.2.2021.
    * in case range to select is huge, for example - select a value between 0 and 1000 and we want 785
    * without accelerateion you need long time to get to that number
    * Using acceleration, faster you turn, faster will the value raise.
    * For fine tuning slow down.
    */
    //rotaryEncoder.disableAcceleration(); //acceleration is now enabled by default - disable if you dont need it
    //100 seems to work pretty good for moving between ~200-400
    rotaryEncoder.setAcceleration(100);  //or set the value - larger number = more accelearation; 0 or 1 means disabled acceleration
  //

  //play kim possible's beeper tone when setup is done
    //rtttl
    delay(500);
    pinMode(BUZZER_PIN, OUTPUT);
    rtttl::begin(BUZZER_PIN, kimPossible);
    while (!rtttl::done()) {
      rtttl::play();
    }
  //end kim possible beeper sound






  }
//

/**********************************l o o p*****************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/

//really gotta move these fing things
  //some late variables... these should be moved up
  int tempToWriteToLabel = 69;
  int setpointFromArc = 0;
  //turn off the pid to initialize
  bool PIDrunning = 0;

  //rtttl
  bool notified = 0;

  //slow down serial output
  int serialCurrentTime = 0;
  int serialLastPostTime = 0;

  bool led = 0;
//

void loop() {
//lvgl 'rtos'
  lv_timer_handler(); /* let the GUI do its work */
//

//check the rotary encoder
  rotary_loop();
//

//idk why this delay is here...  
  delay(5);
//

//slow serial output for debugging/testing
  serialCurrentTime = millis();
  if (serialCurrentTime - serialLastPostTime > 4000) {
    //setpoint
      // Serial.print("setpoint: ");
      // Serial.println(setpoint);
    //
    //blink the led 
      digitalWrite(15, led);
      led = !led;
      Serial.println(led);
    //update the serial print timer
    serialLastPostTime = serialCurrentTime;
  }
//

//process the setpoint from the arc
  setpointFromArc = lv_arc_get_value(ui_tempArc1);
  tempToWriteToLabel = temp;
  setpoint = setpointFromArc;
  myPID.Setpoint(setpoint);
//

//more arc stuff
  lv_label_set_text_fmt(ui_actual, "%d", tempToWriteToLabel);
  lv_label_set_text_fmt(ui_targetAKAsetpoint, "%d", setpointFromArc);
//

//get temp from thermocouple
  temp = readThermo();
//

// //get P value from pot 
//   //smooth out the reading with averages
//   int average = 0;
//   for (int i = 0; i < 30; i++) {
//     average = average + analogRead(6);
//   }
//   average = average / 30;
//   //map the average and set pee equal to the result
//   pee = 2;

//   //HAVE I BEEN SETTING THE FG I AND D TO ZERO THIS WHOLE FUCKING TIME
//   //this is what i was using ffs myPID.SetTunings(pee, 0, 0);
//   //lets try actually using i and d...
//   //myPID.SetTunings(pee, Ki, Kd);
// //

//prepare variables for pid
  const double input = temp;
  /*const*/ double output = 0;
//
//sanity check to make sure thermocouple is working, and to make sure pid is "running"
  if (!isnan(input) && PIDrunning) output = myPID.Run(input);
//

//wtf is this for?
  printOutput = output / WindowSize * 100.000;
//

/************************************************
 * turn the output pin on/off based on pid output
 ************************************************/
  while (millis() - windowStartTime > WindowSize) {
    // time to shift the Relay Window
    windowStartTime += WindowSize;
  }
  if (output < millis() - windowStartTime) {
    // Serial.print("relay:");
    // Serial.println("800");
    digitalWrite(RELAY_PIN, LOW);
  } else {
    // Serial.print("relay:"); 
    // Serial.println("200");
    digitalWrite(RELAY_PIN, HIGH);
  }
//

//server v1 stuff
  // // To access your stored values on inputString, inputInt, inputFloat
  // // String yourInputString = readFile(SPIFFS, "/inputString.txt");
  // // Serial.print("*** Your inputString: ");
  // // Serial.println(yourInputString);

  // int yourInputInt = readFile(SPIFFS, "/inputInt.txt").toInt();
  // // Serial.print("*** Your inputInt: ");
  // // Serial.println(yourInputInt);

  // // float yourInputFloat = readFile(SPIFFS, "/inputFloat.txt").toFloat();
  // // Serial.print("*** Your inputFloat: ");
  // // Serial.println(yourInputFloat);
//

//wifi manager
  wm.process();
//
// //if the set temp is reached play dammit by blink-182
//   if (tempToWriteToLabel > setpointFromArc && !notified) {
//     notified = 1;
//     rtttl::begin(BUZZER_PIN, dammit);
//     while (!rtttl::done()) {
//       rtttl::play();
//     }
  }


