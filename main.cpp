#include <iostream>
#include <string>
#include "codingQuestion.h"

using namespace std;


class Menu
{
public:
    void showTitle()
    {
        cout << "====================================\n";
        cout << "  C++ Exam Auto Evaluation System\n";
        cout << "====================================\n";
    }

    int getChoice()
    {
        int choice;

        cout << "\n1. Start Exam\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        return choice;
    }
};


class CodeInput
{
public:
    string takeCode()
    {
        string line;
        string code = "";

        cout << "\nEnter your C++ code below.\n";
        cout << "Type END to finish entering code.\n";

        cin.ignore();

        while (true)
        {
            getline(cin, line);

            if (line == "END")
            {
                break;
            }

            code = code + line + "\n";
        }

        return code;
    }
};

int main()
{
    Menu menu;
    CodeInput input;

    menu.showTitle();

    int choice = menu.getChoice();

    if (choice == 2)
    {
        cout << "\nProgram ended.\n";
        return 0;
    }

   
    Question* q1;

    q1 = new CodingQuestion(
        "Write a program to find factorial of a number.",
        10,
        "Loops",
        {"#include", "main", "for", "int", "cout"},
        "120"
    );

    cout << "\nStarting Exam...\n";

   
    q1->display();

    
    string studentCode;

    studentCode = input.takeCode();

    
    int marks;

    marks = q1->evaluate(studentCode);

    cout << "\n============================\n";
    cout << "Result\n";
    cout << "============================\n";

    cout << "Marks Obtained: "
         << marks
         << " / "
         << q1->getTotalMarks()
         << endl;

    
    delete q1;

    cout << "\nThank you for using the system.\n";

    return 0;
}
