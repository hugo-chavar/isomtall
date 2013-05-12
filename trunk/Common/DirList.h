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

#include <sys/stat.h>
#include <sys/types.h>


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
	bool _defaulted;
	string extension;
public:
	DirList();
	~DirList();
	static bool isNotDirectory(string);
	static bool canOpenFile(string);
	bool createFromDirectory(string);
	void setExtensionRequired(string);
	bool hasNext();
	bool hasNextDir();
	void addFile(string);
	void addDir(string);
	void loadFromDir(string);
	string next();
	string getDefault();
	bool defaulted();
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
	void serializarDirectorio(string path,string& serialize_s);

};

#endif /* DIRLIST_H_ */
