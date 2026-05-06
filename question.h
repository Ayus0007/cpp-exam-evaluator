#ifndef QUESTION_H
#define QUESTION_H

/*
 * Question.h
 * Represents a coding question given to the student.
 * Stores the question text, expected keywords, and step-wise marks.
 */

#include <string>
#include <vector>
#include <map>
#include <iostream>

// ─── Step: represents a markable step in a question ──────────────────────────
struct Step {
    std::string m_description;   // e.g., "Declared variables"
    int         m_marks;         // marks awarded for this step
    std::string m_keyword;       // keyword to check in student's code

    Step(const std::string& desc, int marks, const std::string& keyword);

    // Operator overloading: add two steps' marks
    Step operator+(const Step& other) const;
    bool operator==(const Step& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Step& s);
};

// ─── Question class ───────────────────────────────────────────────────────────
class Question {
private:
    int                  m_questionId;
    std::string          m_title;
    std::string          m_description;
    std::vector<Step>    m_steps;
    int                  m_totalMarks;
    std::string          m_sampleSolution;

public:
    Question();
    Question(int id, const std::string& title,
             const std::string& description,
             const std::string& sampleSolution);

    // Add a step to this question
    void addStep(const Step& step);
    void addStep(const std::string& desc, int marks, const std::string& kw);  // overload

    // Getters
    int                       getId()           const { return m_questionId;    }
    std::string               getTitle()        const { return m_title;         }
    std::string               getDescription()  const { return m_description;   }
    std::string               getSampleSolution()const{ return m_sampleSolution;}
    const std::vector<Step>&  getSteps()        const { return m_steps;         }
    int                       getTotalMarks()   const { return m_totalMarks;    }

    // Display question to student
    void display() const;

    // Operator overloading
    bool operator==(const Question& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Question& q);
};

#endif // QUESTION_H
