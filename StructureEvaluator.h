#ifndef STRUCTURE_EVALUATOR_H
#define STRUCTURE_EVALUATOR_H

/*
 * StructureEvaluator.h
 * Concrete evaluator: checks overall code structure (functions, loops, etc.)
 * Derived from abstract base class Evaluator — demonstrates polymorphism.
 */

#include "Evaluator.h"
#include <string>
#include <vector>

// Structural patterns to look for
struct StructurePattern {
    std::string m_patternName;  // e.g., "for loop", "function definition"
    std::string m_regex;        // simplified pattern string
    int         m_marks;        // marks for this pattern
};

class StructureEvaluator : public Evaluator {
private:
    std::vector<StructurePattern> m_patterns;
    int                           m_minLinesRequired;

    // Helpers
    bool hasPattern(const std::string& code, const std::string& pattern) const;
    int  countLines(const std::string& code)                             const;
    bool hasMainFunction(const std::string& code)                        const;
    bool hasReturnStatement(const std::string& code)                     const;
    bool hasProperIndentation(const std::string& code)                   const;

public:
    StructureEvaluator(int totalMarks, int passingMarks, int minLines = 5);

    void addPattern(const std::string& name, const std::string& pattern,
                    int marks);

    // Override pure virtual functions
    int         evaluate(const std::string& studentCode)         override;
    void        displayCriteria()                          const  override;
    std::string getEvaluatorType()                         const  override;

    // Function overloading: evaluate with a line-count weight
    int evaluate(const std::string& studentCode, double lineWeight);

    int getMinLines() const { return m_minLinesRequired; }
};

#endif // STRUCTURE_EVALUATOR_H
