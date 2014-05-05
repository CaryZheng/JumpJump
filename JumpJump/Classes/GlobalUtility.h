//
//  GlobalUtility.h
//  JumpJump
//
//  Created by Cary Zheng on 14-3-27.
//
//

#ifndef __JumpJump__GlobalUtility__
#define __JumpJump__GlobalUtility__

#include <sstream>

class GlobalUtility
{
public:
    template<typename T>
    static std::string toString(const T& value)
    {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }
};

#endif /* defined(__JumpJump__GlobalUtility__) */
