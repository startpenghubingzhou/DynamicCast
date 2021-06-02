//
//  SQLFriend.cpp
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

#include "SQLFriend.hpp"
#include <string.h>

SQLFriend::SQLFriend(const char* path) {
    int ret;
    int ncol, nrow;
    char** tmp;

    ret = sqlite3_open(path, &ins);

    if (ret) {
        funcprint("open database failed,  error: %s!\n", sqlite3_errmsg(ins));
        delete(this);
    }

    // get the number of cols from the database
    sqlite3_get_table(ins, "select count(*) from DriedFlowerData", &tmp, &nrow, &ncol, nullptr);

    sqlsize = atoi(tmp[nrow]);

    sqlite3_free_table(tmp);
}

SQLFriend::~SQLFriend() {
    sqlite3_close(ins);
}

int SQLFriend::readdata(int num, sqlfscore* data) {
    const char* based = "select * from DriedFlowerData where Number = %d";
    const char* exec;
    int ncol, nrow, ret = SQLF_OK;
    char** tmp;

    if (!data) {
        ret = SQLF_FAILED;
        goto read_result;
    }

    exec = sqlite3_mprintf(based, num);

    ret = sqlite3_get_table(ins, exec, &tmp, &nrow, &ncol, nullptr);

    if (ret != SQLITE_OK || nrow == 0) {
        ret = SQLF_FAILED;
        goto read_result;
    }

    // fill the sqldata field
    data->num = atoi(tmp[ncol]);
    strcpy(data->name, tmp[ncol + 1]);
    strcpy(data->time, tmp[ncol + 2]);
    data->score.browningscore = atof(tmp[ncol + 3]);
    data->score.fadescore = atof(tmp[ncol + 4]);
    data->score.transferredscore = atof(tmp[ncol + 5]);
    data->score.drytimescore = atof(tmp[ncol + 6]);
    data->score.finalscore = atof(tmp[ncol + 7]);
    data->score.grade = atof(tmp[ncol + 8]);

    // free the tmp field
    sqlite3_free_table(tmp);

read_result:
    return ret;
}

int SQLFriend::writedata(sqlfscore* data) {
    int ret = 0;
    const char* based = "insert into DriedFlowerData values (%d, '%s', '%s', %.3f, %.3f, %.3f, %.3f, %.3f, %d)";
    const char* exec;
    sqlfscore tmp;

    /* if data is null or already had data in database,
       the writting will failed.*/
    if (!data || readdata(data->num, &tmp) == SQLF_OK) {
        goto write_result;
    }

    exec = sqlite3_mprintf(based,
                           data->num,
                           data->name,
                           data->time,
                           data->score.browningscore,
                           data->score.fadescore,
                           data->score.transferredscore,
                           data->score.drytimescore,
                           data->score.finalscore,
                           data->score.grade);

    ret = sqlite3_exec(ins, exec, nullptr, nullptr, nullptr);

write_result:
    if (ret == 0) {
        sqlsize++;
    }

    return ret;
}

int SQLFriend::deletedata(int num) {
    int ret = SQLF_OK;
    const char* based = "delete from DriedFlowerData where Number = %d";
    const char* exec;
    sqlfscore* data;

    SAFEPOINTER(data, new sqlfscore, return SQLF_FAILED);

    ret = readdata(num, data);

    if (ret != SQLF_OK) {
        goto delete_result;
    }

    exec = sqlite3_mprintf(based, num);

    ret = sqlite3_exec(ins, exec, nullptr, nullptr, nullptr);

delete_result:
    SafeReleaseNULL(data);

    if (ret == 0) {
        sqlsize--;
    }

    return ret;
}

int SQLFriend::getsize() {
    return sqlsize;
}
