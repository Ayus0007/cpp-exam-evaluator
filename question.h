#ifndef QUESTION_H
#define QUESTION_H

#include <iostream>
#include <string>

using namespace std;


class Question
{
protected:
    string questionText;
    int totalMarks;
    string topic;

public:

    Question(string text, int marks, string t)
    {
        questionText = text;
        totalMarks = marks;
        topic = t;
    }
    virtual ~Question()
    {
    }

    virtual void display() = 0;

    virtual int evaluate(string code) = 0;

 
    int getTotalMarks()
    {
        return totalMarks;
    }

    string getTopic()
    {
        return topic;
    }
};

#endif
