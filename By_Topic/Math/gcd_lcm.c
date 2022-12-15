/*
The Euclidean algorithm is a method for finding the greatest common divisor (GCD)
of two numbers. It is named after the ancient Greek mathematician Euclid, 
who first described it in his book "Elements".

Here is how the algorithm works:

If the two numbers are equal, then the GCD is that number.
If the two numbers are not equal, then subtract the smaller number 
from the larger number and repeat the process with the result and the smaller number.
For example, to find the GCD of 24 and 16, we first subtract the smaller number (16) from the larger number (24), to get 24 - 16 = 8. Then, we repeat the process with the result and the smaller number, to get 16 - 8 = 8. Since 8 is the same as the result in the previous step, we know that 8 is the GCD.

To prove that this algorithm always finds the GCD, we need to show that it satisfies the three properties of the GCD:

The GCD divides both numbers.
The GCD is the largest number that divides both numbers.
Any common divisor of the two numbers divides the GCD.
We can prove these properties using mathematical induction.

First, let's prove property 1. 
Suppose that the GCD of two numbers, a and b, is d. 
Then, we can write a = d * x and b = d * y, where x and y are integers. 
Since d divides both a and b, it must also divide their difference, a - b = d * (x - y).
Now, suppose that the Euclidean algorithm has reached the step where it is subtracting a - b, 
and let's call this result c. 
Since c = a - b = d * (x - y), d must also divide c. 
This means that d is a common divisor of both a and b, which proves property 1.

Next, let's prove property 2. Suppose that the GCD of two numbers, a and b, is d. 
Then, by property 1, d must divide both a and b. 
This means that any common divisor of a and b must also divide d.

Now, let's suppose that the Euclidean algorithm has reached the step where it is subtracting a - b, and let's call this result c. Since c is a common divisor of both a and b, it must also divide d. This means that d is the largest number that divides both a and b, which proves property 2.

Finally, let's prove property 3. Suppose that the GCD of two numbers, a and b, is d. Then, by property 1, d must divide both a and b. This means that any common divisor of a and b must also divide d.

Now, let's suppose that the Euclidean algorithm has reached the step where it is subtracting a - b, and let's call this result c. Since c is a common divisor of both a and b, it must also divide d. This means that any common divisor of a and b must also divide c, which proves property 3.

In conclusion, we have shown that the Euclidean algorithm satisfies the three properties of the GCD, which means that it always finds the GCD of two numbers.




*/

#include <stdio.h>

typedef long long ll_t;

ll_t gcd(ll_t a, ll_t b)
{
    if (b > a) {
        ll_t temp = a;
        a = b;
        b = temp;
    }
    while (b != 0) {
        int rem = a % b;
        a = b;
        b = rem;
    }
    return a;
}


ll_t lcm(ll_t a, ll_t b)
{
    return a*b/gcd(a,b);
}

int main(int argc, char const *argv[])
{
    ll_t a = 252, b = 105;
    printf("CGD of %lld and %lld is = %lld\n", a, b, gcd(a,b));
    printf("LCM of %lld and %lld is = %lld\n", a, b, lcm(a,b));

    return 0;
}
