/*
 * =====================================================================================
 *
 *       Filename:  judger.cpp
 *
 *    Description:  Kyuyu Judger
 *
 *        Version:  1.0
 *        Created:  2014年11月24日 21时08分12秒
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

DBClientConnection c;

struct Question 
{
    int classID, subID;
    string title;
};

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  chkOutQuestion
 *  Description:  
 * =====================================================================================
 */
    Question
chkOutQuestion ()
{
    OID used_questions_id[50];
    int ready_questions[50][2] = {{0}};
    Question question_ready;
    auto_ptr<DBClientCursor> cursor = c.query( "studb.jj_instance_questions", BSONObj() );

    //Get all used questions
    int i=0, j;
    while( cursor->more() )
    {
        BSONObj p = cursor->next();
        used_questions_id[i] = p.getField( "_id" ).OID();
        i++;
    }

    //Build check question out query bson
    BSONArrayBuilder ba_used_id;
    for(j=0; j<i; j++)
    {
        ba_used_id.append(used_questions_id[i]);
    }
    BSONObjBuilder b;
    b.append( "_id", (BSON ("$nin" << ba_used_id.arr())) );

    //Check questions out
    cursor = c.query( "studb.jj_questions", b.obj()  );
    i=0;
    while( cursor->more() )
    {
        BSONObj p = cursor->next();
        ready_questions[i][0] = p.getIntField( "classID" );
        ready_questions[i][1] = p.getIntField( "subID" );
        i++;
    }

    //Get a random question
    srand(time(0));
    int rand_question_count = rand()%i;

    question_ready.classID = ready_questions[rand_question_count][0];
    question_ready.subID = ready_questions[rand_question_count][1];

    BSONObjBuilder b1;
    b1.append( "classID", question_ready.classID );
    b1.append( "subID", question_ready.subID );

    //Check out the question title 
    question_ready.title = c.query( "studb.jj_questions", b1.obj() ) -> next().getStringField( "title" );
    
    return question_ready;
}		/* -----  end of function chkOutQuestion  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  postAns
 *  Description:  
 * =====================================================================================
 */
    void
postAns ( Question cur_question, bool ans )
{
    if(ans)
    {
        
    }
    else
    {
        
    }

}		/* -----  end of function postAns  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
    int
main ()
{
    c.connect("localhost");
    std::cout << "connected." << endl;

    // Drop all the instance db collections
    c.DBClientWithCommands::dropCollection( "studb.jj_instance_questions" );
    c.DBClientWithCommands::dropCollection( "studb.jj_instance_answer_pool" );

    Question question ;
    char answer;

    question = chkOutQuestion();
    system("clear");
    cout << "Jundger | 判官" << endl;
    puts("");
    cout << "\t\tQ1. " << question.title << endl;
    cout << "\t\t" << "Y. 是" << "        " << "N. 否" << endl;
    cout << "\t\t" << "请作答： ";
    cin  >> answer;



    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
