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
}

DirList::~DirList() {
}

bool DirList::createFromDirectory(string dir) {
	string filepath, filename;

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

	this->directory = dir;

	while(true)
	{
		// Si hay directorios o cosas raras las ignora
		char * buf = findData.cFileName;
		std::wstring filepath2;
		std::string filepath1(buf);

		if ( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) // ignoro subdirectorios
		{
			if(!FindNextFile(findHandle, &findData))
				break;
			continue;
		}

		files.push_back(filepath1);
		_count++;

		if(!FindNextFile(findHandle, &findData))
			break;
	}

	FindClose(findHandle);
	files.sort();
	iterador = files.begin();

	return true;

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

void DirList::clean() {
	files.clear();
	_count = 0;
	_currentPosition = 0;
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

unsigned DirList::count() const {
	return _count;
}

unsigned DirList::currentPosition() {
	return _currentPosition;
}

void DirList::deletePrevious() {
	iterador--;
	files.erase(iterador);
	seek(_currentPosition-1);
	_count--;
}
