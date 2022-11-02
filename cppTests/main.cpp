#include <iostream>
#include <type_traits>

using namespace std;
uint32_t n1;
const uint32_t n3 = 2342;
string msg;


int main(void)
{

    cout << "input the number: " << endl;
    cin >> n1;
    n1 = 2 * n1;
    if constexpr(is_same_v<const uin32_t, decltype(n1)>)
        msg = "type is const uint32_t";

    cout << "the number is: " << n1 << endl;
    return 0;
}