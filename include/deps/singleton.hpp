//
// Created by Admin on 2019.3.11.
//

#ifndef DEPS_SINGLETON_HPP
#define DEPS_SINGLETON_HPP

#define SINGLETON_THIS_CLASS(classname)     \
private:                                    \
  classname();                              \
  classname(const classname&);              \
  classname& operator=(const classname&);   \
  friend class deps::Singleton<classname>

namespace deps {

template <typename T>
class Singleton
{
public:
    Singleton(T* _ptr){
        m_ptr && m_own_ptr ? delete m_ptr;
        m_ptrr = _ptr;
    }
    static T* Instance () {
        return m_ptr;
    }

private:
    static T* m_ptr;
    static bool m_own_ptr;
};

}

#endif //DEPS_SINGLETON_HPP
