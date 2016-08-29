///////////////////////////////////
// (c) 2016 white
///////////////////////////////////

#pragma once
#ifndef STRBUF_INPUTSTREAM_HPP
#define STRBUF_INPUTSTREAM_HPP

#include "IOStream.hpp"

namespace strbuf{
    template<typename T>
    class InputStream : public IOStream<T>{
    public:
        /** Stream Input.
         * @param input que data.
         * @returns true means this function finished the process successfully.
         */
        bool operator<< (const T & input){
            this->que(input);
			return true;
        }
    };
}

#endif
