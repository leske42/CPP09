#include <iostream>
#include <cmath>
#include <cstdlib>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
    	std::cerr << "Please provide only one argument (n)." << std::endl;
    	return (0);
    }
    int k = 1;
    int n = atoi(argv[1]);
    float res = 0.0;
    float a = 3.0;
    float b = 4.0;
    while (k <= n)
    {
    	res += ceil(log2((a/b) * k));
    	k++;
    }
    std::cout << res << std::endl;
}
