#include "../include/Rinex_O.h"
//#include <iostream>


// -----------------------------------------------------------------------------------
// Constructeur qui prend en entrée le chemin vers le fichier à parser, commence par
// parser le header
// -----------------------------------------------------------------------------------
Rinex_O::Rinex_O(bool bool_header, std::string file_path):rinex_file_path(file_path){
    int line_number = 0;
    std::cout<<"GNSSPP is trying to open: "<<rinex_file_path<<"\n";
    std::ifstream Ofile (file_path.c_str());
    if(Ofile.is_open()){
        std::string line;
        std::cout<<"File opened.. Starting processing\n";
        // Read file line by line
        while (getline (Ofile, line)){
            line_number++;
            //std::cout<<line<<"\n";
            if(line.find("RINEX VERSION / TYPE")!=std::string::npos){
                header.version=line.substr(0,20);
                header.rinex_type=line.substr(20,20);
                header.satellite_system=line.substr(40,20);
                // Test
                std::cout<<header.version<<"\n";
                std::cout<<header.rinex_type<<"\n";
                std::cout<<header.satellite_system<<"\n";
            }
            else if(line.find("PGM / RUN BY / DATE")!=std::string::npos){
                header.pgm=line.substr(0,20);
                header.run_by=line.substr(20,20);
                header.date=line.substr(40,20);
                // Test
                std::cout<<header.pgm<<"\n";
                std::cout<<header.run_by<<"\n";
                std::cout<<header.date<<"\n";
            }
            else if(line.find("MARKER NAME")!=std::string::npos){
                header.marker_name=line.substr(0,60);
                // Test
                std::cout<<header.marker_name<<"\n";
            }
            else if(line.find("MARKER NUMBER")!=std::string::npos){
                header.marker_number=line.substr(0,20);
                // Test
                std::cout<<header.marker_number<<"\n";
            }
            else if(line.find("OBSERVER / AGENCY")!=std::string::npos){
                header.observer=line.substr(0,20);
                header.agency=line.substr(20,40);
                // Test
                std::cout<<header.observer<<"\n";
                std::cout<<header.agency<<"\n";
            }
            else if(line.find("REC # / TYPE / VERS")!=std::string::npos){
                header.receiver.number=line.substr(0,20);
                header.receiver.type=line.substr(20,20);
                header.receiver.version=line.substr(40,20);
                // Test
                std::cout<<header.receiver.number<<"\n";
                std::cout<<header.receiver.type<<"\n";
                std::cout<<header.receiver.version<<"\n";
            }
            else if(line.find("ANT # / TYPE")!=std::string::npos){
                header.antenna.number=line.substr(0,20);
                header.antenna.type=line.substr(20,20);
                // Test
                std::cout<<header.antenna.number<<"\n";
                std::cout<<header.antenna.type<<"\n";
            }
            else if(line.find("APPROX POSITION XYZ")!=std::string::npos){
                header.approx_position.x = std::stof(line.substr(0,15));
                header.approx_position.y = std::stof(line.substr(15,15));
                header.approx_position.z = std::stof(line.substr(30,15));
                // Test
                std::cout<<header.approx_position.x<<"\n";
                std::cout<<header.approx_position.y<<"\n";
                std::cout<<header.approx_position.z<<"\n";
            }
            else if(line.find("ANTENNA: DELTA H/E/N")!=std::string::npos){
                header.antenna.delta_h = std::stof(line.substr(0,15));
                header.antenna.delta_e = std::stof(line.substr(15,15));
                header.antenna.delta_n = std::stof(line.substr(30,15));
                std::cout<<header.antenna.delta_h<<"\n";
                std::cout<<header.antenna.delta_e<<"\n";
                std::cout<<header.antenna.delta_n<<"\n";
            }
            else if(line.find("WAVELENGTH FACT L1")!=std::string::npos){
                header.wavelength_fact_L2=std::stoi(line.substr(6,6));
                header.wavelength_fact_L1=std::stoi(line.substr(0,6));
                // Test
                std::cout<<header.wavelength_fact_L1<<"\n";
                std::cout<<header.wavelength_fact_L2<<"\n";
            }
            else if(line.find("# / TYPES OF OBSERV")!=std::string::npos && line.substr(0, 6).find("      ")==std::string::npos){ // Ce n'est pas suffisant ça peut s'etaler sur deux lignes
                header.number_of_obs = std::stoi(line.substr(0,6));
                header.observations = (std::string*)malloc(header.number_of_obs*sizeof(std::string));
                std::cout<<"Nombre des observables :"<<header.number_of_obs;
                for (int i=0; i<header.number_of_obs; i++){
                    if (line.substr((i+1)*6,6).find("L1")!=std::string::npos){
                        header.observations[i]="L1";
                    }
                    else if (line.substr((i+1)*6,6).find("L2")!=std::string::npos){
                        header.observations[i]="L2";
                    }
                    else if (line.substr((i+1)*6,6).find("C1")!=std::string::npos){
                        header.observations[i]="C1";
                    }
                    else if (line.substr((i+1)*6,6).find("C2")!=std::string::npos){
                        header.observations[i]="C2";
                    }
                    else if (line.substr((i+1)*6,6).find("P1")!=std::string::npos){
                        header.observations[i]="P1";
                    }
                    else if (line.substr((i+1)*6,6).find("P2")!=std::string::npos){
                        header.observations[i]="P2";
                    }
                    else if (line.substr((i+1)*6,6).find("S1")!=std::string::npos){
                        header.observations[i]="S1";
                    }
                    else if (line.substr((i+1)*6,6).find("S2")!=std::string::npos){
                        header.observations[i]="S2";
                    }
                    else if (line.substr((i+1)*6,6).find("D1")!=std::string::npos){
                        header.observations[i]="D1";
                    }
                    else if (line.substr((i+1)*6,6).find("D2")!=std::string::npos){
                        header.observations[i]="D2";
                    }
                    // First Line of # / TYPES OF OBSERV
                    std::cout<<header.observations[i]<<"\n";
                    if(i>7){
                        break;
                    }
                }
                // en fonction de number_of_obs
            }
            

            else if(line.find("# / TYPES OF OBSERV")!=std::string::npos && line.substr(0, 6).find("      ")!=std::string::npos){
                int i = 8;
                for (int j = 0; j<header.number_of_obs-7; j++){
                    if (line.substr((j+1)*6,6).find("L1")!=std::string::npos){
                        header.observations[i+j+1]="L1";
                    }
                    else if (line.substr((j+1)*6,6).find("L2")!=std::string::npos){
                        header.observations[i+j+1]="L2";
                    }
                    else if (line.substr((j+1)*6,6).find("C1")!=std::string::npos){
                        header.observations[i+j+1]="C1";
                    }
                    else if (line.substr((j+1)*6,6).find("C2")!=std::string::npos){
                        header.observations[i+j+1]="C2";
                    }
                    else if (line.substr((j+1)*6,6).find("P1")!=std::string::npos){
                        header.observations[i+j+1]="P1";
                    }
                    else if (line.substr((j+1)*6,6).find("P2")!=std::string::npos){
                        header.observations[i+j+1]="P2";
                    }
                    else if (line.substr((j+1)*6,6).find("S1")!=std::string::npos){
                        header.observations[i+j+1]="S1";
                    }
                    else if (line.substr((j+1)*6,6).find("S2")!=std::string::npos){
                        header.observations[i+j+1]="S2";
                        std::cout<<header.observations[i+j+1];
                    }
                    else if (line.substr((j+1)*6,6).find("D1")!=std::string::npos){
                        header.observations[i+j+1]="D1";
                    }
                    else if (line.substr((j+1)*6,6).find("D2")!=std::string::npos){
                        header.observations[i+j+1]="D2";
                    }

                }
            }

            else if(line.find("INTERVAL")!=std::string::npos){
                header.interval = std::stof(line.substr(0,10));
                // Test
                std::cout<<header.interval<<"\n";
            }
            else if(line.find("TIME OF FIRST OBS")!=std::string::npos){
                header.time_first_obs.year = std::stoi(line.substr(0,6));
                header.time_first_obs.month = std::stoi(line.substr(6,6));
                header.time_first_obs.day = std::stoi(line.substr(12,6));
                header.time_first_obs.hour = std::stoi(line.substr(18,6));
                header.time_first_obs.minute = std::stoi(line.substr(24,6));
                header.time_first_obs.seconde = std::stod(line.substr(24,14));
                header.time_first_obs.nav_system = line.substr(37,8);
            }
            else if(line.find("TIME OF LAST OBS")!=std::string::npos){
                header.time_last_obs.year = std::stoi(line.substr(0,6));
                header.time_last_obs.month = std::stoi(line.substr(6,6));
                header.time_last_obs.day = std::stoi(line.substr(12,6));
                header.time_last_obs.hour = std::stoi(line.substr(18,6));
                header.time_last_obs.minute = std::stoi(line.substr(24,6));
                header.time_last_obs.seconde = std::stod(line.substr(24,14));
                header.time_last_obs.nav_system = line.substr(37,8);
            }
            else if(line.find("RCV CLOCK OFFS APPL")!=std::string::npos){
                if (line.substr(0,6).find("1")!=std::string::npos){
                    header.rcv_clock_offs_applied=true;
                }else header.rcv_clock_offs_applied = false;
            }
            else if(line.find("LEAP SECONDS")!=std::string::npos){
                header.leap_seconds = std::stoi(line.substr(0,6));
            }
            else if(line.find("# OF SATELLITES")!=std::string::npos){
                header.number_of_satellites = std::stoi(line.substr(0,6));
            }
            else if(line.find("END OF HEADER")!=std::string::npos){
                // Parse data now
                break;
            }
        }
        // Close O RINEX file
        this->data_start=line_number;
        Ofile.close();
    }else{
        // If we can't open the file
        std::cout<<"Can\'t open the file !\n";
    }
}


// -----------------------------------------------------------------------------------
// Fonction qui prend en entrée le numero de l'epoch à retourner et retourne l'epoch
// demandée
// -----------------------------------------------------------------------------------
void Rinex_O::getEpoch(int index){
    unsigned short int counter=0;
    int line_counter=0;
    std::cout<<"\n"<<rinex_file_path<<"\n";
    std::ifstream Ofile (rinex_file_path.c_str());
    if(Ofile.is_open()){
        std::string line;
        std::cout<<"File opened to read data OK";
        // read file line by line
        std::cout<<"\n"<<data_start;
        while(getline (Ofile, line)){
            line_counter++;
            if(line_counter<data_start){
                std::cout<<line_counter<<"\n";
                continue;
            }
            //break;
            // Parse data from here
            if (line.substr(0,1).find(" ")!=std::string::npos && line.substr(3,1).find(" ")!=std::string::npos && line.substr(6,1).find(" ")!=std::string::npos && line.substr(9,1).find(" ")!=std::string::npos && line.substr(2,1).find(" ")==std::string::npos && index == counter){
                    counter++;
                    epoch.year = std::stoi(line.substr(0, 3));
                    epoch.month = std::stoi(line.substr(3, 3));
                    epoch.day = std::stoi(line.substr(6, 3));
                    epoch.hour = std::stoi(line.substr(9, 3));
                    epoch.minute = std::stoi(line.substr(12, 3));
                    epoch.seconde = std::stod(line.substr(15, 11));
                    epoch.satellite_number = std::stoi(line.substr(29, 3));
                    if(line.size()<=68) epoch.receiver_clock_offset=0.0;
                    else epoch.receiver_clock_offset=std::stod(line.substr( 69, 12));
                    //std::cout<<"offset"<<epoch.receiver_clock_offset;
                    observation tmp_obs;
                    if(epoch.satellite_number>12){
                        for ( int i = 0; i<12; i++){
                            tmp_obs.PRN=line.substr(32+i*3, 3);
                            epoch.observations.push_back(tmp_obs);
                        }
                        getline (Ofile, line);
                        for ( int i = 12; i<epoch.satellite_number; i++){
                            tmp_obs.PRN=line.substr(32+(i-12)*3, 3);
                            epoch.observations.push_back(tmp_obs);
                        }
                        for( int i = 0; i<epoch.satellite_number; i++){
                            for (int j = 0 ; j<header.number_of_obs/5; j++){
                                // ICIIII REGARDE ICI JE ME SUIS ARRETÉ HIER
                            }
                        }
                    }
                    else{ // Le nombre de satellites de l'epoch est <= 12 donc l'entete de l'epoch s'etale sur 1 ligne
                        for ( int i = 0; i<12; i++){
                            tmp_obs.PRN=line.substr(32+i*3, 3);
                            epoch.observations.push_back(tmp_obs);

                        }
                    }
                    std::cout<<"\n\n         "<<epoch.observations.at(15).PRN;
                    
            }
        }
        std::cout<<"\nJ'ai trouvé :"<<counter<<" epochs";
        Ofile.close();
    }else{
        std::cout<<"Problem Occured when trying to open file";
    }
}


// -----------------------------------------------------------------------------------
// Fonction principale
// -----------------------------------------------------------------------------------

int main(int argc, char *argv[]){
    Rinex_O r(true, argv[1]);
    r.getEpoch(0);
    std::cout<<"Fonction principale\n";
    return 0;
}
