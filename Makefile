# Makefile for C++ Exam Evaluator
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include

SRCS = src/main.cpp \
       src/Evaluator.cpp \
       src/Question.cpp \
       src/Student.cpp \
       src/KeywordEvaluator.cpp \
       src/StructureEvaluator.cpp \
       src/ExamSystem.cpp

TARGET = exam_evaluator

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
