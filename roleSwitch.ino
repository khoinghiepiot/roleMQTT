 #include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Arduino.h> 

const char *ssid = "ten wifi";           // wifi SSID
const char *password = "passwifi";

  // wifi password
const char *mqtt_server = "domain"; // change this with your server name
const char *device_id = "mainlight";            // write any unique ID

WiFiClient espClient;
PubSubClient client(espClient);
const int buttond2 = D2;
const byte ledPin5 = D5;
const byte ledPin6 = D6;
const int buttond1 = D1;


int a=0;

int tthaicu;
int tthai1cu;

int stt =1 ;
int sttold =1;
int stt1=1;
int sttold1=1;
int sttoldkwf=1;
int sttoldkwf1=1;
int sttkwf;
int sttkwf1;


char message_buff[100];
String msgString;
String topicStr;
void onoffnwf()
{
          
    sttkwf = digitalRead(buttond1);
    sttkwf1 = digitalRead(buttond2);
          {
          
          if (sttkwf != sttoldkwf)
          {
            
             sttoldkwf = sttkwf;
             if (sttkwf == 1)
        {
             digitalWrite(ledPin5, LOW);
             
        }
        else if (sttkwf == 0)
        {
          digitalWrite(ledPin5, HIGH);
            
            
        }
          }
          else if (sttkwf == sttoldkwf)
               sttoldkwf = sttkwf;
    }
    {
          
          if (sttkwf1 != sttoldkwf1)
          {
             sttoldkwf1 = sttkwf1;
             if (sttkwf1 == 1)
        {
             digitalWrite(ledPin6, LOW);
             
        }
        else if (sttkwf1 == 0)
        {
          digitalWrite(ledPin6, HIGH);
            
            
        }
          }
          else if (sttkwf1 == sttoldkwf1)
               sttoldkwf1 = sttkwf1;
    }
        }
void setup_wifi() 
{
delay(10);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
      
        delay(100);
        
         onoffnwf();
        
   
 
   digitalWrite(LED_BUILTIN, LOW);

        }
  
  blink();
  blink();
  blink();
}
void blink()
{
digitalWrite(LED_BUILTIN, HIGH);
delay(500);
digitalWrite(LED_BUILTIN, LOW);
delay(500);
digitalWrite(LED_BUILTIN, HIGH);
delay(500);
}


void callback(char *topic, byte *payload, unsigned int length)
{
    int i;
    
    topicStr = topic;
    for (i = 0; i < length; i++)
    {
        message_buff[i] = payload[i];
    }
    message_buff[i] = '\0';

    msgString = String(message_buff);
    
    if (topicStr == "relay/mainlight")
{
        if (msgString == "1")
        {
            digitalWrite(ledPin5, LOW); // PIN HIGH will switch OFF the relay
            client.publish("relay/mainlightstate","1");
            
        }
        if (msgString == "0")
        {
            digitalWrite(ledPin5, HIGH); // PIN LOW will switch ON the relay
            client.publish("relay/mainlightstate","0");
            
        }
}
    else if (topicStr == "relay/mainlight1")
    { // write your unique ID here
        if (msgString == "1")
        {
            digitalWrite(ledPin6, LOW); // PIN HIGH will switch OFF the relay
            client.publish("relay/mainlightstate1","1");
            
        }
        if (msgString == "0")
        {
            digitalWrite(ledPin6, HIGH); // PIN LOW will switch ON the relay
            client.publish("relay/mainlightstate1","0");
           
        }
    }
    
}
void reconnect()
{
    
    while (!client.connected())
    {
        a=a+1;
        
        delay(100);
        if (a==150)
        {
        a=0;
        
        
        if (client.connect("mainlight", "usermqqq", "passmqtt"))
      
            {
            client.subscribe("relay/mainlightstate");
            client.subscribe("relay/mainlightstate1");
            client.subscribe("relay/mainlight");
            client.subscribe("relay/mainlight1");

            }
    }
        else if (a<150)
        {
         onoffnwf();
        }
}
}

void setup()
{
    
    delay(10);
    pinMode(LED_BUILTIN, OUTPUT);
    
    pinMode(buttond2, INPUT);
    pinMode(buttond1, INPUT);
    pinMode(ledPin5, OUTPUT);
    pinMode(ledPin6, OUTPUT);
    setup_wifi();
    client.setServer(mqtt_server, 1883); // change port number as mentioned in your cloudmqtt console
    client.setCallback(callback);
 
    
    
    

    
}

void loop()
{ 
  

  
  
    



   
    stt = digitalRead(buttond1);
    stt1 = digitalRead(buttond2);
   
    
    {
    if (topicStr == "relay/mainlightstate")
    { 
        if (msgString == "1")
        {
            tthaicu = 1;
         
        }
        if (msgString == "0")
        {
            tthaicu=0;
            
        }
    }
    
    }
     
     
     
     {
    if (topicStr == "relay/mainlightstate1")
    { 
        if (msgString == "1")
        {
            tthai1cu = 1;
         
        }
        if (msgString == "0")
        {
            tthai1cu=0;
            
        }
    }
    
    }
    
    
    
    
    
    {
    if (stt != sttold)
    { 
      {
      if (tthaicu == 1)
        
        {
            digitalWrite(ledPin5, HIGH); // PIN HIGH will switch OFF the relay
            client.publish("relay/mainlightstate","0");
            
        }
        if (tthaicu == 0)
        {
            digitalWrite(ledPin5, LOW); // PIN LOW will switch ON the relay
            client.publish("relay/mainlightstate","1");
            
        }
      }
      
      sttold = stt;


      }
else if (stt == sttold)
{

    sttold = stt;

}
    }

{       
if (stt1 != sttold1)
    { 
      
        {
       if (tthai1cu == 1)
        
        {
            digitalWrite(ledPin6, HIGH); // PIN HIGH will switch OFF the relay
            client.publish("relay/mainlightstate1","0");
            
        }
        if (tthai1cu == 0)
        {
            digitalWrite(ledPin6, LOW); // PIN LOW will switch ON the relay
            client.publish("relay/mainlightstate1","1");
            
        }
        
        }
   sttold1 = stt1;


      }
else if (stt1 == sttold1)
{

    sttold1 = stt1;

}
} 
    
  




  
{

 if (!client.connected())
    {
        reconnect();
    }
    client.loop();
}

  
}




  


