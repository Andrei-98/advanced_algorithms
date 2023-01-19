#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include <unordered_map>
#include <cassert>

using namespace std;

// pattern = is a phrase consisting of words and placeholders
// word = string of letters
// placeholder = word enclosed in brackets <...>
//
// a phrase matches a pattern if each placeholder in the pattern can be systematically
// replaced by a word so as to make the pattern and phrase equal. By “systematically
// replaced” we mean that all placeholders enclosing the same word are replaced
// by the same word.
bool check_placeholder(string const &word)
{
    if (word.front() == '<' && word.back() == '>')
        return true;
    return false;
}

int get_stream_size(stringstream const& orignal_ss)
{
    stringstream ss; 
    ss.str(orignal_ss.str());

    int counter {};
    string word{};

    while(ss >> word)
    {
        counter++;
    }
    return counter;
}

string process_words(stringstream &sline1, stringstream &sline2)
{
    if (get_stream_size(sline1) != get_stream_size(sline2))
        return "-";

    string next1, next2, phrase;
    unordered_map<string, string> tags;
    unordered_map<string, string> tags2;
    while (sline1 >> next1)
    {
        sline2 >> next2;
        if (check_placeholder(next1))
        {
            if (check_placeholder(next2)) // two placeholders no bueno
            {
                return "-";
            }
            else 
            {
                if (tags.count(next1))
                {
                    if (tags[next1] == next2)
                    {
                        phrase += next2 + " ";
                    }
                    else
                    {
                        return "-";
                    }
                }
                else // record tag
                {
                    tags[next1] = next2;
                    phrase += next2 + " ";
                }
            }
        }
        else if (next1 == next2)
        {
            phrase += next1 + " ";
        }
        else if (check_placeholder(next2))
        {
            if (tags2.count(next2))
            {
                if (tags2[next2] == next1)
                {
                    phrase += next1 + ' ';
                }
                else
                {
                    return "-";
                }
            }
            else // record tag
            {
                tags2[next2] = next1;
                phrase += next1 + ' ';
            }
        }
        else if (next1 == next2)
        {
            phrase += next1 + ' ';
        }
        else
        {
            std::cout << "here" << endl;
            throw std::runtime_error("in else");
            return "-";
        }

    }

    if (phrase.size() == 0 || (tags.size() == 0  && tags2.size() == 0))
    {
        return "-";
    }
    return phrase.erase(phrase.size() - 1);
}

string match_patterns(string & line1, string & line2)
{
    stringstream sline1{line1};
    stringstream sline2{line2};
    string result{process_words(sline1, sline2)};
    return result;
}

void test_mode()
{
    string line1, line2, result;

    line1 = "how now brown <animal>";
    line2 = "<foo> now <color> cow";
    result = match_patterns(line1, line2);
    assert (result == "how now brown cow");

    line1 = "who are you";
    line2 = "<a> <b> <a>";
    result = match_patterns(line1, line2);
    assert (result == "-");

    line1 = "<a> b";
    line2 = "c <a>";
    result = match_patterns(line1, line2);
    assert (result == "c b");

    line1 = "";
    line2 = "";
    result = match_patterns(line1, line2);
    assert (result == "-");

    line1 = "1";
    line2 = "1";
    result = match_patterns(line1, line2);
    assert (result == "-");

    line1 ="<a>";
    line2 ="<a>";
    result = match_patterns(line1, line2);
    assert (result == "-");

    line1 = "a b c d";
    line2 = "<a> <a> c d";
    result = match_patterns(line1, line2);
    assert (result == "-");

    line1 = "a b c";
    line2 = "<a> <b> <c> <d>";
    result = match_patterns(line1, line2);
    assert (result == "-");

    line1 = "<a> <b> <c> <d>";
    line2 = "a b c";
    result = match_patterns(line1, line2);
    assert (result == "-");

    line1 = "";
    line2 = "<c> a";
    result = match_patterns(line1, line2);
    assert (result == "-");

    line1 = "<c> a";
    line2 = "";
    result = match_patterns(line1, line2);
    assert (result == "-");
    
    line1 = "a b c";
    line2 = "a b c";
    result = match_patterns(line1, line2);
    assert (result == "-");
}

int main()
{
    test_mode();
    // int loops;
    // cin >> loops;
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // string line1, line2;
    // for (int i = 0; i < loops; ++i)
    // {
    //     getline(cin, line1);
    //     getline(cin, line2);
    //     cout << match_patterns(line1, line2) << '\n';
    // }
}