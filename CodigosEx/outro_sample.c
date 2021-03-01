/* Um programa para ordenação por seleção de uma matriz com dez elementos. */
int xg[10];
int minloc ( int a[], int low, int high ) { 
    int i; 
    int x; 
    int k; 
    k = low; 
    x = a[low]; 
    i = low + 1;
    while (i < high) {
        if (a[i] < x) {
            x = a[i]; 
            k = i; 
        } 
        i = i + 1;
    } 
    return k; 
}

void sort( int a[], int low, int high) {
    int i; 
    int k; 
    i = low;
    while (i < high-1) { 
        int t;
        k = minloc(a[0],i,high); 
        t = a[k]; 
        a[k] = a[i]; 
        a[i] = t; 
        i = i + 1;
    } 
}

void main(void) { 
    int i; 
    i = 0;
    while (i < 10) {
        xg[i] = input();
        i = i + 1; 
    }
    sort(xg[0],0,10); i = 0;
    while (i < 10) { 
        output(xg[i]); 
        i = i + 1; 
    }
}
