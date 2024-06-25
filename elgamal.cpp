#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <cstdlib> // For rand() function
#include <ctime> // For time() function

using namespace std;
using namespace boost::multiprecision;

#define nl "\n"

// Function to perform modular exponentiation
cpp_int calculating(cpp_int g, cpp_int x, cpp_int p)
{
    cpp_int res = 1;
    g = g % p;
    while (x > 0)
    {
        if (x % 2 == 1)
            res = (res * g) % p;
        x = x >> 1;
        g = (g * g) % p;
    }
    return res;
}

int main()
{
    // Seed the random number generator
    srand(time(0));

    cpp_int g, y, p, x;
    p = cpp_int("53566473908509450873"); // Large prime number (around 19 digits)
    x = cpp_int("12345678901234567890"); // Private key
    g = cpp_int("5"); // Generator

    y = calculating(g, x, p); // Public key
    cout << "Public key (y): " << y << nl;

    cpp_int m = cpp_int("9223372036854775806"); // Large message

    // Generate a small random value using rand()
    cpp_int r = rand() % (p - 1) + 1; // Random value in the range [1, p-1]

    cpp_int c1 = calculating(g, r, p);
    cpp_int c2 = (m * calculating(y, r, p)) % p;

    cpp_int dm = (c2 * calculating(c1, p - 1 - x, p)) % p;

    cout << "Message: " << m << nl;
    cout << "Encryption: " << c1 << " " << c2 << nl;
    cout << "After decryption: " << dm << nl;

    return 0;
}
