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
void
trim(string& s) {
  int i = s.size()-1;  
  while (i >= 0 && s[i] == ' ')
    --i;
  s.erase(i+1);
}

// return the penalty associated with a given line
int line_cost(string line, int text_width) {
  trim(line);
  int gap = text_width - line.size();
  if (gap < 0) gap = -gap+50;
  return gap*gap*gap;
}

// given a sequence of n words, and integer text_width
// find the minimum total penalty possible for 
// any formatting of words[0], words[1], ..., words[n-1]
// return the formatted text as a string
//

int get_min_k(int j, int text_width, const vector<string> words)
{
  int n = words.size();
  string line;
  int temp_cost;
    
  line = words[j];
  int min_cost = line_cost(line, text_width);
  int min_k = j;
  for(int k = j+1; k < n-1; k++)
    {
      line += " " + words[k];
      temp_cost = line_cost(line,text_width);
      if(temp_cost < min_cost)
	{
	  min_cost = temp_cost;
	  min_k = k;
	}
    }
  
  cout << min_cost <<endl;
  return min_k;
}

void fill_cell(int j, int text_width, const vector<string> words, 
	       int cost_table[], string para_table[])
{
  int k = get_min_k(j, text_width, words);
  //cout << k <<endl;
  string line = words[j];
  int i;
  for(i = j+1; i <=k; i++)
    line += " " + words[i];
  cost_table[j] = cost_table[k + 1] + line_cost(line,text_width);
  para_table[j] = line + "\n" + para_table[k+1];
}

//go by paragraph by paragraph
string format_paragraph(vector<string> words, int text_width) 
{
  int n = words.size();
  int cost_table[n];
  string para_table[n];  

  // goal:
  // cost_table[j] = min cost for words[j..n-1] 
  // given that words[j] starts a line
  // and para_table[i] = the formatted string that realizes cost_table[i]
  // initialize
  
  for (int i = 0;  i < n;  ++i) 
    {
      cost_table[i] = INT_INFINITY;
      para_table[i] = "ERROR!";
    }
  
  //para_table[n-1] = words[n-1];
  // first, for j such that words j,j+1,...,n-1 all fit on a line
  // set cost_table[j] = 0
  // (special case: word[n-1] doesn't fit on a line, still allow it)
  /*
  para_table[n-1] = words[n-1];
  cost_table[n-1] = 0;
  int length = words[n-1].size();
  int i;
  for(i = n-2; i >= 0; i--)
    {
      length += words[i].size() + 1;
      if(length > text_width)
	break;
      para_table[i] = words[i] + " " + para_table[i+1];
    } */

  cost_table[n-1] = 0;
  int length = words[n-1].size();
  int i;
  for(i = n-2; i >= 0; i--)
    {
      length += words[i].size() + 1;
      if(length > text_width)
	break;
      para_table[i] = words[i] + " " + para_table[i+1];
    }

  //for(int j = i; j <=n-1; ++j )
  //cout<<para_table[j]<< " " <<cost_table[j]<<endl;


  //fill_cell(n-1, text_width, words, cost_table, para_table);
  //para_table[n-1] = words[n-1];
  //fill_cell(n-1, text_width, words, cost_table, para_table);
  
  for(int j = i; j >= 0; --j)
    fill_cell(j, text_width, words, cost_table, para_table);
   
  //para_table[n-2] = words[n-1];

  // next, for i = n-2, n-3, ..., 0, compute cost_table[i]
  // (and para_table[i]) using the recurrence,
  // based on the values cost_table[k+1] for k = j,j+1,...n-2

  // YOUR CODE HERE
  //para_table[n-1] = words[n-1];
  
  para_table[0] += "\n";
  return para_table[0];
}

int main(int argc, char *argv[]) {

  int text_width = DEFAULT_TEXT_WIDTH;

  if (argc >= 2) {
    text_width = atoi(argv[1]);
  }

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
