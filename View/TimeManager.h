#ifndef _TIMEMANAGER_H_
#define _TIMEMANAGER_H_



//TODO: This class should not have static methods. The class shoud be retrieved from the model.
class TimeManager {
private:
	//TODO: Not OK with this aproach. Review.
	//Internal variable to calculate deltaTime.
	unsigned int startTime;

	//Time between updateTime() calls in seconds.
	float deltaTime;

public:
	TimeManager();

	//Starts world's time.
	void initializeTime();

	//Updates world's time.
	void updateTime();

	//Returns time between updateTime() calls in seconds.
	float getDeltaTime();

	~TimeManager();
};


#endif //_TIMEMANAGER_H_
