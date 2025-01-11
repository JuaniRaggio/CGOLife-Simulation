#pragma once

#define CHECK_ERRORS(expresion, msg)\
        do {\
            if ((expresion)) {\
                std::cout << "Assertion failed at line " << __LINE__ << " at file " << __FILE__ << msg;\
                std::terminate();\
            }\
        } while(0)

