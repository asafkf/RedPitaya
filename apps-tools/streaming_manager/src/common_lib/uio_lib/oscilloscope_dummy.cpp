#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include "oscilloscope.h"
#include <stdio.h>
#include <string.h>

using namespace uio_lib;

auto COscilloscope::create(const UioT &,uint32_t _dec_factor,bool _isMaster,uint32_t _adcMaxSpeed) -> COscilloscope::Ptr {
    return std::make_shared<COscilloscope>(0, nullptr, 0, nullptr, 0, 0,_dec_factor,_isMaster,_adcMaxSpeed);
}

COscilloscope::COscilloscope(int _fd, void *_regset, size_t _regsetSize, void *_buffer, size_t _bufferSize, uintptr_t _bufferPhysAddr,uint32_t _dec_factor,bool _isMaster,uint32_t _adcMaxSpeed) :
    m_Fd(_fd),
    m_Regset(_regset),
    m_RegsetSize(_regsetSize),
    m_Buffer(_buffer),
    m_BufferSize(_bufferSize),
    m_BufferPhysAddr(_bufferPhysAddr),
    m_OscMap(nullptr),
    m_OscBuffer1(nullptr),
    m_OscBuffer2(nullptr),
    m_OscBufferNumber(0),
    m_dec_factor(_dec_factor),
    m_filterBypass(true),
    m_isMaster(_isMaster),
    m_adcMaxSpeed(_adcMaxSpeed)
{    
    m_OscBuffer1 = new uint8_t[osc_buf_size];
    m_OscBuffer2 = new uint8_t[osc_buf_size];
    for(auto i = 0u ; i < osc_buf_size; i++){
        m_OscBuffer1[i] = i % 255;
        m_OscBuffer2[i] = 255- i % 255;
    }
}

COscilloscope::~COscilloscope(){
    delete[] m_OscBuffer1;
    delete[] m_OscBuffer2;
}

void COscilloscope::setReg(volatile OscilloscopeMapT *){}

void COscilloscope::setFilterCalibrationCh1(int32_t ,int32_t , int32_t , int32_t ){}

void COscilloscope::setFilterCalibrationCh2(int32_t ,int32_t , int32_t , int32_t ){}

void COscilloscope::setFilterBypass(bool){}

auto COscilloscope::prepare() -> void{}

auto COscilloscope::setCalibration(int32_t,float, int32_t, float) -> void{}

auto COscilloscope::next(uint8_t *&_buffer1,uint8_t *&_buffer2, size_t &_size,uint32_t &_overFlow) -> bool {
    _buffer1 = m_OscBuffer1;
    _buffer2 = m_OscBuffer2;
    _overFlow = 0;
    _size = osc_buf_size;
    return true;
}

auto COscilloscope::getDecimation() -> uint32_t {
    return m_dec_factor;
}

auto COscilloscope::getOSCRate() -> uint32_t{
    return m_dec_factor;
}

auto COscilloscope::clearBuffer() -> bool{
    return true;
}

auto COscilloscope::wait() -> bool{
    return true;
}

auto COscilloscope::clearInterrupt() -> bool{
    return true;
}

auto COscilloscope::stop() -> void{}

auto COscilloscope::printReg() -> void{}

auto COscilloscope::set8BitMode(bool) -> void{}
