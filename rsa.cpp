#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>

using namespace std;
using namespace boost::multiprecision;

#define nl "\n"

// Function to compute the greatest common divisor
cpp_int gcd(cpp_int a, cpp_int b)
{
    if (b == 0)
    {
        return a;
    }
    return gcd(b, a % b);
}

// Function to perform modular exponentiation
cpp_int power(cpp_int b, cpp_int p, cpp_int mod)
{
    b = b % mod;
    if (p == 0)
        return 1;
    cpp_int j = power(b, p / 2, mod);
    j = (j * j) % mod;
    if (p % 2 == 1)
        j = (j * b) % mod;
    return j;
}

int main()
{
    // Large primes with around 20 digits each
    cpp_int p = cpp_int("898657262941183405798131083479");
    cpp_int q = cpp_int("911495894733986216008917853021");
    cpp_int n = p * q;
    cpp_int phi = (p - 1) * (q - 1);
    cout << "N " << n << " Phi " << phi << nl;

    cpp_int e;
    cpp_int tempE = 2;
    cpp_int c_gcd = 0;
    while (c_gcd != 1 && tempE < phi)
    {
        c_gcd = gcd(tempE, phi);
        if (c_gcd == 1)
        {
            e = tempE;
            break;
        }
        tempE++;
    }
    cout << "Encryption Key-> " << e << nl;

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
    cout << "Decryption Key-> " << d << nl;

    cpp_int msg = cpp_int("1234567890123456789012345678901234567890"); // A large message
    cout << "msg " << msg << nl;
    cpp_int cipher = power(msg, e, n);
    cout << "cipher " << cipher << nl;
    cpp_int decrypted = power(cipher, d, n);
    cout << "decrypted msg " << decrypted << nl;

    return 0;
}
