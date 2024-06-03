#include <iostream>
#include "parse.h"


#include "GPVTG.h"

#define ARRAY_LENGTH(a) (sizeof a / sizeof (a[0]))

void GPVTG::printMe()
{
	printf("GPVTG:\r\n");
	printf("track_deg: %f\r\n", track_deg);
	printf("gndspd_knots: %f\r\n", gndspd_knots);
	printf("gndspd_kmph: %f\r\n", gndspd_kmph);
}


NMEA_Sentence* GPVTG::parse(char* sentence, int length)
{
	type = NMEA_GPVTG;
	NMEA_Sentence::parse(sentence, length);
	return this;
}


int GPVTG::_parse(char* value, int val_index)
{
	switch (val_index) {
	case NMEA_GPVTG_TRACKGOOD:
		track_deg = strtod(value, NULL);
		break;
	case NMEA_GPVTG_GNDSPD_KNOTS:
		gndspd_knots = strtod(value, NULL);
		break;
	case NMEA_GPVTG_GNDSPD_KMPH:
		gndspd_kmph = strtod(value, NULL);
		break;
	default:
		break;
	}


	return 0;
}






