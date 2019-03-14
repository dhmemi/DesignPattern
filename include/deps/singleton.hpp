//
// Created by Admin on 2019.3.11.
//

#ifndef DEPS_SINGLETON_HPP
#define DEPS_SINGLETON_HPP

#define SINGLETON_THIS_CLASS(classname)             \
private:                                            \
  classname(){}                                     \
  classname(const classname&) = delete ;            \
  classname& operator=(const classname&) = delete;  \
  friend class deps::Singleton<classname>

namespace deps {

template <typename T>
class Singleton
{
public:
    static T* Instance () {
        if(!m_ptr) {  m_ptr = new T(); }
        return m_ptr;
    }

private:
    static T* m_ptr;
};

template<typename T> T* Singleton<T>::m_ptr(nullptr);

} //namespace deps

#endif //DEPS_SINGLETON_HPP
