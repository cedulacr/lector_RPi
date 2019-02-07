#include <iostream>
#include <string>

#include "include/config.h"

#include "include/DynamsoftBarcodeReader.h"
#include "include/Persona.h"


bool parse(unsigned char* raw, int length);

using namespace std;

int iFormat = BF_All;
int iMaxCount = 0x7FFFFFFF;
const char * pszImageFile = NULL;
int iIndex = 0;
STextResultArray *paryResult = NULL;
int iRet = -1;
PublicParameterSettings parSettings;
char cErrorMsgBuffer[1024];
void* hBarcode;

unsigned char keysArray[] = { 0x27,
            0x30,
            0x04,
            0xA0,
            0x00,
            0x0F,
            0x93,
            0x12,
            0xA0,
            0xD1,
            0x33,
            0xE0,
            0x03,
            0xD0,
            0x00,
            0xDf,
            0x00
           };

int main(int argc, const char* argv[])
{
	if(argc==2){
		hBarcode = DBR_CreateInstance();
		//  pVersion = DBR_GetVersion();
		DBR_InitLicense(hBarcode,KEY);
		// Set Reader Options
		//DBR_SetBarcodeFormats(hBarcode, iFormat);
		//DBR_SetMaxBarcodesNumPerPage(hBarcode, iMaxCount);
		DBR_GetTemplateSettings(hBarcode,"", &parSettings);
		parSettings.mAntiDamageLevel = 3;
		parSettings.mMaxAlgorithmThreadCount = 1;
		DBR_SetTemplateSettings(hBarcode,"",&parSettings,cErrorMsgBuffer,1024);

		//iRet = DBR_DecodeFileEx(hBarcode, pszImageFile, &paryResult);
		iRet = DBR_DecodeFile(hBarcode,argv[1],"");

		// Output barcode result
		if (iRet != DBR_OK){
			printf("Failed to read barcode: %s\n", DBR_GetErrorString(iRet));
		}

		DBR_GetAllTextResults(hBarcode,&paryResult);

		if (paryResult != NULL && paryResult->nResultsCount != 0){
			for (iIndex = 0; iIndex < paryResult->nResultsCount; iIndex++){
				if(parse(paryResult->ppResults[iIndex]->pBarcodeBytes,paryResult->ppResults[iIndex]->nBarcodeBytesLength)){			
					Persona a(paryResult->ppResults[iIndex]->pBarcodeBytes);
					a.print();	
				}
			}
		}
		DBR_FreeTextResults(&paryResult);
		DBR_DestroyInstance(hBarcode);
		return 0;
	}
	return 1;
}


bool parse(unsigned char* raw, int length){
	if(length!=700) return false;
	int j = 0;
	for (int i = 0; i < length; i++) {
		if (j == 17) {
			j = 0;
		}
		char c = (char) (keysArray[j] ^ ((char) (raw[i])));
		raw[i] = c;
		j ++;
	}
	return true;
}
