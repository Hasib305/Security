#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;
using namespace std;

cpp_int modinv(cpp_int a, cpp_int m) {
    cpp_int m0 = m, t, q;
    cpp_int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {

        q = a / m;
        t = m;

        // m is remainder now, process same as the Euclid's algorithm
        m = a % m, a = t;
        t = x0;

        x0 = x1 - q * x0;
        x1 = t;
    }

    // Make x1 positive
    if (x1 < 0)
        x1 += m0;

    return x1;
}


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

int main() {
    cpp_int p, a, alpha, beta, k;


    p = cpp_int("6421");
    a = cpp_int("3");
    alpha = cpp_int("11");

    beta = calculating(alpha, a, p);
    k = cpp_int("7");

    cout << "Enter message m: ";
    cpp_int m;
    cin >> m;

    cpp_int y1 = calculating(alpha, k, p);
    cout << "y1: " << y1 << endl;

    cpp_int gg = (m - a * y1) * modinv(k, p - 1);
    cpp_int y2 = ((gg % (p - 1)) + (p - 1)) % (p - 1);
    cout << "y2: " << y2 << endl;

    cpp_int first = (calculating(y1, y2, p) * calculating(beta, y1, p)) % p;
    cpp_int second = calculating(alpha, m, p);

    cout << "First- " << first << " Second- " << second << endl;

    if (first == second) {
        cout << "Signature valid" << endl;
    } else {
        cout << "Signature not valid" << endl;
    }

    return 0;
}
