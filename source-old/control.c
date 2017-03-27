#include "headers/controlsys.h"

double RollPrevErr = 0.0;
double RollDevSum = 0.0;

double PitchPrevErr = 0.0;
double PitchDevSum = 0.0;

double PIDcontroller(double TarVal, double NowVal, double * ValPrevErr, double * ValDevSum, double Kp, double Ki, double Kd){
	double ValCurrErr = 0.0;
	double ValPCtrl = 0.0;
	double ValICtrl = 0.0;
	double ValDCtrl = 0.0;
	double ResultVal = 0.0;

	ValCurrErr = TarVal - NowVal;
	
	ValPCtrl = Kp * ValCurrErr;
	*ValDevSum += ValCurrErr* Dt;
	ValICtrl = Ki * *ValDevSum;
	ValDCtrl = Kd * ((ValCurrErr - *ValPrevErr) * InvDt);
	
	ResultVal = (ValPCtrl + ValICtrl + ValDCtrl);
	
	*ValPrevErr = ValCurrErr;
		
	#ifdef DEBUG
		printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
		printf("\\\\Target Value : %d\tNow Value : %d\n",TarVal,NowVal);
		printf("\\\\Value Current Error : %f\n",ValCurrErr);
		printf("\\\\Result of control : %f\n\n",ResultVal);
		printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
	#endif
	
	return ResultVal;
}

double RollControl(double TarTheta, double NowTheta, double * RollPE, double * RollDS){
	static double result = 0.0;
	#ifdef DEBUG
		printf("\\\\\\\\\\\\\\\\\\\\-Roll control-\\\\\\\\\\\\\\\\\\\n");
	#endif
	result = PIDcontroller(TarTheta, NowTheta, RollPE, RollDS, RollKp, RollKi, RollKd);
	return result;
}

double PitchControl(double TarPhi, double NowPhi, double * PitchPE, double * PitchDS){
	static double result = 0.0;
	#ifdef DEBUG
		printf("\\\\\\\\\\\\\\\\\\\\-Pitch control-\\\\\\\\\\\\\\\\\\\n");
	#endif
	result = PIDcontroller(TarPhi, NowPhi, PitchPE, PitchDS, PitchKp, PitchKi, PitchKd);
	return result;
}

double MotorControl(double TarPWM, double NowPWM, double * PWMPE, double * PWMDS, int MotorNum){
	static double result = 0.0;
	switch(MotorNum){
		case 1:
			result = PIDcontroller(TarPWM, NowPWM, PWMPE, PWMDS, M1Kp, M1Ki, M1Kd);
			break;
		case 2:
			result = PIDcontroller(TarPWM, NowPWM, PWMPE, PWMDS, M2Kp, M2Ki, M2Kd);
			break;
		case 3:
			result = PIDcontroller(TarPWM, NowPWM, PWMPE, PWMDS, M3Kp, M3Ki, M3Kd);
			break;
		case 4:
			result = PIDcontroller(TarPWM, NowPWM, PWMPE, PWMDS, M4Kp, M4Ki, M4Kd);
			break;
	}
	return result;
	
}
