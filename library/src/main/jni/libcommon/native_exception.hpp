//
// Created by ben622 on 2019/9/16.
//

#ifndef NATIVEGPUIMAGE_NEXCEPTION_HPP
#define NATIVEGPUIMAGE_NEXCEPTION_HPP
#include<exception>
#include<iostream>
using namespace std;

namespace ben{
    namespace common{
        class NException : public exception{
        public:
            NException() {}
            NException(char *msg) {}

        };
    }
}
#endif //NATIVEGPUIMAGE_NEXCEPTION_HPP
