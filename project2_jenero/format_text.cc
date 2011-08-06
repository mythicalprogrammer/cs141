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

//
// given a sequence of n words, and integer text_width
//
// find the minimum total penalty possible for 
// any formatting of words[0], words[1], ..., words[n-1]
//
// return the formatted text as a string
//

string
format_paragraph(vector<string> words, int text_width) {
  
  int n = words.size();

  int cost_table[n];
  string para_table[n];  

  // goal:
  // cost_table[j] = min cost for words[j..n-1] 
  // given that words[j] starts a line
  //
  // and para_table[i] = the formatted string that realizes cost_table[i]

  // initialize

  for (int i = 0;  i < n;  ++i) {
    cost_table[i] = INT_INFINITY;
    para_table[i] = "ERROR!";
  }


  // first, for j such that words j,j+1,...,n-1 all fit on a line
  // set cost_table[j] = 0
  // (special case: word[n-1] doesn't fit on a line, still allow it)

  // YOUR CODE HERE

  string temp = "";
  string temp2 = "";
  int count = n -1;

  for(count = n-1; count >= 0; count--)
    {
      cost_table[count] = 0;
      temp = words[count]+ " " + temp;
      if (temp.size() >text_width)
	break;
      para_table[count] = temp + "\n";
    }

  int cost, cost2, i, iter;

  for(count; count >= 0; count--)
    {
      temp = words[count];
      temp2 = temp;
      cost = line_cost(temp, text_width) + cost_table[count +1];
     
      i = count;
      
      for(i = count + 1; i < n; i++)
	{
	  temp2 = temp2 +  " " + words[i];
	  if(i != n -1)
	    cost2 = line_cost(temp2, text_width) + cost_table[i+1];
	  else
	    cost2 = line_cost(temp2, text_width);
	  if(cost > cost2)
	    {
	      cost = cost2;
	      cost_table[count] = cost;
	      iter = i;
	      temp = temp2;
	    }
	  if(temp2.size() > text_width)
	    {
	      cout << cost <<endl;
	    break;
	    }
	}

      if(iter != n -1)
	{
	  temp = temp + "\n" + para_table[iter +1];
	}
      else
	temp = temp + "\n";
      cost_table[count] = cost;
      para_table[count] = temp;

	
    }





  //for(int j = i; j <n-1; ++j )
    //cout<<para_table[j]<<endl; 

  // next, for i = n-2, n-3, ..., 0, compute cost_table[i]
  // (and para_table[i]) using the recurrence,
  // based on the values cost_table[k+1] for k = j,j+1,...n-2


  // YOUR CODE HERE



  
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
