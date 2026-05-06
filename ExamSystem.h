#ifndef EXAM_SYSTEM_H
#define EXAM_SYSTEM_H

/*
 * ExamSystem.h
 * Main orchestrator: manages questions, students, and evaluators.
 * Uses STL containers and ties all components together.
 */

#include "Question.h"
#include "Student.h"
#include "Evaluator.h"
#include "KeywordEvaluator.h"
#include "StructureEvaluator.h"
#include "ScoreCard.h"

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <stdexcept>

// ─── Custom Exceptions ────────────────────────────────────────────────────────
class ExamException : public std::runtime_error {
public:
    explicit ExamException(const std::string& msg)
        : std::runtime_error("[ExamError] " + msg) {}
};

class InvalidStudentException : public ExamException {
public:
    explicit InvalidStudentException(const std::string& msg)
        : ExamException("InvalidStudent: " + msg) {}
};

class QuestionNotFoundException : public ExamException {
public:
    explicit QuestionNotFoundException(int qId)
        : ExamException("Question ID " + std::to_string(qId) + " not found") {}
};

// ─── ExamSystem class ─────────────────────────────────────────────────────────
class ExamSystem {
private:
    std::string                          m_examTitle;
    std::vector<Question>                m_questions;
    std::vector<Student>                 m_students;
    std::map<int, std::vector<int>>      m_questionStudentMap; // qId → rollNos
    int                                  m_timeLimit;   // in minutes

    // Helper: find student by roll number
    Student* findStudent(int rollNo);
    const Student* findStudent(int rollNo) const;

    // Helper: find question by ID
    const Question* findQuestion(int qId) const;

    // Helper: display a separator line
    void printSeparator(char ch = '=', int len = 60) const;

    // Function overloading: evaluate submission
    int evaluateSubmission(const std::string& code,
                           const Question& q);

    int evaluateSubmission(const std::string& code,
                           const Question& q,
                           bool detailedOutput);

public:
    ExamSystem(const std::string& title, int timeLimitMinutes);

    // Setup
    void addQuestion(const Question& q);
    void registerStudent(const Student& s);

    // Exam flow
    void startExam();                               // interactive exam session
    void conductExamForStudent(int rollNo);         // run one student's exam
    void showLeaderboard() const;
    void showAllReports() const;
    void showStudentReport(int rollNo) const;
    void exportSummary() const;

    // Statistics using templates
    void showStatistics() const;

    int  getQuestionCount() const { return (int)m_questions.size(); }
    int  getStudentCount()  const { return (int)m_students.size();  }

    std::string getTitle()  const { return m_examTitle; }
};

#endif // EXAM_SYSTEM_H
