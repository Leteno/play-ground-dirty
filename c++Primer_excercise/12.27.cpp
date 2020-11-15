
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
    QueryResult(int occurTime) : occurTime(occurTime) {}
    void append(int count, string line) {
        Pair p;
        p.count = count;
        p.line = line;
        data.push_back(p);
    }
    string toString() {
        stringstream ss;
        ss << "element occurs " << occurTime << " times" << endl;
        for (auto it = data.begin(); it != data.end(); it++) {
            ss << "Line " << it->count << ": " << "\"" << it->line << "\"" << endl;
        }
        return ss.str();
    }

private:
    int occurTime;
    vector<Pair> data;
};

class TextQuery {
public:
    TextQuery(ifstream& infile) {
        filebuf* fbuf = infile.rdbuf();
        int size = fbuf->pubseekoff(0, infile.end, infile.in);
        fbuf->pubseekpos(0, infile.in);

        unique_ptr<char[]> content(new char[size]);
        fbuf->sgetn(content.get(), size);
        fbuf->pubseekpos(0, infile.in);

        // divide into lines
        const char* ptr = content.get();
        int index = 0, begin = 0;
        while (index < size) {
            begin = index;
            while(index < size && content[index] != '\n') index++;
            lines.push_back(string(ptr + begin, index-begin));
            index += 1; // skip '\n', and it should work fine in the EOF
        }

        // Pre-Parse
        string word;
        int lineNumber = 1;
        for (auto it = lines.begin(); it != lines.end(); it++, lineNumber++) {
            istringstream is(*it);
            while (is >> word) {
                markOccurTime(word);
                markLine(word, lineNumber);
                cout << "mark line: word " << word << " lineNumber " << lineNumber << endl;
            }
        }

        // test:
        for (int i = 0; i < lines.size(); i++) {
            cout << "Line " << i << ": " << lines[i] << endl;
        }
    }
    QueryResult query(string q) {
        int occurTime = getOccurTime(q);
        QueryResult result(occurTime);
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