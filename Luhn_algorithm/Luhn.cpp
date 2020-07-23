
#include<iostream>
#include<cstdio>
using namespace std;

int main()
{
  int counting;


  string data;
  while(cin>>counting && counting!=EOF)
  {
    for( int i = 0 ; i < counting ; i++ )
	{
      int odd = 0,even=0;


      for( int j = 0 ; j < 4 ; j++ )
	  {
        cin >> data;
        odd += (data[1]-'0')+(data[3]-'0');
        even += ((data[0]-'0')*2)/10 + ((data[0]-'0')*2)%10 + ((data[2]-'0')*2)/10 + ((data[2]-'0')*2)%10;
      }

      if((odd+even)%10)
	  {
	  	cout<<"Invalid"<<endl;
	  }
	  else cout<<"Valid"<<endl;
	}
  }
  return 0;
}

