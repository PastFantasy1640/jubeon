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
        void addInputStream(std::shared_ptr<InputStream<T>> & inputstream){
            //MUTABLE
            std::lock_guard<std::mutex> lock(this->mutex_);
            this->inputs_.push_back(inputstream);
        }
        
        void addOutputStream(std::shared_ptr<OutputStream<T>> & outputstream){
            //Mutable
            std::lock_guard<std::mutex> lock(this->mutex_);
            this->outputs_.push_back(outputstream);
        }
        
        void flush(void){ 
            //Copy
            std::lock_guard<std::mutex> lock(this->mutex_);
            for(auto i = this->inputs_.begin(); i != this->inputs_.end();){
				if (!*i) 
					continue;
                if(i->unique()) i = this->inputs_.erase(i);
                else{
                    while((*i)->getQueSize()){
                        T tmp = (*i)->unque();   //unque
                        for(auto o = this->outputs_.begin(); o != this->outputs_.end(); ){
							if (!*o) 
								continue;
                            (*o)->que(tmp); //que
                            if(o->unique()) o = this->outputs_.erase(o);
                            else o++;
                        }
                    }
                    i++;
                }
            }
        }
        
    protected:
    
    private:
        std::list<std::shared_ptr<InputStream<T>>> inputs_;
        std::list<std::shared_ptr<OutputStream<T>>> outputs_;
        
        std::mutex mutex_;
    };
};

#endif // end of STRBUF_STREAMCONNECTOR_HPP

