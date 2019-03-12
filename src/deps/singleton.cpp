//
// Created by Admin on 2019.3.11.
//

#include "deps/singleton.hpp"
namespace deps {

template<typename T> T* Singleton<T>::m_ptr = new T();
template<typename T> bool Singleton<T>::m_own_ptr = true;

}