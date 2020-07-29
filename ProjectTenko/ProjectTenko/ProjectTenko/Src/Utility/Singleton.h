#ifndef Singleton_H_
#define Singleton_H_

template<class T>
class Singleton
{
public:
	static inline T& GetInstance()
	{
		static T instance;
		return instance;
	}

protected:
	Singleton(){}
	virtual ~Singleton(){}


private:
	void operator=(const Singleton6 object_) {}
	Singleton(const Singleton& object_){}

};

#endif