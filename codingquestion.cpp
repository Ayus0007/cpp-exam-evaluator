#include "codingQuestion.h"
#include <iostream>

using namespace std;


CodingQuestion::CodingQuestion(
    string text,
    int marks,
    string t,
    vector<string> keys,
    string output
) : Question(text, marks, t)
{
    keywords = keys;
    expectedOutput = output;
}


void CodingQuestion::display()
{
    cout << "\nTopic: " << topic << endl;
    cout << "Marks: " << totalMarks << endl;

    cout << "\nQuestion:\n";
    cout << questionText << endl;
}

int CodingQuestion::countKeywordMatches(string code)
{
    int count = 0;

    for (int i = 0; i < keywords.size(); i++)
    {
        if (code.find(keywords[i]) != string::npos)
        {
            count++;
        }
    }

    return count;
}

int CodingQuestion::evaluate(string code)
{
    try
    {
        int matches;

        matches = countKeywordMatches(code);

        int marks;

        marks = (matches * totalMarks) / keywords.size();

        if (marks > totalMarks)
        {
            marks = totalMarks;
        }

        return marks;
    }
    catch (...)
    {
        cout << "Error during evaluation.\n";
        return 0;
    }
}
