//////////////////////////////////////////////
// (c) 2016 white
//////////////////////////////////////////////

#pragma once
#ifndef STRBUF_STREAMCONNECTOR_HPP
#define STRBUF_STREAMCONNECTOR_HPP

#include <list>
#include <memory>
#include <mutex>

#include "InputStream.hpp"
#include "OutputStream.hpp"

namespace strbuf{
    template <typename T>
    class StreamConnector{
    public:
        void addInputStream(InputStream<T> * inputstream){
            //MUTABLE
            std::lock_guard<std::mutex> lock(this->mutex_);
            this->inputs_.push_back(inputstream);
        }
        
        void addOutputStream(OutputStream<T> * outputstream){
            //Mutable
            std::lock_guard<std::mutex> lock(this->mutex_);
            this->outputs_.push_back(outputstream);
        }
        
        void flush(void){ 
            //Copy
            std::lock_guard<std::mutex> lock(this->mutex_);
            for(auto i : inputs_){
                while(i->getQueSize()){
                    T tmp = i->unque();   //unque
                    for(auto o : outputs_) o->que(tmp); //que./
                }
            }
        }
        
    protected:
    
    private:
        std::list<InputStream<T> *> inputs_;
        std::list<OutputStream<T> *> outputs_;
        
        std::mutex mutex_;
    };
};

#endif // end of STRBUF_STREAMCONNECTOR_HPP

