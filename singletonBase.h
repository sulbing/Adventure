#pragma once

template <typename T>
class singletonBase
{
protected:
	static T* singleton;

	singletonBase(void) {};
	~singletonBase(void) {};
public:
	//싱글톤 접근자
	static T* getSingleton(void);

	//싱글톤 해제(메모리 해제함수)
	void releaseSingleton(void);

};

//싱글톤 초기화
template <typename T>
T* singletonBase<T>::singleton = 0;

//싱글톤 불러오는 함수
template <typename T>
T* singletonBase<T>::getSingleton(void)
{
	//싱글톤이 없다면 할당해줘라
	if (!singleton) singleton = new T;

	//그리고 할당한 싱글톤 반환
	return singleton;
}

//싱글톤 해제
template <typename T>
void singletonBase<T>::releaseSingleton(void)
{
	if (singleton)
	{
		delete singleton;

		singleton = 0;
	}
}