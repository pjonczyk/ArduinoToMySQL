/*
 * mysql
 * Version 1.0 22th of August, 2015
 * Author : Ajay Masi
 * Organisation : Shivy Inc.
 * ***********************************
 * To run this code you have to follow the procedure :
 * Create database 'arduino'
 * Create table in arduino of name 'sensors' with fields:
 * 'id' of type INT with autoincrement
 * 'name' of type VARCHAR with size 100
 * 'value' of type integer
 *
 *
 * If you are using Wamp Server change the credentials according
 * to your MySQL configuration
 *
 *
 * Make sure your Wamp Server or anyother MySQL service as specified 
 * is running else it will generate error 
 */
#include <mysql.h>

char  *host = (char*)"localhost";
char  *user = (char*)"root";
char  *pass = (char*)"";
char  *db   = (char*)"nfcscheduler";
int isconnected = 0;


String result_query(String query, String field){
  String res = "";
  //String q = query + "&field=" + field;
  Serial.println(query);
  //delay(3000);
  res = Serial.readString();
  //Serial.println("reading result: " + res);
  if(res == "-")
  return 0;
  while(res.length() <= 0){
  res = Serial.readString();  
  if(res == "-")
  return 0;
  }
  Serial.println("reading result: " + res);
  Serial.println("second: " + Serial.readString());
  return res;
}

void setup()
{
	Serial.begin(9600);
	isconnected = mysql_connect(host,user,pass,db);

 if(isconnected){
  
    Serial.print("Connected to ");
    Serial.println(host);
    //int result = mysql_query((char*)"INSERT INTO test(`id`, `texttest`) VALUES('30', 'blabla')");
    char *feld = (char*)"";
    String ausgabe = result_query((char*)"query=SELECT * FROM timetable",(char*) "name");
    //Serial.println(ausgabe);
    if(ausgabe != ""){
      Serial.println("Query exexcuted.");
    }else{
      Serial.println("Query execution failed.");
    }
  }else{
    Serial.println("Connection failed.");
  }
	mysql_close();
}

void loop(){}
