#include <iostream>
#include <string>
using namespace std;

#define ll long long
#define pll pair<long long, long long>

void get_prime_factorization(ll n, pll & fact_counter)
{
    while(true)
    {
        if (n % 2 == 0)
        {
            fact_counter.first++;
            n /= 2;
        } else if (n % 5 == 0)
        {
            fact_counter.second++;
            n /= 5;
        } else {
            break;
        }
    }
}


ll recursive_divide(ll factorial, pll & fact_counter)
{
    if (factorial % 2 == 0 && fact_counter.first > 0)
    {
        fact_counter.first -= 1;
        return recursive_divide(factorial / 2, fact_counter);
    } else if (factorial % 5 == 0 && fact_counter.second > 0) {
        fact_counter.second -= 1;
        return recursive_divide(factorial / 5, fact_counter);
    } else {
        return factorial;
    }
}


void get_threedigits(pll fact_counter, ll factorial)
{

    ll intermidiate{1};

    for (ll i{factorial}; i > 0; i--)
    {
        ll result {recursive_divide(i, fact_counter)};
        cout << result * intermidiate << " % 1000 = " << (result * intermidiate) % 1000 << endl;
        intermidiate = (result * intermidiate) % 1000;
    }

    string result {to_string(intermidiate)};
    if (result.size() == 1 && factorial > 7)
        cout << "00" << intermidiate << endl;
    else if (result.size() == 2 && factorial > 7)
        cout << "0" << intermidiate << endl;
    else
        cout << intermidiate << endl;

}


int main()
{
    ll factorial{};
    scanf("%lld", &factorial);
    pll prime_fact_counter{};

    for (ll i{1}; i <= factorial; i++)
    {
        get_prime_factorization(i, prime_fact_counter);
    }

    if(prime_fact_counter.first < prime_fact_counter.second)
        prime_fact_counter.second = prime_fact_counter.first;
    else
        prime_fact_counter.first = prime_fact_counter.second;   

    get_threedigits(prime_fact_counter, factorial);

    return 0;
}