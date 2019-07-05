#include <iostream>

#define DPRINT(ARG) std::cout << #ARG << " = " << ARG << std::endl;

int main(int argc, char** argv) {
	int i = 3;
	{
		int i = 2;
		{
			int i = 1;
			{
				int i = 0;
				{
					DPRINT(i);
				}
			}
			DPRINT(i);
		}
		DPRINT(i);
	}
	DPRINT(i);
	return 0;
}
