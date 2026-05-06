/*
 * KeywordEvaluator.cpp
 * Concrete evaluator: step-wise keyword matching in student code.
 */

#include "../include/KeywordEvaluator.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <sstream>

// ─── Constructor ──────────────────────────────────────────────────────────────
KeywordEvaluator::KeywordEvaluator(const Question* question, bool caseSensitive)
    : Evaluator("KeywordEvaluator", question->getTotalMarks(),
                question->getTotalMarks() / 2),
      m_question(question),
      m_caseSensitive(caseSensitive)
{
    if (!m_question)
        throw std::invalid_argument("Question pointer cannot be null.");
}

// ─── normalizeCode ────────────────────────────────────────────────────────────
std::string KeywordEvaluator::normalizeCode(const std::string& code) const {
    std::string result;
    bool inSingleComment = false;
    bool inMultiComment  = false;

    for (size_t i = 0; i < code.size(); i++) {
        // Detect // comment
        if (!inMultiComment && i + 1 < code.size() &&
            code[i] == '/' && code[i+1] == '/') {
            inSingleComment = true;
        }
        if (inSingleComment && code[i] == '\n') {
            inSingleComment = false;
            result += ' ';
            continue;
        }
        // Detect /* comment
        if (!inSingleComment && i + 1 < code.size() &&
            code[i] == '/' && code[i+1] == '*') {
            inMultiComment = true;
        }
        if (inMultiComment && i + 1 < code.size() &&
            code[i] == '*' && code[i+1] == '/') {
            inMultiComment = false;
            i++;  // skip '/'
            result += ' ';
            continue;
        }
        if (!inSingleComment && !inMultiComment)
            result += code[i];
    }

    if (!m_caseSensitive) {
        std::transform(result.begin(), result.end(), result.begin(),
                       [](unsigned char c){ return std::tolower(c); });
    }
    return result;
}

// ─── containsKeyword ─────────────────────────────────────────────────────────
bool KeywordEvaluator::containsKeyword(const std::string& code,
                                        const std::string& keyword) const {
    std::string haystack = code;
    std::string needle   = keyword;

    if (!m_caseSensitive) {
        std::transform(haystack.begin(), haystack.end(), haystack.begin(),
                       [](unsigned char c){ return std::tolower(c); });
        std::transform(needle.begin(), needle.end(), needle.begin(),
                       [](unsigned char c){ return std::tolower(c); });
    }
    return haystack.find(needle) != std::string::npos;
}

// ─── evaluate (main override) ─────────────────────────────────────────────────
int KeywordEvaluator::evaluate(const std::string& studentCode) {
    if (studentCode.empty())
        throw std::invalid_argument("Student code cannot be empty.");

    std::string normalized = normalizeCode(studentCode);
    int totalEarned = 0;

    std::cout << "\n  [Keyword Evaluator] Checking steps...\n";

    for (const auto& step : m_question->getSteps()) {
        bool found = containsKeyword(normalized, step.m_keyword);
        if (found) {
            totalEarned += step.m_marks;
            std::cout << "  [+] \"" << step.m_description
                      << "\" → +" << step.m_marks << " marks\n";
        } else {
            std::cout << "  [-] \"" << step.m_description
                      << "\" → 0 marks (keyword '"
                      << step.m_keyword << "' not found)\n";
        }
    }

    std::cout << "  Total Keyword Score: " << totalEarned
              << "/" << m_totalMarks << "\n";
    return totalEarned;
}

// ─── evaluate (overload 1: with extra keywords) ───────────────────────────────
int KeywordEvaluator::evaluate(const std::string& studentCode,
                                const std::vector<std::string>& extraKeywords) {
    int base = evaluate(studentCode);
    int bonus = 0;
    int bonusPerKeyword = 1;

    std::cout << "\n  [Bonus Keywords Check]\n";
    for (const auto& kw : extraKeywords) {
        if (containsKeyword(studentCode, kw)) {
            bonus += bonusPerKeyword;
            std::cout << "  [B] Bonus keyword '" << kw << "' found +1\n";
        }
    }
    int total = std::min(base + bonus, m_totalMarks);
    std::cout << "  Final Score (with bonus): " << total << "\n";
    return total;
}

// ─── evaluateDetailed (overload 2: returns map) ───────────────────────────────
std::map<std::string, int> KeywordEvaluator::evaluateDetailed(
        const std::string& studentCode) {

    std::map<std::string, int> breakdown;
    std::string normalized = normalizeCode(studentCode);

    for (const auto& step : m_question->getSteps()) {
        bool found = containsKeyword(normalized, step.m_keyword);
        breakdown[step.m_description] = found ? step.m_marks : 0;
    }
    return breakdown;
}

// ─── displayCriteria ─────────────────────────────────────────────────────────
void KeywordEvaluator::displayCriteria() const {
    std::cout << "\n  [KeywordEvaluator] Evaluation Criteria:\n";
    std::cout << "  Mode: " << (m_caseSensitive ? "Case Sensitive" : "Case Insensitive") << "\n";
    std::cout << "  Steps being checked:\n";
    for (const auto& step : m_question->getSteps()) {
        std::cout << "    → " << step.m_description
                  << " (keyword: '" << step.m_keyword
                  << "', marks: " << step.m_marks << ")\n";
    }
}

std::string KeywordEvaluator::getEvaluatorType() const {
    return "KeywordEvaluator";
}
