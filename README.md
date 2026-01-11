# Quiz Program

## Description
A simple console-based multiple-choice quiz program written in C++.  
The program reads questions from a text file, selects random questions, tracks user answers, calculates the score, and applies a penalty for wrong answers.

## Features
- Random selection of questions without repetition  
- User input validation (A, B, C, D, or X for blank)  
- Net score calculation where 3 wrong answers cancel 1 correct  
- Final score is always clamped to a minimum of 0  
- Maximum number of questions is configurable (default: 200)  
- ASCII-compatible questions file to avoid Turkish character encoding issues  

## How to Run
1. Compile the program with any C++ compiler (e.g., g++, Code::Blocks):
   ```bash
   g++ quiz.cpp -o quiz
   ```
2. Ensure there is a 'questions.txt' file in the same directory, formatted as:
   ```txt
   Question;OptionA;OptionB;OptionC;OptionD;CorrectAnswer
   ```
  Example:
   ```txt
   What is the capital of France?;Paris;London;Berlin;Rome;A
   ```
3. Run the program:
   ```bash
   ./quiz
   ```

## Usage
- Enter the number of questions you want to attempt (up to the remaining questions).
- Answer each question with A, B, C, D, or X (for blank).
- After completing the quiz, the program displays:
    - Your answers
    - Correct answers
    - Net score
    - Final score out of 100
- You can choose to play again without restarting the program.

## Notes
- Maximum number of questions supported is 200.
- Turkish characters in the questions file are replaced with ASCII equivalents to avoid encoding issues.
- Each quiz session selects unique random questions until all questions are used.

## License
This project is free to use and modify.

## Author 
Ezgi N.Y.
