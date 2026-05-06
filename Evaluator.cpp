/*
 * Evaluator.cpp
 * Implementation of the abstract base class Evaluator.
 */

#include "../include/Evaluator.h"
#include <iostream>
#include <iomanip>

// ─── Constructor ──────────────────────────────────────────────────────────────
Evaluator::Evaluator(const std::string& name, int totalMarks, int passingMarks)
    : m_evaluatorName(name),
      m_totalMarks(totalMarks),
      m_passingMarks(passingMarks)
{
    if (totalMarks <= 0)
        throw std::invalid_argument("Total marks must be positive.");
    if (passingMarks < 0 || passingMarks > totalMarks)
        throw std::invalid_argument("Passing marks out of range.");
}

// ─── getGrade: default implementation (can be overridden) ────────────────────
std::string Evaluator::getGrade(int marks) const {
    double pct = (m_totalMarks > 0)
                 ? (100.0 * marks / m_totalMarks)
                 : 0.0;

    if (pct >= 90) return "A+";
    if (pct >= 80) return "A";
    if (pct >= 70) return "B+";
    if (pct >= 60) return "B";
    if (pct >= 50) return "C";
    if (pct >= 40) return "D";
    return "F";
}

// ─── printReport ─────────────────────────────────────────────────────────────
void Evaluator::printReport(const std::string& studentName,
                             int marksObtained) const {
    std::cout << "\n";
    std::cout << "  ┌─────────────────────────────────────┐\n";
    std::cout << "  │         EVALUATION REPORT           │\n";
    std::cout << "  ├─────────────────────────────────────┤\n";
    std::cout << "  │ Student  : " << std::left << std::setw(25)
              << studentName << "│\n";
    std::cout << "  │ Evaluator: " << std::setw(25)
              << m_evaluatorName << "│\n";
    std::cout << "  │ Marks    : " << marksObtained << " / "
              << std::setw(21) << m_totalMarks << "│\n";
    std::cout << "  │ Grade    : " << std::setw(25)
              << getGrade(marksObtained) << "│\n";
    std::cout << "  │ Status   : " << std::setw(25)
              << (marksObtained >= m_passingMarks ? "PASS" : "FAIL") << "│\n";
    std::cout << "  └─────────────────────────────────────┘\n";
}

// ─── Operator Overloading ─────────────────────────────────────────────────────
bool Evaluator::operator>(const Evaluator& other) const {
    return m_totalMarks > other.m_totalMarks;
}

bool Evaluator::operator<(const Evaluator& other) const {
    return m_totalMarks < other.m_totalMarks;
}

bool Evaluator::operator==(const Evaluator& other) const {
    return m_evaluatorName == other.m_evaluatorName &&
           m_totalMarks    == other.m_totalMarks;
}

std::ostream& operator<<(std::ostream& os, const Evaluator& ev) {
    os << "Evaluator[" << ev.m_evaluatorName
       << ", Total=" << ev.m_totalMarks
       << ", Pass=" << ev.m_passingMarks << "]";
    return os;
}
