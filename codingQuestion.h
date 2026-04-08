#ifndef CODINGQUESTION_H
#define CODINGQUESTION_H

#include "question.h"
#include <vector>

using namespace std;

class CodingQuestion : public Question
{
private:
    vector<string> keywords;
    string expectedOutput;

public:
    
    CodingQuestion(
        string text,
        int marks,
        string topic,
        vector<string> keys,
        string output
    );

   
    void display();

    int evaluate(string code);

  
    int countKeywordMatches(string code);
};

#endif
