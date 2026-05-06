#ifndef SCORECARD_H
#define SCORECARD_H

/*
 * ScoreCard.h
 * Template-based ScoreCard: can hold scores of any numeric type.
 * Also provides generic utility functions using templates.
 */

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <numeric>

// ─── Template: Generic ScoreCard ─────────────────────────────────────────────
template <typename T>
class ScoreCard {
private:
    std::string         m_ownerName;
    std::map<std::string, T> m_scores;   // subject → score

public:
    ScoreCard() : m_ownerName("Unknown") {}
    explicit ScoreCard(const std::string& ownerName)
        : m_ownerName(ownerName) {}

    void addScore(const std::string& subject, T score) {
        m_scores[subject] = score;
    }

    T getScore(const std::string& subject) const {
        auto it = m_scores.find(subject);
        if (it == m_scores.end())
            throw std::out_of_range("Subject not found: " + subject);
        return it->second;
    }

    T getTotal() const {
        T total = T();
        for (const auto& pair : m_scores)
            total += pair.second;
        return total;
    }

    double getAverage() const {
        if (m_scores.empty()) return 0.0;
        return static_cast<double>(getTotal()) / m_scores.size();
    }

    std::string getOwner() const { return m_ownerName; }

    void display() const {
        std::cout << "\n  Score Card: " << m_ownerName << "\n";
        std::cout << "  " << std::string(30, '-') << "\n";
        for (const auto& pair : m_scores) {
            std::cout << "  " << pair.first
                      << ": " << pair.second << "\n";
        }
        std::cout << "  Total   : " << getTotal()   << "\n";
        std::cout << "  Average : " << getAverage() << "\n";
    }

    // Operator overloading: merge two scorecards
    ScoreCard<T> operator+(const ScoreCard<T>& other) const {
        ScoreCard<T> merged(m_ownerName + "+" + other.m_ownerName);
        for (const auto& p : m_scores)
            merged.addScore(p.first, p.second);
        for (const auto& p : other.m_scores) {
            auto it = merged.m_scores.find(p.first);
            if (it != merged.m_scores.end())
                it->second += p.second;
            else
                merged.addScore(p.first, p.second);
        }
        return merged;
    }

    friend std::ostream& operator<<(std::ostream& os,
                                    const ScoreCard<T>& sc) {
        os << "ScoreCard[" << sc.m_ownerName
           << ", Total=" << sc.getTotal() << "]";
        return os;
    }
};

// ─── Template utility functions ───────────────────────────────────────────────

// Returns the maximum element from a vector
template <typename T>
T findMax(const std::vector<T>& vec) {
    if (vec.empty())
        throw std::invalid_argument("Cannot find max of empty vector");
    return *std::max_element(vec.begin(), vec.end());
}

// Returns the minimum element from a vector
template <typename T>
T findMin(const std::vector<T>& vec) {
    if (vec.empty())
        throw std::invalid_argument("Cannot find min of empty vector");
    return *std::min_element(vec.begin(), vec.end());
}

// Computes average of a vector
template <typename T>
double computeAverage(const std::vector<T>& vec) {
    if (vec.empty()) return 0.0;
    T sum = std::accumulate(vec.begin(), vec.end(), T());
    return static_cast<double>(sum) / vec.size();
}

// Clamp a value between low and high
template <typename T>
T clamp(T value, T low, T high) {
    if (value < low)  return low;
    if (value > high) return high;
    return value;
}

// Generic swap
template <typename T>
void swapValues(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

#endif // SCORECARD_H
