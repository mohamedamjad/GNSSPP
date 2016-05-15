#include <stdlib.h>
#include<time.h>
#include<stdio.h>

#define SECONDS_IN_WEEK 604800

typedef struct t_gps{
    int week;
    int sec;
}t_gps;

void getGPStime(t_gps *gps_time, int leap_seconds, int year, int mon, int day, int hour, int min, int sec){
  int seconds; // secondes entre l'origine et la date en paramètres
  // origine du temps GPS
  struct tm origin;
  origin.tm_sec = 0;
  origin.tm_min = 0;
  origin.tm_hour = 0;
  origin.tm_mday = 6;
  origin.tm_mon = 0;
  origin.tm_year = 1980 - 1900;
  origin.tm_zone = "UTC";
  origin.tm_isdst = 0;

  // La date qu'on veut calculer
  struct tm now;
  now.tm_sec = sec;
  now.tm_min = min;
  now.tm_hour = hour;
  now.tm_mday = day;
  now.tm_mon = mon-1;
  now.tm_year = year - 1900;
  now.tm_zone = "UTC";
  now.tm_isdst = 0;

  // calculer la différence entre les deux dates et ajouter les leap seconds
  seconds = (time_t)mktime(&now) - (time_t)mktime(&origin) + leap_seconds;
  printf("Les secondes GPS: %d", seconds);
  // calculer la semaine gps
  gps_time->week = seconds / SECONDS_IN_WEEK;
  gps_time->sec = seconds % SECONDS_IN_WEEK;
}

int main(){
  t_gps gps_time;
  // function test
  getGPStime(&gps_time, 17, 2016, 5, 12, 7, 27, 31);
  printf("La semaine GPS: %d\n", gps_time.week);
  printf("Les secondes GPS: %d", gps_time.sec);
  return 0;
}
