//
//  DelayLine.h
//  DelayWithMeter
//
//  Created by Hosack, Matthew on 7/20/15.
//
//

#ifndef DelayWithMeter_DelayLine_h
#define DelayWithMeter_DelayLine_h

#include <cstring>
#include <boost/atomic/atomic.hpp>

template <class T>
class DelayLine
{
private:
    T *p_buf;

protected:
    size_t length;
    size_t maxlength;
    boost::atomic<unsigned int> read;
    boost::atomic<unsigned int> write;
    float SR;

public:

    DelayLine(long maxMillis, float _SR) {
        maxlength = (int)(maxMillis * _SR / 1000.) + 1;
        length = maxlength;
        SR = _SR;
        p_buf = new T[length + 1];
        read = write = 0;
        memset(p_buf, 0, sizeof(T) * (length + 1));
    }

    DelayLine() {
        delete [] p_buf;
    }

    int push(const T input) {
        p_buf[write++] = input;
        if(write >= length)
            write -= (int)length;
        
        if (write == read)
            read++;
        
        return 0;
    }
    
    int pop(T &output) {
        output = p_buf[read++];
        if(read >= length)
            read -= (int)length;
        
        return 0;
    }
    
    /* Helper functions */
    bool isEmpty() {
        return this->size() == 0;
    }
    size_t available() {
        return length - 1 - this->size();
    }
    size_t size() {
        return (read > write) ? (write + (int)length) - read : write - read;
    }
    
    void setDelay(const unsigned millis) {
        const unsigned long samps = millis * SR / 1000;
        read = (samps > write) ? length - (samps - write): write - samps;
    }
    
    void addSamples(const T *input, const unsigned numSamples)
    {
        for(int i = 0; i < numSamples; ++i)
            this->push(input[i]);
    }
    
    void getSamples(T *output, const unsigned numSamples)
    {
        float tmp;
        for(int i = 0; i < numSamples; ++i)
        {
            this->pop(tmp);
            output[i] = tmp;
        }
    }

/* Only for testing */
#ifdef GTESTING
    unsigned getRead()
    {
        return read;
    }

    unsigned getWrite()
    {
        return write;
    }
    size_t getLength()
    {
        return length;
    }
#endif
};

#endif
