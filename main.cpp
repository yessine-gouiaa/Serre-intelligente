#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "DHT.h"
 #include <Adafruit_Sensor.h>


// parametre wifi
const char *ssid = "TOPNET_0530";
const char *password = "drealkv03u";


//pin de la led

#define DHTPIN 4 
#define DHTTYPE DHT11
#define ventilateur 2
#define firein 15
#define fireout 21
#define pompe 5
#define moisture 33
#define caplum 32
#define led 22
#define wls 35
#define test 23
#define pompe2 18


//declaration des variables
float t;
int seuil = 20;
int lumseuil =2000;
float m;
float h =2000;
String firestate="";
String pompestate="";
String waterlevelstate="";
String moisturestate="";
String ledstate="";
String WLSstate="";
String pompe2state ="";
String ventstate ="";

String state = " ";

// capteur de temperature 
#define A0 36
#define refV 3300 
#define bits 4096.0

// serveur asynchrone 

AsyncWebServer server(80);
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(115200);
  pinMode(A0, INPUT);
  pinMode(led, OUTPUT);
  pinMode(ventilateur,OUTPUT);
  pinMode(firein,INPUT);
  pinMode(fireout,OUTPUT);
  pinMode(pompe,OUTPUT);
  pinMode(moisture ,INPUT);
  pinMode(caplum,INPUT);
  pinMode(wls,INPUT);
  pinMode(test,OUTPUT);
  pinMode(pompe2,OUTPUT);
  
  dht.begin();
//******************************* vérification des fichiers dans la mémoire **********
  if(!SPIFFS.begin())
  {
    Serial.println("Erreur SPIFFS...");
    return;
  }

  File root = SPIFFS.open("/");
  File file = root.openNextFile();

  while(file)
  {
    Serial.print("File: ");
    Serial.println(file.name());
    file.close();
    file = root.openNextFile();
  }

  //************** connexion au wifi **************
  WiFi.begin(ssid, password);
	Serial.print("Tentative de connexion...");
	
	while(WiFi.status() != WL_CONNECTED)
	{
		Serial.print(".");
		delay(100);
	}
	
	Serial.println("\n");
	Serial.println("Connexion etablie!");
	Serial.print("Adresse IP: ");
	Serial.println(WiFi.localIP());

  //************************  chargement des fichiers ****************** 
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/home.html", "text/html");
  });

 // server.on("/votre.css", HTTP_GET, [](AsyncWebServerRequest *request)
  //{
  //  request->send(SPIFFS, "/votrecss.css", "text/css");
  //});

  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/script.js", "text/javascript");
  });

//******************** réponses aux requetes du client ************

  server.on("/seuil", HTTP_GET, [](AsyncWebServerRequest *request)
  {
   Serial.println("seuil:");
   Serial.println(seuil);
    request->send(200, "text/plain", String(seuil));
  });


server.on("/seuilup", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    seuil =seuil+1;
    request->send(200);
  });

  server.on("/seuildown", HTTP_GET, [](AsyncWebServerRequest *request)
  {
   seuil =seuil-1;
    request->send(200);
  });


//fct daffichage de la temeprature
  server.on("/lireTemperature", HTTP_GET, [](AsyncWebServerRequest *request)
  {
   float t = dht.readTemperature();
   Serial.println("temperature:");
   Serial.println(t);
  

   if(t<seuil){
    digitalWrite(ventilateur , LOW);
    ventstate="vetilateur en repos";
   }
   else{
    digitalWrite(ventilateur,HIGH);
    ventstate="ventilateur en marche";
   }
     request->send(200, "text/plain", String(t));
   
  });
  server.on("/ventilateur", HTTP_GET, [](AsyncWebServerRequest *request)
  {
   
     request->send(200, "text/plain", ventstate);
   
  });


//fct affichage et controle de capteur d'incendie
  server.on("/incendie", HTTP_GET, [](AsyncWebServerRequest *request)
  {
int a = digitalRead(firein);
   

   if(a ==1){
    Serial.println("incendie:");
   Serial.println(a);
   Serial.println("no fire");
   firestate="no fire";
  
  
    digitalWrite(fireout , LOW);
   }
   else{
    Serial.println("incendie:");
   Serial.println(a);
   Serial.println("fire");
    
    firestate="fire";
    
    digitalWrite(fireout,HIGH);
   }
     request->send(200, "text/plain", firestate);
   
  });


//fct affichae et controle de l'etat du capteur moisture
 server.on("/humidite", HTTP_GET, [](AsyncWebServerRequest *request)
  {
   Serial.println("humidite:");
   Serial.println(h);
    request->send(200, "text/plain", String(h));
  });


server.on("/humup", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    h =h+50;
    request->send(200);
  });

  server.on("/humdown", HTTP_GET, [](AsyncWebServerRequest *request)
  {
   h =h-50;
    request->send(200);
  });
 
 
 
  server.on("/moisture", HTTP_GET, [](AsyncWebServerRequest *request)
  {
   float m = analogRead(moisture);
   Serial.println("moisture:");
   Serial.println(m);
  

   if(m<h){
    moisturestate="wet";
   }
   else{
    moisturestate="dry";
   }
     request->send(200, "text/plain", moisturestate);
   
  });
  server.on("/pompe", HTTP_GET, [](AsyncWebServerRequest *request)
  {

   if((firestate =="fire") ||(moisturestate=="dry") ){
    digitalWrite(pompe , HIGH);
    pompestate="activée";
    Serial.println("pompestate:");
    Serial.println(pompestate);
   }
   else{
     digitalWrite(pompe , LOW);
    pompestate="désactivée";
     Serial.println("pompestate:");
    Serial.println(pompestate);
   }
     request->send(200, "text/plain", pompestate);
   
  });

//fct affichage et controle de capteur niveau d'eau
server.on("/wls", HTTP_GET, [](AsyncWebServerRequest *request)
  {
   float w =analogRead(wls);
   Serial.println("wls:");
   Serial.println(w);
   //digitalWrite(test,HIGH); 
  

   if(w<2000){
   waterlevelstate="low";
   }
   else if(w>3500){
    waterlevelstate="high";
   }
   
   else{}
     request->send(200, "text/plain", waterlevelstate);
   
  });
  server.on("/pompe2", HTTP_GET, [](AsyncWebServerRequest *request)
  {

   if(waterlevelstate =="low" ){
    digitalWrite(pompe2 , HIGH);
    pompe2state="activée";
    Serial.println("pompe2state:");
    Serial.println(pompe2state);
   }
   else{
     digitalWrite(pompe2 , LOW);
    pompe2state="désactivée";
     Serial.println("pompestate:");
    Serial.println(pompe2state);
   }
     request->send(200, "text/plain", pompe2state);
   
  });


//fct de controle et activation de la pompe


//capteur luminosité
   server.on("/luminosite", HTTP_GET, [](AsyncWebServerRequest *request)
  {
   float lum = analogRead(caplum);;
   Serial.println("luminosité:");
   Serial.println(lum);
  

   if(lum>    lumseuil){
    digitalWrite(led , HIGH);
    ledstate="led activé";
   }
   else{
    digitalWrite(led,LOW);
    ledstate="led désactivée";
   }
     request->send(200, "text/plain", ledstate);
   
  });

//controle de la luminosité de seuil
server.on("/lumseuil", HTTP_GET, [](AsyncWebServerRequest *request)
  {
   Serial.println("lumseuil:");
   Serial.println(lumseuil);
    request->send(200, "text/plain", String(lumseuil));
  });


server.on("/lumseuilup", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    lumseuil =lumseuil+50;
    request->send(200);
  });

  server.on("/lumseuildown", HTTP_GET, [](AsyncWebServerRequest *request)
  {
   lumseuil =lumseuil-50;
    request->send(200);
  });

  server.begin();
  Serial.println("Serveur actif!");
}

void loop() {

  
}