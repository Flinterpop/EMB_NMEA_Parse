#include <iostream>
#include "parse.h"

#include "GPRMC.h"



#define ARRAY_LENGTH(a) (sizeof a / sizeof (a[0]))

void GPRMC::printMe()
{
	printf("GPRMC:\r\n");
	printDate();
	printTime();
	printLatLon();
	printf("gndspd_knots: %f\r\n", gndspd_knots);
	printf("track_deg: %f\r\n", track_deg);
	printf("magvar_deg: %f\r\n", magvar_deg);

	printf("magvar_cardinal: %c\r\n", magvar_cardinal);
	//The direction of the magnetic variation determines whether or not it
	//is additive - Easterly means subtract magvar_deg from track_deg and
	//westerly means add magvar_deg to track_deg for the correct course.

	printf("Mode: %c: ", mode);
	if (mode == 'A') printf("Autonomous\r\n");
	else if (mode == 'D') printf("DGPS\r\n");
	else if (mode == 'E') printf("DR\r\n");
	else printf("??\r\n");

}


NMEA_Sentence* GPRMC::parse(char* sentence, int length)
{
	type = NMEA_GPRMC;
	NMEA_Sentence::parse(sentence, length);
	return this;
}


int GPRMC::_parse(char* value, int val_index)
{
	switch (val_index) {
		case NMEA_GPRMC_TIME:
			/* Parse time */
			if (-1 == nmea_time_parse(value, &time)) {
				return -1;
			}
			break;

		case NMEA_GPRMC_DATE:
			/* Parse date */
			if (-1 == nmea_date_parse(value, &time)) {
				return -1;
			}
			break;

		case NMEA_GPRMC_STATUS:
			/* Parse status */
			if (*value == 'A') {
				valid = true;
			}
			else if (*value == 'V') {
				valid = false;
			}
			else {
				return -1;
			}
			break;

		case NMEA_GPRMC_LATITUDE:
			/* Parse latitude */
			if (-1 == nmea_position_parse(value, &latitude)) {
				return -1;
			}
			break;

		case NMEA_GPRMC_LATITUDE_CARDINAL:
			/* Parse cardinal direction */
			latitude.cardinal = nmea_cardinal_direction_parse(value);
			if (NMEA_CARDINAL_DIR_UNKNOWN == latitude.cardinal) {
				return -1;
			}
			break;

		case NMEA_GPRMC_LONGITUDE:
			/* Parse longitude */
			if (-1 == nmea_position_parse(value, &longitude)) {
				return -1;
			}
			break;

		case NMEA_GPRMC_LONGITUDE_CARDINAL:
			/* Parse cardinal direction */
			longitude.cardinal = nmea_cardinal_direction_parse(value);
			if (NMEA_CARDINAL_DIR_UNKNOWN == longitude.cardinal) {
				return -1;
			}
			break;

		case NMEA_GPRMC_GNDSPD_KNOTS:
			/* Parse Ground speed, knots */
			gndspd_knots = strtod(value, NULL);
			break;

		case NMEA_GPRMC_TRUECOURSE_DEG:
			/* Parse the true course, degrees */
			track_deg = strtod(value, NULL);
			break;

		case NMEA_GPRMC_MAGVAR_DEG:
			/* Parse the Magnetic variation, degrees */
			magvar_deg = strtod(value, NULL);
			break;

		case NMEA_GPRMC_MAGVAR_CARDINAL:
			/* Parse the Magnetic variation direction, only E and W are valid */
			magvar_cardinal = nmea_cardinal_direction_parse(value);
			if (NMEA_CARDINAL_DIR_UNKNOWN == magvar_cardinal) {
				magvar_cardinal = NMEA_CARDINAL_DIR_UNKNOWN;
				return -1;
			}
			break;
		case NMEA_GPRMC_MODE:
			/* Parse the Mode */
			mode = *value;
			break;

		default:
			break;
		}

	return 0;
}
