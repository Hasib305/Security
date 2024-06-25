#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <vector>
#include <map>
#include<set>
using namespace boost::multiprecision;
using namespace std;

cpp_int power(cpp_int b, cpp_int p, cpp_int mod)
{
    cpp_int res = 1;
    while(p > 0)
    {
        if(p % 2 != 0)
        {
            res = (res * b) % mod;
        }
        p = p / 2;
        b = (b * b) % mod;
    }
    return res % mod;
}

int main()
{
    cpp_int p = 67;
    vector<cpp_int> primitives;

    for(cpp_int i = 1; i <= p - 1; i++)
    {
          set<cpp_int>s;
        map<cpp_int, cpp_int> cnt;

       cpp_int flag=1;

        for(cpp_int j = 1; j <= p - 1; j++)
        {
            cpp_int ans = power(i, j, p);


            cnt[ans]++;
            if(cnt[ans] > 1)
            {
                flag = false;
                break;
            }
        }

        if(flag)
        {
            primitives.push_back(i);
        }
    }

    cout << "Total " << primitives.size() << "\n";
    for(auto x : primitives)
    {
        cout << x << " ";
    }
    cout << "\n";

    return 0;
}



