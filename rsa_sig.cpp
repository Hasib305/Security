#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>

using namespace std;
using namespace boost::multiprecision;

#define nl "\n"

// Function to compute the greatest common divisor
cpp_int gcd(cpp_int a, cpp_int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to perform modular exponentiation
cpp_int power(cpp_int a, cpp_int p, cpp_int mod)
{
    cpp_int res = 1;
    a = a % mod;
    while (p > 0)
    {
        if (p % 2 == 1) // If p is odd, multiply a with result
            res = (res * a) % mod;
        p = p >> 1;     // p = p / 2
        a = (a * a) % mod; // Change a to a^2
    }
    return res;
}

int main()
{
    // Large primes with around 20 digits each
    cpp_int p = cpp_int("898657262941183405798131083479");
    cpp_int q = cpp_int("911495894733986216008917853021");

    cpp_int n = p * q;
    cpp_int phi = (p - 1) * (q - 1);

    cpp_int can_e = 2;
    cpp_int e = 2;
    while (can_e < phi)
    {
        cpp_int c_gcd = gcd(can_e, phi);
        if (c_gcd == 1)
        {
            e = can_e;
            break;
        }
        can_e++;
    }

    cpp_int d;
    cpp_int k = 1;
    while (true)
    {
        cpp_int j = (phi * k) + 1;
        if (j % e == 0)
        {
            d = j / e;
            break;
        }
        k++;
    }

    cpp_int m = cpp_int("1234567890123456789012345678901234567890"); // A large message
    cout << "Private key(p,q,d) " << p << ", " << q << ", " << d << nl;
    cout << "Public key(e,n) " << e << ", " << n << nl;
    cout << "Msg " << m << nl;

    // Signing
    cpp_int s = power(m, d, n);
    cout << "Signing " << s << nl;

    // Verification
    cpp_int v = power(s, e, n);
    cout << "Verification " << v << nl;

    if (v == m)
    {
        cout << "Verified" << nl;
    }
    else
    {
        cout << "Not Verified" << nl;
    }

    return 0;
}
