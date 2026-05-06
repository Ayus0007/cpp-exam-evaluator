/*
 * ExamSystem.cpp
 * Implementation of ExamSystem: manages the full exam lifecycle.
 */

#include "../include/ExamSystem.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <limits>

// ─── Constructor ──────────────────────────────────────────────────────────────
ExamSystem::ExamSystem(const std::string& title, int timeLimitMinutes)
    : m_examTitle(title), m_timeLimit(timeLimitMinutes)
{
    if (title.empty())
        throw ExamException("Exam title cannot be empty.");
    if (timeLimitMinutes <= 0)
        throw ExamException("Time limit must be positive.");
}

// ─── Helpers ──────────────────────────────────────────────────────────────────
void ExamSystem::printSeparator(char ch, int len) const {
    std::cout << "\n  " << std::string(len, ch) << "\n";
}

Student* ExamSystem::findStudent(int rollNo) {
    for (auto& s : m_students)
        if (s.getRollNumber() == rollNo) return &s;
    return nullptr;
}

const Student* ExamSystem::findStudent(int rollNo) const {
    for (const auto& s : m_students)
        if (s.getRollNumber() == rollNo) return &s;
    return nullptr;
}

const Question* ExamSystem::findQuestion(int qId) const {
    for (const auto& q : m_questions)
        if (q.getId() == qId) return &q;
    return nullptr;
}

// ─── Setup ────────────────────────────────────────────────────────────────────
void ExamSystem::addQuestion(const Question& q) {
    for (const auto& existing : m_questions)
        if (existing.getId() == q.getId())
            throw ExamException("Duplicate question ID: " + std::to_string(q.getId()));
    m_questions.push_back(q);
}

void ExamSystem::registerStudent(const Student& s) {
    for (const auto& existing : m_students)
        if (existing.getRollNumber() == s.getRollNumber())
            throw InvalidStudentException("Duplicate roll number: " +
                                          std::to_string(s.getRollNumber()));
    m_students.push_back(s);
}

// ─── evaluateSubmission (overload 1) ─────────────────────────────────────────
int ExamSystem::evaluateSubmission(const std::string& code, const Question& q) {
    return evaluateSubmission(code, q, true);
}

// ─── evaluateSubmission (overload 2: with output flag) ────────────────────────
int ExamSystem::evaluateSubmission(const std::string& code,
                                    const Question& q, bool detailedOutput) {
    // Run both evaluators (polymorphism in action)
    KeywordEvaluator   kEval(&q);
    StructureEvaluator sEval(q.getTotalMarks(), q.getTotalMarks() / 2, 3);

    sEval.addPattern("for loop",    "for",    2);
    sEval.addPattern("while loop",  "while",  2);
    sEval.addPattern("if condition","if",     1);
    sEval.addPattern("cout/print",  "cout",   1);

    int kMarks = 0, sMarks = 0;

    try {
        kMarks = kEval.evaluate(code);
    } catch (const std::exception& e) {
        std::cout << "  [Warning] Keyword eval failed: " << e.what() << "\n";
    }

    try {
        sMarks = sEval.evaluate(code);
    } catch (const std::exception& e) {
        std::cout << "  [Warning] Structure eval failed: " << e.what() << "\n";
    }

    // Combine: 70% keyword + 30% structure
    int combined = static_cast<int>(0.7 * kMarks + 0.3 * sMarks);
    combined = std::min(combined, q.getTotalMarks());

    if (detailedOutput) {
        std::cout << "\n  ── Combined Score ──────────────────────\n";
        std::cout << "  Keyword Score    : " << kMarks << "\n";
        std::cout << "  Structure Score  : " << sMarks << "\n";
        std::cout << "  Combined (70/30) : " << combined
                  << "/" << q.getTotalMarks() << "\n";
        std::cout << "  ────────────────────────────────────────\n";
    }

    return combined;
}

// ─── conductExamForStudent ────────────────────────────────────────────────────
void ExamSystem::conductExamForStudent(int rollNo) {
    Student* student = findStudent(rollNo);
    if (!student)
        throw InvalidStudentException("Roll No " + std::to_string(rollNo) +
                                      " not registered.");

    printSeparator('=');
    std::cout << "\n  Welcome, " << student->getName()
              << " (Roll: " << rollNo << ")\n";
    std::cout << "  Exam: " << m_examTitle << "\n";
    printSeparator('-');

    for (const auto& q : m_questions) {
        // Display question
        q.display();

        // Collect student code
        std::cout << "  Enter your C++ code below.\n";
        std::cout << "  (Type 'END' on a new line when done)\n\n";
        std::cout << "  > ";

        std::string code, line;
        while (std::getline(std::cin, line)) {
            if (line == "END") break;
            code += line + "\n";
        }

        if (code.empty()) {
            std::cout << "  [!] No code submitted for this question.\n";
            Submission sub(q.getId(), code, q.getTotalMarks());
            sub.m_marksObtained = 0;
            student->addSubmission(sub);
            student->setMarks(q.getId(), 0);
            continue;
        }

        // Evaluate
        int marks = 0;
        try {
            marks = evaluateSubmission(code, q, true);
        } catch (const ExamException& e) {
            std::cout << "  [ExamError] " << e.what() << "\n";
        } catch (const std::exception& e) {
            std::cout << "  [Error] " << e.what() << "\n";
        }

        // Store submission
        Submission sub(q.getId(), code, q.getTotalMarks());
        student->addSubmission(sub);
        student->setMarks(q.getId(), marks);

        // Use polymorphism to print report via base class pointer
        Evaluator* evalPtr = new KeywordEvaluator(&q);
        evalPtr->printReport(student->getName(), marks);
        delete evalPtr;

        printSeparator('-');
    }

    std::cout << "\n  Exam complete for " << student->getName() << "!\n";
    student->displayReportCard();
}

// ─── startExam (interactive menu) ────────────────────────────────────────────
void ExamSystem::startExam() {
    if (m_questions.empty())
        throw ExamException("No questions loaded. Cannot start exam.");
    if (m_students.empty())
        throw ExamException("No students registered. Cannot start exam.");

    printSeparator('=');
    std::cout << "\n  ★  " << m_examTitle << "  ★\n";
    std::cout << "  Total Questions: " << m_questions.size() << "\n";
    std::cout << "  Time Limit     : " << m_timeLimit << " minutes\n";
    printSeparator('=');

    bool running = true;
    while (running) {
        std::cout << "\n  MAIN MENU\n";
        std::cout << "  1. Start My Exam\n";
        std::cout << "  2. View Questions\n";
        std::cout << "  3. View Leaderboard\n";
        std::cout << "  4. View All Reports\n";
        std::cout << "  5. View Statistics\n";
        std::cout << "  0. Exit\n";
        std::cout << "  Choice: ";

        int choice = 0;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        try {
            switch (choice) {
                case 1: {
                    std::cout << "  Enter your Roll Number: ";
                    int rollNo;
                    std::cin >> rollNo;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    conductExamForStudent(rollNo);
                    break;
                }
                case 2:
                    for (const auto& q : m_questions) q.display();
                    break;
                case 3:
                    showLeaderboard();
                    break;
                case 4:
                    showAllReports();
                    break;
                case 5:
                    showStatistics();
                    break;
                case 0:
                    running = false;
                    std::cout << "  Exiting exam system. Goodbye!\n";
                    break;
                default:
                    std::cout << "  Invalid choice. Try again.\n";
            }
        } catch (const InvalidStudentException& e) {
            std::cout << "  [Student Error] " << e.what() << "\n";
        } catch (const QuestionNotFoundException& e) {
            std::cout << "  [Question Error] " << e.what() << "\n";
        } catch (const ExamException& e) {
            std::cout << "  [Exam Error] " << e.what() << "\n";
        } catch (const std::exception& e) {
            std::cout << "  [Error] " << e.what() << "\n";
        }
    }
}

// ─── showLeaderboard ─────────────────────────────────────────────────────────
void ExamSystem::showLeaderboard() const {
    if (m_students.empty()) {
        std::cout << "  No students registered.\n";
        return;
    }

    // Copy and sort using operator> (operator overloading)
    std::vector<Student> sorted = m_students;
    std::sort(sorted.begin(), sorted.end(),
              [](const Student& a, const Student& b) { return a > b; });

    printSeparator('=');
    std::cout << "\n  LEADERBOARD — " << m_examTitle << "\n";
    printSeparator('-');
    std::cout << "  " << std::left
              << std::setw(5)  << "Rank"
              << std::setw(10) << "Roll"
              << std::setw(20) << "Name"
              << std::setw(10) << "Marks"
              << std::setw(10) << "Percent" << "\n";
    printSeparator('-');

    int rank = 1;
    for (const auto& s : sorted) {
        std::cout << "  " << std::left
                  << std::setw(5)  << rank++
                  << std::setw(10) << s.getRollNumber()
                  << std::setw(20) << s.getName()
                  << std::setw(10) << s.getTotalMarks()
                  << std::setw(9)  << (int)s.getPercentage() << "%\n";
    }
    printSeparator('=');
}

// ─── showAllReports ───────────────────────────────────────────────────────────
void ExamSystem::showAllReports() const {
    if (m_students.empty()) {
        std::cout << "  No student data available.\n";
        return;
    }
    for (const auto& s : m_students)
        s.displayReportCard();
}

// ─── showStudentReport ────────────────────────────────────────────────────────
void ExamSystem::showStudentReport(int rollNo) const {
    const Student* s = findStudent(rollNo);
    if (!s) throw InvalidStudentException("Roll No " + std::to_string(rollNo));
    s->displayReportCard();
}

// ─── showStatistics (uses templates from ScoreCard.h) ─────────────────────────
void ExamSystem::showStatistics() const {
    if (m_students.empty()) {
        std::cout << "  No data for statistics.\n";
        return;
    }

    std::vector<int> allMarks;
    for (const auto& s : m_students)
        allMarks.push_back(s.getTotalMarks());

    printSeparator('=');
    std::cout << "\n  EXAM STATISTICS\n";
    printSeparator('-');
    std::cout << "  Total Students : " << m_students.size() << "\n";
    std::cout << "  Total Questions: " << m_questions.size() << "\n";

    if (!allMarks.empty()) {
        std::cout << "  Highest Score  : " << findMax(allMarks)        << "\n";
        std::cout << "  Lowest Score   : " << findMin(allMarks)        << "\n";
        std::cout << "  Average Score  : " << computeAverage(allMarks) << "\n";
    }

    // ScoreCard template
    ScoreCard<int> classCard("Class Summary");
    for (const auto& s : m_students)
        classCard.addScore(s.getName(), s.getTotalMarks());
    classCard.display();

    printSeparator('=');
}
