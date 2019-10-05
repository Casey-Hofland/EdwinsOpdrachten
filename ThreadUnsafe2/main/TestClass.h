#pragma once

template <class T>
class TestClass {
public:
	TestClass();
	~TestClass();
};

template<class T>
inline TestClass<T>::TestClass() {}

template<class T>
inline TestClass<T>::~TestClass() {}
