/* Um programa para calcular o mdc segundo o algoritmo de Euclides */

int gcd (int u, int v)
{   int (v == 0) return u;
    /* OI! */
    else return gcd(v,u-u/v*v); 
    /* u-u/v*v == u mod v */
}

void main(void)
{   int x; int y;
    x = input(); y = input();
    output(gcd(x,y));
}
