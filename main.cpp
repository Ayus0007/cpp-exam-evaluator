

#include "../include/ExamSystem.h"
#include "../include/ScoreCard.h"
#include <iostream>
#include <stdexcept>


static void loadQuestions(ExamSystem& exam) {

    
    Question q1(1,
        "Basic Input / Output",
        "Write a C++ program that takes the user's name as input "
        "and prints: Hello, <name>! using cin and cout.",
       
        "#include<iostream>\nusing namespace std;\n"
        "int main(){\n  string name;\n  cin>>name;\n"
        "  cout<<\"Hello, \"<<name<<\"!\";\n  return 0;\n}");

    q1.addStep("Include iostream header",      2, "#include");
    q1.addStep("Use namespace std",            1, "namespace std");
    q1.addStep("Declare main function",        2, "int main");
    q1.addStep("Declare string variable",      2, "string");
    q1.addStep("Read input using cin",         2, "cin");
    q1.addStep("Print output using cout",      2, "cout");
    q1.addStep("Return 0 from main",           1, "return 0");

    
    Question q2(2,
        "Array Sum Using For Loop",
        "Write a C++ program that declares an array of 5 integers, "
        "takes input for each element using a for loop, "
        "and prints their sum.",
        
        "#include<iostream>\nusing namespace std;\n"
        "int main(){\n  int arr[5], sum=0;\n"
        "  for(int i=0;i<5;i++){\n    cin>>arr[i];\n    sum+=arr[i];\n  }\n"
        "  cout<<\"Sum: \"<<sum;\n  return 0;\n}");

    q2.addStep("Include iostream",             1, "#include");
    q2.addStep("Declare integer array",        2, "int arr");
    q2.addStep("Declare sum variable",         2, "sum");
    q2.addStep("Use for loop",                 3, "for");
    q2.addStep("Read array elements via cin",  2, "cin");
    q2.addStep("Accumulate sum",               2, "sum+=");
    q2.addStep("Print result with cout",       2, "cout");
    q2.addStep("Return 0",                     1, "return 0");

    
    Question q3(3,
        "Factorial Using Function",
        "Write a C++ program that defines a function factorial(int n) "
        "which returns the factorial of n using a while loop. "
        "Call it from main and print the result.",
        
        "#include<iostream>\nusing namespace std;\n"
        "int factorial(int n){\n  int result=1;\n"
        "  while(n>0){ result*=n; n--; }\n  return result;\n}\n"
        "int main(){\n  int n;\n  cin>>n;\n"
        "  cout<<factorial(n);\n  return 0;\n}");

    q3.addStep("Define factorial function",    3, "factorial");
    q3.addStep("Function takes int parameter", 2, "int n");
    q3.addStep("Use while loop",               3, "while");
    q3.addStep("Compute product in loop",      2, "result");
    q3.addStep("Return value from function",   2, "return result");
    q3.addStep("Call function from main",      2, "factorial(n)");
    q3.addStep("Print output",                 1, "cout");

    exam.addQuestion(q1);
    exam.addQuestion(q2);
    exam.addQuestion(q3);
}


static void loadStudents(ExamSystem& exam) {
    exam.registerStudent(Student(101, "Aryan Sharma",   "CS-A"));
    exam.registerStudent(Student(102, "Priya Verma",    "CS-A"));
    exam.registerStudent(Student(103, "Rohan Mehta",    "CS-B"));
    exam.registerStudent(Student(104, "Sneha Kapoor",   "CS-B"));
    exam.registerStudent(Student(105, "Kabir Singh",    "CS-C"));
}


static void demonstrateTemplates() {
    std::cout << "\n  ── Template Demo ────────────────────────────────\n";

   
    ScoreCard<int> sc("Demo Student");
    sc.addScore("Q1", 8);
    sc.addScore("Q2", 12);
    sc.addScore("Q3", 10);
    sc.display();

    
    ScoreCard<double> sc2("Weighted Scores");
    sc2.addScore("Code Quality", 8.5);
    sc2.addScore("Efficiency",   7.0);
    sc2.addScore("Correctness",  9.5);
    sc2.display();

    
    std::vector<int> scores = {45, 78, 92, 60, 55};
    std::cout << "\n  Max Score    : " << findMax(scores)       << "\n";
    std::cout << "  Min Score    : " << findMin(scores)       << "\n";
    std::cout << "  Avg Score    : " << computeAverage(scores) << "\n";

    
    int raw = 105;
    std::cout << "  Clamped(105) : " << clamp(raw, 0, 100) << "\n";

    // Operator overloading on ScoreCard (merge)
    ScoreCard<int> scA("A"), scB("B");
    scA.addScore("Part1", 5);
    scB.addScore("Part2", 7);
    ScoreCard<int> merged = scA + scB;
    std::cout << "  " << merged << "\n";

    std::cout << "  ────────────────────────────────────────────────\n";
}


static void demonstratePolymorphism() {
    std::cout << "\n  ── Polymorphism Demo ────────────────────────────\n";

    Question demoQ(99, "Demo", "Demo question.", "");
    demoQ.addStep("Declare variable", 3, "int");
    demoQ.addStep("Print output",     3, "cout");

    
    Evaluator* ev1 = new KeywordEvaluator(&demoQ);
    Evaluator* ev2 = new StructureEvaluator(10, 5, 2);

    std::cout << "  Evaluator 1 type: " << ev1->getEvaluatorType() << "\n";
    std::cout << "  Evaluator 2 type: " << ev2->getEvaluatorType() << "\n";

    
    std::cout << "  ev1 > ev2? "
              << (*ev1 > *ev2 ? "Yes" : "No") << "\n";

    std::string sampleCode =
        "int main(){\n  int x = 5;\n  cout << x;\n  return 0;\n}\n";

    std::cout << "\n  Running both evaluators on sample code:\n";
    ev1->evaluate(sampleCode);
    ev2->evaluate(sampleCode);

    delete ev1;
    delete ev2;

    std::cout << "  ────────────────────────────────────────────────\n";
}


int main() {
    std::cout << "\n";
    std::cout << "  ╔══════════════════════════════════════════════════════╗\n";
    std::cout << "  ║       C++ EXAM EVALUATOR — OOP PROJECT               ║\n";
    std::cout << "  ║   Step-wise Code Evaluation System (Paper Pattern)   ║\n";
    std::cout << "  ╚══════════════════════════════════════════════════════╝\n";

    try {
       
        demonstrateTemplates();
        demonstratePolymorphism();

        
        ExamSystem exam("Mid-Semester C++ Programming Exam", 120);

        loadQuestions(exam);
        loadStudents(exam);

        std::cout << "\n  System loaded: "
                  << exam.getQuestionCount() << " questions, "
                  << exam.getStudentCount()   << " students.\n";

        
        exam.startExam();

    } catch (const ExamException& e) {
        std::cerr << "\n  [FATAL Exam Error] " << e.what() << "\n";
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "\n  [FATAL Error] " << e.what() << "\n";
        return 1;
    }

    return 0;
}
