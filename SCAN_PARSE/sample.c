/* Um programa para calcular o mdc segundo o algoritmo de Euclides 
int gcd (int u, int v)
{   int x;
    if (v == 0){
        return u;
    }else { 
        return gcd(v,u-u/v*v);
    }
}
*/
void parab(int x[], int n)
{   
    int i;
    i = 0;
    while (i < n){
        x[i] = i*i; /* funcao quadratica*/
    }
    output(x + y[x = 2],2);
    return;
    /*output(gcd(x,y));*/
}


/*
int x;
int y[3];
int main(int param1, int param2){
    int localvar1;
    int localvar2;
    if (localvar2 <  3){
        localvar1 = 2;
    }
    param1[2] = 3 + 4;
    return 0;
}*/
