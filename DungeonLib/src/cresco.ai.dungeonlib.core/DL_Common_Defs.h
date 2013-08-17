/*
 * DL_Common_Defs.h
 *
 *  Created on: May 27, 2013
 *      Author: CresCoJeff
 */

#ifndef DL_COMMON_DEFS_H_
#define DL_COMMON_DEFS_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string.h>
#include <math.h>
#include <tr1/unordered_map>

#define OK_BYTE 'a'
#define NOK_BYTE 'z'


static void myStaticWriteStringLog(std::string s){
		//add a timestamp here
		time_t rawtime;
		struct tm* timeinfo;
		rawtime = time(&rawtime);
		timeinfo = localtime ( &rawtime );
		char* myTime = asctime (timeinfo);
		FILE* pFile = fopen("DebugLog.txt", "a+");
		fprintf(pFile, "%s %s\n",myTime,s.c_str());
		fclose(pFile);
	}


static int srcUUID = 0;

static int getAndIncrementUUID(){
	srcUUID++;
	return srcUUID-1;
}

#endif /* DL_COMMON_DEFS_H_ */
