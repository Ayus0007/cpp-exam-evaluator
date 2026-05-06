#ifndef KEYWORD_EVALUATOR_H
#define KEYWORD_EVALUATOR_H

/*
 * KeywordEvaluator.h
 * Concrete evaluator: checks student code for expected keywords (step-wise).
 * Derived from abstract base class Evaluator.
 */

#include "Evaluator.h"
#include "Question.h"
#include <string>
#include <vector>

class KeywordEvaluator : public Evaluator {
private:
    const Question* m_question;      // The question being evaluated
    bool            m_caseSensitive; // Whether keyword check is case-sensitive

    // Helper: check if a keyword exists in the code
    bool containsKeyword(const std::string& code,
                         const std::string& keyword) const;

    // Helper: normalize code (strip comments, extra spaces)
    std::string normalizeCode(const std::string& code) const;

public:
    KeywordEvaluator(const Question* question,
                     bool caseSensitive = false);

    // Override pure virtual functions
    int         evaluate(const std::string& studentCode)         override;
    void        displayCriteria()                          const  override;
    std::string getEvaluatorType()                         const  override;

    // Function overloading: evaluate with custom keyword list
    int evaluate(const std::string& studentCode,
                 const std::vector<std::string>& extraKeywords);

    // Function overloading: evaluate and return step-wise breakdown
    std::map<std::string, int> evaluateDetailed(const std::string& studentCode);
};

#endif // KEYWORD_EVALUATOR_H
