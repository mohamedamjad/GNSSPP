#include "../include/Rinex_N.h"

Rinex_N::Rinex_N(std::string file_path):Nfile(file_path){
    int line_counter;
    std::ifstream NfileStream(Nfile.c_str());
    if(NfileStream.is_open()){
        std::string line;
        while(getline (NfileStream, line)){
            line_counter++;
            std::cout<<line<<"\n";
            if(line.find("RINEX VERSION / TYPE")!=std::string::npos){
                header.version = line.substr(0, 20);
                header.rinex_type = line.substr(20, 20);
            }else if(line.find("PGM / RUN BY / DATE")!=std::string::npos){
                header.pgm = line.substr(0, 20);
                header.run_by = line.substr(20, 20);
                header.date = line.substr(40, 20);
            }else if(line.find("ION ALPHA")!=std::string::npos){
                header.ionAlpha[0] = std::stod(line.substr(0, 15));
                header.ionAlpha[1] = std::stod(line.substr(15, 15));
                header.ionAlpha[2] = std::stod(line.substr(30, 15));
                header.ionAlpha[3] = std::stod(line.substr(45, 15));
            }else if(line.find("ION BETA")!=std::string::npos){
                header.ionBeta[0] = std::stod(line.substr(0, 15));
                header.ionBeta[1] = std::stod(line.substr(15, 15));
                header.ionBeta[2] = std::stod(line.substr(30, 15));
                header.ionBeta[3] = std::stod(line.substr(45, 15));
            }else if(line.find("DELTA-UTC")!=std::string::npos){
                header.delta_utc.A0 = std::stod(line.substr(0, 21));
                header.delta_utc.A1 = std::stod(line.substr(21, 21));
                header.delta_utc.T = std::stoi(line.substr(42, 9));
                header.delta_utc.W = std::stoi(line.substr(42, 9));
            }else if(line.find("LEAP SECONDS")!=std::string::npos){
                header.leap_seconds = std::stoi(line.substr(0, 6));
            }else if(line.find("END OF HEADER")!=std::string::npos){
                index_start_data = line_counter+1;
                break;
            }

        }
        NfileStream.close();
    }else std::cout<<"\n Problem when trying to open Navigation file";
}


void Rinex_N::getEphemeris( short int PRN, std::vector <eph>& ephemeris_vector){
    std::ifstream NfileStream(Nfile.c_str());
    std::string line;
    int line_counter=0;
    
    while (getline(NfileStream, line)){
        line_counter++;
        if(line_counter<index_start_data) continue;
        if(line.substr(0, 3).find("   ")==std::string::npos && PRN==std::stoi(line.substr(0,2))){
            std::cout<<line<<"\n";
            ephemeris->PRN = std::stoi(line.substr(0,2));
            ephemeris->year = std::stoi(line.substr(2,3));
            ephemeris->month = std::stoi(line.substr(5,3));
            ephemeris->day = std::stoi(line.substr(8,3));
            ephemeris->hour = std::stoi(line.substr(11, 3));
            ephemeris->minute = std::stoi(line.substr(14,3));
            ephemeris->seconde = std::stod(line.substr(17, 5));
            ephemeris->SV_clock_bias = std::stod(line.substr(22, 19));
            ephemeris->SV_clock_drift = std::stod(line.substr(41, 19));
            ephemeris->SV_clock_drift_rate = std::stod(line.substr(60, 19));
            getline(NfileStream, line);
            ephemeris->IODE = std::stod(line.substr(3, 19));
            ephemeris->crs = std::stod(line.substr(22, 19));
            ephemeris->delta_n = std::stod(line.substr(41, 19));
            ephemeris->Mo = std::stod(line.substr(60, 19));
            getline(NfileStream, line);
            ephemeris->cuc = std::stod(line.substr(3, 19));
            ephemeris->eccentricity = std::stod(line.substr(22, 19));
            ephemeris->cus = std::stod(line.substr(41, 19));
            ephemeris->sqrt_a = std::stod(line.substr(60, 19));
            getline(NfileStream, line);
            ephemeris->ToE = std::stod(line.substr(3, 19));
            ephemeris->cic = std::stod(line.substr(22, 19));
            ephemeris->OMEGA = std::stod(line.substr(41, 19));
            ephemeris->cis = std::stod(line.substr(60, 19));
            getline(NfileStream, line);
            ephemeris->Io = std::stod(line.substr(3, 19));
            ephemeris->crc = std::stod(line.substr(22, 19));
            ephemeris->omega = std::stod(line.substr(41, 19));
            ephemeris->OMEGA_dot = std::stod(line.substr(60, 19));
            getline(NfileStream, line);
            ephemeris->I_dot = std::stod(line.substr(3, 19));
            ephemeris->L2_codes_channel = std::stod(line.substr(22, 19));
            ephemeris->gps_week = std::stod(line.substr(41, 19));
            ephemeris->L2_P_data_flag = std::stod(line.substr(60, 19));
            getline(NfileStream, line);
            ephemeris->sv_accuracy = std::stod(line.substr(3, 19));
            ephemeris->sv_health = std::stod(line.substr(22, 19));
            ephemeris->TGD = std::stod(line.substr(41, 19));
            ephemeris->IODC = std::stod(line.substr(60, 19));
            getline(NfileStream, line);
            ephemeris->transmission_time = std::stod(line.substr(3, 19));
            //ephemeris.fit_interval = std::stod(line.substr(22, 19));
            
        }
    }
    
}

int main(){
    Rinex_N r("/home/anonyme/Téléchargements/tmp/brdc0030.16n");
    std::vector<Rinex_N::eph> ephemeris_vector;
    r.getEphemeris(3, ephemeris_vector);
}
