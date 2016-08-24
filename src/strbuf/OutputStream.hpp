///////////////////////////////////
// (c) 2016 white
///////////////////////////////////

#pragma once
#ifndef STRBUF_OUTPUTSTREAM_HPP
#define STRBUF_OUTPUTSTREAM_HPP

#include "OutputStream.hpp"

namespace strbuf{
    template<typename T>
    class OutputStream : public IOStream<T>{
    public:
        /** Stream Output.
         * @param output que data.
         * @returns true means this function finished the process successfully.
         */
        bool operator>> (T & output){
            output = this->unque();
            return true;
        }
    };
}

#endif
