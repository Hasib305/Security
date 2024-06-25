#include <bits/stdc++.h>
using namespace std;
#define int            long long int
#define nl             "\n"


int32_t main()
{
    string plaintext;
    string key;
    cin>>plaintext;
    cin>>key;
    int col = key.size();
    int n = plaintext.size();
    int row = (n/col)+1;
    if( n%col != 0 )
    	row++;

    for( int i = 0 ; i < col ; i++ )
    {
    	key[i] = toupper(key[i]);
    }

    int keynum[col+10];
    int cnt = 1;
    for( char ch = 'A' ; ch <= 'Z' ; ch++ )
    {
    	for( int i = 0 ; i < col ; i++ )
    	{
    		if( key[i] == ch )
    		{
    			keynum[i] = cnt;
    			cnt++;
    		}
    	}
    }

    for( int i = 0 ; i < col ; i++ )
    {
    	cout<<keynum[i]<<" ";
    }
    cout<<nl<<nl;

    char mat1[row+10][col+10];
    char mat2[col+10][row+10];

    for( int i = 0 ; i < col ; i++ )
    {
    	mat1[0][i] =  '0'+keynum[i];
    }


    cnt = 0;
    for( int i = 1 ; i < row ; i++ )
    {
    	for( int j = 0 ; j < col ; j++ )
    	{
    		if( cnt < n )
    		{
    			mat1[i][j] = plaintext[cnt];
    			cnt++;
    		}
    		else
    		{
    			mat1[i][j] = '-';
    		}
    	}
    }

    for( int i = 0 ; i < row ; i++ )
    {
    	for( int j = 0 ; j < col ; j++ )
    	{
    		cout<<mat1[i][j]<<" ";
    	}
    	cout<<nl;
    }
    cout<<nl;


    for( int i = 0 ; i < col ; i++ )
    {
    	for( int j = 0 ; j < row ; j++ )
    	{
    		mat2[i][j] = mat1[j][i];
    	}
    }

    for( int i = 0 ; i < col ; i++ )
    {
    	for( int j = 0 ; j < row ; j++ )
    	{
    		cout<<mat2[i][j]<<" ";
    	}
    	cout<<nl;
    }
    cout<<nl;

    string cipher;
    cipher = "";
    int keycnt = col;
    for( int k = 1 ; k <= keycnt ; k++ )
    {
    	for( int i = 0 ; i < col ; i++ )
	    {
	    	for( int j = 1 ; j < row ; j++ )
	    	{
	    		if( mat2[i][0] == '0'+k )
	    		{
	    			cipher += mat2[i][j];
	    		}
	    	}
	    }
    }


    cout<<cipher<<nl;

    string decrypted;
    decrypted = "";
    for( int i = 1 ; i < row ; i++ )
    {
    	for( int j = 0 ; j < col ; j++ )
    	{
    		if( mat2[j][i] != '-' )
    		{
    			decrypted += mat2[j][i];
    		}
    	}
    }
    cout<<decrypted<<nl;
    return 0;
}
