#include <iostream>
#include "parse.h"


#include "GPGLL.h"


#define ARRAY_LENGTH(a) (sizeof a / sizeof (a[0]))

std::string GPGLL::printMe()
{
	std::string retVal;

	printf("GPGLL:\r\n");
	printTime();
	printLatLon();
    return retVal;
}

NMEA_Sentence* GPGLL::parse(char* sentence, int length)
{
	type = NMEA_GPGLL;
	NMEA_Sentence::parse(sentence, length);
	return this;
}

int GPGLL::_parse(char* value, int val_index)
{
	switch (val_index) {

		case NMEA_GPGLL_TIME:
			/* Parse time */
			if (-1 == nmea_time_parse(value, &time)) {
				return -1;
			}
			break;


		case NMEA_GPGLL_LATITUDE:
			/* Parse latitude */
			if (-1 == nmea_position_parse(value, &latitude)) {
				return -1;
			}
			break;

		case NMEA_GPGLL_LATITUDE_CARDINAL:
			/* Parse cardinal direction */
			latitude.cardinal = nmea_cardinal_direction_parse(value);
			if (NMEA_CARDINAL_DIR_UNKNOWN == latitude.cardinal) {
				return -1;
			}
			break;

		case NMEA_GPGLL_LONGITUDE:
			/* Parse longitude */
			if (-1 == nmea_position_parse(value, &longitude)) {
				return -1;
			}
			break;

		case NMEA_GPGLL_LONGITUDE_CARDINAL:
			/* Parse cardinal direction */
			longitude.cardinal = nmea_cardinal_direction_parse(value);
			if (NMEA_CARDINAL_DIR_UNKNOWN == longitude.cardinal) {
				return -1;
			}
			break;


		default:
			break;
	}

	return 0;
}

