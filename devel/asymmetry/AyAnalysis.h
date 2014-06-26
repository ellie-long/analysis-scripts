// This is a header file that will define
// some functions that are useful for the
// Ay analysis.

// Returns 1 if Beam Half-Wave Plate is IN,
// returns -1 if Beam Half-Wave Plate is OUT.
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
// This needs to be finished. I stopped
// until I can figure out what runs > 3180/22054 
// should be
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
double GetHWP(int runNumber)
{
	double halfwaveplate = 0;
	if (runNumber < 20000)
	{
		if (runNumber < 1778) halfwaveplate = 1;
		if (runNumber > 1777 && runNumber < 1822) halfwaveplate = -1;
		if (runNumber > 1822 && runNumber < 1906) halfwaveplate = 1;
		if (runNumber > 1905 && runNumber < 2272) halfwaveplate = -1;
		if (runNumber > 2271 && runNumber < 2420) halfwaveplate = 1;
		if (runNumber > 2419 && runNumber < 2638) halfwaveplate = -1;
		if (runNumber > 2637 && runNumber < 2823) halfwaveplate = 1;
		if (runNumber > 2822 && runNumber < 2904) halfwaveplate = -1;
		if (runNumber > 2903 && runNumber < 2973) halfwaveplate = 1;
		if (runNumber > 2973 && runNumber < 3004) halfwaveplate = -1;
		if (runNumber > 3003 && runNumber < 3016) halfwaveplate = 1;
		if (runNumber > 3015 && runNumber < 3033) halfwaveplate = -1;
		if (runNumber > 3032 && runNumber < 3181) halfwaveplate = 1;
		if (runNumber > 3181 && runNumber < 3324) halfwaveplate = -1;
		if (runNumber > 3323 && runNumber < 3438) halfwaveplate = 1;
		if (runNumber > 3437 && runNumber < 3453) halfwaveplate = -1;
		if (runNumber > 3452 && runNumber < 3556) halfwaveplate = 1;
		if (runNumber > 3555 && runNumber < 3613) halfwaveplate = -1;
		if (runNumber > 3613) halfwaveplate = 1;

	}
	if (runNumber > 20000)
	{
		if (runNumber < 20682) halfwaveplate = 1;
		if (runNumber > 20683 && runNumber < 20728) halfwaveplate = -1;
		if (runNumber > 20728 && runNumber < 20814) halfwaveplate = 1;
		if (runNumber > 20813 && runNumber < 21179) halfwaveplate = -1;
		if (runNumber > 21178 && runNumber < 21326) halfwaveplate = 1;
		if (runNumber > 21325 && runNumber < 21541) halfwaveplate = -1;
		if (runNumber > 21540 && runNumber < 21724) halfwaveplate = 1;
		if (runNumber > 21723 && runNumber < 21783) halfwaveplate = -1;
		if (runNumber > 21782 && runNumber < 21850) halfwaveplate = 1;
		if (runNumber > 21850 && runNumber < 21882) halfwaveplate = -1;
		if (runNumber > 21881 && runNumber < 21894) halfwaveplate = 1;
		if (runNumber > 21893 && runNumber < 21911) halfwaveplate = -1;
		if (runNumber > 21910 && runNumber < 22053) halfwaveplate = 1;
		if (runNumber > 22053 && runNumber < 22196) halfwaveplate = -1;
		if (runNumber > 22195 && runNumber < 22309) halfwaveplate = 1;
		if (runNumber > 22308 && runNumber < 22324) halfwaveplate = -1;
		if (runNumber > 22323 && runNumber < 22411) halfwaveplate = 1;
		if (runNumber > 22410 && runNumber < 22468) halfwaveplate = -1;
		if (runNumber > 22468) halfwaveplate = 1;

	}
