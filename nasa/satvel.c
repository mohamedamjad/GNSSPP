#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define bPI                 3.1415926535898
#define bGM84               3.986005e14
#define bOMEGAE84           7.2921151467e-5

/* Sample Broadcast Message in unit of radians, seconds, meters.
20 01  7 23  2  0  0.0 -.857324339449D-04 -.272848410532D-11  .000000000000D+00
     .200000000000D+02  .886875000000D+02  .465376527657D-08  .105827953357D+01
     .457651913166D-05  .223578442819D-02  .177137553692D-05  .515379589081D+04
     .936000000000D+05  .651925802231D-07  .164046615454D+01 -.856816768646D-07
     .961685061380D+00  .344968750000D+03  .206374037770D+01 -.856928551657D-08
     .342514267094D-09  .000000000000D+00  .112400000000D+04  .000000000000D+00
     .200000000000D+01  .000000000000D+00 -.651925802231D-08  .276000000000D+03
     .865800000000D+05  .000000000000D+00  .000000000000D+00  .000000000000D+00
*/

//Program written for instructional purposes only.  In practice this would be a generalized function.
//This approach was adopted for clarity and for non-programmers.  Benjamin W. Remondi, February 2004
//Dr. Benjamin W. Remondi is the President & CEO of The XYZs of GPS, Inc.
//It is essential that the reader have the ICD-200 available.

void main(void)
{
long double roota                    =  5153.79589081;
long double toe                      =  93600.0;
long double m0                       =  1.05827953357;
long double e                        =  0.00223578442819;
long double delta_n                  =  0.465376527657e-08;
long double smallomega               =  2.06374037770;
long double cus                      =  0.177137553692e-05; 
long double cuc                      =  0.457651913166e-05; 
long double crs                      =  88.6875000000; 
long double crc                      =  344.968750000; 
long double cis                      = -0.856816768646e-07;
long double cic                      =  0.651925802231e-07; 
long double idot                     =  0.342514267094e-09; 
long double i0                       =  0.961685061380; 
long double bigomega0                =  1.64046615454; 
long double earthrate                =  bOMEGAE84;
long double bigomegadot              = -0.856928551657e-08; 
long double t                        =  86400.00;
long double A;
long double n0, n;
long double tk;
long double mk, ek, vk, tak, ik, omegak, phik, uk, rk;
long double corr_u, corr_r, corr_i;
long double xpk, ypk;
long double xk, yk, zk;
long double mkdot, ekdot, takdot, ukdot, ikdot, rkdot, omegakdot;
long double xpkdot, ypkdot;
long double xkdot, ykdot, zkdot;
long iter;

A = roota*roota;           //roota is the square root of A
n0 = sqrt(bGM84/(A*A*A));  //bGM84 is what the ICD-200 calls Greek mu
tk = t - toe;              //t is the time of the pos. & vel. request.
n = n0 + delta_n;
mk = m0 + n*tk;
mkdot = n;
ek = mk;
for(iter=0; iter<7; iter++) ek = mk + e*sin(ek);  //Overkill for small e
ekdot = mkdot/(1.0 - e*cos(ek));
//In the line, below, tak is the true anomaly (which is nu in the ICD-200).
tak = atan2( sqrt(1.0-e*e)*sin(ek), cos(ek)-e);
takdot = sin(ek)*ekdot*(1.0+e*cos(tak))/(sin(tak)*(1.0-e*cos(ek)));

phik = tak + smallomega;
corr_u = cus*sin(2.0*phik) + cuc*cos(2.0*phik);
corr_r = crs*sin(2.0*phik) + crc*cos(2.0*phik);
corr_i = cis*sin(2.0*phik) + cic*cos(2.0*phik);
uk = phik + corr_u;
rk = A*(1.0-e*cos(ek)) + corr_r;
ik = i0 + idot*tk + corr_i;

ukdot = takdot +2.0*(cus*cos(2.0*uk)-cuc*sin(2.0*uk))*takdot;
rkdot = A*e*sin(ek)*n/(1.0-e*cos(ek)) + 2.0*(crs*cos(2.0*uk)-crc*sin(2.0*uk))*takdot;
ikdot = idot + (cis*cos(2.0*uk)-cic*sin(2.0*uk))*2.0*takdot;

xpk = rk*cos(uk);
ypk = rk*sin(uk);

xpkdot = rkdot*cos(uk) - ypk*ukdot;
ypkdot = rkdot*sin(uk) + xpk*ukdot;

omegak = bigomega0 + (bigomegadot-earthrate)*tk - earthrate*toe;

omegakdot = (bigomegadot-earthrate);

xk = xpk*cos(omegak) - ypk*sin(omegak)*cos(ik);
yk = xpk*sin(omegak) + ypk*cos(omegak)*cos(ik);
zk =                   ypk*sin(ik);

xkdot = ( xpkdot-ypk*cos(ik)*omegakdot )*cos(omegak)
        - ( xpk*omegakdot+ypkdot*cos(ik)-ypk*sin(ik)*ikdot )*sin(omegak);
ykdot = ( xpkdot-ypk*cos(ik)*omegakdot )*sin(omegak)
        + ( xpk*omegakdot+ypkdot*cos(ik)-ypk*sin(ik)*ikdot )*cos(omegak);
zkdot = ypkdot*sin(ik) + ypk*cos(ik)*ikdot;

//Results follow.

printf("BCpos: t, xk, yk, zk: %9.3Lf %21.11Lf %21.11Lf %21.11Lf\n", t, xk, yk, zk );
//BCpos: t, xk, yk, zk: 86400.000 -12611434.19782218519 -13413103.97797041226  19062913.07357876760
printf("BCvel: t, Vxk, Vyk, Vzk: %9.3Lf %16.10Lf %16.10Lf %16.10Lf\n", t, xkdot, ykdot, zkdot );
//BCvel: t, Vxk, Vyk, Vzk: 86400.000   266.2803795674 -2424.7683468482 -1529.7620784616

//Use the positions at 86400.000+0.005 and 86400.000-0.005 for numerical computation check.
//Perfect agreement is precluded because we have a limited precision machine.
printf("xdotnumerical.01: %20.12lf\n", (-12611432.86642217014 - (-12611435.52922596496) )/0.01 );
//xdotnumerical.01:     266.280379332602
printf("ydotnumerical.01: %20.12lf\n", (-13413116.10180993562 - (-13413091.85412646334) )/0.01 );
//ydotnumerical.01:   -2424.768347293139
printf("zdotnumerical.01: %20.12lf\n", ( 19062905.42476327563 - ( 19062920.72238405509) )/0.01 );
//zdotnumerical.01:   -1529.762077704072

}


