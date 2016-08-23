////////////////////////////////////////////////////
// (c) 2016  StreamBuffer.hpp  white
////////////////////////////////////////////////////

//Concept : Thread Safe

/*

[NODE] This StreamBuffer class's data flow is like below.
InputStreamBuffer--->                           --->OutputStreamBuffer
InputStreamBuffer--->StreamBuffer(Data Instance)--->OutputStreamBuffer
InputStreamBuffer--->                           --->OutputStreamBuffer

All Buffer is Thread Safe!!
*/

#pragma once

#ifndef STRBUF_STREAMBUFFER_HPP
#define STRBUF_STREAMBUFFER_HPP

#include <list>
#include <memory>

namespace strbuf{

    template<typename T> class InputStreamBuffer;
    template<typename T> class OutputStreamBuffer;

    template<typename T>
    class StreamBuffer<T>{       
    public:
    private:
        //Connecting Buffers
        std::list<std::shared_ptr<InputStreamBuffer<T>>> inputs_;
        std::list<std::shared_ptr<OutputStreamBuffer<T>>> outputs_;
        
        
    };
};

#endif  //end of STRBUF_STREAMBUFFER_HPP
