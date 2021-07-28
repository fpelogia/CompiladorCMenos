int a;
int b[3];
int func(int x){
    int y;
    y = b[1];
    return x + y;
}
void main(void){
    int num;
    num = 2;
    b[0] = func(a);
}
