#pragma once


#include "time.h"

#include "NMEA_Sentence.h"


class GPGGA:NMEA_Sentence
{
	/* Value indexes */
	#define NMEA_GPGGA_TIME			0
	#define NMEA_GPGGA_LATITUDE		1
	#define NMEA_GPGGA_LATITUDE_CARDINAL	2
	#define NMEA_GPGGA_LONGITUDE		3
	#define NMEA_GPGGA_LONGITUDE_CARDINAL	4
	#define NMEA_GPGGA_POSITION_FIX		5
	#define NMEA_GPGGA_N_SATELLITES		6
	#define NMEA_GPGGA_HDOP		7
	#define NMEA_GPGGA_ALTITUDE		8
	#define NMEA_GPGGA_ALTITUDE_UNIT	9
	#define NMEA_GPGGA_UNDULATION		10
	#define NMEA_GPGGA_UNDULATION_UNIT	11

	#define INVALID_UNDULATION -9999.999

	int Count = 0;


public: 

	virtual NMEA_Sentence* parse(char* sentence, int length);
	virtual int _parse(char* value, int val_index);
	virtual std::string printMe();

	//struct tm time;
	//nmea_position longitude;
	//nmea_position latitude;
	int n_satellites;
	double hdop;
	double altitude;
	char altitude_unit;
	double undulation = INVALID_UNDULATION;
	char undulation_unit;
	unsigned char position_fix;

	


};

