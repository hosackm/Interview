//
//  delayline_tests.cpp
//  DelayWithMeter
//
//  Created by Hosack, Matthew on 7/20/15.
//
//

#define GTESTING

#include <gtest/gtest.h>
#include "DelayLine.h"

class DelayLineZeroFix : public testing::Test {
public:
    virtual void SetUp() {
        /* Max Delay of 1 sec @ 48 kHz sampling rate */
        line = new DelayLine<float>(1000, 48000);
    }
    virtual void TearDown() {
        
    }
    DelayLine<float> *line;
};

TEST_F(DelayLineZeroFix, EmptyDelayLine)
{
    EXPECT_EQ(0, line->size());
}

TEST_F(DelayLineZeroFix, NoDelayEqualIndeces)
{
    float out;
    EXPECT_EQ(line->getRead(), line->getWrite());
    line->push(1.0f);
    line->pop(out);
    EXPECT_EQ(line->getRead(), line->getWrite());
    line->push(1.0f);
    line->push(1.0f);
    line->pop(out);
    EXPECT_NE(line->getRead(), line->getWrite());
    line->pop(out);
    EXPECT_EQ(line->getRead(), line->getWrite());
}

TEST_F(DelayLineZeroFix, PushOnePopOne)
{
    float out;
    line->push(1.0);
    line->push(1.0);
    line->pop(out);
    EXPECT_EQ(1.0, out);
}

TEST_F(DelayLineZeroFix, HalfSecondDelay)
{
    /* 500 ms == 24000 sample delay @ 48 kHz SR */
    line->setDelay(500);

    EXPECT_NE(line->getRead(), line->getWrite());
    /* + length to account for buffer wrap around */
    EXPECT_EQ(line->getRead(), line->getWrite() + line->getLength() - 24000);
}

TEST_F(DelayLineZeroFix, UpdateToQuarterSecondDelay)
{
    /* 500 ms == 24000 sample delay @ 48 kHz SR */
    line->setDelay(500);
    
    EXPECT_NE(line->getRead(), line->getWrite());
    /* + length to account for buffer wrap around */
    EXPECT_EQ(line->getRead(), line->getWrite() + line->getLength() - 24000);

    /* 250 ms == 12000 sample delay @ 48 kHz SR */
    line->setDelay(250);
    
    EXPECT_NE(line->getRead(), line->getWrite());
    /* + length to account for buffer wrap around */
    EXPECT_EQ(line->getRead(), line->getWrite() + line->getLength() - 12000);
}

TEST_F(DelayLineZeroFix, AddSamplesNoDelay)
{
    float samps[] = {1., 2., 3., 4., 5.};
    float out[5];
    line->addSamples(samps, 5);
    line->getSamples(out, 5);
    for(int i = 0; i < 5; ++i)
        EXPECT_EQ(samps[i], out[i]);
}

TEST_F(DelayLineZeroFix, AddSamplesWithDelay)
{
    /* 2400 sample delay */
    line->setDelay(500);
    float samps[] = {1., 2., 3., 4., 5.};
    float out[5];
    line->addSamples(samps, 5);
    
    /* Pop Half a second worth manually */
    for(int i = 0; i < 24000; ++i)
        line->pop(out[0]);
    
    /* The next 5 samples should match the input */
    line->getSamples(out, 5);
    for(int i = 0; i < 5; ++i)
        EXPECT_EQ(samps[i], out[i]);
}
