//Nodo usado por el pathfinder

#ifndef NODO_H
#define NODO_H

class Nodo {

public:
	Nodo();
	Nodo (int X, int Y);
	Nodo (const Nodo &nodo);
	~Nodo();

	void getPos (int &X, int &Y) const;
	void setPos (int X, int Y);
	void getPosP (int &X, int &Y) const;
	void setPosP (int X, int Y);
	unsigned int getGScore () const;
	unsigned int getHScore () const;
	void setGScore (unsigned int Score);
	void setHScore (unsigned int Score);

	const Nodo &operator=(const Nodo &nodo);
	bool operator==(const Nodo &nodo) const;
	bool operator!=(const Nodo &nodo) const;
	bool operator<(const Nodo &nodo) const;
	bool operator>(const Nodo &nodo) const;

private:
	int posX;
	int posY;
	int posXP;	//Posicion del nodo padre
	int posYP;
	unsigned int GScore;
	unsigned int HScore;

};


#endif