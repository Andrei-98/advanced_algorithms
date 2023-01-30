#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include <unordered_map>
#include <cassert>
#include <iterator>

using namespace std;

#define vs vector<string>
#define mss unordered_map<string, string>

bool check_placeholder(string const &word)
{
    if (word.front() == '<' && word.back() == '>')
        return true;
    return false;
}


string match_tags(vs & vec, mss & tags, mss & tags2)
{
    string line {};
    for (auto & i : vec)
    {
        if (tags.count(i))
            i = tags[i];
        else if(check_placeholder(i))
        {
            if(tags2.count(i))
                i = tags2[i];
            else
                return "-";
        }
        line += i + " ";
    }
    return line.erase(line.size() - 1);
}

string process_words(vs const &phrase1, vs const &phrase2)
{
    if(phrase1.size() != phrase2.size())
        throw runtime_error("lel");

    mss tags1{}, tags2{};
    vs phrase_vec1{}, phrase_vec2{};

    for (size_t i{}; i < phrase1.size(); i++)
    {
        string word1{phrase1[i]}, word2{phrase2[i]};

        if (check_placeholder(word1))
        {
            if (tags1.count(word1))
            {
                phrase_vec1.push_back(tags1[word1]);
            }
            else
            { 
                if(check_placeholder(word2))
                {
                    // phrase_vec1.push_back(word2);
                } else
                {
                    tags1[word1] = word2;
                }

                phrase_vec1.push_back(word1);
            }

            if (check_placeholder(word2))
            {
                if (tags2.count(word2))
                    phrase_vec2.push_back(tags2[word2]);
                else
                    phrase_vec2.push_back(word2);
            }
            else
            {
                phrase_vec2.push_back(word2);
            }
        }
        else if (check_placeholder(word2))
        {
            phrase_vec1.push_back(word1);
            if (tags2.count(word2))
                phrase_vec2.push_back(tags2[word2]);
            else
            {
                tags2[word2] = word1;
                phrase_vec2.push_back(word2);
            }
        }
        else
        {
            phrase_vec1.push_back(word1);
            phrase_vec2.push_back(word2);
        }
    }
    string match1 {match_tags(phrase_vec1, tags1, tags2)};
    string match2 {match_tags(phrase_vec2, tags2, tags1)};

    if(match1 == match2)
        return match1;
    else
        return "-";
}

string match_patterns(string &line1, string &line2)
{
    stringstream sphrase1{line1};
    stringstream sphrase2{line2};

    vs phrase1{istream_iterator<string>(sphrase1), istream_iterator<string>()};
    vs phrase2{istream_iterator<string>(sphrase2), istream_iterator<string>()};

    string result{process_words(phrase1, phrase2)};

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

    line1 = "a b c d";
    line2 = "<a> <a> c d";
    result = match_patterns(line1, line2);
    assert(result == "-");

    line1 = "a b c";
    line2 = "a b c ";
    result = match_patterns(line1, line2);
    assert(result == "a b c");

    line1 = "<a> there was raglan";
    line2 = "<a> <b> was <a>";
    result = match_patterns(line1, line2);
    assert(result == "raglan there was raglan");

    line2 = "<a> <b> foo <a>";
    line1 = "foo foo <b> foo";
    result = match_patterns(line1, line2);
    assert(result == "foo foo foo foo");

    line1 = "<a> <a b c";
    line2 = "<a> <a b <a>";
    result = match_patterns(line1, line2);
    assert(result == "c <a b c");

    line1 = "<a> a <a>";
    line2 = "c <c> <c>";
    result = match_patterns(line1, line2);
    assert(result == "-");
}

int main()
{
    // test_mode();
    int loops;
    cin >> loops;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    string line1, line2;
    for (int i = 0; i < loops; ++i)
    {
        getline(cin, line1);
        getline(cin, line2);
        cout << match_patterns(line1, line2) << '\n';
    }
}