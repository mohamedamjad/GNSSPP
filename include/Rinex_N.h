#ifndef RINEX_N_H
#define RINEX_N_H
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>

class Rinex_N{
    private:
        struct header{
            std::string version;
            std::string rinex_type;
            std::string pgm; // Program Generator
            std::string run_by;
            std::string date;
            double ionAlpha[4];
            double ionBeta[4];
            struct delta_utc{
                double A0;
                double A1;
                int T;
                int W;
                }delta_utc;
            short int leap_senconds;
            }header;

        typedef struct ephemeris{
            short int PRN; // Pseudo Random Noise
            unsigned int unix_time;
            int year;
            int month;
            int day;
            int hour;
            int minute;
            double seconde;
            double SV_clock_bias;
            double SV_clock_drift;
            double SV_clock_drift_rate;
            double IODE; // Issue of Data Ephemeris
            double Crs; // Radius Correction Sinus Component
            double delta_n;
            double Mo; // Mo angle
            double cuc;
            double eccentricity;
            double cus;
            double sqrt_a;
            double ToE; // Time of Ephemeris
            double cic;
            double OMEGA;
            double cis;
            double Io;
            double crc;
            double omega;
            double Omega_dot; // angular velocity
            double I_dot; // Inclination rate
            double L2_codes_channel;
            double gps_week;
            double L2_P_data_flag;
            double sv_accuracy;
            double sv_health;
            double TGD; // Total Group Delay
            double IoDC; // Issue of Data Clock
            double transmission_time;
            double fit_interval;
            }ephemeris;

    public:
        Rinex_N(std::string file_path);
        void getEphemeris( short int PRN, ephemeris& eph);
};
#endif
