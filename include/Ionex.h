#ifndef RINEX_I_H
#define RINEX_I_H
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>

class Ionex{
    private:
        std::string ionex_file;
        struct header{
            std::string version;
            std::string type;
            std::string satellite_system;
            std::string pgm;
            std::string run_by;
            std::string date;
            std::string description="";
            typedef struct epoch_first_map{
                short int year;
                short int month;
                short int day;
                short int hour;
                short int minute;
                short int seconde;
            }epoch_first_map;

            typedef struct epoch_last_map{
                short int year;
                short int month;
                short int day;
                short int hour;
                short int minute;
                short int seconde;
            }epoch_last_map;
            int interval;
            int maps_number;
            std::string mapping_function;
            float elevation_cutoff;
            std::string observables_used;
            short int number_of_stations;
            short int number_of_satellites;
            float base_radius;
            short int map_dimension;
            float HGT1;
            float HGT2;
            float DHGT;
            float LAT1;
            float LAT2;
            float DLAT;
            float LON1;
            float LON2;
            float DLON;
            int exponent;
            };


    public:



};
#endif
