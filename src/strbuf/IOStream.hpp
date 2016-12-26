///////////////////////////////////
// (c) 2016 white
///////////////////////////////////

#pragma once
#ifndef STRBUF_IOSTREAM_HPP
#define STRBUF_IOSTREAM_HPP

#include <list>
#include <mutex>

namespace strbuf{
    template<typename T>
    class IOStream : private std::list<T>{
    protected:
        ///////////////////
        // Constructor
        ///////////////////
        IOStream() {}
        
        ///////////////////
        // Destructor
        ///////////////////
        virtual ~IOStream() {}
        
    public:
        //////////////////////////////////
        // unque data.
        // thread safe interface.
        //////////////////////////////////
        T unque() {
            { //Mutable Area
                std::lock_guard<std::mutex> lock(this->mutex_);
                if(this->size() > 0) {
                    T ret(this->front());
                    this->pop_front();
					return ret;
                }
            }
            return T();
        }

        
        //////////////////////////////////
        // que data.
        // thread safe interface.
        //////////////////////////////////
        void que(const T & elem){
            //Mutable Area
            std::lock_guard<std::mutex> lock(this->mutex_);
            this->push_back(elem);
        }
        
        //////////////////////////////////
        // get que size.
        // thread safe interface.
        //////////////////////////////////
        std::size_t getQueSize(void){
            //Mutable Area
            std::lock_guard<std::mutex> lock(this->mutex_);
            return this->size();
        }
        
    private:
    
        //Mutex Lock
        std::mutex mutex_;
    
    };
}

#endif
