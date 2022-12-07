/*
Divide the message into N blocks of 512 bits each.
For each block K in the list of N blocks, do:
Divide K into 16 words (W(0) to W(15) say)
For t = 16 to 79 do:
W(t) = (W(t-3) XOR W(t-8) XOR W(t-14) XOR W(t-16)) <<< 1
Assign A = H0, B = H1, C = H2, D = H3, E = H4
For t = 0 to 79 do:
Tmp = A <<< 5 + f(t; B, C, D) + E + W(t) + K(t)
E = D; D = C; C = B <<< 30, B = A, A = Tmp
H0 = H0 + A; H1 = H1 + B; H2 = H2 + C; H3 = H3 + D; H4 = H4 + E
Output: The contents of H0, H1, H2, H3 and H4 are returned in sequence as the final hash.
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

//buffor
const string H0 = "0x67452301", H1 = "0xEFCDAB89", H2 = "0x98BADCFE", H3 = "0x10325476", H4 = "0xC3D2E1F0";

string function(int t,string A,string B,string C,string D){
	if (t<=19)	return ((B && A)||(!B) && D);
	if((t>=20)&&(t<=39))	return(B^C^D);
	if((t>=40)&&(t<=59))	return((B&&C)||(B&&D)||(C&&D));
	if((t>=20)&&(t<=39))	return(B^C^D);
}

string proccesing(int t){
	if (t<=19)				return 0x5A827999;
	if((t>=20)&&(t<=39))	return 0x6ED9EBA1;
	if((t>=40)&&(t<=59))	return 0x8F1BBCDC;
	if((t>=20)&&(t<=39))	return 0xCA62C1D6;
}


unsigned int Hash(string a){
	int n=a.size();
	unsigned int result=0;
	for(int i=0;i<n;i++){
			result=i+(result<<4)+(result<<10) -result;
			cout<<i<<"\t"<<result<<endl;
			}
	return result;
}

int main()
{
 	string password;
 	cin>>password;
 	for(int i=0;i<password.size();i++)
 	cout<<password[i]<<" -> "(int)password[i]<<endl;
 	return 0;
}
