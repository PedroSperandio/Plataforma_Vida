#include <iostream>
#include "ThreadBase.h"
#include <cstdint>

ThreadBase::ThreadBase(){
    this->is_running=0;
    this->is_alive=0;
}
ThreadBase::~ThreadBase(){

}
void *ThreadBase::start(void *param){//A função retorna um ponteiro para a função que a thread executará
    ThreadBase *pto = (ThreadBase*) param;
    return(void*)(intptr_t)pto->run();
}
void ThreadBase::startActivity()//A thread é criada e um ponteiro é salvo no parametro "thread"
{
    int pt = pthread_create(&this->thread, NULL, this->start, (void*)this);//serve para verificar se a thread foi correntamente criada
    if(pt)
    {
        std::cerr << "Unable to create thread." << std::endl;
    }
}

void ThreadBase::stopActivity()
{
    if(this->is_alive)
    {
        this->is_alive = 0;
        this->tim3.tv_sec = 0;
        this->tim4.tv_nsec = 100000000L;

        while(this->is_running)
        {
            nanosleep(&this->tim3, &this->tim4);
        }
    }
    //espera a thread terminar um loop e assim para-la
    std::cout << "STOPPED THREAD ";
}