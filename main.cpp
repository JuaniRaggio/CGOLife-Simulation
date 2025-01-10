#include <exception>
#include <iostream>
#include <SDL2/SDL.h>

#define CHECK_ERRORS(expresion)\
        do {\
            if ((expresion)) {\
                std::cout << "Assertion failed at line " << __LINE__ << " at file " << __FILE__ << std::endl;\
                std::terminate();\
            }\
        } while(0)

int main(void) {
    std::cout << "Hello world!" << std::endl;
    CHECK_ERRORS(true);
    std::cout << "Hey!" << std::endl;
}

