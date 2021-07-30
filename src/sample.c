int a;
int b[3];
int func(int x){
    int y;
    y = b[1];
    return x[0] + y;
}
void main(void){
    int varx;
    int num;
    num = 2;
    b[77] = func(5);
}
