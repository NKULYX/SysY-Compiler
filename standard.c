int f(int a, int b, int c, int d, int e) {
    return a + b + c + d + e ;
}

int abc = 10;

int main() {
    abc = 1;
    int a = 1, b = 2, c = 3, d = 4, e = 5, ff = 6, g = 7;
    int res = f(a, b, c, abc, e);
    res += abc;
    return res;
}