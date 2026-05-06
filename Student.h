#ifndef STUDENT_H
#define STUDENT_H

/*
 * Student.h
 * Represents a student taking the exam.
 * Stores personal details, submitted answers, and scores.
 */

#include <string>
#include <vector>
#include <map>
#include <iostream>

// ─── Submission: student's answer for one question ───────────────────────────
struct Submission {
    int         m_questionId;
    std::string m_code;          // Code written by student
    int         m_marksObtained;
    int         m_marksTotal;

    Submission(int qId, const std::string& code, int total);

    // Operator overloading: compare submissions by marks
    bool operator>(const Submission& other) const;
    bool operator<(const Submission& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Submission& sub);
};

// ─── Student class ────────────────────────────────────────────────────────────
class Student {
private:
    int                       m_rollNumber;
    std::string               m_name;
    std::string               m_section;
    std::vector<Submission>   m_submissions;
    int                       m_totalMarksObtained;
    int                       m_totalMarksPossible;

public:
    Student();
    Student(int rollNo, const std::string& name, const std::string& section);

    // Add a submission record
    void addSubmission(const Submission& sub);

    // Update marks for a specific submission
    void setMarks(int questionId, int marks);

    // Getters
    int         getRollNumber()       const { return m_rollNumber;          }
    std::string getName()             const { return m_name;                }
    std::string getSection()          const { return m_section;             }
    int         getTotalMarks()       const { return m_totalMarksObtained;  }
    int         getTotalPossible()    const { return m_totalMarksPossible;  }

    const std::vector<Submission>& getSubmissions() const { return m_submissions; }

    // Compute percentage
    double getPercentage() const;

    // Display full report card
    void displayReportCard() const;

    // Operator overloading: compare students by total marks
    bool operator>(const Student& other) const;
    bool operator<(const Student& other) const;
    bool operator==(const Student& other) const;

    // Prefix increment: add 5 grace marks
    Student& operator++();

    friend std::ostream& operator<<(std::ostream& os, const Student& s);
};

#endif // STUDENT_H
