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
    int used_questions_id[200][2] = {{0}};
    int ready_questions[200][2] = {{0}};
    Question question_ready = {0, 0, ""};
    auto_ptr<DBClientCursor> cursor = c.query( "studb.jj_instance_questions", BSONObj() );

    //Get all used questions
    int i=0, j;
    while( cursor->more() )
    {
        BSONObj p = cursor->next();
        used_questions_id[i][0] = p.getIntField( "classID" );
        used_questions_id[i][1] = p.getIntField( "subID" );
        i++;
    }

    //Build check question out query bson
    /* BSONArrayBuilder ba_used_classID; */
    /* BSONArrayBuilder ba_used_subID; */
    /* for(j=0; j<i; j++) */
    /* { */
    /*     ba_used_classID.append(used_questions_id[i][0]); */
    /*     ba_used_subID.append(used_questions_id[i][1]); */
    /* } */


    //Check questions out
    cursor = c.query( "studb.jj_questions", BSONObj()  );
    int used_questions_count = i;
    i=0;

    while( cursor->more() )
    {
        BSONObj p = cursor->next();
        ready_questions[i][0] = p.getIntField( "classID" );
        ready_questions[i][1] = p.getIntField( "subID" );
        for( j=0; j<used_questions_count; j++ )
        {
            if( ready_questions[i][0] == used_questions_id[j][0] && ready_questions[i][1] == used_questions_id[j][1] )
            {
                i--;
                j=used_questions_count;
            }
        }
        i++;
    }


    //Get a random question
    srand(time(0));
    int rand_question_count;
    if(i)
        rand_question_count = rand()%i;
    else
    {
        return question_ready;
    }
        
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
    int
postAns ( Question cur_question, bool ans )
{
    struct Ranker {
        int id, points;
    };
    Ranker top_ranker = {0, 0};
    Ranker second_ranker = {0, 0};
    int cur_question_ans_pool[300];
    int i=0, j;
    auto_ptr<DBClientCursor> q;
    q = c.query( "studb.jj_questions", BSON( "classID" << cur_question.classID << "subID" << cur_question.subID ) );
    //q = c.query( "studb.jj_questions", BSON( "classID" << 1 << "subID" << 1 ) );
    BSONObj b = q->next();
    vector<BSONElement> ans_array = b.getField("answer_pool").Array();

    size_t size_i=0;
    while ( size_i < ans_array.size() )
    {
        cur_question_ans_pool[i] = b.getField("answer_pool").Array()[i].numberInt();
        i++;
        ++size_i;
    }

    //Insert new stu in instance answer pool & build bson array
    BSONArrayBuilder ba;
    for( j=0; j<i; j++ )
    {
        ba.append( cur_question_ans_pool[j] );
    }

    //Update answer pool points
    if(ans)
    {
        c.update( "studb.jj_instance_answer_pool", BSON( "stuid" << BSON( "$in" <<  ba.arr() ) ), BSON( "$inc" << BSON( "points" << 10 ) ), 0, 1 );
    }
    else
    {
        c.update( "studb.jj_instance_answer_pool", BSON( "stuid" << BSON( "$in" <<  ba.arr() ) ), BSON( "$inc" << BSON( "points" << -10 ) ), 0, 1 );
    }

    //Check top rankers
    q =   c.query( "studb.jj_instance_answer_pool", Query(BSONObj()).sort("points", -1)  );
    BSONObj b_ranker;
    if( q->more() )
    {
        b_ranker = q->next();
        top_ranker.points = b_ranker.getIntField("points");
        top_ranker.id = b_ranker.getIntField("stuid");
    }
    if( q->more() )
    {
        b_ranker = q->next();
        second_ranker.points = b_ranker.getIntField("points");
        second_ranker.id = b_ranker.getIntField("stuid");
    }

    //cout << "[TOP]" <<top_ranker.id << " [UPCOMMING]" << second_ranker.id << endl;
    if( top_ranker.points - second_ranker.points >= 10 )
    {
        system("clear");
        cout << "我猜你是: ";
        cout << top_ranker.id << " - " << c.query( "studb.stuinfo", BSON( "_id" << top_ranker.id ) )->next().getStringField("name") << endl;
        puts("------------------------------------");
        cout << "以下同学和你特征相近：" << endl;
        cout << second_ranker.id << " - " << c.query( "studb.stuinfo", BSON( "_id" << second_ranker.id ) )->next().getStringField("name") << endl;
        cout << q->next().getIntField("stuid") << " - " << c.query( "studb.stuinfo", BSON( "_id" << q->next().getIntField("stuid") ) )->next().getStringField("name") << endl;
        cout << q->next().getIntField("stuid") << " - " << c.query( "studb.stuinfo", BSON( "_id" << q->next().getIntField("stuid") ) )->next().getStringField("name") << endl;
        puts("------------------------------------");
        return 1;
    }

    //Cast cur question into instance_questions
    /* if ( ans ) */
    /* { */
    /*     q = c.query ( "studb.jj_questions", BSON( "classID" << cur_question.classID ) ); */
    /*     BSONObj qbn; */
    /*     while(q->more()) */
    /*     { */
    /*         qbn = q->next(); */
    /*         if( ! c.query( "studb.jj_instance_questions", BSON( "classID" << cur_question.classID << "subID" << qbn.getIntField("subID") ))->more() ) */
    /*             c.insert( "studb.jj_instance_questions", BSON( "classID" << cur_question.classID << "subID" << qbn.getIntField("subID") ) ); */ 
    /*     } */
    /* } */
    /* else */
    /* { */
    /*     if( ! c.query( "studb.jj_instance_questions", BSON( "classID" << cur_question.classID << "subID" << cur_question.subID ) )->more() ) */
    /*         c.insert( "studb.jj_instance_questions", BSON( "classID" << cur_question.classID << "subID" << cur_question.subID ) ); */ 
    /* } */

    q = c.query ( "studb.jj_questions", BSON( "classID" << cur_question.classID ) );
    BSONObj qbn;
    while(q->more())
    {
        qbn = q->next();
        if( ! c.query( "studb.jj_instance_questions", BSON( "classID" << cur_question.classID << "subID" << qbn.getIntField("subID") ))->more() )
            c.insert( "studb.jj_instance_questions", BSON( "classID" << cur_question.classID << "subID" << qbn.getIntField("subID") ) ); 
    }

    return 0;

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
    cout << "connected." << endl;

    // Drop all the instance db collections
    c.DBClientWithCommands::dropCollection( "studb.jj_instance_questions" );
    c.DBClientWithCommands::dropCollection( "studb.jj_instance_answer_pool" );

    auto_ptr<DBClientCursor> p = c.query( "studb.stuinfo", BSONObj() );
    while(p->more())
    {
        c.insert("studb.jj_instance_answer_pool", BSON("stuid" << p->next().getIntField("_id") << "points" << 0 ));
    }


    Question question ;
    char answer;

    int i=1;
    while(true)
    {
        question = chkOutQuestion();
        system("clear");
        if( question.classID )
        {
            cout << "Judger | 判官" << endl;
            puts("");
            cout << "\t\tQ" << i << ". " << question.title << endl;
            cout << "\t\t" << "Y. 是" << "        " << "N. 否" << endl;
            cout << "\t\t" << "请作答： ";
        }
        else
        {
            cout << "Judger | 判官" << endl;
            puts("");
            cout << "\t\t" << "对不起，我猜不出你是谁，但是我认为你很可能是这些人中的一个：" << endl;
            auto_ptr<DBClientCursor> q = c.query( "studb.jj_instance_answer_pool", Query(BSONObj()).sort("points", -1)  );
            BSONObj b;
            int j=0;
            while( q->more() && j<3 )
            {
                b =  q->next();
                cout << "\t\t" << b.getIntField("stuid") << " - " << c.query( "studb.stuinfo", BSON( "_id" << b.getIntField("stuid") ) )->next().getStringField("name") << endl;
                j++;
            }
            return EXIT_SUCCESS;
        }

        while(true)
        {
            cin  >> answer;
            if ( answer >= 'a' )
                answer -= 32;

            if( answer=='Y' )
            {
                answer = 1;
                break;
            }
            else if( answer=='N' )
            {
                answer = 0;
                break;
            }
            else
            {
                cout << "输入错误，请重试: ";
            }
        }
        if(postAns( question, answer ))
            break;
        i++;
    }

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
