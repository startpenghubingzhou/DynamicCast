//
//  SQLFriend.hpp
//  DynamicCast
//
//  Created by penghubingzhou on 2021/5/18.
//  Copyright © 2021 penghubingzhou. All rights reserved.
//

#ifndef SQLFriend_hpp
#define SQLFriend_hpp

#include <stdio.h>
#include <sqlite3.h>
#include "Basedefs.h"

class SQLFriend {
 public:
    explicit SQLFriend(const char* path);

    ~SQLFriend();

    int readdata(int num, sqlfscore* data);

    int writedata(sqlfscore* data);

    int deletedata(int num);

    int getsize();

 private:
    sqlite3* ins;

    int size;
};

#endif /* SQLFriend_hpp */
