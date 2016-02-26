#include "../include/Rinex_N.h"

Rinex_N::Rinex_N(std::string file_path){
    int line_counter;
    std::ifstream Nfile (file_path.c_str());
    if(Nfile.is_open()){
        std::string line;
        while(getline (Nfile, line)){
            line_counter++;
            if(line.find("RINEX VERSION / TYPE")!=std::string::npos){
                header.version = line.substr(0, 20);
                header.rinex_type = line.substr(20, 20);
            }else if(line.find("PGM / RUN BY / DATE")!=std::string::npos){
                header.pgm = line.substr(0, 20);
                header.run_by = line.substr(20, 20);
                header.date = line.substr(40, 20);
            }else if(line.find("ION ALPHA")!=std::string::npos){
                header.ionAlpha[0] = std::stod(line.substr(0, 15).replace('D','e'));
                header.ionAlpha[1] = std::stod(line.substr(15, 15).replace('D','e'));
                header.ionAlpha[2] = std::stod(line.substr(30, 15).replace('D','e'));
                header.ionAlpha[3] = std::stod(line.substr(45, 15).replace('D','e'));
            }else if(line.find("ION BETA")!=std::string::npos){
                header.ionBeta[0] = std::stod(line.substr(0, 15).replace('D','e'));
                header.ionBeta[1] = std::stod(line.substr(15, 15).replace('D','e'));
                header.ionBeta[2] = std::stod(line.substr(30, 15).replace('D','e'));
                header.ionBeta[3] = std::stod(line.substr(45, 15).replace('D','e'));
            }else if(line.find("DELTA-UTC")!=std::string::npos){
                header.delta_utc.A0 = std::stod(line.substr(0, 21).replace('D','e'));
                header.delta_utc.A1 = std::stod(line.substr(21, 21).replace('D','e'));
                header.delta_utc.T = std::stoi(line.substr(42, 9));
                header.delta_utc.W = std::stoi(line.substr(42, 9));
            }else if(line.find("LEAP SECONDS")!=std::string::npos){
                header.leap_seconds = std::stoi(line.substr(0, 6));
            }else if(line.find("END OF HEADER")!=std::string::npos){
                start_data = line_counter+1;
            }

        }
    }else std::cout<<"\n Problem when trying to open Navigation file";
}


int main(){
    std::cout<<"OK";
}
