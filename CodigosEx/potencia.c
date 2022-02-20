void main(void) { 
    int x; 
    int y;
    int xElevy;
    x = input(); 
    y = input(); 
    xElevy = x;
    while(y >= 2){
        xElevy = xElevy*x;
        y = y - 1;
    }
    output(xElevy);
}
