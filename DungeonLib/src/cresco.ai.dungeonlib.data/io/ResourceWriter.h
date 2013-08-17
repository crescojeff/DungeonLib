/*
 * ResourceWriter.h
 *
 *  Created on: Jul 16, 2013
 *      Author: CresCoJeff
 *
 *      This fellow takes tokenized string data from Tokenizer and StringTokenizer
 *      and generates valid C++ resource files with said data.
 *      Example:
 *      Input: <TEXT> @+id/DDBOOBS at byte offset 0x00001234, value "Boobs"
 *      or Input: <TEXT id='DDBOOBS'>"Boobs"</TEXT>
 *      Output:
 *      #ifndef RESOURCES_H_
 *      #define RESOURCES_H_
 *
 *      class Resources{
 *      public:
 *
 *      class strings{
 *        static const std::string* DDBOOBS = new std::string("Boobs");
 *
 *       };
 *
 *      };
 *
 *      #endif //RESOURCES_H_
 *
 *      which can be grabbed (wink) in other C++ by simply including the
 *      Resources.h file and accessed via Resources.strings.DDBOOBS
 *      AND since only the pointer is static, its content can be freed or reassigned
 *      however we wish within the program...
 *      BE SURE TO DELETE ALL SUCH STATIC POINTERS ALLOCATED
 *      IN Resources.h AT PROGRAM EXIT (can use an if!=NULL guard set
 *      if you want to avoid double-frees)
 *
 */

#ifndef RESOURCEWRITER_H_
#define RESOURCEWRITER_H_

#include "../../cresco.ai.dungeonlib.core/DL_Common_Defs.h"
#include <iostream>
#include <stdio.h>
#include <fstream>

class ResourceWriter {
private:
	std::string sResContent;
	std::string sTempContent;

public:

	const static int WRITE_MODE_OVER = 0;
	const static int WRITE_MODE_APPEND = 1;
	const static int WRITE_MODE_PREPEND = 2;

	ResourceWriter(){
		sResContent = "";
		sTempContent = "";
	}
	virtual ~ResourceWriter(){

	}

	//accessors
	std::string getResContent(){
		return sResContent;
	}
	void setResContent(std::string s){
		sResContent = s;
	}

	//control functions
	template <class data> void appendToResContent(data d){
		std::stringstream ss;
		ss << sResContent << d << std::endl;
		sResContent = ss.str();
	}

	void writeContentToResources(int mode){
		std::string errStr = "";
		switch(mode){
		case WRITE_MODE_OVER:{
			//first delete the current res file
			if( remove( "Resources.h" ) != 0 ){
			    perror( "Error deleting file" );
			    std::stringstream errBuffer;
			    std::streambuf* old = std::cerr.rdbuf(errBuffer.rdbuf());
			    errStr = errBuffer.str();
			    std::cout << errStr << std::endl;
			}
			  else{
			    std::cout << "File successfully deleted" << std::endl;
			}

			//if(errStr == "filenotfound"){
			//now we recreate it empty
			std::ofstream ofs("Resources.h");

			//finally write content
			ofs << sResContent << std::endl;
			ofs.close();
		    //}

			break;
		}
		case WRITE_MODE_APPEND:{
			std::ofstream resFileOFS;
			resFileOFS.open("Resources.h",std::ios::out|std::ios::app);
			if(resFileOFS.is_open()){
				resFileOFS << sResContent << std::endl;
			}
			resFileOFS.close();
			break;
		}
		case WRITE_MODE_PREPEND:{

			//create an input fs on the file
			std::ifstream resFileIFS;
			resFileIFS.open("Resources.h",std::ios::in);

			//read in its contents to sTempContent
			if(resFileIFS.is_open()){
				resFileIFS.seekg (0, resFileIFS.end);
				int length = resFileIFS.tellg();
				resFileIFS.seekg(0, resFileIFS.beg);

				char * buffer = new char [length];

				std::cout << "Reading " << length << " characters... ";
				// read data as a block:
				resFileIFS.read (buffer,length);
				sTempContent = buffer;
				delete[] buffer;
			}
			resFileIFS.close();

			std::cout << sTempContent << std::endl;
			myStaticWriteStringLog(sTempContent);

			//now we erase and recreate the res file
			if( remove( "Resources.h" ) != 0 ){
				perror( "Error deleting file" );
				std::stringstream errBuffer;
				std::streambuf* old = std::cerr.rdbuf(errBuffer.rdbuf());
				errStr = errBuffer.str();
				std::cout << errStr << std::endl;
			}
			  else{
				std::cout << "File successfully deleted" << std::endl;
			}

			//if(errStr == "filenotfound"){
			//now we recreate it empty
			std::ofstream ofs("Resources.h");

			//finally write content
			ofs << sResContent << std::endl << sTempContent << std::endl;
			ofs.close();


			break;
		}
		default:{
			std::stringstream ss;
			ss << "Whoops, we are in an unsupported WRITE_MODE of " << mode << std::endl;
			myStaticWriteStringLog(ss.str());
			break;
		}
		}
	}




};

#endif /* RESOURCEWRITER_H_ */
