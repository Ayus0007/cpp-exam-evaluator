/*
 * Student.cpp
 * Implementation of the Student and Submission classes.
 */

#include "../include/Student.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

// ─── Submission implementation ────────────────────────────────────────────────
Submission::Submission(int qId, const std::string& code, int total)
    : m_questionId(qId), m_code(code),
      m_marksObtained(0), m_marksTotal(total) {}

bool Submission::operator>(const Submission& other) const {
    return m_marksObtained > other.m_marksObtained;
}

bool Submission::operator<(const Submission& other) const {
    return m_marksObtained < other.m_marksObtained;
}

std::ostream& operator<<(std::ostream& os, const Submission& sub) {
    os << "Submission[Q" << sub.m_questionId
       << ", Marks=" << sub.m_marksObtained
       << "/" << sub.m_marksTotal << "]";
    return os;
}

// ─── Student implementation ───────────────────────────────────────────────────
Student::Student()
    : m_rollNumber(0), m_name("Unknown"), m_section("X"),
      m_totalMarksObtained(0), m_totalMarksPossible(0) {}

Student::Student(int rollNo, const std::string& name, const std::string& section)
    : m_rollNumber(rollNo), m_name(name), m_section(section),
      m_totalMarksObtained(0), m_totalMarksPossible(0) {}

void Student::addSubmission(const Submission& sub) {
    m_submissions.push_back(sub);
    m_totalMarksPossible += sub.m_marksTotal;
}

void Student::setMarks(int questionId, int marks) {
    for (auto& sub : m_submissions) {
        if (sub.m_questionId == questionId) {
            m_totalMarksObtained -= sub.m_marksObtained;  // remove old
            sub.m_marksObtained   = marks;
            m_totalMarksObtained += marks;                 // add new
            return;
        }
    }
}

double Student::getPercentage() const {
    if (m_totalMarksPossible == 0) return 0.0;
    return 100.0 * m_totalMarksObtained / m_totalMarksPossible;
}

void Student::displayReportCard() const {
    std::cout << "\n";
    std::cout << "  ╔══════════════════════════════════════════════════╗\n";
    std::cout << "  ║              STUDENT REPORT CARD                 ║\n";
    std::cout << "  ╠══════════════════════════════════════════════════╣\n";
    std::cout << "  ║  Roll No : " << std::left << std::setw(38)
              << m_rollNumber  << "║\n";
    std::cout << "  ║  Name    : " << std::setw(38) << m_name     << "║\n";
    std::cout << "  ║  Section : " << std::setw(38) << m_section  << "║\n";
    std::cout << "  ╠══════════════════════════════════════════════════╣\n";
    std::cout << "  ║  Question Breakdown:                             ║\n";

    for (const auto& sub : m_submissions) {
        std::string entry = "  Q" + std::to_string(sub.m_questionId)
                          + ": " + std::to_string(sub.m_marksObtained)
                          + "/" + std::to_string(sub.m_marksTotal);
        std::cout << "  ║  " << std::left << std::setw(48)
                  << entry << "║\n";
    }

    std::cout << "  ╠══════════════════════════════════════════════════╣\n";

    std::string totalStr = std::to_string(m_totalMarksObtained)
                         + "/" + std::to_string(m_totalMarksPossible);
    std::string pctStr   = std::to_string((int)getPercentage()) + "%";

    std::cout << "  ║  Total   : " << std::setw(38) << totalStr   << "║\n";
    std::cout << "  ║  Percent : " << std::setw(38) << pctStr     << "║\n";
    std::cout << "  ╚══════════════════════════════════════════════════╝\n";
}

// Operator overloading
bool Student::operator>(const Student& other) const {
    return m_totalMarksObtained > other.m_totalMarksObtained;
}

bool Student::operator<(const Student& other) const {
    return m_totalMarksObtained < other.m_totalMarksObtained;
}

bool Student::operator==(const Student& other) const {
    return m_rollNumber == other.m_rollNumber;
}

// Prefix ++ : add 5 grace marks
Student& Student::operator++() {
    m_totalMarksObtained += 5;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << "Student[Roll=" << s.m_rollNumber
       << ", Name=" << s.m_name
       << ", Marks=" << s.m_totalMarksObtained << "]";
    return os;
}
