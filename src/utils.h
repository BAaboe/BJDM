#include <string>

using namespace std;


//gives number of lines in a fiel. Dont know why it's here
int getNumberOfLines(string fileName);


//splits string on del
string* adv_tokenizer(string s, char del, int len);