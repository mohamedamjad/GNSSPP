#include <stdlib.h>
#include<time.h>
#include<stdio.h>
//#include<fstream>
//#include<iostream>

/*int main(){
  char *mem_bloc;
  mem_bloc = new char [4];
  mem_bloc[0] = 0xb5;
  mem_bloc[1] = 0x62;
  mem_bloc[2] = 0xe7;
  mem_bloc[3] = 0x4a;
  std::ofstream ubx_stream;
  ubx_stream.open("test.ubx",std::ios::out|std::ios::binary);
  ubx_stream.write(mem_bloc,3);
  ubx_stream.close();
  return 0;
}
*/
typedef struct t_gps{
    int week;
    int sec;
}t_gps;

void getGPStime(t_gps *gps_time, int leap_seconds, int year, int mon, int day, int hour, int min, int sec){
  long int seconds; // secondes entre l'origine et la date en paramètres
  // origine du temps GPS
  struct tm origin = {0};
  origin.tm_sec = 0;
  origin.tm_min = 0;
  origin.tm_hour = 0;
  origin.tm_mday = 6;
  origin.tm_mon = 1;
  origin.tm_year = 80;

  // La date qu'on veut calculer
  struct tm now;
  now.tm_sec = sec;
  now.tm_min = min;
  now.tm_hour = hour;
  now.tm_mday = day;
  now.tm_mon = mon;
  now.tm_year = year - 1900;

  // calculer la différence entre les deux dates et ajouter les leap seconds
  seconds = (time_t)mktime(&now) - (time_t)mktime(&origin) + leap_seconds;

  // calculer la semaine gps
  gps_time->week = (seconds-(seconds%604800))/604800;
  gps_time->sec = seconds-(seconds%604800);
}

int main(){
  t_gps *gps_time;
  getGPStime(gps_time, 17, 2016, 5, 11, 11, 2, 35);
  printf("%d",gps_time->week);
  return 0;
}
