/*
* DirList.cpp
*
*  Created on: 13/04/2013
*      Author: Hugo Chavar
*/
#include <algorithm>
#include <windows.h>
#include "DirList.h"

using namespace std;


DirList::DirList() {
	_count = 0;
	_currentPosition = 0;
	_countDir = 0;
	_currentPositionDir = 0;
	testExtension = false;
}

DirList::~DirList() {
}

bool DirList::createFromDirectory(string dir) {

	DWORD attr = GetFileAttributesA(dir.c_str());
	if (attr == INVALID_FILE_ATTRIBUTES){
		cerr << "Error al acceder a " << dir << endl;
		return false; 
	}

	if (!(attr & FILE_ATTRIBUTE_DIRECTORY)){
		cerr << "No existe el directorio " << dir << endl;
		return false;
	}

	this->directory = dir;

	if (dir[dir.size()-1] != '/'){
		dir.append("/*.*");
	} else {
		dir.append("*.*");
	}

	WIN32_FIND_DATA findData;
	HANDLE findHandle;

	findHandle = FindFirstFile(dir.c_str(), &findData);

	while(true)
	{
		char * buf = findData.cFileName;
		std::string filepath1(buf);

		if ( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) // podria ser subdirectorio
		{
			// saltear carpeta raiz (..) y actual (.)
			if ( strcmp(findData.cFileName,".") && strcmp(findData.cFileName,"..") ) 
			{
				directories.push_back(filepath1); // es subdirectorio
				_countDir++;
			}
		} else { //es archivo
			if (!(testExtension)||(filepath1.find(extension)!=string::npos)){
				files.push_back(filepath1);
				_count++;
			}
		}

		if(!FindNextFile(findHandle, &findData))
			break;
	}

	FindClose(findHandle);
	files.sort();
	directories.sort();
	iterador = files.begin();
	iteradorDir = directories.begin();
	return true;
}

string DirList::nextDir() {
	string sigte = *iteradorDir;
	iteradorDir++;
	_currentPositionDir++;

	return sigte;
}

bool DirList::emptyDir() {
	return (_countDir == 0);
}

string DirList::nextFullPathDir() {
	string sigte = directory + "/" + (*iteradorDir);
	iteradorDir++;
	_currentPositionDir++;

	return sigte;

}
bool DirList::hasNextDir() {
	return (_currentPositionDir < _countDir);
}

void DirList::clean() {
	files.clear();
	_count = 0;
	_currentPosition = 0;
	directories.clear();
	_countDir = 0;
	_currentPositionDir = 0;
}

bool DirList::seek(unsigned pos) {
	bool status = (pos < _count);
	if (status) {
		_currentPosition = pos;
		iterador = files.begin();
		for (unsigned i = 0; i < pos; i++) {
			iterador++;
		}
	}
	return status;
}

unsigned DirList::countDir() const {
	return _countDir;
}

unsigned DirList::count() const {
	return _count;
}

unsigned DirList::currentPositionDir() {
	return _currentPositionDir;
}

void DirList::deletePrevious() {
	iterador--;
	files.erase(iterador);
	seek(_currentPosition-1);
	_count--;
}

string DirList::next() {
	string sigte = *iterador;
	iterador++;
	_currentPosition++;

	return sigte;

}

bool DirList::empty() {
	return (_count == 0);
}

string DirList::nextFullPath() {
	string sigte = directory + "/" + (*iterador);
	iterador++;
	_currentPosition++;

	return sigte;

}
bool DirList::hasNext() {
	return (_currentPosition < _count);
}

void DirList::setExtensionRequired(string ext){
	testExtension = true;
	extension = ext;
}

void DirList::restartCurrentPosition() {
	_currentPosition = 0;
	iterador = files.begin();
}
