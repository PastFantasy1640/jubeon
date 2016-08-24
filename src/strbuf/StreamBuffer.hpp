////////////////////////////////////////////////////
// (c) 2016  StreamBuffer.hpp  white
////////////////////////////////////////////////////

//Concept : Thread Safe

/*

[NODE] This StreamBuffer class's data flow is like below.
InputStream--->                           --->OutputStream
InputStream--->StreamBuffer(Data Instance)--->OutputStream
InputStream--->                           --->OutputStream

All Buffer is Thread Safe!!
*/

#pragma once

#ifndef STRBUF_STREAMBUFFER_HPP
#define STRBUF_STREAMBUFFER_HPP

#include "StreamConnector.hpp"

namespace strbuf{

    template<typename T>
    class StreamBuffer : public StreamConnector<T>{       
    public:
    
    StreamBuffer(){ }
    
    virtual ~StreamBuffer(){ }
    
    
    
    private:
    
    };
};

#endif  //end of STRBUF_STREAMBUFFER_HPP
