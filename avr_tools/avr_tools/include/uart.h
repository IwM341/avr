#ifndef UART_H
#define UART_H

#include "signals.h"

namespace aos{

template <typename uart_impl_type,typename pipe_type,size_t out_qsize = 124>
struct uart_writer{
    pipe stream_out;
    uart_impl_type uart_impl;
    __guard g;
    uart_writer(uart_impl_type uart_impl):uart_impl(uart_impl){}
    void write(uint8_t data){
        g.lock();
        if(uart_impl.ready())
            uart_impl.send(data);
        else
            stream_out.write(&data,1);
        g.unlock();
    }
    void write(const char *data,uint8_t size){
        g.lock();
        stream_out.write(data,size);
        if(uart_impl.ready()){
            available_to_send();
        }
        g.unlock();
    }
    /*slot*/ void available_to_send(){
        g.lock();
        uint8_t data;
        if(stream_out.size()){
            stream_out.read(&data,1);
            uart_impl.send(data);
        }
        g.unlock();
    }
}; 
template <typename pipe_type,typename signal_type = signal_cs<1>>
struct uart_reader_nbyte{
    
    pipe_type stream_in;
    signal_type bytes_recieved_or_;

    /*slot*/ void recieve(uint8_t byte){
        stream_in.write(&byte,1);
        if(bytes_remain == stream_in){

        }
        bytes_remain--;
        if(!bytes_remain){
            bytes_remain = package_size;
        }
    }
    /*slot*/ wake_up_and_flush{
        
    }

    uint8_t package_size;
    uint8_t bytes_remain;
    timer_size_type _delay;
};

};

#endif//UART_H