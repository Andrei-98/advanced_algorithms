#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include <unordered_map>
#include <cassert>

using namespace std;

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


bool process_placeholder(string const& next1, string const& next2,
                         unordered_map<string, string> & tags, vector<string> & phrase_vec)
{
    if (check_placeholder(next2)) 
    {
        if (tags.count(next1))
        {
            phrase_vec.push_back(tags[next1]);
        }
        else
        {
            phrase_vec.push_back(next1);
        }
    }
    else
    {
        if (tags.count(next1))
        {
            if (tags[next1] == next2)
            {
                phrase_vec.push_back(next2);
            }
            else
            {
                return false;
            }
        }
        else // record tag
        {
            tags[next1] = next2;
            phrase_vec.push_back(next2);
        }
    }
    return true;
}

void check_upper(string const& word)
{
    //TODO: REMOVE LATER
    if (word.size() > 16)
        throw std::runtime_error("UPPERCHASE char");

    for (const char& c : word)
    {
        // if(!islower(c) && isalpha(c))
        //     throw std::runtime_error("UPPERCHASE char");
    }

}

string process_words(stringstream &sline1, stringstream &sline2)
{
    if (get_stream_size(sline1) != get_stream_size(sline2))
        return "-";


    string next1, next2;
    vector<string> phrase_vec{};
    unordered_map<string, string> tags;
    unordered_map<string, string> tags2;
    while (sline1 >> next1)
    {
        sline2 >> next2;
        check_upper(next1);
        check_upper(next2);
        if (next1.size() > 16)
            return "-";
        if (next2.size() > 16)
            return "-";

        if (check_placeholder(next1))
        {
            if (!process_placeholder(next1, next2, tags, phrase_vec))
                return "-";
        }
        else if (next1 == next2)
        {
            phrase_vec.push_back(next2);
        }
        else if (check_placeholder(next2))
        {
            if (!process_placeholder(next2, next1, tags2, phrase_vec))
                return "-";
        }
        else
        {
            throw std::runtime_error("in else");
            return "-";
        }
    }

    if (phrase_vec.size() == 0 || (tags.size() == 0 && tags2.size() == 0))
    {
        // cout << phrase_vec.size() << " " << tags.size() << " " << tags2.size() << endl;
        return "-";
    }
    

    string phrase{};

    for (auto const &item : phrase_vec)
    {
        if (tags.count(item))
            phrase += tags[item] + ' ';
        else if (tags2.count(item))
            phrase += tags2[item] + ' ';
        else
            phrase += item + " ";
    };

    return phrase.erase(phrase.size() - 1);
}


string match_patterns(string &line1, string &line2)
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
    assert(result == "how now brown cow");

    line1 = "who are you";
    line2 = "<a> <b> <a>";
    result = match_patterns(line1, line2);
    assert(result == "-");

    line1 = "<a> b";
    line2 = "c <a>";
    result = match_patterns(line1, line2);
    assert(result == "c b");

    line1 = "";
    line2 = "";
    result = match_patterns(line1, line2);
    assert(result == "-");

    line1 = "1";
    line2 = "1";
    result = match_patterns(line1, line2);
    assert(result == "-");

    line1 = "<a>";
    line2 = "<a>";
    result = match_patterns(line1, line2);
    assert(result == "-");

    line1 = "a b c d";
    line2 = "<a> <a> c d";
    result = match_patterns(line1, line2);
    assert(result == "-");

    line1 = "a b c";
    line2 = "<a> <b> <c> <d>";
    result = match_patterns(line1, line2);
    assert(result == "-");

    line1 = "<a> <b> <c> <d>";
    line2 = "a b c";
    result = match_patterns(line1, line2);
    assert(result == "-");

    line1 = "";
    line2 = "<c> a";
    result = match_patterns(line1, line2);
    assert(result == "-");

    line1 = "<c> a";
    line2 = "";
    result = match_patterns(line1, line2);
    assert(result == "-");

    line1 = "a b c";
    line2 = "a b c ";
    result = match_patterns(line1, line2);
    assert(result == "-");

    line2 = "<a> <b> was <a>";
    line1 = "<a> there was raglan";
    result = match_patterns(line1, line2);
    assert(result == "raglan there was raglan");

    line2 = "<a> <b> foo <a>";
    line1 = "foo foo <b> foo";
    result = match_patterns(line1, line2);
    cout << result << endl;
    assert(result == "foo foo foo foo");
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