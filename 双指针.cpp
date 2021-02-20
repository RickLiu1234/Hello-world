#include <vector>
#include <iostream>
using namespace std;
int remove_elements(vector<int>nums, int val) {
	//My Solution
	/*for (int i = 0; i < nums.size(); i++) {
		if (nums[i] == val) {
			nums.erase(nums.begin() + i);
			//erase funciton has time complexity of O(n)
			//which results in a total time complexity of O(n^2)
			i--;
		}
	}
	return nums.size();
	*/
	//Solution 2; using double pointers
	//Only has a time complexity of O(n)
	int slow_ptr = 0;
	for (int fast_ptr = 0; fast_ptr < nums.size(); fast_ptr++) {
		if (nums[fast_ptr] != val) {
			slow_ptr++;
			nums[slow_ptr] = nums[fast_ptr];
		}
	}
	return slow_ptr;
}
void reverse_string(vector<char>& s) {
	int second_ptr = s.size() - 1;
	for (int first_ptr = 0; first_ptr < s.size()/2; first_ptr++) {
		if (s[first_ptr] != s[second_ptr]) {
			char temp = s[first_ptr];
			s[first_ptr] = s[second_ptr];
			s[second_ptr] = temp;
		}
		second_ptr--;
	}
	
}
string replace_space(string s) {
	int count = 0;
	int old_size = s.size();
	for (int  i = 0; i < s.length(); i++){
		if (s[i] == ' ') {
			count++;
		}
	}
	s.resize(s.size() + count * 2); 
	//count times 2 because space takes one place
	int new_size = s.size();
	for (int first_ptr = new_size - 1, second_ptr = old_size - 1; second_ptr < first_ptr; first_ptr--, second_ptr--) {
		if (s[second_ptr] != ' ') {
			s[first_ptr] = s[second_ptr];
		}
		else {
			s[first_ptr] = '0';
			s[first_ptr - 1] = '2';
			s[first_ptr - 2] = '%';
			first_ptr -= 2;
		}

	}
	return s;
}
void reverse_word(string& s, int start, int end) {
	for (int i = start, j = end; i < j; i++, j--) {
		swap(s[i], s[j]);
	}
}
void reverse_each_word(string& s) {
	//Step 1; remove redundant spaces as required
	int slow_ptr = 0, fast_ptr = 0;
	//use a while loop to remove the spaces at the front because you can have more than one space
	while (s.size() > 0 && fast_ptr < s.size() && s[fast_ptr] == ' ') {
		fast_ptr++;//slow_ptr remains at the beginning
	}
	//use a for loop to remove consecutive spaces in the middle
	for (; fast_ptr < s.size(); fast_ptr++) {
		if (fast_ptr - 1 > 0 && s[fast_ptr] == s[fast_ptr-1]&& s[fast_ptr] == ' ') {
			continue;
		}
		else {
			s[slow_ptr] = s[fast_ptr];
			slow_ptr++;
		}
	}
	//now to remove the spaces at the end
	if (slow_ptr - 1 > 0 && s[slow_ptr - 1] == ' ') {
		s.resize(slow_ptr - 1); 
		//since slow_ptr is the index of the string,
		//slow_ptr -1 is the number of elements with out the space 
	}
	else {
		s.resize(slow_ptr);
	}
	//Step2: reverse the entire string
	reverse_word(s, 0, s.size()-1);
	//Step3: reverse certain words
	bool word_entry = false; //use this bool to determine whether a word is found
	int start, end; //mark the start and end index of each word
	for (int i = 0; i < s.size(); i++) {
		//mark the beginning of each word
		if ((!word_entry) || (s[i] != ' ' && s[i - 1] == ' ')) {
			word_entry = true;
			start = i;
		}
		//find the end and perform reverse on the word
		if (word_entry && s[i] == ' ' && s[i - 1] != ' ') {
			end = i - 1;
			word_entry = false;
			//shor version of reverse_string
			reverse_word(s, start, end);
			
		}
		//find the end of the last word
		if (word_entry && (i == (s.size() - 1)) && s[i] != ' ') {
			end = i;
			word_entry = false;
			reverse_word(s, start, end);
		}
	}

	for (auto s : s) {
		cout << s;
	}
}
int main() {
	vector<int>test1= { 0,1,2,2,3,0,4,2 };
	vector<int>test2 = { 3,2,2,3 };
	vector<char>test3 = { 'h','e','l','l','o' };
	string test4 = "the sky is  blue ";
	//cout << remove_elements(test2,3);
	//reverse_string(test3);
	//cout << replace_space(test4);
	/*char a[5] = "asd+";
	for (int i = 0; a[i] != '\0';i++) {
		//the condition is met when the character is not equal to '\0'
		cout << a[i];
	}
	*/
	reverse_each_word(test4);
}