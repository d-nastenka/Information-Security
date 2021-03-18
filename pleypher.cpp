#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;

const string code_word = "WHEATSON";
set <char> alphabet = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
char matrix[5][5];

pair<int, int> coord(char a) {

    char x, y;
    pair<int, int> p;

    for (int k = 0; k < 5; k++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[k][j] == a) {
                x = k;
                y = j;
                p.first = k;
                p.second = j;
                return p;
            }
        }
    }
}

string scrambler(string text) {
    vector<string> bigramma;

    //удаляем из алфавита слова которые уже есть в кодовом слове
    for (int k = 0; k < code_word.size(); k++) {
        alphabet.erase(code_word[k]);
    }
    // Удаляем пробелы 
    text.erase(remove(text.begin(), text.end(), ' '), text.end());

    int i = 0;
    //заполняем матрицу 5*5
    for (int k = 0; k < 5; k++) {
        for (int j = 0; (j < 5); j++) {
            if (k * 5 + j < code_word.size())
                matrix[k][j] = code_word[k * 5 + j];
            else {
                matrix[k][j] = *next(alphabet.begin(), i);
                i++;
            }
        }
    }

    //создаем биграмму
    for (int k = 0; k < text.size(); k += 2) {
        string temp = "  ";
        if (text[k] != text[k + 1] && k + 1 < text.size())
            temp[0] = text[k];
        temp[1] = text[k + 1];
        if (text[k] == text[k + 1] && k + 1 < text.size()) {
            temp[0] = text[k];
            temp[1] = 'X';
            k--;
        }
        if (k + 1 >= text.size()) {
            temp[0] = text[k];
            temp[1] = 'X';
        }
        bigramma.push_back(temp);
    }

    string result;

    for (int k = 0; k < bigramma.size(); k++) {
        pair<int, int> a;
        a = coord(bigramma[k][0]);
        pair<int, int> b;
        b = coord(bigramma[k][1]);

        if (a.first != b.first && a.second != b.second) {
            result += matrix[a.first][b.second];
            result += matrix[b.first][a.second];
        }
        if (a.first == b.first && a.second != b.second) {
            result += matrix[a.first][(a.second + 1) % 5];
            result += matrix[b.first][(b.second + 1) % 5];
        }
        if (a.first != b.first && a.second == b.second) {
            result += matrix[(a.first + 1) % 5][a.second];
            result += matrix[(b.first + 1) % 5][b.second];
        }
    }
  
    return result;
}
string decoder(string text){
    vector<string> bigramma;
    //удаляем из алфавита слова которые уже есть в кодовом слове
    for (int k = 0; k < code_word.size(); k++) {
        alphabet.erase(code_word[k]);
    }

    int i = 0;
    //заполняем матрицу 5*5
    for (int k = 0; k < 5; k++) {
        for (int j = 0; (j < 5); j++) {
            if (k * 5 + j < code_word.size())
                matrix[k][j] = code_word[k * 5 + j];
            else {
                matrix[k][j] = *next(alphabet.begin(), i);
                i++;
            }
        }
    }

    //создаем биграмму
    for (int k = 0; k < text.size(); k += 2) {
        string temp = "  ";
        if (text[k] != text[k + 1] && k + 1 < text.size())
            temp[0] = text[k];
        temp[1] = text[k + 1];
        if (text[k] == text[k + 1] && k + 1 < text.size()) {
            temp[0] = text[k];
            temp[1] = 'X';
            k--;
        }
        if (k + 1 >= text.size()) {
            temp[0] = text[k];
            temp[1] = 'X';
        }
        bigramma.push_back(temp);
    }

    string result;

    for (int k = 0; k < bigramma.size(); k++) {
        pair<int, int> a;
        a = coord(bigramma[k][0]);
        pair<int, int> b;
        b = coord(bigramma[k][1]);

        if (a.first != b.first && a.second != b.second) {
            result += matrix[a.first][b.second];
            result += matrix[b.first][a.second];
        }
        if (a.first == b.first && a.second != b.second) {
            if (a.second == 0)
                a.second = 5;
            if (b.second == 0)
                b.second = 5;

            result += matrix[a.first][(a.second - 1)];
            result += matrix[b.first][(b.second - 1)];
        }
        if (a.first != b.first && a.second == b.second) {
            if (a.first == 0)
                a.first = 5;
            if (b.first == 0)
                b.first = 5;

            result += matrix[(a.first - 1)][a.second];
            result += matrix[(b.first - 1)][b.second];
        }
    }

    return result;
}

//IDIOCY OFTEN LOOKS LIKE INTELLIGENCE
int main()
{   
    string text;
    getline(cin, text);
    cout << text << endl;
    cout << scrambler(text) << endl;
    cout << decoder(scrambler(text));
 
    return 0;
}
