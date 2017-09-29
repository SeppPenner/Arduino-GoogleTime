/***********************************************
 * Arduino GoogleTime Library - version 1.0.0
 * Ryan Downing <redm961@gmail.com>
***********************************************/

#ifndef GOOGLETIME_H
#define GOOGLETIME_H
#include <ESP8266HTTPClient.h>

/*
 * Gets current time (GMT) and date from Google.com http response header
 * Response header expected in the following format:
 *    date:Fri, 28 Sep 2017 20:56:54 GMT
 * Returns true if successful response received
 * 
 * Inputs are passed by reference and thus updated outside the function
 * int &w: 1-7 corresponding to day of the week Sunday-Saturday
 * int &D: 1-31 day of current date
 * int &M: 1-12 corresponding to month of current date Jan-Dec
 * int &Y, &h, &m, &s: year, hour, minute, second
 */
bool googleTime(int &w, int &D, int &M, int &Y, int &h, int &m, int &s) {
  HTTPClient http;
#ifdef GOOGLETIME_TIMEOUT
  http.setTimeout(GOOGLETIME_TIMEOUT);
#endif
  http.begin("http://www.google.com");
  const char* headerNames[] = {"date"};
  http.collectHeaders(headerNames, 1);
  if (http.GET() && http.hasHeader("date")) {
    String d = http.header("date");
    char dc[40];
    d.toCharArray(dc, 40);
    w = String("..SuMoTuWeThFrSa").indexOf(String(strtok(dc, " ,:")).substring(0, 2)) / 2;
    D = String(strtok(NULL, " ,:")).toInt();
    M = String("...JanFebMarAprMayJunJulAugSepOctNovDec").indexOf(String(strtok(NULL, " ,:")).substring(0, 3)) / 3;
    Y = String(strtok(NULL, " ,:")).toInt();
    h = String(strtok(NULL, " ,:")).toInt();
    m = String(strtok(NULL, " ,:")).toInt();
    s = String(strtok(NULL, " ,:")).toInt();
    return true;
  }//if
  return false;
}//bool googleTime

#endif //GOOGLETIME_H
