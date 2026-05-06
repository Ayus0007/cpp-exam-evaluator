/*
 * StructureEvaluator.cpp
 * Concrete evaluator: checks structural elements of code (loops, functions, etc.)
 */

#include "../include/StructureEvaluator.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <sstream>

// ─── Constructor ──────────────────────────────────────────────────────────────
StructureEvaluator::StructureEvaluator(int totalMarks, int passingMarks,
                                        int minLines)
    : Evaluator("StructureEvaluator", totalMarks, passingMarks),
      m_minLinesRequired(minLines)
{}

void StructureEvaluator::addPattern(const std::string& name,
                                     const std::string& pattern,
                                     int marks) {
    m_patterns.push_back({name, pattern, marks});
}

// ─── Helpers ──────────────────────────────────────────────────────────────────
bool StructureEvaluator::hasPattern(const std::string& code,
                                     const std::string& pattern) const {
    std::string lCode = code, lPat = pattern;
    std::transform(lCode.begin(), lCode.end(), lCode.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    std::transform(lPat.begin(),  lPat.end(),  lPat.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return lCode.find(lPat) != std::string::npos;
}

int StructureEvaluator::countLines(const std::string& code) const {
    if (code.empty()) return 0;
    int count = 1;
    for (char c : code) if (c == '\n') count++;
    return count;
}

bool StructureEvaluator::hasMainFunction(const std::string& code) const {
    return hasPattern(code, "int main") || hasPattern(code, "void main");
}

bool StructureEvaluator::hasReturnStatement(const std::string& code) const {
    return hasPattern(code, "return");
}

bool StructureEvaluator::hasProperIndentation(const std::string& code) const {
    // Check if any line starts with spaces or tabs (basic indentation check)
    std::istringstream stream(code);
    std::string line;
    int indentedLines = 0;
    while (std::getline(stream, line)) {
        if (!line.empty() && (line[0] == ' ' || line[0] == '\t'))
            indentedLines++;
    }
    return indentedLines >= 2;
}

// ─── evaluate (main override) ─────────────────────────────────────────────────
int StructureEvaluator::evaluate(const std::string& studentCode) {
    if (studentCode.empty())
        throw std::invalid_argument("Code cannot be empty for structure evaluation.");

    int earned = 0;
    int lines  = countLines(studentCode);

    std::cout << "\n  [Structure Evaluator] Analyzing code structure...\n";
    std::cout << "  Lines of code: " << lines << " (min required: "
              << m_minLinesRequired << ")\n";

    // Check line count
    if (lines >= m_minLinesRequired) {
        std::cout << "  [+] Sufficient lines of code\n";
        earned += 2;
    } else {
        std::cout << "  [-] Too few lines (expected >= "
                  << m_minLinesRequired << ")\n";
    }

    // Check main function
    if (hasMainFunction(studentCode)) {
        std::cout << "  [+] main() function present\n";
        earned += 2;
    } else {
        std::cout << "  [-] main() function missing\n";
    }

    // Check return statement
    if (hasReturnStatement(studentCode)) {
        std::cout << "  [+] return statement present\n";
        earned += 1;
    } else {
        std::cout << "  [-] return statement missing\n";
    }

    // Check indentation
    if (hasProperIndentation(studentCode)) {
        std::cout << "  [+] Code appears to be indented\n";
        earned += 1;
    } else {
        std::cout << "  [-] No indentation detected\n";
    }

    // Check custom patterns
    for (const auto& pat : m_patterns) {
        if (hasPattern(studentCode, pat.m_regex)) {
            earned += pat.m_marks;
            std::cout << "  [+] Pattern '" << pat.m_patternName
                      << "' found → +" << pat.m_marks << "\n";
        } else {
            std::cout << "  [-] Pattern '" << pat.m_patternName
                      << "' not found → 0\n";
        }
    }

    earned = std::min(earned, m_totalMarks);
    std::cout << "  Structure Score: " << earned << "/" << m_totalMarks << "\n";
    return earned;
}

// ─── evaluate (overload: with line weight) ────────────────────────────────────
int StructureEvaluator::evaluate(const std::string& studentCode,
                                  double lineWeight) {
    int base  = evaluate(studentCode);
    int lines = countLines(studentCode);
    int bonus = static_cast<int>(lines * lineWeight);
    bonus = std::min(bonus, 3);  // cap bonus at 3

    std::cout << "  Line-weight bonus: +" << bonus << "\n";
    return std::min(base + bonus, m_totalMarks);
}

// ─── displayCriteria ─────────────────────────────────────────────────────────
void StructureEvaluator::displayCriteria() const {
    std::cout << "\n  [StructureEvaluator] Criteria:\n";
    std::cout << "  - Minimum lines: " << m_minLinesRequired << "\n";
    std::cout << "  - Checks: main(), return, indentation\n";
    for (const auto& p : m_patterns) {
        std::cout << "  - Pattern: " << p.m_patternName
                  << " (" << p.m_marks << " marks)\n";
    }
}

std::string StructureEvaluator::getEvaluatorType() const {
    return "StructureEvaluator";
}
