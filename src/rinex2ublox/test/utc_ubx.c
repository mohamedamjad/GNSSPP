#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<time.h>

#define SECONDS_IN_WEEK 604800

typedef struct ubxmsg{
  unsigned char id[2];
  unsigned char length[2];
  unsigned char *payload;
  unsigned char checksum_a;
  unsigned char checksum_b;
}ubxmsg;

typedef struct nav_timeutc{
 unsigned short int sec, minute, hour, day, month, year, ToW, time_accuracy, nanosec_of_sec, validity_flag;
}nav_timeutc;

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
  //printf("Les secondes GPS: %d", seconds);
  // calculer la semaine gps
  gps_time->week = seconds / SECONDS_IN_WEEK;
  gps_time->sec = seconds % SECONDS_IN_WEEK;
}

void getChecksum(ubxmsg *ptr_ubx){
  // probleme dans cette fonction: les checksum sont variables
  // Algorithme de Fletcher: voir page 86 de u-blox6 receiver description protocol
  unsigned short int length = (ptr_ubx->length[1]<<8)|ptr_ubx->length[0];
  ptr_ubx->checksum_a = 0x00;
  ptr_ubx->checksum_b = 0x00;
  ptr_ubx->checksum_a = ptr_ubx->checksum_a + ptr_ubx->id[0];
  ptr_ubx->checksum_b = ptr_ubx->checksum_a + ptr_ubx->checksum_b;
  ptr_ubx->checksum_a = ptr_ubx->checksum_a + ptr_ubx->id[1];
  ptr_ubx->checksum_b = ptr_ubx->checksum_a + ptr_ubx->checksum_b;
  ptr_ubx->checksum_a = ptr_ubx->checksum_a + ptr_ubx->length[1];
  ptr_ubx->checksum_b = ptr_ubx->checksum_a + ptr_ubx->checksum_b;
  ptr_ubx->checksum_a = ptr_ubx->checksum_a + ptr_ubx->length[0];
  ptr_ubx->checksum_b = ptr_ubx->checksum_a + ptr_ubx->checksum_b;
  for(int i; i<(length+4); i++){
    ptr_ubx->checksum_a = ptr_ubx->checksum_a + ptr_ubx->payload[i];
    ptr_ubx->checksum_b = ptr_ubx->checksum_a + ptr_ubx->checksum_b;
  }

}

void getUTCUBX(ubxmsg *utc_msg, int leap_seconds, int year, int month, int day, int hour, int minute, int sec){
  t_gps gps_time;
  nav_timeutc *utc_t;

  utc_msg->id[0] = 0x01;
  utc_msg->id[1] = 0x21;
  utc_msg->length[0] = 0x14;
  utc_msg->length[1] = 0x00;
  // Ajout joe 
  utc_t = malloc(sizeof(utc_t));
  utc_msg->payload = (unsigned char*)utc_t;

  // GPS Millis time of week
  getGPStime(&gps_time, leap_seconds, year, month, day, hour, minute, sec);
  gps_time.sec *= 1000;
  utc_msg->payload[0] = gps_time.sec;
  memcpy(&utc_msg->payload[0], &gps_time.sec, sizeof(int));

  // Time Accuracy estimate
  utc_msg->payload[4] = 0x10;
  utc_msg->payload[5] = 0x00;
  utc_msg->payload[6] = 0x00;
  utc_msg->payload[7] = 0x00;
  
  // Nanoseconds of second
  utc_msg->payload[8] = 0x91;
  utc_msg->payload[9] = 0xf7;
  utc_msg->payload[10] = 0xfb;
  utc_msg->payload[11] = 0xff;

  // year
  memcpy(&utc_msg->payload[12], &year, sizeof(unsigned short));

  // month
  memcpy(&utc_msg->payload[14], &month, sizeof(unsigned char));

  // day of month
  memcpy(&utc_msg->payload[15], &day, sizeof(unsigned char));

  // hour of day
  memcpy(&utc_msg->payload[16], &hour, sizeof(unsigned char));

  // Minute of hour
  memcpy(&utc_msg->payload[17], &minute, sizeof(unsigned char));

  // seconds of minute
  memcpy(&utc_msg->payload[18], &sec, sizeof(unsigned char));

  // valid flag(toujours mettre à 7 lorsque les données proviennent du rinex)
  utc_msg->payload[19] = 0x07;

  // Compute checksums
  getChecksum(utc_msg);
}

int main(){
  ubxmsg utc_msg;
  //b5 62 01 21 14 00 60 5c 29 0b 10 00 00 00 91 f7 fb ff e0 07 05 0a 04 00 2b 07 e4 d4
  getUTCUBX(&utc_msg, 17, 2016, 5, 10, 4, 0, 43);
  printf("\n%02X%02X%02X%02X%02X%02X",utc_msg.id[0],utc_msg.id[1], utc_msg.length[0], utc_msg.length[1], utc_msg.payload[0],utc_msg.payload[1]);
  printf("\n\n%u", (utc_msg.length[1]<<8)|utc_msg.length[0]);
  for(int i=0; i < ((utc_msg.length[1]<<8)|utc_msg.length[0]); i++){
    printf("%u:%02X ",i,utc_msg.payload[i]);
  }
  printf("\n:checksum:%02X %02X\n", utc_msg.checksum_a, utc_msg.checksum_b);
  printf("\n");
  return 0;
}
