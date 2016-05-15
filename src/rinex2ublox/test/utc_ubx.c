#include<stdlib.h>
#include<string.h>
#include<stdio.h>

typedef struct ubxmsg{
  unsigned char id[2];
  unsigned char length[2];
  unsigned char *payload;
  unsigned char checksum_a;
  unsigned char checksum_b;
}ubxmsg;


void getChecksum(ubxmsg *ptr_ubx, unsigned char *checksum_a, unsigned char *checksur_b){
  // Algorithme de Fletcher: voir page 86 de u-blox6 receiver description protocol
 
}

void getUTCUBX(ubxmsg *utc_msg, int year, int month, int day, int hour, int minute, int sec){
  (*utc_msg).id[0] = 0x01;
  (*utc_msg).id[1] = 0x21;
  (*utc_msg).length[0] = 0x14;
  (*utc_msg).length[1] = 0x00;
  (*utc_msg).payload = (unsigned char *)malloc(20*sizeof(unsigned char));
  // GPS Millis time of week
  
  // Time Accuracy estimate

  // Nanoseconds of second

  // year

  // month

  // Hour of day

  // Minute of hour

  // seconds of minute
  
}

int main(){
  unsigned char c[4];
  int a=32454;
  bcopy(&a, &c, 4);
  printf("\nfirst c of 4 is : %.02X %.02X %.02X %.02X\n", c[0], c[1], c[2], c[3]);
  return 0;
}
