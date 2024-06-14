#ifndef ASYNC_IO_H
#define ASYNC_IO_H
#include "pipe.h"
#include "scheduler.h"
#include "optional.h"
#include <stdlib.h>

namespace asyncruino{
    template <typename writer_t>
    concept WriteDevice = requires (writer_t w){
        {w.write(char {})};
    };

    template <Scheduler scheduler_t,Guard guard_t, 
            typename size_type = size_t,size_type buff_size = 64>
    struct async_input_impl : sheduler_getter<scheduler_t>{
        pipe<char,size_type,buff_size> m_buf;
        char * buffer_out;
        size_type remain_space;
        char control_seq[2];
        uint8_t match_length;
        guard_t m_guard;
        struct coro_data{
            enum action_type:uint8_t{
                READ_BYTE = 0,
                READ_BYTES = 1,
                READ_BYTES_UNTIL_1 = 2,
                READ_BYTES_UNTIL_2 = 3
            };
            action_type action;
            std::coroutine_handle<> handle; 
        };
        async_input_impl(scheduler_t & m_scheduler):sheduler_getter<scheduler_t>(m_scheduler){
            match_length = 0;
        }
        optional<coro_data> m_waitor;
        
        inline bool read_from_buf_byte(char & out){
            return m_buf.read(out);
        }
        inline size_type read_from_buf_bytes(char * out,size_type bytes){
            return m_buf.read(out,bytes);
        }
        struct read_until_1_ret_t {size_type read_bytes;bool success;};
        inline read_until_1_ret_t read_from_buf_until_1_bytes(char * out,char c0,size_type bytes){
            char c;
            for(size_type i=0;i<bytes;++i){
                if(!m_buf.read(c)){
                    return {i,false};
                } else {
                    *out = c;
                    ++out;
                    if(c == c0){
                        return {i+static_cast<size_type>(1),true};
                    }
                }
            }
            return {bytes,true};
        }
        struct read_until_2_ret_t {size_type read_bytes;bool success;uint8_t bytes_match;};
        inline read_until_2_ret_t read_from_buf_until_2_bytes(char * out,char c0,char c1,size_type bytes){
            char c;
            uint8_t bytes_match = 0;
            for(size_type i=0;i<bytes;++i){
                
                if(!m_buf.read(c)){
                    return {i,false,bytes_match};
                } else {
                    *out = c;
                    ++out;
                    if(c == c0 && bytes_match == 0){
                        bytes_match++;
                    } else if (c == c1 && bytes_match == 1){
                        return {i+1,true,2};
                    }
                }
            }
            return {bytes,true,bytes_match};
        }


        void interrupt(char c){

            //m_guard.lock();
            if(!m_waitor){
                m_buf.write(c);
            } else {
                switch (m_waitor.value.action)
                {
                case coro_data::READ_BYTE:
                {
                    auto m_c_handle = m_waitor.value.handle;
                    m_waitor.reset();
                    m_buf.write(c);
                    this->_get_sheduler().push_task(m_c_handle);
                    break;
                }
                case coro_data::READ_BYTES: {
                    *buffer_out = c;
                    buffer_out++;
                    remain_space--;
                    if(!remain_space){
                        auto m_c_handle = m_waitor.value.handle;
                        m_waitor.reset();
                        this->_get_sheduler().push_task(m_c_handle);
                    }
                    break;
                }
                case coro_data::READ_BYTES_UNTIL_1:{
                    *buffer_out = c;
                    remain_space--;
                    if(!remain_space || c == control_seq[0]){
                        auto m_c_handle = m_waitor.value.handle;
                        m_waitor.reset();
                        this->_get_sheduler().push_task(m_c_handle);
                    }else{
                        ++buffer_out;
                    }
                    break;
                }
                case coro_data::READ_BYTES_UNTIL_2:{
                    *buffer_out = c;
                    ++buffer_out;
                    remain_space--;
                    if(!remain_space){
                        goto exit_label;
                    }
                    if(c == control_seq[match_length]){
                        if(match_length ==1){
                            goto exit_label;
                        } else {
                            match_length++;
                            break;
                        }
                    } else {
                        match_length = 0;
                        break;
                    }
                    
                    exit_label:{
                        auto m_c_handle = m_waitor.value.handle;
                        m_waitor.reset();
                        this->_get_sheduler().push_task(m_c_handle);
                        break;
                    }
                }
                default:
                    break;
                }
                
            }
            //m_guard.unlock();
        }

        private:
        struct read_byte_awaitor{
            async_input_impl *m_input;
            bool is_ready;
            char ready_char;
            inline read_byte_awaitor(async_input_impl &_input_impl):
                m_input(&_input_impl){
                m_input->m_guard.lock();
                is_ready = m_input->read_from_buf_byte(ready_char);
            }
            inline bool await_ready(){
                return is_ready;
            }
		    char await_resume(){
                if(is_ready){
                    m_input->m_guard.unlock();
                    return ready_char;
                }
                else{
                    char c;
                    m_input->m_guard.lock();
                    m_input->m_buf.read(c);
                    m_input->m_guard.unlock();
                    return c;
                }
            }
            void await_suspend(std::coroutine_handle<> h){
                m_input->m_waitor = {coro_data::READ_BYTE,h};
                m_input->m_guard.unlock();
            }
        };

        
        struct read_bytes_awaitor{
            async_input_impl *m_input;
            size_type bytes_to_read;
            char * dest;
            bool aw_ready;
            inline read_bytes_awaitor(async_input_impl &_input_impl,char * m_dest,size_type m_bytes_to_read):
            m_input(&_input_impl){
                m_input->m_guard.lock();
                size_type already_read = m_input->read_from_buf_bytes(m_dest,m_bytes_to_read);
                bytes_to_read =m_bytes_to_read - already_read;
                dest = m_dest + already_read;
                aw_ready = (bytes_to_read == 0);
            }

            inline bool await_ready(){
                return aw_ready;
            }
            inline void await_resume(){
                if(aw_ready){
                    m_input->m_guard.unlock();
                }
            }
            inline void await_suspend(std::coroutine_handle<> h){
                m_input->m_waitor = {coro_data::READ_BYTES,h};
                m_input->buffer_out = dest;
                m_input->remain_space = bytes_to_read;
                m_input->m_guard.unlock();
            }
        };

        template <size_type bytes_cmp_size>
        struct read_bytes_until_awaitor{
            async_input_impl *m_input;
            size_type bytes_to_read;
            size_type already_read;
            char * dest;
            char c0;
            char c1;
            uint8_t bytes_matched;
            bool aw_ready;

            inline read_bytes_until_awaitor(
				async_input_impl &_input_impl,char * m_dest,
				size_type m_bytes_to_read,const char * seq
			):
            m_input(&_input_impl){
                m_input->m_guard.lock();
                if constexpr(bytes_cmp_size == 1){
                    c0 = seq[0];
                    read_until_1_ret_t res_1 = m_input->read_from_buf_until_1_bytes(m_dest,c0,m_bytes_to_read);
                    already_read = res_1.read_bytes;
                    aw_ready = res_1.success;
                } else if constexpr(bytes_cmp_size == 2){
                    c0 = seq[0];
                    c1 = seq[1];
                    read_until_2_ret_t res2 = m_input->read_from_buf_until_2_bytes(m_dest,c0,c1,m_bytes_to_read);
                    already_read = res2.read_bytes;
                    bytes_matched = res2.bytes_match;
                    aw_ready = res2.success;
                } else{
                    static_assert( 0 < bytes_cmp_size < 3 ,"bytes_cmp_size should be 0 or 1");
                }
                
                bytes_to_read =m_bytes_to_read - already_read;
                dest = m_dest + already_read;
            }

            inline bool await_ready(){
                return aw_ready;
            }
            inline size_type await_resume(){
                if(aw_ready){
                    m_input->m_guard.unlock();
                    return already_read;
                }
                return already_read + (bytes_to_read-m_input->remain_space);
            }
            inline void await_suspend(std::coroutine_handle<> h){
                if constexpr(bytes_cmp_size == 1){
                    m_input->m_waitor = {coro_data::READ_BYTES_UNTIL_1,h};
                    m_input->control_seq[0] = c0;
                    m_input->match_length = 0;
                } else {
                    m_input->m_waitor = {coro_data::READ_BYTES_UNTIL_2,h};
                    m_input->control_seq[0] = c0;
                    m_input->control_seq[1] = c1;
                    m_input->match_length = 0;
                }
                m_input->buffer_out = dest;
                m_input->remain_space = bytes_to_read;
                m_input->m_guard.unlock();
            }
        };
        public:
        read_byte_awaitor ReadByte(){
            return read_byte_awaitor(*this);
        }
        read_bytes_awaitor ReadBytes(char * dest,size_type n_bytes){
            return read_bytes_awaitor(*this,dest,n_bytes);
        }
        read_bytes_until_awaitor<1> ReadBytesUntil(char * dest,size_type n_bytes,char escape_symbol){
            return read_bytes_until_awaitor<1>(*this,dest,n_bytes,&escape_symbol);
        }
        read_bytes_until_awaitor<2> ReadBytesUntil(char * dest,size_type n_bytes,const char *escape_symbol){
            return read_bytes_until_awaitor<2>(*this,dest,n_bytes,escape_symbol);
        }
    };

    template <typename awaiter_t>
    concept Awaitor = requires (awaiter_t _a){
        {_a.await_ready()}->std::same_as<bool>;
        {_a.await_resume()};
        {_a.await_suspend(std::coroutine_handle<>{})};
    };

    template <typename input_t>
    concept InputStream = requires(input_t _in){
        {_in.ReadByte()}->Awaitor;
        {_in.ReadBytes((char *)0,0)}->Awaitor;
    };


    template <typename write_input_t>
    concept AsyncWriterImpl = requires(write_input_t W){
        {W.write_if_ready(char {})}->std::convertible_to<bool>;
        {W.write(char {})};
    };

    template <Scheduler scheduler_t,AsyncWriterImpl writer_impl_t,
    Guard guard_t,typename size_type = size_t>
    struct async_output_impl : sheduler_getter<scheduler_t>{
        writer_impl_t * m_writer;
        guard_t m_guard;
        char m_byte;
        const char * m_buf;
        size_type remain_bytes;
        struct coro_data{
            enum action_type:uint8_t{
                WRITE_BYTE = 0,
                WRITE_BYTES = 1
            };
            action_type action;
            std::coroutine_handle<> handle; 
        };
        optional<coro_data> m_waitor;
        async_output_impl(scheduler_t & m_shed,writer_impl_t & m_writer):
            sheduler_getter<scheduler_t>(m_shed),m_writer(&m_writer){}
        void interrupt(){
            //m_guard.lock();
            if(m_waitor){
                switch (m_waitor.value.action)
                {
                case coro_data::WRITE_BYTE:{
					m_writer->write(m_byte);
					auto m_handle = m_waitor.value.handle;
					m_waitor.reset();
					this->_get_sheduler().push_task(m_handle);
					break;
				}
                case coro_data::WRITE_BYTES:{
                    m_writer->write(*m_buf);
                    remain_bytes--;
                    if(!remain_bytes){
                        auto m_handle = m_waitor.value.handle;
                        m_waitor.reset();
                        this->_get_sheduler().push_task(m_handle);
                    }
                    ++m_buf;
                    break;
				}
                default:
                    break;
                }
            }
            //m_guard.unlock();
        }

        private:
        struct write_byte_awaitor{
            async_output_impl * m_input;
            char byte;
            bool success;
            inline write_byte_awaitor(async_output_impl & _input_impl,char byte):m_input(&_input_impl),byte(byte){
                m_input->m_guard.lock();
                if(m_input->m_writer->write_if_ready(byte)){
                    success = true;
                } else {
                    success = false;
                }
            }
            inline bool await_ready(){
                return success;
            }
            void await_resume(){
                if(success){
                    m_input->m_guard.unlock();
                }
            };
            inline void await_suspend(std::coroutine_handle<> h){
                m_input->m_waitor = {coro_data::WRITE_BYTE,h};
                m_input->m_byte = byte;
                
                m_input->m_guard.unlock();
            }

        };

        struct write_bytes_awaitor{
            async_output_impl * m_input;
            char const *bytes;
            size_type remain_bytes;
            bool success;
            inline write_bytes_awaitor(
                async_output_impl & _input_impl,char const *m_bytes,size_type n_bytes):m_input(&_input_impl){
                m_input->m_guard.lock();
                while(n_bytes && m_input->m_writer->write_if_ready(*m_bytes)){
                    n_bytes--;
                    m_bytes++;
                }
                if(n_bytes){
                    remain_bytes = n_bytes;
                    bytes = m_bytes;
                    success = false;
                }else{
                    success = true;
                }
                
            }
            inline bool await_ready(){
                return success;
            }
            void await_resume(){
                if(success){
                    m_input->m_guard.unlock();
                }
            };
            inline void await_suspend(std::coroutine_handle<> h){
                m_input->m_waitor = {coro_data::WRITE_BYTES,h};
                m_input->m_buf = bytes;
                m_input->remain_bytes = remain_bytes;
                
                m_input->m_guard.unlock();
            }

        };
        public:
        write_byte_awaitor WriteByte(char c){
            return write_byte_awaitor(*this,c);
        }
        write_bytes_awaitor WriteBytes(const char* S,size_type _size){
            return write_bytes_awaitor(*this,S,_size);
        }
		write_bytes_awaitor WriteBytes(const char* S){
			size_type i = 0;
			for(;S[i] != 0;++i){}
			return write_bytes_awaitor(*this,S,i);
		}
    };
};

#endif//ASYNC_IO_H