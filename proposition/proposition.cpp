/*
 * =====================================================================================
 *
 *       Filename:  proposition.cpp
 *
 *    Description:  The proposition for Kyuyu Judger.
 *
 *        Version:  1.0
 *        Created:  2014年11月24日 18时31分32秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Archie Lu (), chienius@outlook.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <stdlib.h>
#include "../include/mongo/client/dbclient.h"
using namespace mongo;


#define QUESTION_ID     "1.1"
#define QUESTION_QUERY  "{ name: /^.{3}$/ }"


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  createAnsPool
 *  Description:  Create answer pool for specified question.
 * =====================================================================================
 */
    void 
createAnsPool (int question_classID, int question_subID, string question_query, string question_title )
{
    DBClientConnection c;
    c.connect("localhost");
    std::cout << "connected." << endl;

    int count=0;
    int result[200] = {0};
    auto_ptr<DBClientCursor> cursor = c.query("studb.stuinfo", fromjson(question_query));
    while ( cursor -> more() ){
        BSONObj p = cursor -> next();
        result[count] = p.getIntField("_id");
        count ++;
    }
    std::cout << count << " results in all." << std::endl;
    std::cout << "Inserting results to the proposition colle..." << std:: endl;

    /* ## Insert results ## */

    BSONObjBuilder b;
    BSONArrayBuilder ba;

    b.append("classID", question_classID);
    b.append("subID", question_subID);
    b.append("title", question_title);

    int i;

    for ( i=0; result[i]>0; i++ ) {
        ba.append(result[i]);
    }

    b.append("answer_pool", ba.arr());

    c.insert("studb.jj_questions", b.obj());

    std::cout << question_classID << "-" << question_subID << " answer pool created." << std::endl;
    puts("");
    puts("");
}				/* ----------  end of function main  ---------- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  The main function of proposition.
 * =====================================================================================
 */
    int
main ( int argc, char *argv[] )
{
    struct Question {
        int classID, subID;
        string query, title;
    };

    Question q[45] = {
        {1, 1, "{ name: /^.{3}$/ }", "你的名字是三个字的吗？"},

        {2, 1, "{ hometown: { $in: [\"北京\", \"天津\", \"河北\", \"山西\", \"内蒙古\"] } }", "你的家乡在华北吗？"},
        {2, 2, "{ hometown: { $in: [\"陕西\", \"青海\", \"甘肃\", \"新疆\", \"宁夏\"] } }", "你的家乡在西北吗？"},
        {2, 3, "{ hometown: { $in: [\"黑龙江\", \"辽宁\", \"吉林\"] } }", "你的家乡在东北吗？"},
        {2, 4, "{ hometown: { $in: [\"江苏\", \"浙江\", \"安徽\", \"福建\", \"江西\", \"山东\", \"上海\"] } }", "你的家乡在华东吗？"},
        {2, 5, "{ hometown: { $in: [\"河南\", \"湖北\", \"湖南\"] } }", "你的家乡在华中吗？"},
        {2, 6, "{ hometown: { $in: [\"广东\", \"海南\", \"广西\", \"香港\", \"澳门\"] } }", "你的家乡在华南吗？"},
        {2, 7, "{ hometown: { $in: [\"重庆\", \"四川\", \"贵州\", \"云南\", \"西藏\"] } }", "你的家乡在西南吗？"},

        {3, 1, "{ hometown: { $in: [\"重庆\", \"上海\", \"北京\", \"天津\"] } }", "你的家乡在直辖市吗？"},

        {4, 1, "{ gender: \"M\" }", "你住在西南一楼吗？"},

        {5, 1, "{ $where: \"/^.{6}1996/i.test(this.citizen_id+'')\" }", "你出生于 1996 年吗？"},

        {6, 1, "{ $where: \"parseFloat((this.citizen_id+'').substr(10, 4)) >= 321 && parseFloat((this.citizen_id+'').substr(10, 4)) <= 420 \" }", "你的星座是 白羊座 吗？"},
        {6, 2, "{ $where: \"parseFloat((this.citizen_id+'').substr(10, 4)) >= 421 && parseFloat((this.citizen_id+'').substr(10, 4)) <= 520 \" }", "你的星座是 金牛座 吗？"},
        {6, 3, "{ $where: \"parseFloat((this.citizen_id+'').substr(10, 4)) >= 521 && parseFloat((this.citizen_id+'').substr(10, 4)) <= 621 \" }", "你的星座是 双子座 吗？"},
        {6, 4, "{ $where: \"parseFloat((this.citizen_id+'').substr(10, 4)) >= 622 && parseFloat((this.citizen_id+'').substr(10, 4)) <= 722 \" }", "你的星座是 巨蟹座 吗？"},
        {6, 5, "{ $where: \"parsefloat((this.citizen_id+'').substr(10, 4)) >= 723 && parsefloat((this.citizen_id+'').substr(10, 4)) <= 822 \" }", "你的星座是 狮子座 吗？"},
        {6, 6, "{ $where: \"parseFloat((this.citizen_id+'').substr(10, 4)) >= 823 && parseFloat((this.citizen_id+'').substr(10, 4)) <= 922 \" }", "你的星座是 处女座 吗？"},
        {6, 7, "{ $where: \"parseFloat((this.citizen_id+'').substr(10, 4)) >= 923 && parseFloat((this.citizen_id+'').substr(10, 4)) <= 1022 \" }", "你的星座是 天秤座 吗？"},
        {6, 8, "{ $where: \"parseFloat((this.citizen_id+'').substr(10, 4)) >= 1023 && parseFloat((this.citizen_id+'').substr(10, 4)) <= 1121 \" }", "你的星座是 天蝎座 吗？"},
        {6, 9, "{ $where: \"parseFloat((this.citizen_id+'').substr(10, 4)) >= 1122 && parseFloat((this.citizen_id+'').substr(10, 4)) <= 1221 \" }", "你的星座是 射手座 吗？"},
        {6, 10, "{ $where: \"parseFloat((this.citizen_id+'').substr(10, 4)) >= 1222 || parseFloat((this.citizen_id+'').substr(10, 4)) <= 119 \" }", "你的星座是 摩羯座 吗？"},
        {6, 11, "{ $where: \"parseFloat((this.citizen_id+'').substr(10, 4)) >= 120 && parseFloat((this.citizen_id+'').substr(10, 4)) <= 218 \" }", "你的星座是 水瓶座 吗？"},
        {6, 12, "{ $where: \"parseFloat((this.citizen_id+'').substr(10, 4)) >= 219 && parseFloat((this.citizen_id+'').substr(10, 4)) <= 320 \" }", "你的星座是 双鱼座 吗？"},

        {7, 1, "{ $where : \"this.mobile%10 == 1\" }", "你的手机尾号是 1 吗？"},
        {7, 2, "{ $where : \"this.mobile%10 == 2\" }", "你的手机尾号是 2 吗？"},
        {7, 3, "{ $where : \"this.mobile%10 == 3\" }", "你的手机尾号是 3 吗？"},
        {7, 4, "{ $where : \"this.mobile%10 == 4\" }", "你的手机尾号是 4 吗？"},
        {7, 5, "{ $where : \"this.mobile%10 == 5\" }", "你的手机尾号是 5 吗？"},
        {7, 6, "{ $where : \"this.mobile%10 == 6\" }", "你的手机尾号是 6 吗？"},
        {7, 7, "{ $where : \"this.mobile%10 == 7\" }", "你的手机尾号是 7 吗？"},
        {7, 8, "{ $where : \"this.mobile%10 == 8\" }", "你的手机尾号是 8 吗？"},
        {7, 9, "{ $where : \"this.mobile%10 == 9\" }", "你的手机尾号是 9 吗？"},
        {7, 10, "{ $where : \"this.mobile%10 == 0\" }", "你的手机尾号是 0 吗？"},

        {8, 1, "{ post: {$ne: \"\"} }", "你在班级中有职位吗？"},

        {9, 1, "{ gender: \"F\" };", "你是女生吗？"},

        {10, 1, "{ $where : \"this._id%10 == 1\" }", "你的学号尾号是 1 吗？"},
        {10, 2, "{ $where : \"this._id%10 == 2\" }", "你的学号尾号是 2 吗？"},
        {10, 3, "{ $where : \"this._id%10 == 3\" }", "你的学号尾号是 3 吗？"},
        {10, 4, "{ $where : \"this._id%10 == 4\" }", "你的学号尾号是 4 吗？"},
        {10, 5, "{ $where : \"this._id%10 == 5\" }", "你的学号尾号是 5 吗？"},
        {10, 6, "{ $where : \"this._id%10 == 6\" }", "你的学号尾号是 6 吗？"},
        {10, 7, "{ $where : \"this._id%10 == 7\" }", "你的学号尾号是 7 吗？"},
        {10, 8, "{ $where : \"this._id%10 == 8\" }", "你的学号尾号是 8 吗？"},
        {10, 9, "{ $where : \"this._id%10 == 9\" }", "你的学号尾号是 9 吗？"},
        {10, 10, "{ $where : \"this._id%10 == 0\" }", "你的学号尾号是 0 吗？"}

    };

    int i;
    for ( i=0; i<46; i++ ) {
        createAnsPool( q[i].classID, q[i].subID, q[i].query, q[i].title );
    }

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
