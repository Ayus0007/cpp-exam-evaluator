/*
 * Question.cpp
 * Implementation of the Question and Step classes.
 */

#include "../include/Question.h"
#include <iostream>
#include <iomanip>

// ─── Step implementation ──────────────────────────────────────────────────────
Step::Step(const std::string& desc, int marks, const std::string& keyword)
    : m_description(desc), m_marks(marks), m_keyword(keyword) {}

// Operator overloading: combine two steps into one (sum marks)
Step Step::operator+(const Step& other) const {
    return Step(m_description + " + " + other.m_description,
                m_marks + other.m_marks,
                m_keyword + "|" + other.m_keyword);
}

bool Step::operator==(const Step& other) const {
    return m_keyword == other.m_keyword && m_marks == other.m_marks;
}

std::ostream& operator<<(std::ostream& os, const Step& s) {
    os << "  Step[" << s.m_description << ", Marks=" << s.m_marks
       << ", Keyword='" << s.m_keyword << "']";
    return os;
}

// ─── Question implementation ──────────────────────────────────────────────────
Question::Question()
    : m_questionId(0), m_title("Untitled"),
      m_description(""), m_totalMarks(0), m_sampleSolution("") {}

Question::Question(int id, const std::string& title,
                   const std::string& description,
                   const std::string& sampleSolution)
    : m_questionId(id), m_title(title),
      m_description(description), m_totalMarks(0),
      m_sampleSolution(sampleSolution) {}

void Question::addStep(const Step& step) {
    m_steps.push_back(step);
    m_totalMarks += step.m_marks;
}

// Function overloading: add step directly with parameters
void Question::addStep(const std::string& desc, int marks, const std::string& kw) {
    addStep(Step(desc, marks, kw));
}

void Question::display() const {
    std::cout << "\n";
    std::cout << "  ╔══════════════════════════════════════════════╗\n";
    std::cout << "  ║  Q" << m_questionId << ": " << std::left
              << std::setw(40) << m_title << "║\n";
    std::cout << "  ╠══════════════════════════════════════════════╣\n";

    // Word-wrap the description at ~44 chars
    std::string desc = m_description;
    std::cout << "  ║  " << std::setw(44) << desc.substr(0, 44) << "║\n";
    if (desc.length() > 44) {
        std::string rest = desc.substr(44);
        while (!rest.empty()) {
            std::cout << "  ║  " << std::setw(44) << rest.substr(0, 44) << "║\n";
            rest = rest.length() > 44 ? rest.substr(44) : "";
        }
    }

    std::cout << "  ╠══════════════════════════════════════════════╣\n";
    std::cout << "  ║  Marks: " << std::setw(38) << m_totalMarks << "║\n";
    std::cout << "  ╚══════════════════════════════════════════════╝\n\n";

    std::cout << "  Marking Scheme (Steps):\n";
    int stepNo = 1;
    for (const auto& step : m_steps) {
        std::cout << "    Step " << stepNo++ << " (" << step.m_marks
                  << " marks): " << step.m_description << "\n";
    }
    std::cout << "\n";
}

bool Question::operator==(const Question& other) const {
    return m_questionId == other.m_questionId;
}

std::ostream& operator<<(std::ostream& os, const Question& q) {
    os << "Question[ID=" << q.m_questionId
       << ", Title=" << q.m_title
       << ", Marks=" << q.m_totalMarks << "]";
    return os;
}
