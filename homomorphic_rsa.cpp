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
    cout << "N " << n << " Phi " << phi << nl;

    // Finding the encryption key e
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

    // Finding the decryption key d
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

    cpp_int msg1 = cpp_int("12345678901234567890");
    cpp_int msg2 = cpp_int("98765432109876543210");
    cpp_int tot = msg1 * msg2;
    cpp_int Msg_Combined_cipher = power(msg1 * msg2, e, n);

    cout<<"Combined Msg : "<<tot<<endl;

    cpp_int cipher1 = power(msg1, e, n);
    cpp_int cipher2 = power(msg2, e, n);

    cpp_int Cipher_Combined = (cipher1 * cipher2) % n;

    cpp_int Decrypted_Combined = power(Msg_Combined_cipher, d, n);
    cpp_int Decrypted_Combined_Cipher = power(Cipher_Combined, d, n);

    cout << "Decrypted_Combined " << Decrypted_Combined << nl;
    cout << "Decrypted_Combined_Cipher " << Decrypted_Combined_Cipher << nl;

    return 0;
}
