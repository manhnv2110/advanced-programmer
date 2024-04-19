#include <iostream>

using namespace std;

char *concat(const char *str1,const char *str2){
	int l = strlen(str1) + strlen(str2);
	char *result = new char[l+1]; 
	strcpy(result, str1);
	strcat(result, str2);
	return result;
}

int main (){
	char *str1 ="NguyenVanManh";
	char *str2 ="CA1";
	char *result = concat(str1, str2);
	cout << result; 
	delete[] result;
	return 0;
}