/*
 * DirList.cpp
 *
 *  Created on: 05/09/2012
 *      Author: Hugo Chavar
 */
#include <algorithm>
#include "DirList.h"

using namespace std;

DirList::DirList() {
	_count = 0;
	_currentPosition = 0;
	maxFileNameLength = 0;

}

DirList::~DirList() {
}

bool DirList::createFromDirectory(string dir) {
	string filepath, filename;
	DIR *dp;
	struct dirent *dirp;
	struct stat filestat;
	dp = opendir(dir.c_str());
	if (dp == NULL) {
		cerr << "Se produjo un error al abrir el directorio " << dir << endl;
		return false;
	}
	this->directory = dir;

	while ((dirp = readdir(dp))) {
		filepath = dir + "/" + dirp->d_name;

		// Si hay directorios o cosas raras las ignora
		if (stat(filepath.c_str(), &filestat))
			continue;
		if (S_ISDIR( filestat.st_mode ))
			continue;
		filename = dirp->d_name;
		if (maxFileNameLength < filename.length())
			maxFileNameLength = filename.length();
		files.push_back(filename);
		_count++;

	}
	files.sort();
	iterador = files.begin();

	closedir(dp);

	return true;

}

string DirList::next() {
	string sigte = *iterador;
	//iteratorPrev=iterator;
	iterador++;
	_currentPosition++;

	return sigte;

}

string DirList::nextFullPath() {
	string sigte = directory + "/" + (*iterador);
	//iteratorPrev=iterator;
	iterador++;
	_currentPosition++;

	return sigte;

}
bool DirList::hasNext() {
	return (_currentPosition < _count);
}

bool DirList::empty() {
	return (_count == 0);
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
			//iteratorPrev=iterator;
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
