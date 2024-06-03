#pragma once


#include "time.h"

#include "NMEA_Sentence.h"


class GPVTG:NMEA_Sentence
{
	/* Value indexes */
#define NMEA_GPVTG_TRACKGOOD 0
#define NMEA_GPVTG_GNDSPD_KNOTS 4
#define NMEA_GPVTG_GNDSPD_KMPH 6

	double track_deg;
	double gndspd_knots;
	double gndspd_kmph;



public:

	virtual NMEA_Sentence* parse(char* sentence, int length);
	virtual int _parse(char* value, int val_index);
	virtual std::string printMe();



};

