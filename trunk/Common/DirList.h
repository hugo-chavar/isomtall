/*
 * DirList.h
 *
 *  Created on: 05/09/2012
 *      Author: Hugo Chavar
 */

#ifndef DIRLIST_H_
#define DIRLIST_H_

#include <iostream>
#include <string>
#include <list>

//#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

//#include "dirent.h"

//#include "Archivo.h"
//#include "TermFile.h"

using namespace std;

class DirList {
private:
	list<string> files;
	list<string>::iterator iterador;
	list<string>::iterator iteradorPrev;
	unsigned _count;
	unsigned _currentPosition;
	string directory;
public:
	DirList();
	~DirList();
	bool createFromDirectory(string);
	bool hasNext();
	string next();
	string nextFullPath();
	bool seek(unsigned);
	unsigned currentPosition();
	unsigned count() const;
	void clean();
	void deletePrevious();
	bool empty();

};

#endif /* DIRLIST_H_ */
