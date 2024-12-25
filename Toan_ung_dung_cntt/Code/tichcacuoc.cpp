#include <iostream>
#include <vector>
#include <string>
using namespace std;

string multiply(string num1, int num2)
{
    if (num2 == 0 || num1 == "0")
        return "0";
    int carry = 0;
    string result = "";

    for (int i = num1.length() - 1; i >= 0; --i)
    {
        int product = (num1[i] - '0') * num2 + carry;
        result = char(product % 10 + '0') + result;
        carry = product / 10;
    }

    while (carry)
    {
        result = char(carry % 10 + '0') + result;
        carry /= 10;
    }

    return result;
}

string tichcacuoctu1denN(int N)
{
    vector<string> dp(N + 1, "1");

    for (int i = 1; i <= N; ++i)
    {
        for (int j = i; j <= N; j += i)
        {
            dp[j] = multiply(dp[j], i);
        }
    }

    return dp[N];
}

int main()
{
    int N;
    cout << "Nhap N = ";
    cin >> N;

    string result = tichcacuoctu1denN(N);
    cout << "Tich cac uoc cua " << N << " la: " << result << endl;

    return 0;
}
