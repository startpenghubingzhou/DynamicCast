//
//  SQLFriend.hpp
//  DynamicCast
//
//  Created by penghubingzhou on 2021/5/18.
//  Copyright © 2021 penghubingzhou. All rights reserved.
//

/* BSD 3-Clause License
 
   Copyright (c) 2021, penghubingzhou
   All rights reserved.
 
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
 
   1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
 
   2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
 
   3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.
 
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SQLFriend_hpp
#define SQLFriend_hpp

#include <stdio.h>
#include <sqlite3.h>
#include "Basedefs.h"

/*!
 * @class SQLFriend
 *
 * @abstract The helper class to handle sql
 * data
 *
 * @discussion
 * This class is an helper class to process
 * sql data with sqlite3 library.
 */

class SQLFriend {
 public:
    /*!
     * @function SQLFriend
     *
     * @abstract
     * The constructor of SQLFriend, initializes
     * the function of the class
     *
     * @param path a const char that contained the file path of the db file.
     *
     * @discussion
     * This function will be executed automatically
     * as this class is created. This function will
     * call the API of sqlite3 to initialize the sql
     * db file and connect with the sql database
     */
    explicit SQLFriend(const char* path);

    /*!
     * @function ~SQLFriend
     *
     * @abstract
     * The destructor of SQLFriend, release all the
     * sources that the class uses
     */
    ~SQLFriend();

    /*!
     * @function readdata
     *
     * @abstract
     * read the data from the database of the
     * dried flowers
     *
     * @param num an integer of the number of a SQL query.
     * @param data a pointer of sqlfscore that will contain the score data.
     *
     * @discussion
     * This function will read the data from the database
     * and read the query with its number column
     *
     * @return the status code of SQLF_OK or error code
     */
    int readdata(int num, sqlfscore* data);

    /*!
     * @function writedata
     *
     * @abstract
     * write the data to the database of the
     * dried flowers
     *
     * @param data a pointer of sqlfscore that contain the score data
     * to write.
     *
     * @discussion
     * This function will check the data and try to write it
     * to the database. null data or exist number will return
     * failed.
     *
     * @return the status code of SQLF_OK or error code
     */
    int writedata(sqlfscore* data);

    /*!
     * @function deletedata
     *
     * @abstract
     * delete the data from the database with number column
     *
     * @param num an integer of the number of a SQL query.
     *
     * @discussion
     * This function will try to delete the query from the
     * database of the driedflowerdata. Not-exist data will
     * get failed.
     *
     * @return the status code of SQLF_OK or error code
     */
    int deletedata(int num);

    /*!
     * @function getsize
     *
     * @abstract
     * get the size of the queries
     *
     * @return the number of the queries
     */
    int getsize();

 private:
    sqlite3* ins;

    int sqlsize;
};

#endif /* SQLFriend_hpp */
