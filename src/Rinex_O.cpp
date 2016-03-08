#include "../include/Rinex_O.h"

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
                    std::cout<<header.observations[i]<<"	"<<i<<"\n";
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
// Fonction pour logger tous les epochs d'un rinex dans un fichier .m
// -----------------------------------------------------------------------------------
void Rinex_O::logEpochs(){
    std::string prn_matrix_format;
    std::string obs_ligne, obs_ligne_start;
    short int counter=0;
    int line_counter=0;
    std::ifstream Ofile (rinex_file_path.c_str());
    if(Ofile.is_open()){
        // read file line by line
        std::string line;
        while(getline (Ofile, line)){
            line_counter++;
            if(line_counter<=data_start){
                continue;
            }
            //break;
            // Parse data from here
            if (line.substr(0,1).find(" ")!=std::string::npos && line.substr(3,1).find(" ")!=std::string::npos && line.substr(6,1).find(" ")!=std::string::npos && line.substr(9,1).find(" ")!=std::string::npos){
                    obs_ligne_start="";
                    counter++;
                    epoch.year = std::stoi(line.substr(0, 3));
                    obs_ligne_start+=line.substr(0, 3)+" ";
                    epoch.month = std::stoi(line.substr(3, 3));
                    obs_ligne_start+=line.substr(3, 3)+" ";
                    epoch.day = std::stoi(line.substr(6, 3));
                    obs_ligne_start+=line.substr(6, 3)+" ";
                    epoch.hour = std::stoi(line.substr(9, 3));
                    obs_ligne_start+=line.substr(9, 3)+" ";
                    epoch.minute = std::stoi(line.substr(12, 3));
                    obs_ligne_start+=line.substr(12, 3)+" ";
                    epoch.seconde = std::stod(line.substr(15, 11));
                    obs_ligne_start+=line.substr(15, 11)+" ";
                    epoch.satellite_number = std::stoi(line.substr(29, 3));
                    if(line.size()<=68) epoch.receiver_clock_offset=0.0;
                    else epoch.receiver_clock_offset=std::stod(line.substr( 69, 12));
                    observation tmp_obs;
                    short int line_length;
                    short int char_counter=0;
                    std::vector <std::string> tmp_PRN;

                    if(epoch.satellite_number>12){
                        for ( int i = 0; i<12; i++){
                            tmp_PRN.push_back(line.substr(32+i*3, 3));
                            tmp_obs.PRN=line.substr(32+i*3, 3);
                        }
                        getline (Ofile, line);
                        for ( int i = 12; i<epoch.satellite_number; i++){
                            tmp_PRN.push_back(line.substr(32+(i-12)*3, 3));
                            tmp_obs.PRN=line.substr(32+(i-12)*3, 3);
                        }
                        for( int i = 0; i<epoch.satellite_number; i++){
                            obs_ligne+="\n";
                            std::cout<<obs_ligne;
                            if(tmp_PRN[i].find("G")!=std::string::npos){
                                prn_matrix_format = std::to_string(std::stoi(tmp_PRN[i].substr(1,2))+100);
                            }else if(tmp_PRN[i].find("R")!=std::string::npos){
                                prn_matrix_format = std::to_string(std::stoi(tmp_PRN[i].substr(1,2))+200);
                            }
                            obs_ligne=obs_ligne_start+" "+prn_matrix_format+" ";
                            for (int j = 0 ; j<ceil(header.number_of_obs/5.0); j++){
                                char_counter=0;
                                getline (Ofile, line);
                                line_length = line.size();
                                char_counter+=14;
                                if (char_counter<=line_length){
                                     setObservation(i ,j*5+0, line.substr(0, 14), tmp_obs, tmp_PRN);
                                     obs_ligne+=line.substr(0, 14)+" ";
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    if(line.substr(14, 1).find(" ")==std::string::npos)
                                        tmp_obs.L1LLI=std::stoi(line.substr(14, 1));
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                     if(line.substr(15, 1).find(" ")==std::string::npos)
                                         tmp_obs.L1SSI=std::stoi(line.substr(15, 1));
                                }else continue;
                                char_counter+=14;
                                if (char_counter<=line_length){
                                    setObservation(i, j*5+1, line.substr(16, 14), tmp_obs, tmp_PRN);
                                    obs_ligne+=line.substr(16, 14)+" ";
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(30, 1);
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(31, 1);
                                }else continue;
                                char_counter+=14;
                                if (char_counter<=line_length){
                                    setObservation(i, j*5+2, line.substr(32, 14), tmp_obs, tmp_PRN);
                                    obs_ligne+=line.substr(32, 14)+" ";
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(46, 1);
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(47, 1);
                                }else continue;
                                char_counter+=14;
                                if (char_counter<=line_length){
                                    setObservation(i, j*5+3, line.substr(48, 14), tmp_obs, tmp_PRN);
                                    obs_ligne+=line.substr(48, 14)+" ";
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(62, 1);
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(63, 1);
                                }else continue;
                                char_counter+=14;
                                if (char_counter<=line_length){
                                    line.substr(64, 14);
                                    setObservation(i, j*5+4, line.substr(64, 14), tmp_obs, tmp_PRN);
                                    obs_ligne+=line.substr(64, 14)+" ";
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(78, 1);
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(79, 1);
                                }else continue;
                            }
                        } //epoch.observations.push_back(tmp_obs);
                    }
                    else{ // Le nombre de satellites de l'epoch est <= 12 donc l'entete de l'epoch s'etale sur 1 ligne
                        for ( int i = 0; i<epoch.satellite_number; i++){
                            tmp_PRN.push_back(line.substr(32+i*3, 3));
                            tmp_obs.PRN=line.substr(32+i*3, 3);
                        }
                        for( int i = 0; i<epoch.satellite_number; i++){
                            obs_ligne+="\n";
                            std::cout<<obs_ligne;
                            if(tmp_PRN[i].find("G")!=std::string::npos){
                                prn_matrix_format = std::to_string(std::stoi(tmp_PRN[i].substr(1,2))+100);
                            }else if(tmp_PRN[i].find("R")!=std::string::npos){
                                prn_matrix_format = std::to_string(std::stoi(tmp_PRN[i].substr(1,2))+200);
                            }
                            obs_ligne=obs_ligne_start+" "+prn_matrix_format+" ";
                           for (int j = 0 ; j<ceil(header.number_of_obs/5.0); j++){
                                char_counter=0;
                                getline (Ofile, line);
                                line_length = line.size();
                                char_counter+=14;
                                if (char_counter<=line_length){
                                     setObservation(i ,j*5+0, line.substr(0, 14), tmp_obs, tmp_PRN);
                                     obs_ligne+=line.substr(0, 14)+" ";
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length) line.substr(15, 1); else continue;
                                char_counter+=14;
                                if (char_counter<=line_length){
                                    setObservation(i, j*5+1, line.substr(16, 14), tmp_obs, tmp_PRN);
                                    obs_ligne+=line.substr(16, 14)+" ";
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(30, 1);
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(31, 1);
                                }else continue;
                                char_counter+=14;
                                if (char_counter<=line_length){
                                    setObservation(i, j*5+2, line.substr(32, 14), tmp_obs, tmp_PRN);
                                    obs_ligne+=line.substr(32, 14)+" ";
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(46, 1);
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(47, 1);
                                }else continue;
                                char_counter+=14;
                                if (char_counter<=line_length){
                                    setObservation(i, j*5+3, line.substr(48, 14), tmp_obs, tmp_PRN);
                                    obs_ligne+=line.substr(48, 14)+" ";
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(62, 1);
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(63, 1);
                                }else continue;
                                char_counter+=14;
                                if (char_counter<=line_length){
                                    line.substr(64, 14);
                                    setObservation(i, j*5+4, line.substr(64, 14), tmp_obs, tmp_PRN);
                                    obs_ligne+=line.substr(64, 14)+" ";
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(78, 1);
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(79, 1);
                                }else continue;
                            }
                        }
                    }
                //break;
                // LOGGER LA LIGNE DES OBS
            }
        }
        Ofile.close();
    }else{
        std::cout<<"Problem Occured when trying to open file";
    }

}
// -----------------------------------------------------------------------------------
// Fonction qui prend en entrée le numero de l'epoch à retourner et retourne l'epoch
// demandée
// -----------------------------------------------------------------------------------
void Rinex_O::getEpoch(int index){
    short int counter=0;
    int line_counter=0;
    std::cout<<"\n"<<rinex_file_path<<"\n";
    std::ifstream Ofile (rinex_file_path.c_str());
    if(Ofile.is_open()){
        // read file line by line
        std::string line;
        std::cout<<"\n"<<data_start;
        while(getline (Ofile, line)){
            std::cout<<"\nLIGNE:"<<line<<"\n";
            line_counter++;
            if(line_counter<=data_start){
                std::cout<<line_counter<<"\n";
                continue;
            }
            //break;
            if (line.substr(0,1).find(" ")!=std::string::npos && line.substr(3,1).find(" ")!=std::string::npos && line.substr(6,1).find(" ")!=std::string::npos && line.substr(9,1).find(" ")!=std::string::npos && index != counter){
                std::cout<<"\nLIGNE:"<<line<<"\n";
                getline (Ofile, line);
                std::cout<<"\nLIGNE:"<<line<<"\n";
                counter++;
                continue;
            }
            // Parse data from here
            if (line.substr(0,1).find(" ")!=std::string::npos && line.substr(3,1).find(" ")!=std::string::npos && line.substr(6,1).find(" ")!=std::string::npos && line.substr(9,1).find(" ")!=std::string::npos && index == counter ){
                    counter++;
                    std::cout<<"ENTRER";
                    std::cout<<"\nLINE        :"<<line.size()<<"\n";
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
                    short int line_length;
                    short int char_counter=0;
                    std::vector <std::string> tmp_PRN;

                    if(epoch.satellite_number>12){
                        for ( int i = 0; i<12; i++){
                            tmp_PRN.push_back(line.substr(32+i*3, 3));
                            std::cout<<tmp_PRN.at(i);
                            tmp_obs.PRN=line.substr(32+i*3, 3);
                        }

                        getline (Ofile, line);

                        for ( int i = 12; i<epoch.satellite_number; i++){
                            tmp_PRN.push_back(line.substr(32+(i-12)*3, 3));
                            std::cout<<tmp_PRN.at(i);
                            tmp_obs.PRN=line.substr(32+(i-12)*3, 3);
                        }
                        for( int i = 0; i<epoch.satellite_number; i++){
                           for (int j = 0 ; j<ceil(header.number_of_obs/5.0); j++){
                                char_counter=0;
                                getline (Ofile, line);
                                std::cout<<"\n"<<line<<"\n";
                                line_length = line.size();
                                char_counter+=14;
                                if (char_counter<=line_length){
                                     setObservation(i ,j*5+0, line.substr(0, 14), tmp_obs, tmp_PRN);
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    if(line.substr(14, 1).find(" ")==std::string::npos)
                                        tmp_obs.L1LLI=std::stoi(line.substr(14, 1));
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                     if(line.substr(15, 1).find(" ")==std::string::npos)
                                         tmp_obs.L1SSI=std::stoi(line.substr(15, 1));
                                }else continue;
                                char_counter+=14;
                                if (char_counter<=line_length){
                                    setObservation(i, j*5+1, line.substr(16, 14), tmp_obs, tmp_PRN);
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(30, 1);
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(31, 1);
                                }else continue;
                                char_counter+=14;
                                if (char_counter<=line_length){
                                    setObservation(i, j*5+2, line.substr(32, 14), tmp_obs, tmp_PRN);
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(46, 1);
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(47, 1);
                                }else continue;
                                char_counter+=14;
                                if (char_counter<=line_length){
                                    setObservation(i, j*5+3, line.substr(48, 14), tmp_obs, tmp_PRN);
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(62, 1);
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(63, 1);
                                }else continue;
                                char_counter+=14;
                                if (char_counter<=line_length){
                                    line.substr(64, 14);
                                    setObservation(i, j*5+4, line.substr(64, 14), tmp_obs, tmp_PRN);
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(78, 1);
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(79, 1);
                                }else continue;
                            }

                            std::cout<<"\n\nNOMBRE DE STATELLITES PARC:"<<i<<"\n\n";

                        } //epoch.observations.push_back(tmp_obs);
                    }
                    else{ // Le nombre de satellites de l'epoch est <= 12 donc l'entete de l'epoch s'etale sur 1 ligne
                        for ( int i = 0; i<epoch.satellite_number; i++){
                            tmp_PRN.push_back(line.substr(32+i*3, 3));
                            std::cout<<tmp_PRN.at(i);
                            tmp_obs.PRN=line.substr(32+i*3, 3);
                        }
                        for( int i = 0; i<epoch.satellite_number; i++){
                           for (int j = 0 ; j<ceil(header.number_of_obs/5.0); j++){
                                char_counter=0;
                                getline (Ofile, line);
                                std::cout<<"\n"<<line<<"\n";
                                line_length = line.size();
                                char_counter+=14;
                                if (char_counter<=line_length){
                                     setObservation(i ,j*5+0, line.substr(0, 14), tmp_obs, tmp_PRN);
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length) line.substr(15, 1); else continue;
                                char_counter+=14;
                                if (char_counter<=line_length){
                                    setObservation(i, j*5+1, line.substr(16, 14), tmp_obs, tmp_PRN);
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(30, 1);
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(31, 1);
                                }else continue;
                                char_counter+=14;
                                if (char_counter<=line_length){
                                    setObservation(i, j*5+2, line.substr(32, 14), tmp_obs, tmp_PRN);
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(46, 1);
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(47, 1);
                                }else continue;
                                char_counter+=14;
                                if (char_counter<=line_length){
                                    setObservation(i, j*5+3, line.substr(48, 14), tmp_obs, tmp_PRN);
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(62, 1);
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(63, 1);
                                }else continue;
                                char_counter+=14;
                                if (char_counter<=line_length){
                                    line.substr(64, 14);
                                    setObservation(i, j*5+4, line.substr(64, 14), tmp_obs, tmp_PRN);
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(78, 1);
                                }else continue;
                                char_counter+=1;
                                if (char_counter<=line_length){
                                    line.substr(79, 1);
                                }else continue;
                            }
                        }
                    }
                break;
            }
        }
        std::cout<<"\nJ'ai trouvé :"<<counter<<" epochs";
        Ofile.close();
    }else{
        std::cout<<"Problem Occured when trying to open file";
    }
}


// -----------------------------------------------------------------------------------
// Fonction qui permet de remplir la structure observation à partir des substr
// découpés depuis le fichier RINEX. Elle prend en entrée l'odre de l'observable
// et la valeur de la substr
// -----------------------------------------------------------------------------------
void Rinex_O::setObservation(int s_index, int m_index, std::string obs, observation &obser, std::vector <std::string> tmp_PRN){
    obser.PRN = tmp_PRN.at(s_index);
    if(header.observations[m_index].find("L1") != std::string::npos && obs.find("              ")==std::string::npos){
        obser.L1 = std::stod(obs);
    }
    else if(header.observations[m_index].find("L2") != std::string::npos && obs.find("              ")==std::string::npos){
        obser.L2 = std::stod(obs);
    }
    else if(header.observations[m_index].find("P1") != std::string::npos && obs.find("              ")==std::string::npos){
        obser.P1 = std::stod(obs);
    }
    else if(header.observations[m_index].find("P2") != std::string::npos && obs.find("              ")==std::string::npos){
        obser.P2 = std::stod(obs);
    }
    else if(header.observations[m_index].find("C1") != std::string::npos && obs.find("              ")==std::string::npos){
        obser.C1 = std::stod(obs);
    }
    else if(header.observations[m_index].find("C2") != std::string::npos && obs.find("              ")==std::string::npos){
        obser.C2 = std::stod(obs);
    }
    else if(header.observations[m_index].find("D1") != std::string::npos && obs.find("              ")==std::string::npos){
        obser.D1 = std::stod(obs);
    }
    else if(header.observations[m_index].find("D2") != std::string::npos && obs.find("              ")==std::string::npos){
        obser.D2 = std::stod(obs);
    }
    else if(header.observations[m_index].find("S1") != std::string::npos && obs.find("              ")==std::string::npos){
        obser.S1 = std::stod(obs);
    }
    else if(header.observations[m_index].find("S2") != std::string::npos && obs.find("              ")==std::string::npos){
        obser.S2 = std::stod(obs);
    }
}

// -----------------------------------------------------------------------------------
// Fonction qui permet de parser les LLI et les SSI
// -----------------------------------------------------------------------------------
//void Rinex_O::setSmallObservation(int s_index, int m_index, std::string obs, observation &obser, std::vector <std::string> tmp_PRN)

// -----------------------------------------------------------------------------------
// Fonction principale
// -----------------------------------------------------------------------------------

int main(int argc, char *argv[]){
    Rinex_O r(true, argv[1]);
    r.logEpochs();
    std::cout<<"Fonction principale\n";
    return 0;
}
