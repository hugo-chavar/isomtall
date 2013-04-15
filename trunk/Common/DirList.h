/*
 * DirList.h
 *
 *  Created on: 13/04/2013
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
	list<string> directories;
	list<string>::iterator iterador;
	list<string>::iterator iteradorDir;
	unsigned _count;
	unsigned _currentPosition;
	unsigned _countDir;
	unsigned _currentPositionDir;
	string directory;
	bool testExtension;
	string extension;
public:
	DirList();
	~DirList();
	bool createFromDirectory(string);
	void setExtensionRequired(string);
	bool hasNext();
	bool hasNextDir();
	string next();
	string nextFullPath();
	string nextDir();
	string nextFullPathDir();
	bool seek(unsigned);
	unsigned currentPosition();
	unsigned currentPositionDir();
	unsigned count() const;
	unsigned countDir() const;
	void clean();
	void deletePrevious();
	bool empty();
	bool emptyDir();
	void restartCurrentPosition();

};

#endif /* DIRLIST_H_ */
