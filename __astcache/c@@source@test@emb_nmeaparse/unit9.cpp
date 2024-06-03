//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit9.h"

#include <vector>
#include <filesystem>
#include <fstream>

#include "nmea.h"
#include "parse.h"
#include "GPGGA.h"
#include "GPRMC.h"
#include "GPGLL.h"
#include "GPGSA.h"
#include "GPGSV.h"
#include "GPVTG.h"
#include "GPTXT.h"
#include "SatVehicle.h"


#define ARRAY_LENGTH(a) (sizeof a / sizeof (a[0]))

extern const char* NMEASentenceTypeNames[];

NMEA_Sentence* ParseNMEASentence(char* sentence);  //Fwd declartion

static int g_Debug=88;

int g_msgCount[7];  //7 types of NMEA strings, this is a running count of how many of each type was received
static std::vector<NMEA_Sentence*> g_NMEA_list; //list of all NMEA sentences received/parsed
std::vector<SatVehicle*> g_SVList; //list of all GPS satellites (SatVehicle struct)


NMEA_Sentence *ParseNMEASentence(char* sentence)
{
	//if (g_Debug != 0) pmeF("Parsing %s\r\n", sentence);
	int check_checksum=0;
	size_t length = strlen(sentence);
	if (-1 == nmea_validate(sentence, length)) {
		puts("Fail in nmea_validate");
		return nullptr;
	}

	nmea_t type = nmea_get_type(sentence);

	switch (type)
	{
		case NMEA_UNKNOWN:
		{
			return nullptr;
		}
		case NMEA_GPGGA:
		{
			GPGGA* myGPGGA = new GPGGA();
			return myGPGGA->parse(sentence, length);
		}
		case NMEA_GPGLL:
		{
			GPGLL* myGPGLL = new GPGLL();
			return myGPGLL->parse(sentence, length);
		}
		case NMEA_GPGSA:
		{
			GPGSA* myGPGSA = new GPGSA();
			return myGPGSA->parse(sentence, length);
		}
		case NMEA_GPGSV:
		{
			GPGSV* myGPGSV = new GPGSV();
			myGPGSV->parse(sentence, length);
			myGPGSV->AddToSatList();
			return (NMEA_Sentence*)myGPGSV;
		}
		case NMEA_GPRMC:
		{
			GPRMC* myGPRMC = new GPRMC();
			return myGPRMC->parse(sentence, length);
		}
		case NMEA_GPTXT:
		{
			GPTXT* myGPTXT = new GPTXT();
			return myGPTXT->parse(sentence, length);
		}
		case NMEA_GPVTG:
		{
			GPVTG* myGPVTG = new GPVTG();
			return myGPVTG->parse(sentence, length);
		}

	}
	return nullptr;
}




void TForm9::TestNMEAFile()
{
	std::ifstream ifs;
	std::string str;
	ifs.open("waas2.txt", std::ios::in);  // input file stream
	if (ifs)
	{
		char buf[100];
		while (!ifs.eof())
		{
			std::getline(ifs, str);
			//pmeF("%s\r\n", str.c_str());
			strcpy(buf, str.c_str());
			strcat(buf, "\r\n");
			NMEA_Sentence* next = ParseNMEASentence(buf);
			if (next != nullptr)
			{
				g_NMEA_list.push_back(next);
			}

			else pme("Failed to parse sentence!\n");
		}
		ifs.close();
	}
	else pme("Unable to open file to read");

	pme("Summary\r\n==============================================================");
	for (int i = 0;i < 7;i++)
	{
		pmeF("Count: %s  %d\r\n", NMEASentenceTypeNames[i], g_msgCount[i]);
	}
	GPGSV::showSatList();

	for (auto itr : g_SVList)
	{
		pmeF("PRN: %d  MsgCount: %d ",itr->prn, itr->msgCount);
		checkPRN(itr->prn);
		pme("");
		pmeF("Time: %02d:%02d:%02d\r\n", itr->TimeOfLastRx.tm_hour, itr->TimeOfLastRx.tm_min, itr->TimeOfLastRx.tm_sec);
	}


    return;

	//puts("Hit a key to continue");
	//getchar();

	for (int index = 0; index < g_NMEA_list.size(); ++index)
	{
		if (g_NMEA_list[index]->getType() == NMEA_GPGSV)
		{
			GPGSV* gpgsv = (GPGSV*)g_NMEA_list[index];
			gpgsv->printMe();
		}
	}

	//puts("Hit a key to continue");
	//getchar();


	for (int index = 0; index < g_NMEA_list.size(); ++index)
	{
		if (g_NMEA_list[index]->getType() == NMEA_GPGGA)
		{
			GPGGA* gpgga = (GPGGA*)g_NMEA_list[index];
			pmeF("GPGGA: altitude [m msl]: %8.3f\r\n", gpgga->altitude);
		}
	}

	pmeF("g_Debug = %d\r\n", g_Debug);
	//getchar();
	//puts("Hit a key to exit");

}




//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm9 *Form9;
//---------------------------------------------------------------------------
__fastcall TForm9::TForm9(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------





//this is a printf for the Debug Memo widget
void  TForm9::pmeF(const char* fmt, ...)
{
	if (TM_Debug->Lines->Count > 1000) TM_Debug->Lines->Clear();

	va_list args;
	va_start(args, fmt);
	char buf[200];
	vsprintf(buf,fmt,args);

	TM_Debug->Lines->Add(buf);
	va_end(args);
	//RE_Debug->Lines->Add("\n");
}

//this is a printf for the Debug Memo widget
void  TForm9::pmeF_Config(TColor color, bool isBold)
{
	//TM_Debug->SelAttributes->Color = color;
	//if (isBold) TM_Debug->SelAttributes->Style = Form9->TM_Debug->SelAttributes->Style << fsBold;
	//else TM_Debug->SelAttributes->Style = Form9->TM_Debug->SelAttributes->Style >> fsBold;
}

void  TForm9::pme(const char* fmt)
{
	if (TM_Debug->Lines->Count > 1000) TM_Debug->Lines->Clear();
	TM_Debug->SelText = fmt;
}

void  TForm9::pme(String st)
{
	if (TM_Debug->Lines->Count > 1000) TM_Debug->Lines->Clear();
	TM_Debug->Lines->Append(st);
}



std::wstring ExePath() {
	TCHAR buffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
	return std::wstring(buffer).substr(0, pos);
}



void __fastcall TForm9::Button1Click(TObject *Sender)
{

	pme("test\r\n");

    std::filesystem::path cwd = std::filesystem::current_path();
	//pmeF("Current directory: %s\r\n", cwd.c_str());
	//pmeF("Current directory: %s\r\n", ExePath().c_str());

	pmeF("Current directory:");
	TM_Debug->Lines->Append(cwd.c_str()	);
	pme("\r\n");

	pmeF("Current directory:");
	TM_Debug->Lines->Append(ExePath().c_str()	);
	pme("\r\n");


	g_Debug = 0;
	//TestStaticLines();
	TestNMEAFile();



}
//---------------------------------------------------------------------------








