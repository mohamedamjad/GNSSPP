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
            }else if(line.find("EPOCH OF FIRST MAP")){
                header.epoch_first_map.year = line.substr(0,6);
                header.epoch_first_map.month = line.substr(6,6);
                header.epoch_first_map.day = line.substr(12,6);
                header.epoch_first_map.hour = line.substr(18,6);
                header.epoch_first_map.minute = line.substr(24,6);
                header.epoch_first_map.seconde = line.substr(30,6);
            }else if(line.find("EPOCH OF LAST MAP")){
                header.epoch_last_map.year = line.substr(0,6);
                header.epoch_last_map.month = line.substr(6,6);
                header.epoch_last_map.day = line.substr(12,6);
                header.epoch_last_map.hour = line.substr(18,6);
                header.epoch_last_map.minute = line.substr(24,6);
                header.epoch_last_map.seconde = line.substr(30,6);
            }else if(line.find("")){
                header.epoch_last_map.

            }
        }
    Ifile.close();
    }else{
        std::cout<<"\nProblème lors de l'ouverture du fichier"
    }
}
