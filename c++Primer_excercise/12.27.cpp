
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class QueryResult {
public:
    struct Pair {
        int count;
        string line;
    };
    QueryResult(string query, int occurTime) : occurTime(occurTime), query(query) {}
    void append(int count, string line) {
        Pair p;
        p.count = count;
        p.line = line;
        data.push_back(p);
    }
    string toString() {
        stringstream ss;
        ss << "element \"" << query << "\" occurs " << occurTime << " times" << endl;
        for (auto it = data.begin(); it != data.end(); it++) {
            ss << "Line " << it->count << ": " << "\"" << it->line << "\"" << endl;
        }
        return ss.str();
    }

private:
    int occurTime;
    string query;
    vector<Pair> data;
};

class TextQuery {
public:
    TextQuery(ifstream& infile) {

        string text, word;
        while (getline(infile, text)) {
            lines.push_back(text);
            istringstream is(text);
            int lineNumber = lines.size() - 1;
            while (is >> word) {
                markOccurTime(word);
                markLine(word, lineNumber);
                cout << "mark line: word " << word << " lineNumber " << lineNumber << endl;
            }
        }
    }

    void test() {
        // test:
        for (int i = 0; i < lines.size(); i++) {
            cout << "Line " << i << ": " << lines[i] << endl;
        }
    }
    QueryResult query(string q) {
        int occurTime = getOccurTime(q);
        QueryResult result(q, occurTime);
        if (occurTime > 0) {
            // Add lines detail to report.
            getLineDetails(result, q);
        }
        return result;
    }

private:
    void markOccurTime(string word) {
        if (wordOccurTimes.find(word) == wordOccurTimes.end()) {
            wordOccurTimes[word] = 1;
        } else {
            wordOccurTimes[word] ++;
        }
    }

    void markLine(string word, int lineNumber) {
        if (wordLinesMap.find(word) == wordLinesMap.end()) {
            wordLinesMap[word] = set<int>();
        }
        wordLinesMap[word].insert(lineNumber);
    }

    int getOccurTime(string word) {
        if (wordOccurTimes.find(word) == wordOccurTimes.end()) {
            return 0;
        }
        return wordOccurTimes.find(word)->second;
    }

    void getLineDetails(QueryResult& qr, string word) {
        if (wordLinesMap.find(word) == wordLinesMap.end()) {
            return;
        }
        auto s = wordLinesMap.find(word)->second;
        for (auto it = s.begin(); it != s.end(); it++) {
            cout << "line " << *it << ": " << lines[*it] << endl;
            qr.append(*it, lines[*it]);
        }
    }

    vector<string> lines;
    map<string, int> wordOccurTimes;
    map<string, set<int>> wordLinesMap;
};

ostream& print(ostream& out, QueryResult qr) {
    return out << qr.toString();
}

void runQueries(ifstream &infile) {
    TextQuery tq(infile);
    tq.test();

    stringstream instruction;
    instruction << "We" << endl;
    instruction << "are" << endl;
    instruction << "people" << endl;
    instruction << "I" << endl;
    instruction << "q" << endl;
    while (true) {
        cout << "enter word to look for, or q to quit: ";
        string s;
        if (!(instruction >> s) || s == "q") break;
        print(cout, tq.query(s)) << endl;
    }
}

int main() {
    ifstream ifs;
    string filename("c++Primer_excercise/data/NothingToFear.speech.txt");
    ifs.open(filename, std::ifstream::in);
    if (!ifs) {
        cout << "fail to open the file: " << filename << endl;
        return -1;
    }
    runQueries(ifs);
    ifs.close();

    return 0;
}