#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <cstdlib> // For rand() function
#include <ctime>   // For time() function

using namespace std;
using namespace boost::multiprecision;

#define nl "\n"

// Function to perform modular exponentiation
cpp_int power(cpp_int base, cpp_int exp, cpp_int mod) {
    cpp_int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) // If exp is odd, multiply base with result
            result = (result * base) % mod;
        exp = exp >> 1; // Divide exp by 2
        base = (base * base) % mod; // Square the base
    }
    return result;
}

// Function to calculate modular inverse using Extended Euclidean Algorithm
cpp_int modinv(cpp_int a, cpp_int m) {
    cpp_int m0 = m, t, q;
    cpp_int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        q = a / m;
        t = m;

        m = a % m, a = t;
        t = x0;

        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

// Function to generate a random number in the range [1, p-1]
cpp_int generateRandom(cpp_int p) {
    cpp_int r;
    do {
        r = rand() % (p - 1) + 1; // Generate random number in the range [1, p-1]
    } while (gcd(r, p) != 1); // Ensure r is coprime with p (gcd(r, p) == 1)
    return r;
}

// ElGamal Encryption function
pair<cpp_int, cpp_int> elgamalEncrypt(cpp_int m, cpp_int p, cpp_int g, cpp_int y) {
    cpp_int r = generateRandom(p); // Generate random r
    cpp_int c1 = power(g, r, p);   // c1 = g^r mod p
    cpp_int c2 = (power(y, r, p) * m) % p; // c2 = y^r * m mod p
    return make_pair(c1, c2);
}

// ElGamal Decryption function
cpp_int elgamalDecrypt(cpp_int c1, cpp_int c2, cpp_int p, cpp_int x) {
    cpp_int s = power(c1, x, p); // s = c1^x mod p
    cpp_int plaintext = (c2 * modinv(s, p)) % p; // m = c2 * (s^-1 mod p) mod p
    return plaintext;
}

int main() {
    // Seed the random number generator
    srand(time(0));

    cpp_int p = cpp_int("53566473908509450873"); // Large prime number (around 19 digits)
    cpp_int g = cpp_int("5");                   // Generator
    cpp_int x = cpp_int("12345678901234567890"); // Private key
    cpp_int y = power(g, x, p);                  // Public key

    cout << "Public key (y): " << y << nl;

    cpp_int m1 = cpp_int("9223372036854775806"); // Large message 1
    cpp_int m2 = cpp_int("9876543210987654321"); // Large message 2

    // Encrypt messages
    auto encrypted1 = elgamalEncrypt(m1, p, g, y);
    auto encrypted2 = elgamalEncrypt(m2, p, g, y);

    cout << "Message 1: " << m1 << nl;
    cout << "Message 2: " << m2 << nl;

    cout << "Encryption 1 (c1, c2): " << encrypted1.first << ", " << encrypted1.second << nl;
    cout << "Encryption 2 (c1, c2): " << encrypted2.first << ", " << encrypted2.second << nl;

    // Homomorphic addition: multiply ciphertexts together
    cpp_int c1_product = (encrypted1.first * encrypted2.first) % p;
    cpp_int c2_product = (encrypted1.second * encrypted2.second) % p;

    cout << "Homomorphic Encryption (c1, c2): " << c1_product << ", " << c2_product << nl;

    // Decrypt the result
    cpp_int decrypted_result = elgamalDecrypt(c1_product, c2_product, p, x);
    cout << "Decrypted Result: " << decrypted_result << nl;

    // Verification
    if (decrypted_result == (m1 * m2) % p) {
        cout << "Verification: Decrypted result matches the product of messages." << nl;
    } else {
        cout << "Verification: Decrypted result does not match the product of messages." << nl;
    }

    return 0;
}
