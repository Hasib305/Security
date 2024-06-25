#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>

using namespace std;
using namespace boost::multiprecision;
using namespace boost::random;
namespace mp = boost::multiprecision;

typedef mp::cpp_int bigint;

bigint ModExp(bigint base, bigint exponent, bigint mod) {
    bigint result = 1;
    while (exponent > 0) {
        if (exponent & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exponent >>= 1;
    }
    return result % mod;
}

bigint GenerateRandomNumber(const bigint& max_exclusive) {
    boost::random::mt19937 generator(static_cast<unsigned int>(time(nullptr)));
    boost::random::uniform_int_distribution<bigint> distribution(1, max_exclusive - 1);
    return distribution(generator);
}

bigint ModularInverse(bigint a, bigint m) {
    bigint m0 = m, t, q;
    bigint x0 = 0, x1 = 1;

    if (m == 1) return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0) x1 += m0;

    return x1;
}

bigint GCD(bigint a, bigint b) {
    while (b != 0) {
        bigint temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void GenerateKeys(const bigint& p, const bigint& q, bigint& publicModulus, bigint& publicBase, bigint& privateLambda, bigint& privateMu) {
    publicModulus = p * q;
    bigint phi = (p - 1) * (q - 1);
    privateLambda = (p - 1) * (q - 1) / GCD(p - 1, q - 1); // LCM calculation using GCD
    publicBase = publicModulus + 1;
    bigint l_g = ModExp(publicBase, privateLambda, publicModulus * publicModulus);
    privateMu = ModularInverse((l_g - 1) / publicModulus, publicModulus);

    cout << "\nKeys have been successfully generated!" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Public Key (N, G): (" << publicModulus << ", " << publicBase << ")" << endl;
    cout << "Private Key (Lambda, Mu): (" << privateLambda << ", " << privateMu << ")" << endl;
    cout << "-------------------------------------------\n" << endl;
}

bigint Encrypt( bigint m,  bigint publicBase,  bigint publicModulus) {
    bigint r = GenerateRandomNumber(publicModulus);
    bigint gcd;
    while ((gcd = GCD(r, publicModulus)) != 1) {
        r = GenerateRandomNumber(publicModulus);
    }
    bigint c = (ModExp(publicBase, m, publicModulus * publicModulus) * ModExp(r, publicModulus, publicModulus * publicModulus)) % (publicModulus * publicModulus);
    cout << "Message encrypted successfully!" << endl;
    cout << "Encrypted message: " << c << "\n" << endl;
    return c;
}

bigint Decrypt(const bigint& c, const bigint& privateLambda, const bigint& privateMu, const bigint& publicModulus) {
    bigint l_c = ModExp(c, privateLambda, publicModulus * publicModulus);
    bigint message = ((l_c - 1) / publicModulus * privateMu) % publicModulus;
    cout << "Message decrypted successfully!" << endl;
    cout << "Decrypted message: " << message << "\n" << endl;
    return message;
}

int main() {
cpp_int p("670197397338703611192080945390927725697202258657636743682404629052313744270709616307049600030343962080302493858377710745187607247472224734121983597650570162798918484642908931512006860669574225979252915914752697573698683165230230774017453485913422255320582683220856562686379066285643486629151458074191");
    cpp_int q("605299228560284352724027832683920493112259727886161988913231446434143383374208105426479866437732036827723966643786014345133304382683944025140499120411397726385475721747586944805415936143873272044867015952453730334408333346228090738362377074757173858227902370097704924424438799901293577030173610947183");

bigint publicModulus, publicBase, privateLambda, privateMu;

    GenerateKeys(p, q, publicModulus, publicBase, privateLambda, privateMu);

    bigint m = 5347102683;
    bigint encrypted_message = Encrypt(m, publicBase, publicModulus);
    bigint decrypted_message = Decrypt(encrypted_message, privateLambda, privateMu, publicModulus);

    if (decrypted_message == m) {
        cout << "Success: The original message and the decrypted message match!" << endl;
    } else {
        cout << "Error: The decrypted message does not match the original!" << endl;
    }

    return 0;
}
