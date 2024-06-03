

#include <iostream>
#include <vector>

#include "parse.h"

#include "GPGSV.h"

#include "SatVehicle.h"

#define ARRAY_LENGTH(a) (sizeof a / sizeof (a[0]))

std::string checkPRN(int prn)
{
	std::string retVal ="";
	//see https://receiverhelp.trimble.com/alloy-gnss/en-us/NMEA-0183messages_GSV.html
	//$GPGSV indicates GPS and SBAS satellites. If the PRN is greater than 32, this indicates an SBAS PRN,
	// 87 should be added to the GSV PRN number to determine the SBAS PRN number.
	if (prn==44) {
		//puts("WAAS: Eutelsat so PRN is 44 + 87 = 131");
		retVal ="WAAS: Eutelsat so PRN is 44 + 87 = 131";
		//Eutelsat 117 West B
		//8°W
	}
	else if (prn==46)
	{
		retVal ="WAAS: SES 15 so PRN is 46 + 87 = 133";
		//puts("WAAS: SES 15 so PRN is 46 + 87 = 133");
		//WAAS GEO 6 (S15 - PRN 133)  
		//SES 15
		//Longitude	129° West
	}
	else if (prn == 48)
	{
		retVal ="WAAS: Galaxy 30 so PRN is 48 + 87 = 135";
		puts("WAAS: Galaxy 30 so PRN is 48 + 87 = 135");
		//Galaxy 30
		//Slot	125° West
	}
	return retVal;

}




extern std::vector<SatVehicle*> g_SVList;

int CheckForSatVeh(int prn)
{
	for (auto itr : g_SVList)
	{
		if (itr->prn == prn) return 1; //PRN already exists;
	}
	return 0;
}

int UpdateForSatVeh(int prn)
{
	for (auto itr : g_SVList)
	{
		if (itr->prn == prn)
		{
			itr->msgCount++;
			return 1; //PRN already exists;
		}
	}
	return 0;
}






void GPGSV::AddToSatList()
{
	int numSatsThisSentence = 4;
	if ((sentence_number * 4) < satellites) numSatsThisSentence = 4;
	else
	{
		numSatsThisSentence = satellites % 4;
		if (0 == numSatsThisSentence) numSatsThisSentence = 4;
	}
	//printf("numSatsThisSentence: %d\r\n", numSatsThisSentence);

	for (int i = 0;i < numSatsThisSentence;i++)
	{
		SatVehicle *sv = new SatVehicle(sat[i].prn, sat[i].elevation, sat[i].azimuth, sat[i].snr);

		struct tm newtime;


		/*
		//__time64_t long_time;
		__int64 long_time;



		char timebuf[26];
		errno_t err;
		// Get time as 64-bit integer.
		_time64(&long_time);
		// Convert to local time.
		err = _localtime64_s(&sv->TimeOfLastRx, &long_time);
		if (err)
		{
		}
		  */

		if (CheckForSatVeh(sat[i].prn))
		{
			UpdateForSatVeh(sat[i].prn);
		}
		else g_SVList.push_back(sv); //add it

	}


}



std::string GPGSV::printMe()
{
	char buf[1000];

	sprintf(buf,"GPGSV:\r\n");
	std::string retVal=buf;
	sprintf(buf,"Num sentences: %d\r\n", sentences);
	retVal+=buf;
	sprintf(buf,"This sentence #: %d\r\n", sentence_number);
	retVal+=buf;
	sprintf(buf,"Num satellites in view: %d\r\n", satellites);
	retVal+=buf;

	int numSatsThisSentence = 4;
	if ((sentence_number*4) < satellites) numSatsThisSentence = 4;
	else
	{
		numSatsThisSentence = satellites % 4;
		if (0 == numSatsThisSentence) numSatsThisSentence = 4;

	}
	sprintf(buf,"numSatsThisSentence: %d\r\n", numSatsThisSentence);
	retVal+=buf;
	for (int i = 0;i < numSatsThisSentence;i++)
	{
		sprintf(buf,"PRN: %d  Elevation: %d  Azimuth: %d  SNR: %d\r\n", sat[i].prn, sat[i].elevation, sat[i].azimuth, sat[i].snr);
		retVal+=buf;
		checkPRN(sat[i].prn);
	}

    return retVal;
}



NMEA_Sentence* GPGSV::parse(char* sentence, int length)
{
	type = NMEA_GPGSV;
	NMEA_Sentence::parse(sentence, length);
	return this;
}




int GPGSV::_parse(char* value, int val_index)
{
	switch (val_index) {
	case NMEA_GPGSV_SENTENCES:
		/* Parse number of sentences */
		 sentences = atoi(value);
		break;

	case NMEA_GPGSV_SENTENCE_NUMBER:
		/* Parse sentence number */
		 sentence_number = atoi(value);
		break;

	case NMEA_GPGSV_SATELLITES:
		/* Parse number of SVs in view */
		 satellites = atoi(value);
		break;

	case NMEA_GPGSV_PRN:
	case NMEA_GPGSV_PRN + 4:
	case NMEA_GPGSV_PRN + 8:
	case NMEA_GPGSV_PRN + 12:
		/* Parse PRN */
		 sat[(val_index - NMEA_GPGSV_PRN) / 4].prn = atoi(value);
		 PRNList.insert(sat[(val_index - NMEA_GPGSV_PRN) / 4].prn);
		break;

	case NMEA_GPGSV_ELEVATION:
	case NMEA_GPGSV_ELEVATION + 4:
	case NMEA_GPGSV_ELEVATION + 8:
	case NMEA_GPGSV_ELEVATION + 12:
		/* Parse cardinal direction */
		 sat[(val_index - NMEA_GPGSV_ELEVATION) / 4].elevation = atoi(value);
		break;

	case NMEA_GPGSV_AZIMUTH:
	case NMEA_GPGSV_AZIMUTH + 4:
	case NMEA_GPGSV_AZIMUTH + 8:
	case NMEA_GPGSV_AZIMUTH + 12:
		/* Parse number of satellites */
		 sat[(val_index - NMEA_GPGSV_AZIMUTH) / 4].azimuth = atoi(value);
		break;

	case NMEA_GPGSV_SNR:
	case NMEA_GPGSV_SNR + 4:
	case NMEA_GPGSV_SNR + 8:
	case NMEA_GPGSV_SNR + 12:
		/* Parse altitude */
		 sat[(val_index - NMEA_GPGSV_SNR) / 4].snr = atoi(value);
		break;

	default:
		break;
	}

	return 0;
}

