#include <string>
#include <vector>
using namespace std;

#define INSERT_PREFIX(counter) id ## counter
#define MAKE_ID(counter) INSERT_PREFIX(counter)
#define UNIQ_ID MAKE_ID(__COUNTER__)

int main() {
	int UNIQ_ID = 0;
	string UNIQ_ID = "hello";
	vector<string> UNIQ_ID = { "hello", "world" };
	vector<int> UNIQ_ID = { 1, 2, 3, 4 };

	int UNIQ_ID = 5; string UNIQ_ID = "hello"; // В рамках данной задачи допускается, что код не будет компилироваться. 
}
