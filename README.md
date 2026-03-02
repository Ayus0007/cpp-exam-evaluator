# cpp-exam-evaluator
Students copy C++ code without real evaluation • Paper exams give no structured feedback • Gap between practice and actual marking • Console-based Auto-Evaluation System proposed • Analyzes code using pattern detection • Simulates paper-style checking • Helps C++/DSA exam preparation • Improves performance tracking and readiness
📘 C++ Exam Auto-Evaluation & Simulation System

A console-based C++ application designed to simulate paper-style exam evaluation for Software Development (C++ & DSA) courses.

🚩 Problem Statement

In many colleges, students prepare for C++ exams by copying code from shared documents without receiving structured feedback. Since exams are conducted on paper, students cannot compile their code or verify correctness. There is no system to evaluate logic, structure, or exam readiness.

This project bridges that gap by simulating paper-style code checking in a structured and automated manner.

🎯 Objective

To build a console-based C++ system that:

Allows students to attempt exam-style coding questions

Accepts full C++ code submissions

Automatically evaluates code structure and logic patterns

Assigns marks based on predefined marking schemes

Tracks topic-wise performance

⚙️ Features

📄 Paper-style coding question simulation

🧠 Pattern-based auto-evaluation engine

📊 Topic-wise performance analytics

🎲 Random question paper generation

🏷 Mark distribution (logic, structure, output)

💾 File-based result storage

📈 Weak topic detection

🏗️ System Architecture
Core Modules

Question Module

Abstract base class Question

Derived class CodingQuestion

Polymorphism-based evaluation

Code Analyzer Engine

Keyword detection

Structure validation (main(), includes, loops, etc.)

Logic pattern matching

Exam Engine

Question handling

Code submission

Score calculation

Analytics Module

Topic performance tracking

Weak area identification

Template-Based Record Manager

Generic storage using C++ templates

🧩 OOP & C++ Concepts Used

Abstract Classes

Polymorphism

Templates

STL (vector, map, algorithm)

Exception Handling

File Handling

Modular header & source file separation

📂 Project Structure

🧠 How Evaluation Works

Instead of compiling code, the system:

Checks required keywords (for, while, class, etc.)

Verifies structural elements (#include, main())

Detects logic patterns

Compares expected output

Assigns marks based on marking scheme

This replicates real paper-based exam checking.

🎓 Target Users

Students preparing for C++ & DSA exams

Institutions conducting paper-based programming exams

Beginners seeking structured practice

🚀 Future Improvements

Enhanced logic pattern detection

Difficulty-based question generation

GUI integration

Online version with database support

👨‍💻 Author

Developed as an academic mini-project to demonstrate practical application of Object-Oriented Programming and STL in C++.
