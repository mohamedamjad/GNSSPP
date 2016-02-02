#include "../include/Rinex_O.h"
#include <iostream>

Rinex_O::Rinex_O(bool bool_header, bool bool_data, std::string file_path){
    std::cout<<"GNSSPP is trying to open: "<<file_path<<"\n";
    std::ifstream Ofile (file_path.c_str());
    if(Ofile.is_open()){
        std::string line;
        std::cout<<"File opened.. Starting processing\n";
        // Read file line by line
        while (getline (Ofile, line)){
            //std::cout<<line<<"\n";
            if(line.find("RINEX VERSION / TYPE")!=std::string::npos){
                header.version=line.substr(0,20);
                header.rinex_type=line.substr(20,20);
                header.satellite_system=line.substr(40,20);
                std::cout<<header.version<<"\n";
            }
            else if(line.find("PGM / RUN BY / DATE")!=std::string::npos){
                header.pgm=line.substr(0,20);
                header.run_by=line.substr(20,20);
                header.date=line.substr(40,20);
            }
            else if(line.find("MARKER NAME")!=std::string::npos){
                header.marker_name=line.substr(0,60);
            }
            else if(line.find("MARKER NUMBER")!=std::string::npos){
                header.marker_number=line.substr(0,20);
            }
            else if(line.find("OBSERVER / AGENCY")!=std::string::npos){
                header.observer=line.substr(0,20);
                header.agency=line.substr(20,40);
            }
            else if(line.find("REC # / TYPE / VERS")!=std::string::npos){
                header.receiver.number=line.substr(0,20);
                header.receiver.type=line.substr(20,20);
                header.receiver.version=line.substr(40,20);
            }
            else if(line.find("ANT # / TYPE")!=std::string::npos){
                header.antenna.number=line.substr(0,20);
                header.antenna.type=line.substr(20,20);
            }
            else if(line.find("APPROX POSITION XYZ")!=std::string::npos){
                header.approx_postion.x = line.substr(0,15);
                header.approx_position.y = line.substr(15,15);
                header.approx_position.z = line.substr(30,15);
            }
            else if(line.find("ANTENNA: DELTA H/E/N")!=std::string::npos){
                header.antenna.delta_h = line.substr(0,15);
                header.antenna.data_e = line.substr(15,15);
                header.antenna.data_n = line.substr(30,15);
            }
            else if(line.find("WAVELENGTH FACT L1")!=std::string::npos){
                header.wavelegth_fact_L1 = line.substr(0,15);
                header. wavelength_fact_L2= line.substr(15,15);
            }
            else if(line.find("# / TYPES OF OBSERV")!=std::string::npos){
                header.number_of_obs = line.substr(0,6);
                // en fonction de number_of_obs
            }
            else if(line.find("INTERVAL")!=std::string::npos){
                header.number_of_obs = line.substr(0,10);
            }
            else if(line.find("TIME OF FIRST OBS")!=std::string::npos){
                header.time_first_obs.year = line.substr(0,6);
                header.time_first_obs.year = line.substr(6,6);
                header.time_first_obs.year = line.substr(12,6);
                header.time_first_obs.year = line.substr(18,6);
                header.time_first_obs.year = line.substr(24,6);
                header.time_first_obs.year = line.substr(24,14);
                header.time_first_obs.nav_system = line.substr(24,14);
            }
            else if(line.find("TIME OF LAST OBS")!=std::string::npos){
                header.time_last_obs.year = line.substr(0,6);
                header.time_last_obs.year = line.substr(6,6);
                header.time_last_obs.year = line.substr(12,6);
                header.time_last_obs.year = line.substr(18,6);
                header.time_last_obs.year = line.substr(24,6);
                header.time_last_obs.year = line.substr(24,14);
            }

        }
        Ofile.close();
    }else{
        std::cout<<"Can\'t open the file !\n";
    }
    if(bool_header){
        std::cout<<"Parsing header\n";
    }
    if(bool_data){
        std::cout<<"Parsing data\n";
    }
}

Rinex_O::Rinex_O(std::string file_path){
    Rinex_O(true, true, file_path);
}

int main(int argc, char *argv[]){

    Rinex_O r(argv[1]);
    std::cout<<"Fonction principale\n";
}
