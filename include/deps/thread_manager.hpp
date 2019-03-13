//
// Created by Admin on 2019.3.13.
//

#ifndef DEPS_THREAD_MANAGER_HPP
#define DEPS_THREAD_MANAGER_HPP

#include <thread>
#include <string>
#include <memory>
#include <list>
#include <functional>
#include <cassert>
#include <random>
#include <iostream>



class _Thr_Nd {
public:
    _Thr_Nd(): _thr_ptr(nullptr){}
    ~_Thr_Nd() {
        for(auto i: _chld_ptr) { delete i; }
        if(_thr_ptr) {
            if (_thr_ptr->joinable()) { _thr_ptr->join();
//#ifdef DEBUG
                std::cout << "thread ["<< _thr_ptr->get_id() << "] joined"<<std::endl;
//#endif
            }
            delete _thr_ptr;
        }
    }
private:
    std::thread::id _id;
    std::string _name;
    std::thread* _thr_ptr;
    std::list<_Thr_Nd*> _chld_ptr;

    friend class ThreadManager;
    friend class _Thr_reg;
};

class _Thr_reg{
public:
    explicit  _Thr_reg(_Thr_Nd* _thr_ptr): cur_nd(_thr_ptr) {
        _thr_ptr->_id = std::this_thread::get_id();
    }

    ~_Thr_reg() {
        for(auto i: cur_nd->_chld_ptr) {
            delete i;
        }
        cur_nd->_chld_ptr.clear();
    }
private:
    _Thr_Nd* cur_nd;
};

template<class _Fn, class... _Args>
void _Wap_func(_Thr_Nd* _thr_ptr, _Fn&& _Fx, _Args&&... _Ax){
    volatile _Thr_reg _reg(_thr_ptr);
    auto _tg = ::std::bind(_Decay_copy(::std::forward<_Fn>(_Fx)),
                         _Decay_copy(::std::forward<_Args>(_Ax))...);
    _tg();
}

class ThreadManager{
public:
    static void Init(const std::string& name = std::string()){
        _root = new _Thr_Nd();
        _root->_id = std::this_thread::get_id();
        _root->_name = name;
    }

    static const std::thread* find_by_id(std::thread::id tid) {
        std::function<bool(_Thr_Nd*)> func =
                [&tid](_Thr_Nd* nd)->bool{ return nd->_id == tid;};
        _Thr_Nd* nd = _travel(_root, func);
        return (nd ?  nd->_thr_ptr: nullptr);
    }

    static const std::thread* find_by_name(const std::string& name) {
        std::function<bool(_Thr_Nd*)> func =
                [&name](_Thr_Nd* nd)->bool{ return nd->_name == name;};
        _Thr_Nd* nd = _travel(_root, func);
        return (nd ?  nd->_thr_ptr: nullptr);
    }

//    template<typename _Fn, typename... _Args>
//    static void new_thread(_Fn&& _Fx, _Args&&... _Ax){
//        std::string rnd_name = "thread_" + std::to_string(rnd_eng());
//        new_thread(rnd_name, _Fx, std::forward<_Args>(_Ax)...);
//    }

    template<typename _Fn, typename ... _Args>
    static void new_thread(const std::string& name, _Fn&& _Fx, _Args&&... _Ax){
        std::thread::id _P_tid = std::this_thread::get_id();
        _Thr_Nd* current_thread_inited = _cur_Nd();
        assert(current_thread_inited);
        _Thr_Nd* chld = new _Thr_Nd;
        chld->_name = name;
        chld->_thr_ptr = new std::thread(_Wap_func, std::forward<_Thr_Nd*, _Fn, _Args>(chld, _Fx, _Ax)...);
        current_thread_inited->_chld_ptr.push_back(chld);
    }
private:
    static _Thr_Nd* _cur_Nd(){
        std::thread::id _P_tid = std::this_thread::get_id();
        std::function<bool(_Thr_Nd*)> func =
                [&_P_tid](_Thr_Nd* nd)->bool{ return nd->_id == _P_tid;};
        return _travel(_root, func);
    }

    static _Thr_Nd* _travel(_Thr_Nd* root, std::function<bool(_Thr_Nd*)> found){
        if(found(root)) { return root; }
        else for(auto i : root->_chld_ptr) {
            _Thr_Nd* nd = _travel(i, found);
            if(nd) { return nd; }
        }
        return nullptr;
    }

    static _Thr_Nd* _root;
    static std::default_random_engine rnd_eng;

    friend class _Thr_reg;
};

#endif //DEPS_THREAD_MANAGER_HPP
