#ifndef process_HPP
#define process_HPP

enum class PState{
    END = 0,WORKING = 1,SLEEP = 2
};
struct abstract_process{
	PState m_state;
    virtual void work(){}
    PState state(){return m_state;}
    virtual ~abstract_process(){}
};

#endif