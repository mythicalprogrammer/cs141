#include <iostream>
#include <vector>
#include <string>

//////////////////////////////////////////////////////
///
///  Usage:
///
///    format_text text_width
///
///  reads lines of text on standard input, then
///  prints the text, formatted, on standard output.
///
///  line breaking is done to minimize a penalty function.
///
//////////////////////////////////////////////////////

using std::vector;
using std::string;

using std::cout;
using std::cerr;
using std::cin;
using std::endl;

#define DEFAULT_TEXT_WIDTH 60
#define INT_INFINITY (1<<30)

#define MIN(a,b) ((a)<(b)?(a):(b))

// trim trailing blanks from a given string
void trim(string& s) 
{
  int i = s.size()-1;  
  while (i >= 0 && s[i] == ' ')
    --i;
  s.erase(i+1);
}

// return the penalty associated with a given line
int line_cost(string line, int text_width) 
{
  trim(line);
  int gap = text_width - line.size();
  if (gap < 0) gap = -gap+50;
  return gap*gap*gap;
}

//
// given a sequence of n words, and integer text_width
//
// find the minimum total penalty possible for 
// any formatting of words[0], words[1], ..., words[n-1]
//
// return the formatted text as a string
//

int get_min_k(int j, int text_width, const vector<string> &words)
{
  int n = words.size();
  string line = "";
  int penalty = text_width*text_width*text_width;
  int temp;
  int min_k;
  for(int k = j; k <= n-2; k++)
    {
      line += " " + words[k];
      temp = line_cost(line,text_width);
      if(temp < penalty)
	{
	  penalty = temp;
	  min_k = k;
	}
    }
  return min_k;
}
string format_paragraph(vector<string> words, int text_width) 
{
  int n = words.size();
  int cost_table[n];
  string para_table[n];  
  for(int i = 0; i < n; i++) 
    {
      cost_table[i] = INT_INFINITY;
      para_table[i] = "ERROR!";
    }
  //para_table[0].append(words[words.size()-1]);
  for(int j = n-2; j >= 0; j--)
    {
      int k = get_min_k(j, text_width, words);
      string word ="";
      for(int iter = j; iter <= k; iter++)
	word += words[iter] +" ";
      para_table[j] =  word + "\n" + para_table[k+1];
    }
  return para_table[0];
}

int main(int argc, char *argv[]) 
{
  int text_width = DEFAULT_TEXT_WIDTH;
  if (argc >= 2)
    text_width = atoi(argv[1]);
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
    // output paragraph, formatted
    if (words.empty()) continue;
    cout << format_paragraph(words, text_width);
    cout << endl;
  }
}
