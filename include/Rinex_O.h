#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>


class Rinex_O{

    private:
        // Observation Rinex Header
        struct header{
            std::string version;
            std::string rinex_type;
            std::string satellite_system; // G = GPS,  R = GLONASS,
                                         //  E = GALILEO,  M = MIXED
            std::string pgm; // Program Generator
            std::string run_by;
            std::string date;
            std::string marker_name;
            std::string marker_number;
            std::string observer;
            std::string agency;
            struct receiver{
                std::string number;
                std::string type;
                std::string version;
            }receiver;
            struct antenna{
                std::string number;
                std::string type;
                float delta_h;
                float delta_e;
                float delta_n;
            }antenna;
            struct approx_position{
                float x;
                float y;
                float z;
            }approx_position;
            std::string wavelegth_fact_L1; // Wavelength factory L1
            std::string wavelength_fact_L2; // Wavelength factory L2
            int number_of_obs;
            std::string *types_of_obs;
            float interval;
            struct time_first_obs{
                int year;
                int month;
                int day;
                int hour;
                int minute;
                double second;
                std::string nav_system;
            }time_first_obs;
            struct time_last_obs{
                int year;
                int month;
                int day;
                int hour;
                int minute;
                double second;
                std::string nav_system;
            }time_last_obs;
            bool rcv_clock_offs_applied;
            int leap_seconds;
            int number_of_satellites;
        }header;

        public:
            Rinex_O(std::string);
            Rinex_O(bool, bool, std::string);

};
