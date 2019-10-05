#pragma once

#include <vector>

template<class T>
class concurrent_vector {
public:
	concurrent_vector();
	concurrent_vector(std::vector<T>);
	~concurrent_vector();
	void setVec(std::vector<T>);
	std::vector<T> getVec();

private:
	std::vector<T> vec;
};

template<class T>
inline concurrent_vector<T>::concurrent_vector() {}

template<class T>
inline concurrent_vector<T>::concurrent_vector(std::vector<T> vec) {
	setVec(vec);
}

template<class T>
inline concurrent_vector<T>::~concurrent_vector() {}

template<class T>
inline void concurrent_vector<T>::setVec(std::vector<T> vec) {
	this->vec = vec;
}

template<class T>
inline std::vector<T> concurrent_vector<T>::getVec() {
	return vec;
}
