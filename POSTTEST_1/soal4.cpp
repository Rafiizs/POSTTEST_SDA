#include <iostream>
using namespace std;

void tukar(int **a, int **b) {
    int temp = **a;
    **a = **b;
    **b = temp;
}

int main() {
    int x, y;
    cout << "Masukkan nilai pertama: ";
    cin >> x;
    cout << "Masukkan nilai kedua  : ";
    cin >> y;

    cout << "Sebelum ditukar: x=" << x << ", y=" << y << endl;

    int *px = &x;
    int *py = &y;
    tukar(&px, &py);

    cout << "Sesudah ditukar: x=" << x << ", y=" << y << endl;
    return 0;
}
