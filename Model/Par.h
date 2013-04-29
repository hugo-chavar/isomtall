//Par Ordenado

#ifndef PAR_H
#define PAR_H

class Par {

public:
	Par();
	Par(int posX, int posY);
	Par (const Par &par);
	void getPos(int& posX, int& posY) const;
	void setPos(int posX, int posY);
	const Par &operator=(const Par &par);
	bool operator==(const Par &par) const;
	bool operator!=(const Par &par) const;
	bool operator<(const Par &par) const;
	bool operator>(const Par &par) const;
	bool operator>=(const Par &par) const;
	bool operator<=(const Par &par) const;
	~Par();
private:
	int X;
	int Y;
};


#endif