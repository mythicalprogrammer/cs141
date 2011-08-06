#include <iostream>
#include <string>

//////////////////////////////////////////////////////
///
///  Usage:
///
///    show_cost text_width
///
///  reads lines of text on standard input, then
///  shows the text, with cost calculation, on std output
///
//////////////////////////////////////////////////////

#include <map>

using std::string;

using std::cout;
using std::cin;
using std::endl;

#define DEFAULT_TEXT_WIDTH 60

// trim blanks off end of string
void trim(string& s) {
  int i = s.size()-1;
  while (i >= 0 && s[i] == ' ') --i;
  s.erase(i+1);
}

// print string i times
void plop(int i, string& s) {  while (i-- > 0) cout << s;  }
void plop(int i, char* s)   {  while (i-- > 0) cout << s;  }

// penalty associated with line
int line_cost(string& line, int text_width) {
  int gap = text_width - line.size();
  if (gap < 0) gap = -gap+50;
  return gap*gap*gap;
}


int main(int argc, char *argv[]) {

  int text_width = DEFAULT_TEXT_WIDTH;

  if (argc >= 2) text_width = atoi(argv[1]);

  int total_cost = 0;

  plop(text_width, "#");
  cout << " [" << text_width << "]" << endl;

  // get sequence of paragraphs
  while (std::cin) {
    string line;

    int para_cost = 0;
    int prev_line_cost = -1;
    int prev_length;

    // get paragraph
    // count and show costs for all lines but the last
    while (std::cin) {
      string line;
      getline(cin, line);
      trim(line);
      if (line.empty()) break;

      // count (and output) cost of _previous_ line
      // (this way we don't count cost for last line in para)
      if (prev_line_cost >= 0) {
	para_cost += prev_line_cost;
	cout << "length=" << prev_length << 
	  ", cost=" << prev_line_cost << endl;
      }

      // output this line, without endl
      cout << line;
      plop(text_width-line.size(), " ");
      cout << "| ";

      // compute possible cost
      prev_line_cost = line_cost(line, text_width);
      prev_length = line.size();
    }

    // output cost of paragraph, if at least 1 line
    if (prev_line_cost >= 0) {
      cout << " paragraph cost " << para_cost << endl;
      plop(text_width, "#");
      cout << endl;
      total_cost += para_cost;
    }
  }
  // output total cost
  plop(text_width, " ");
  cout << " TOTAL COST " << total_cost << endl;
}
