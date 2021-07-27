int a;
int b[3];
int func(int x){
    int y;
    y = b[2];
    return x + y;
}
void main(void){
    int num;
    num = 2;
    num = func(a);
}
