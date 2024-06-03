
#include <iostream>

#include "parse.h"

#include "GPGGA.h"


const char* posfixText[] = { "Fix Not available or invalid","GPS SPS Mode, fix valid","Differntial GPS, SPS Mode, fix valid","3","4","5","Dead Reckoning Mode, fix valid" };




#define ARRAY_LENGTH(a) (sizeof a / sizeof (a[0]))

std::string GPGGA::printMe()
{
	std::string retVal;

	printf("GPGGA: \r\n");
	printTime();
	printLatLon();
	printf("n_satellites: %d\r\n", n_satellites);
	printf("horizontal DOP: %f\r\n", hdop);
	printf("altitude [m msl]: %8.3f\r\n", altitude);
	printf("undulation [m]: %2.4f\r\n", undulation);
	printf("Pos Fix : %d %s\r\n", position_fix, posfixText[position_fix]);
    return retVal;
}



NMEA_Sentence* GPGGA::parse(char* sentence, int length)
{
	type = NMEA_GPGGA;
	NMEA_Sentence::parse(sentence, length);
	return this;
}



int GPGGA::_parse(char* value, int val_index)
{
	switch (val_index) {
	case NMEA_GPGGA_TIME:
		/* Parse time */
		if (-1 == nmea_time_parse(value, &time)) {
			return -1;
		}
		break;

	case NMEA_GPGGA_LATITUDE:
		/* Parse latitude */
		if (-1 == nmea_position_parse(value, &latitude)) {
			return -1;
		}
		break;

	case NMEA_GPGGA_LATITUDE_CARDINAL:
		/* Parse cardinal direction */
		latitude.cardinal = nmea_cardinal_direction_parse(value);
		if (NMEA_CARDINAL_DIR_UNKNOWN == latitude.cardinal) {
			return -1;
		}
		break;

	case NMEA_GPGGA_LONGITUDE:
		/* Parse longitude */
		if (-1 == nmea_position_parse(value, &longitude)) {
			return -1;
		}
		break;

	case NMEA_GPGGA_LONGITUDE_CARDINAL:
		/* Parse cardinal direction */
		longitude.cardinal = nmea_cardinal_direction_parse(value);
		if (NMEA_CARDINAL_DIR_UNKNOWN == longitude.cardinal) {
			return -1;
		}
		break;

	case NMEA_GPGGA_POSITION_FIX:
		/* Parse position fix indicator */
		position_fix = atoi(value);
		break;

	case NMEA_GPGGA_N_SATELLITES:
		/* Parse number of satellies */
		n_satellites = atoi(value);
		break;
	case NMEA_GPGGA_HDOP:
		/* Parse Horizontal Dilution of Precison */
		hdop = atof(value);
		break;
	case NMEA_GPGGA_ALTITUDE:
		/* Parse altitude */
		altitude = atof(value);
		break;

	case NMEA_GPGGA_ALTITUDE_UNIT:
		/* Parse altitude unit */
		altitude_unit = *value;
		break;

	case NMEA_GPGGA_UNDULATION:
		/* Parse undulation */
		undulation = atof(value);
		break;

	case NMEA_GPGGA_UNDULATION_UNIT:
		/* Parse undulation unit */
		undulation_unit = *value;
		break;

	default:
		break;
	}

	return 0;
}

