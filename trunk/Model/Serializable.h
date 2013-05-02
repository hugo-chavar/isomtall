#ifndef _SERIALIZABLE_H_
#define _SERIALIZABLE_H_

#include <string>

class Serializable{
public:
	Serializable();

	virtual void deserialize(std::string serializedObject) = 0;

	virtual std::string serialize() = 0;

	virtual ~Serializable();
};


#endif // _SERIALIZABLE_H_