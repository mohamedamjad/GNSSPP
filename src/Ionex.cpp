//IONEX 1.0
#include "../include/Ionex.h"

// -----------------------------------------------------------------------------------
// IONEX constructor
// -----------------------------------------------------------------------------------
Ionex::Ionex(std::string file_path):ionex_file(file_path){
    std::string line;
    std::ifstram Ifile
    if(Ifile.isOpen()){
        while(getline()){
            if(line.find("IONEX VERSION")!=std::string::npos){
                header.version = line.substr(0, 20);
                header.type = line.substr(20, 20);
                header.satellite_system = line.substr(40,60);
            }else if(line.find("PGM / RUN BY")!=std::string::npos){
                header.pgm = line.substr(0, 20);
                header.run_by = line.substr(20, 20);
                header.date = line.substr(40,60);
            }else if(line.find("DESCRIPTION")!=std::string::npos){
                header.description+=line.substr(0,60);
            }else if(line.find("EPOCH OF FIRST MAP")!=std::string::npos){
                header.epoch_first_map.year = line.substr(0,6);
                header.epoch_first_map.month = line.substr(6,6);
                header.epoch_first_map.day = line.substr(12,6);
                header.epoch_first_map.hour = line.substr(18,6);
                header.epoch_first_map.minute = line.substr(24,6);
                header.epoch_first_map.seconde = line.substr(30,6);
            }else if(line.find("EPOCH OF LAST MAP")!=std::string::npos){
                header.epoch_last_map.year = line.substr(0,6);
                header.epoch_last_map.month = line.substr(6,6);
                header.epoch_last_map.day = line.substr(12,6);
                header.epoch_last_map.hour = line.substr(18,6);
                header.epoch_last_map.minute = line.substr(24,6);
                header.epoch_last_map.seconde = line.substr(30,6);
            }else if(line.find("INTERVAL")!=std::string::npos){
                header.interval = std::stoi(line.substr(0,6));
            }else if(line.find("# OF MAPS IN FILE")!=std::string::npos){
                header.maps_number = std::stoi(line.substr(0,6));
            }else if(line.find("MAPPING FUNCTION")!=std::string::npos){
                header.mapping_function = line.substr(0,6);
            }else if(line.find("ELEVATION CUTOFF")!=std::string::npos){
                header.elevation_cutoff = std::stof(line.substr(0,8));
            }else if(line.find("OBSERVABLES USED")!=std::string::npos){
                header.observables_used = line.substr(0,60);
            }else if(line.find("# OF STATIONS")!=std::string::npos){
                header.number_of_stations = std::stoi(line.substr(0,6));
            }else if(line.find("# OF SATELLITES")!=std::string::npos){
                header.number_of_satellites = std::stoi(line.substr(0,6));
            }else if(line.find("BASE RADIUS")!=std::string::npos){
                header.base_radius = std::stof(line.substr(0,6));
            }else if(line.find("MAP DIMENSION")!=std::string::npos){
                header.map_dimension = std::stoi(line.substr(0,6));
            }else if(line.find("HGT1 / HGT2 /")!=std::string::npos){
                header.HGT1 = std::stof(line.substr(2,6));
                header.HGT2 = std::stof(line.substr(8,6));
                header.DHGT = std::stof(line.substr(14,6));
            }else if(line.find("LAT1 / LAT2 /")!=std::string::npos){
                header.LAT1 = std::stof(line.substr(2,6));
                header.LAT2 = std::stof(line.substr(8,6));
                header.DLAT = std::stof(line.substr(14,6));
            }else if(line.find("LON1 / LON2 /")!=std::string::npos){
                header.LON1 = std::stof(line.substr(2,6));
                header.LON2 = std::stof(line.substr(8,6));
                header.DLON = std::stof(line.substr(14,6));
            }else if(line.find("EXPONENT")!=std::string::npos){
                header.exponent = std::stoi(line.substr(0,6));
            }else if(line.find("END OF HEADER")!=std::string::npos){
                break;
            }
        }
    Ifile.close();
    }else{
        std::cout<<"\nProblème lors de l'ouverture du fichier"
    }
}
