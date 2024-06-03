#pragma once


#include "time.h"

#include "NMEA_Sentence.h"


class GPTXT:NMEA_Sentence
{
	/* Value indexes */
	#define NMEA_GPTXT_ID00 0
	#define NMEA_GPTXT_ID01 1
	#define NMEA_GPTXT_ID02 2
	#define NMEA_GPTXT_TEXT 3
	/* Text field length */
	#define NMEA_GPTXT_TEXT_SIZE 64

	int id_00;
	int id_01;
	int id_02;
	char text[NMEA_GPTXT_TEXT_SIZE];


public:

	virtual NMEA_Sentence* parse(char* sentence, int length);
	virtual int _parse(char* value, int val_index);
	virtual std::string printMe();


};

