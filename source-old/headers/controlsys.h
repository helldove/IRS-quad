#include <stdio.h>
#include "base.h"


#define RollKp 19.31
#define RollKi 0.0
#define RollKd 8.0

#define PitchKp 19.31
#define PitchKi 0.0
#define PitchKd 8.0

#define M1Kp 1.0
#define M1Ki 0.0
#define M1Kd 0.0

#define M2Kp 1.0
#define M2Ki 0.0
#define M2Kd 0.0

#define M3Kp 1.0
#define M3Ki 0.0
#define M3Kd 0.0

#define M4Kp 1.0
#define M4Ki 0.0
#define M4Kd 0.0

#define Dt 0.005
#define InvDt 200

extern double RollPrevErr;
extern double RollDevSum ;

extern double PitchPrevErr;
extern double PitchDevSum;

extern double PIDcontroller(double TarVal, double NowVal, double * ValPrevErr, double * ValDevSum, double Kp, double Ki, double Kd);
extern double RollControl(double TarTheta, double NowTheta, double * RollPE, double * RollDS);
extern double PitchControl(double TarPhi, double NowPhi, double * PitchPE, double * PitchDS);