#pragma once
#include <sstream>
#include <string>
#include <Windows.h>
using namespace std;
class Question
{
public:
    Question(string que, string ans, int c, int cc) :question(que), answer(ans), count(c), correctCount(cc) {}

    string getText() const
    {
        stringstream ss;
        ss << "correct: " << (count==0?0:(static_cast<double>(correctCount) / count * 100)) << "%("<<correctCount<<"/"<<count<<")\n" << question;
        return ss.str();
    }

    void correct(string ans)
    {
        count++;
        if (answer == ans)
        {
            correctCount++;
            cout<<"Correct!";
        }
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            cout <<"Wrong, the answer is" + answer + " , and your input was" + ans;
        }

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    }

    double getRank() const
    {
        return correctCount;
    }

    int getCount() const { return count; }
    int getCorrectCount() const { return correctCount; }

    string getSaveLine() const
    {
        stringstream ss;
        ss << question << "," << answer << "," << count << "," << correctCount << endl;
        return ss.str();
    }

private:
    string question;
    string answer;
    int count;
    int correctCount;

};
