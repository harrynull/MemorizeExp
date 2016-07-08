#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include "Question.h"
using namespace std;

vector<Question> questions;

vector<string> split(const string& src, const string& separator)
{
    string str = src;
    string substring;
    string::size_type start = 0, index;
    vector<string> dest;

    do
    {
        index = str.find_first_of(separator, start);
        if (index != string::npos)
        {
            substring = str.substr(start, index - start);
            dest.push_back(substring);
            start = str.find_first_not_of(separator, index);
            if (start == string::npos) return dest;
        }
    }
    while (index != string::npos);

    //the last token
    substring = str.substr(start);
    dest.push_back(substring);

    return dest;
}
void save(string str)
{
    ofstream os(str);
    for (auto& q : questions)
    {
        os << q.getSaveLine();
    }
    os.close();
}
void printInfo()
{
    int count = 0;
    int corcount = 0;
    int finish = 0;
    for (const auto& q : questions)
    {
        count += q.getCount();
        corcount += q.getCorrectCount();
        if (static_cast<double>(q.getCorrectCount()) / q.getCount() > 0.9) finish++;
    }
    cout << "Correct rate" << int(static_cast<double>(corcount) / count * 1000) / 10.0 << " % (" << corcount << " / " << count << ") Progress:"
         << int(static_cast<double>(finish) / questions.size() * 1000) / 10.0 << "%(" << finish << "/" << questions.size() << ")" << endl << endl;
}
int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    ifstream islist("list.txt");
    vector<string> filenames;
    while (!islist.eof())
    {
        string line;
        getline(islist, line);
        filenames.push_back(line);
    }
    cout << "Choose the file you want to load" << endl;
    int i = 0;
    for (string filename : filenames)
    {
        cout << "<" << char('a' + i) << ">" << " " << filename << endl;
        i++;
    }
    unsigned char choice = 0;
    do
    {
        cin >> choice;
        choice -= 'a';
    }
    while (choice > filenames.size());
    system("cls");

    ifstream is(filenames[choice]);
    while(!is.eof())
    {
        string line;
        getline(is,line);
        if(line=="") continue;
        auto data = split(line, ",");
        questions.push_back(Question(data[0], data[1], atoi(data[2].c_str()), atoi(data[3].c_str())));
    }
    is.close();

    printInfo();
    while (true)
    {
        double sum = 0;
        for (auto& q : questions)
        {
            sum += q.getRank();
        }
        double avg = sum / questions.size();
        Question* pickQuestion;
        while (true)
        {
            pickQuestion = &questions[rand() % questions.size()];
            if (pickQuestion->getRank() <= avg) break;
        }
        cout << pickQuestion->getText() << ": ";
        string ans;
        cin >> ans;
        system("cls");
        printInfo();
        pickQuestion->correct(ans);
        cout << endl << endl;
        save(filenames[choice]);
    }
}
