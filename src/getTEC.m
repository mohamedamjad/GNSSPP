%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                   FONCTIONS POUR TRAITER LES EPHEMERIDES                    %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%23  16   1   4   0   0   0.0 1451865600 -1.531341113150e-04 -1.932676241267e-12  0.000000000000e+00  3.100000000000e+01  6.543750000000e+01  4.797342685722e-09 -2.279089703154e+00  3.110617399216e-06  1.039854902774e-02  8.732080459595e-06  5.153750686646e+03  8.640000000000e+04  6.891787052155e-08  2.436764677075e+00 -1.192092895508e-07  9.468818869627e-01  2.054375000000e+02 -2.617797048703e+00 -8.016048186297e-09  1.332198348551e-10  1.000000000000e+00  1.878000000000e+03  0.000000000000e+00  2.000000000000e+00  0.000000000000e+00 -2.002343535423e-08  3.100000000000e+01  7.921800000000e+04


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% fonction qui prend en entée la matrice issue du fichier de navigation et    %
% renvoie la vitesse à l'instant t du satellite prn                           %
%http://fenrir.naruoka.org/download/autopilot/note/080205_gps/gps_velocity.pdf%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [xk,yk,zk,xkdot, ykdot, zkdot] = getSatelliteVelocity(year, month, day, hour, minute, sec, t, prn, M)
  CONST_earth_rotatio_rate = 7.2921151467e-5;
  CONST_mu = 3.986005e14

  for i = 1:size(M)(1)
    if (M(i,1)==prn && M(i,2)==year && M(i,3)==month && M(i,4)==day && M(i,5)==hour)
      earth_rate = 7.2921151467e-5
      OMEGA = M(i, 22)
      OMEGAdot = M(i, 27)
      i0 = M(i,24)
      idot = M(i,28)
      crs = M(i,13)
      cus = M(i,18)
      cic = M(i,21)
      cis = M(i,23)
      crc = M(i,25)
      cuc = M(i, 16)
      e = M(i,17)
      toe = M(i,20)
      omega = M(i,26)
      A = M(i,19)*M(i,19)
      n0 = sqrt(CONST_mu/(A*A*A))
      tk = t-toe
      n = n0 + M(i,14)
      Mk = M(i,15)+n*tk
      Ek = Mk
      Mkdot = n;
      for j = 1:7
        Ek = Mk +e*sin(Ek);
      endfor
      Ek
      Ekdot = Mkdot/(1.0-e*cos(Ek))
      vk = atan2(sqrt(1.0-e*e)*sin(Ek),cos(Ek)-e);
      vkdot = sin(Ek)*Ekdot*(1.0+e*cos(vk))/(sin(vk)*(1.0-e*cos(Ek)));
      phik = vk + omega;
      phikdot = vkdot;

      corr_u = cus*sin(2.0*phik) + cuc*cos(2.0*phik);
      corr_r = crs*sin(2.0*phik) + crc*cos(2.0*phik);
      corr_i = cis*sin(2.0*phik) + cic*cos(2.0*phik);
      uk = phik + corr_u;
      rk = A*(1.0-e*cos(Ek)) + corr_r;
      ik = i0 + idot*tk + corr_i;

      ukdot = vkdot +2.0*(cus*cos(2.0*uk)-cuc*sin(2.0*uk))*vkdot;
      rkdot = A*e*sin(Ek)*n/(1.0-e*cos(Ek)) + 2.0*(crs*cos(2.0*uk)-crc*sin(2.0*uk))*vkdot;
      ikdot = idot + (cis*cos(2.0*uk)-cic*sin(2.0*uk))*2.0*vkdot;

      xpk = rk*cos(uk);
      ypk = rk*sin(uk);

      xpkdot = rkdot*cos(uk) - ypk*ukdot;
      ypkdot = rkdot*sin(uk) + xpk*ukdot;
   
      omegak = OMEGA + (OMEGAdot - earth_rate)*tk - earth_rate*toe;

      omegakdot = (OMEGAdot - earth_rate);

      xk = xpk*cos(omegak) - ypk*sin(omegak)*cos(ik);
      yk = xpk*sin(omegak) + ypk*cos(omegak)*cos(ik);
      zk =                   ypk*sin(ik);

      xkdot = ( xpkdot-ypk*cos(ik)*omegakdot )*cos(omegak) - ( xpk*omegakdot+ypkdot*cos(ik)-ypk*sin(ik)*ikdot )*sin(omegak);
      ykdot = ( xpkdot-ypk*cos(ik)*omegakdot )*sin(omegak) + ( xpk*omegakdot+ypkdot*cos(ik)-ypk*sin(ik)*ikdot )*cos(omegak);
      zkdot = ypkdot*sin(ik) + ypk*cos(ik)*ikdot;

      

    endif

  endfor

endfunction

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%      FONCTIONS POUR TRAITER LES DONNÉES DES FICHIERS D'OBSERVATIONS        %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% fonction qui prend en input le prn et la matrice issue du traitement RINEX
% et donne le VTEC en fonction du temps UNIX
function [unix_time,TECvect] = getVTEC (prn, M)
  TECvect=[];
  unix_time=[];
  for i = 1:size(M)(1)
    if (M(i,8)==prn)
      TECvect(end+1) = -9.52*10^16*(M(i,12)-M(i,13));
      unix_time(end+1) = M(i,7);
    endif
  endfor
endfunction

% fonction qui prend en input le prn et la matrice issue du traitement RINEX
% et donne le STEC en fonction du temps UNIX
function [unix_time,TECvect] = getSTEC (prn, M)
  TECvect=[];
  unix_time=[];
  for i = 1:size(M)(1)
    if (M(i,8)==prn)
      TECvect(end+1) = -9.52*10^16*(M(i,12)-M(i,13));
      unix_time(end+1) = M(i,7);
    endif
  endfor
endfunction

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% FONCTIONS POUR LA CONVERSION ENTRE DIFFERENTS SYSTÈMES DE TEMPS             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Fonction qui prend en entrée le unixtim UTC et les leap secondes et retourne
% le GPSweek et le TOE (TIme Of Ephemeris)
function [GPS_week,TOE] = unixToGPSTime(Unixtime, leap_seconds)
  tmp = Unixtime - 315964800; % On soustrait le nombre de sec entre1/1/1970 et 6/1/1980
  GPS_week = (tmp-mod(tmp, 604800))/604800
  TOE = tmp - GPS_week*604800 + leap_seconds
endfunction
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Fonction pour ajouter deux columns (GPS_week et TOE) dans la matrice        %
% d'observations                                                              %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function gpstime = GPSTimeColumn(M, leap_seconds)
  for i = 1:size(M)(1)
    [GPS_week,TOE] = unixToGPSTime(M(i,7), leap_seconds);
    gpstime(end+1,1) = GPS_week;
    gpstime(end,2) = TOE;
  endfor
endfunction

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Fonction pour construire la grande matrice d'observations                   %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function navmatrix = buildNavMatrix(M, N)
  for i = 1:size(M)(1)
    for j = 1:size(N)(1)
      navmatrix(i,1) = M(e)
    endfor
  endfor
endfunction


