#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>

using namespace boost::multiprecision;
using namespace std;

cpp_int power(cpp_int b, cpp_int p, cpp_int mod)
{
    b = b % mod;
    if(p == 0)
        return 1;
    cpp_int j = power(b, p / 2, mod);
    j = (j * j) % mod;
    if(p % 2 == 1)
        j = (j * b) % mod;
    return j;
}

int main()
{
    cpp_int e("10000019");
    cpp_int n = 20000900009;
    cpp_int msg("20000000000");
    cout << "Message: " << msg << endl;
    cpp_int cypher = power(msg, e, n);
    cout << "Cypher: " << cypher << endl;

    cpp_int d("6283524500");
    while(true)
    {
        cpp_int new_msg = power(cypher, d, n);
        if(new_msg == msg)
        {
            cout << "New Message: " << new_msg << endl;
            cout << "Private key: " << d << endl;
            break;
        }
        d++;
    }

    return 0;
}