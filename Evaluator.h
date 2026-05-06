#ifndef EVALUATOR_H
#define EVALUATOR_H

/*
 * Evaluator.h
 * Abstract Base Class for the C++ Exam Evaluation System
 * Defines the interface for all evaluator types (polymorphism)
 */

#include <string>
#include <vector>
#include <map>
#include <stdexcept>

// ─── Abstract Base Class ──────────────────────────────────────────────────────
class Evaluator {
protected:
    std::string m_evaluatorName;
    int         m_totalMarks;
    int         m_passingMarks;

public:
    // Constructor
    Evaluator(const std::string& name, int totalMarks, int passingMarks);

    // Pure virtual functions → makes this an abstract class
    virtual int  evaluate(const std::string& studentCode)         = 0;
    virtual void displayCriteria()                          const  = 0;
    virtual std::string getEvaluatorType()                  const  = 0;

    // Non-pure virtual with default behavior
    virtual std::string getGrade(int marks) const;
    virtual void        printReport(const std::string& studentName,
                                    int marksObtained)     const;

    // Getters
    std::string getName()        const { return m_evaluatorName; }
    int         getTotalMarks()  const { return m_totalMarks;    }
    int         getPassingMarks()const { return m_passingMarks;  }

    // Operator Overloading: compare two evaluators by total marks
    bool operator>(const Evaluator& other) const;
    bool operator<(const Evaluator& other) const;
    bool operator==(const Evaluator& other) const;

    // Stream output operator (friend)
    friend std::ostream& operator<<(std::ostream& os, const Evaluator& ev);

    virtual ~Evaluator() = default;
};

#endif // EVALUATOR_H
