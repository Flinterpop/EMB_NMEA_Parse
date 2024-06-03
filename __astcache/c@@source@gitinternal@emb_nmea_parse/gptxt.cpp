#include <iostream>
#include "parse.h"



#include "GPTXT.h"


#define ARRAY_LENGTH(a) (sizeof a / sizeof (a[0]))

std::string GPTXT::printMe()
{
	std::string retVal;

	printf("GPTXT:\r\n");
	printf("IDs: % d % d % d\r\n",id_00,id_01,id_02);
	printf("Text: %s\r\n", text);
	return retVal;

}



NMEA_Sentence* GPTXT::parse(char* sentence, int length)
{
	type = NMEA_GPTXT;
	NMEA_Sentence::parse(sentence, length);
	return this;
}

int GPTXT::_parse(char* value, int val_index)
{

		memset(text, 0, NMEA_GPTXT_TEXT_SIZE);

		switch (val_index) {
		case NMEA_GPTXT_ID00:
			id_00 = strtol(value, NULL, 10);
			break;
		case NMEA_GPTXT_ID01:
			id_01 = strtol(value, NULL, 10);
			break;
		case NMEA_GPTXT_ID02:
			id_02 = strtol(value, NULL, 10);
			break;
		case NMEA_GPTXT_TEXT:
			strncpy(text, value, NMEA_GPTXT_TEXT_SIZE);
			text[NMEA_GPTXT_TEXT_SIZE - 1] = '\0';
			break;
		default:
			break;
		}

	return 0;
}





