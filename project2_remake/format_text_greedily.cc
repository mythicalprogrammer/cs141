#include <iostream>
#include <vector>
#include <string>

//////////////////////////////////////////////////////
///
///  Usage:
///
///    format_text_greedily text_width
///
///  reads lines of text on standard input, then
///  prints the text, formatted, on standard output.
///  line breaking is done greedily.
///
//////////////////////////////////////////////////////

#include <map>

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;

#define DEFAULT_TEXT_WIDTH 60

// trim trailing blanks from a given string
void
trim(string& s) {
  int i = s.size()-1;  
  while (i >= 0 && s[i] == ' ')
    --i;
  s.erase(i+1);
}

// format paragraph, inserting line breaks only when needed
string
format_paragraph_greedily(vector<string> words, int text_width) {
  string output = "";

  int length=0;

  for (int i=0;  i < words.size(); ++i) {
    if (length > 0 && length + words[i].size() > text_width) {
      output += "\n";
      length = 0;
    }
    output += words[i] + " ";
    length += words[i].size() + 1;
  }
  if (length > 0) output += "\n";
  return output;
}

int main(int argc, char *argv[]) {

  int text_width = DEFAULT_TEXT_WIDTH;

  if (argc >= 2) text_width = atoi(argv[1]);

  // read, format, and output a sequence of paragraphs
  // (new paragraph starts with a word "<p>")

  while (std::cin) {

    // get paragraph
    vector<string> words;
    while (std::cin) {
      string word;
      std::cin >> word;
      if (word.empty()) break;
      if (word == "<p>") break;
      words.push_back(word);
    }

    // output paragraph, formatted greedily
    if (words.empty()) continue;
    cout << format_paragraph_greedily(words, text_width);
    cout << endl;
  }
}
