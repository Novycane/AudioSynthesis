/*
 *  AudioSynthesis.cpp
 *  AudioSynthesis
 *
 *  Created by Steven Novak on 3/7/17.
 *  Copyright © 2017 Steven Novak. All rights reserved.
 *
 */

#include <iostream>
#include "AudioSynthesis.hpp"
#include "AudioSynthesisPriv.hpp"

void AudioSynthesis::HelloWorld(const char * s)
{
    AudioSynthesisPriv *theObj = new AudioSynthesisPriv;
    theObj->HelloWorldPriv(s);
    delete theObj;
};

void AudioSynthesisPriv::HelloWorldPriv(const char * s) 
{
    std::cout << s << std::endl;
};

