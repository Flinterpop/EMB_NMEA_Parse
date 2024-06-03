#pragma once

#include "time.h"

#include "NMEA_Sentence.h"

class GPGLL:NMEA_Sentence
{

	/* Value indexes */
	#define NMEA_GPGLL_LATITUDE		0
	#define NMEA_GPGLL_LATITUDE_CARDINAL	1
	#define NMEA_GPGLL_LONGITUDE		2
	#define NMEA_GPGLL_LONGITUDE_CARDINAL	3
	#define NMEA_GPGLL_TIME	4  //verify this should be 4	

public:

	virtual NMEA_Sentence* parse(char* sentence, int length);
	virtual int _parse(char* value, int val_index);
	virtual std::string printMe();


};

