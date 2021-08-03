int fatorial (int n){
    if (n == 1)
        return 1;
    else{
        return n * fatorial(n-1) ;
    }
}
int main (void){
    int n ;
    int fat ;
    n = input() ;
    fat = fatorial(n) ;
    output(fat) ;
}
