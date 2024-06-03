#pragma once

#include <ctime>


struct SatVehicle
{

	struct tm TimeOfLastRx;
	int prn; //Satellite PRN number
	int elevation; //Elevation, degrees
	int azimuth; //Azimuth, degrees
	int snr; //SNR - higher is better

	int msgCount=0;

public:
	SatVehicle(int _prn, int _elevation, int _azimuth, int _snr)
	{
		prn = _prn;
		elevation = _elevation;
		azimuth = _azimuth;
		snr = _snr;
	}





};

