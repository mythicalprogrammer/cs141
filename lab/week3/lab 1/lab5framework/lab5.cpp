// CS 141 Lab 5
// Your header goes here (include name, login, and lab section
// Name: Quoc Anh Doan 
// login: qdoan
// Name: Charles Ma
// Login: cma
#include <iostream>
#include <vector>

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// Given a sequence of n integers, seq[0..n-1], compute the following:
// a) for 0 <= i <n , the length len[i] of the longest increasing subsequence
//    of seq[0..i]
// b) for 0 <= i <n , predec[i], the index of the corresponding predecessor of
//    the LIS ending at seq[i] (use -1 whre predecessor doe not exist)
// c) end_of_longest, the index of the last element in the LIS of seq
//    not that len[end_of_longest] is the length of the LIS of seq
//////////////////////////////////////////////////////////////////////////////

void findLIS(vector<int> const &seq, vector<int> &len, vector<int> &predec, int &end_of_longest)
{
  // Let n be the number of elements in the input sequence
  int n = seq.size();

  //Make len and predec vectors the same size as the original sequence
  len.resize(n);
  predec.resize(n);
  
  // TODO: Compute len[0..n-1], predec[0..n-1], and end_of_longest
  end_of_longest = 0;
  for(int i = 0; i < n; ++i)
    {
	  len[i] = 1;
	  predec[i] = -1;

	  for(int j = 0; j<i; ++j)
	    {
	      if(seq[j] < seq[i] && len[i] < len[j]+1)
		{		  
		  len[i] = len[j]+1;
		  predec[i] = j;
		}
	      if(len[i] > len[end_of_longest])
		end_of_longest = i;
	    }
	

      
    }
  
  


  //int len_longest_squen = end seq[i]
}

//////////////////////////////////////////////////////////////////////////////
// Given predec[0..n-1] and end_of_longest from above, construct a vector of
// bools inLIS[0..n-1] where inLIS[i] is true iff seq[i] is in the LIS of
// seq[0..n-1]. The vector is allocated from the heap (a pointer ot the vector
// is returned), so the caller is responsible for freeing it when done

vector<bool> *inLIS(vector<int> const &predec, int end_of_longest)
{
  //TODO: Allocate vector of n elements, initialized to false
  // (can be done in one line of code).  
  vector<bool> *inLIS = new vector<bool>(predec.size(), false);


	
  //TODO: Set appropriate entries in vector to true (2 lines of code).
  for(int k = end_of_longest; k >= 0; k = predec[k] )
  (*inLIS)[k] = true;
  
  
  //TODO: return (pointer to) vector
  return inLIS;
}

	
//////////////////////////////////////////////////////////////////////////////
// Print sequence to stdout, marking entries in the LIS using ANSI escapes

void showLIS(vector<int> const &sequence, vector<bool> const &in_lis)
{
	const string TERM_BOLD = "\033[1m";	
	const string TERM_BLINK = "\033[5m";		
	const string TERM_NORMAL = "\033[m";	
	
	for (unsigned int i = 0; i < sequence.size(); ++i)
	{
		if (i < in_lis.size() && in_lis[i])
			cout << TERM_BOLD << TERM_BLINK << sequence[i] << TERM_NORMAL;
		else
			cout << sequence[i];
			
			if (i + 1 == sequence.size())
				cout << endl;
			else
				cout << ' ';
	}
}	
	
	
//////////////////////////////////////////////////////////////////////////////
// Main reads integers from stdin, computs LIS and displays to stdout

int main()
{
	// Sequence of ints for which to compute LIS
	vector<int> sequence;
	
	cout << "Enter sequence of integers for which to comput the LIS.\n"
			 << "Use whitespace to seperate integers.\n"
			 << "use EOF (Ctrl-D on new line) to end input.\n";
			 
	// read sequence of ints from standard input.
	
	int i;
	while (cin >> i)
	{
		sequence.push_back(i);
	}
	
	//if no input, just quit/
	if (sequence.empty())
	{
		cerr << "No integers input,\n";
		return 1;
	}
	
	//Find the LIS.
	vector<int> lis_lengths;
	vector<int> predec_indices;
	int end_of_longest;
	findLIS(sequence, lis_lengths, predec_indices, end_of_longest);
	
	// Extract the LIS
	vector<bool> *in_lis = inLIS(predec_indices, end_of_longest);
	
	// Print the sequence to standard output, with the LIS highlighted.
	cout << "Sequence with LIS: ";
	showLIS(sequence, *in_lis);
	
	//Clean up and quit.
	delete in_lis;
	return 0;
}
	
