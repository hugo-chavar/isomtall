#ifndef _TIMEMANAGER_H_
#define _TIMEMANAGER_H_

namespace model { 
	//no estoy de acuerdo en un ppio que esto pertenezca al modelo
	//cada clase del modelo debe tener un metodo update que debe ser invocado cada cierta cant de tiempo
	//pero no implica q deba manejar el "tiempo" (Hugo)

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
 
} // namespace model

#endif //_TIMEMANAGER_H_
