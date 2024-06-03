#pragma once

#include "nmea.h"

#define ARRAY_LENGTH(a) (sizeof a / sizeof (a[0]))


extern int g_msgCount[7];

class NMEA_Sentence    //abstract base class for NMEA sentences
{

protected:
	nmea_t type = NMEA_UNKNOWN;

	//many, but not all NMEA sentences include Time, DATE, and/or position data
	struct tm time;
	nmea_position longitude;
	nmea_position latitude;
		

public:
	
	virtual int _parse(char* value, int val_index) = 0;
	virtual std::string printMe() = 0;

	std::string printDate()
	{
		char buf[100];
		const char* strMonths[] = { "Jan","Feb", "Mar", "Apr", "May", "Jun", "Jul","Aug","Sep","Oct","Nov","Dec" };
		const char* strDays[] = { "Sun","Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
		sprintf(buf,"Date[DD-MM-YYYY]: %02d-%0d-%04d\t", time.tm_mday, 1 + time.tm_mon, 1900 + time.tm_year);
		std::string retVal = buf;
		sprintf(buf, "Date: %s %02d %s %04d\r\n", strDays[time.tm_wday], time.tm_mday, strMonths[time.tm_mon], 1900 + time.tm_year);
		retVal +=buf;
		return retVal;
	}

	std::string printTime()
	{
		char buf[100];
		sprintf(buf,"Time: %02d:%02d:%02d\r\n", time.tm_hour, time.tm_min, time.tm_sec);
		std::string retVal = buf;
		return retVal;
	}

	std::string printLatLon()
	{
		char buf[100];
		sprintf(buf, "Latitude: %c%d %6.04f\r\n", latitude.cardinal, latitude.degrees, latitude.minutes);
		std::string retVal =buf;
		sprintf(buf, "Longitude: %c%d %6.04f\r\n", longitude.cardinal, longitude.degrees, longitude.minutes);
		//pmeF("Latitude: %c%d %6.04f\r\n", latitude.cardinal, latitude.degrees, latitude.minutes);
		//pmeF("Longitude: %c%d %6.04f\r\n", longitude.cardinal, longitude.degrees, longitude.minutes);
		retVal +=buf;
		return retVal;
	}

	nmea_t getType() { return type; }


	virtual NMEA_Sentence* parse(char* sentence, int length)
	{
		unsigned int n_vals, val_index;
		char* value, * val_string;
		char* values[255];

		/* Crop sentence from type word and checksum */
		val_string = _crop_sentence(sentence, length);
		if (NULL == val_string) {
			return nullptr;
		}

		/* Split the sentence into values */
		n_vals = _split_string_by_comma(val_string, values, ARRAY_LENGTH(values));
		if (0 == n_vals) {
			return nullptr;
		}
		
		for (val_index = 0; val_index < n_vals; val_index++) {
			value = values[val_index];
			int retVal = _parse(value, val_index); // this will call the subclass's parser
		}
		g_msgCount[this->getType()]++;
		return this;
	}




};

