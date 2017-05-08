//EP4 by Zhou Xiao
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<map>
#include<vector>
using namespace std;

int main() {
	int len;
	cout << "Please input the number of letters of suffix:" <<endl;
	cin >> len;
	string wordlist;
	vector<string>list;
	map<string, int>suf;
	ifstream filename("dictionary.txt");
	while (getline(filename, wordlist)) {
		for (int i = 0;i<wordlist.size(); ++i) {
				string word = "";
				for (int j = wordlist.size() - len; j < wordlist.size(); ++j) {
					word = word + wordlist[j];
				}
				++suf[word];
				break;
		}}
	map<string, int>newmap = suf;
	while (!suf.empty())
	{   int max = 0;
		for (map<string, int>::iterator j = suf.begin(); j != suf.end(); j++){
			if (suf[j->first] >= max){
				max = suf[j->first];
			}}
		for (map<string, int>::iterator j = suf.begin(); j != suf.end();){
			if (suf[j->first] == max){   
				list.push_back(j->first);
				suf.erase(j++);}
			else{
				j++;
			}}}
	for (int k = 0; k < 10; ++k) {
		cout << list[k] << "  " << newmap[list[k]] << endl;
	}
	string sufname;
	cout << "Please enter the suffix you want to query:" << endl;
	cin >> sufname;
	cout << newmap[sufname] << '\n' << endl;
	
}
