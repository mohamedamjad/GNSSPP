#include <stdlib.h>
#include <string>
#include "../include/common_structures.h"
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
    int wavelength_fact_L1; // Wavelength factory L1
    int wavelength_fact_L2; // Wavelength factory L2
    int number_of_obs;
    std::string *observations;
    float interval;
    struct time_first_obs{
        int year;
        int month;
        int day;
        int hour;
        int minute;
        double seconde;
        std::string nav_system;
    }time_first_obs;
    struct time_last_obs{
        int year;
        int month;
        int day;
        int hour;
        int minute;
        double seconde;
        std::string nav_system;
    }time_last_obs;
    bool rcv_clock_offs_applied;
    int leap_seconds;
    int number_of_satellites;
};


typedef struct observation{
    std::string PRN;
    double L1;
    short int L1LLI;
    short int L1SSI;
    double L2;
    short int L2LLI;
    short int L2SSI;
    double P1;
    short int P1SSI;
    double P2;
    short int P2SSI;
    double C1;
    short int C1SSI;
    double C2;
    short int C2SSI;
    float S1;
    float S2;
    float D1;
    float D2;
}observation;

struct epoch{
    unsigned int unix_time;
    int year;
    int month;
    int day;
    int hour;
    int minute;
    double seconde;
    short int satellite_number;
    double receiver_clock_offset;
    // tableau d'observations
    std::vector<observation> observations;
};
