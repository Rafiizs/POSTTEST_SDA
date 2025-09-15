#include <iostream>
using namespace std;

int main() {
    const int N = 3;
    int matriks[N][N];

    cout << "Masukkan elemen matriks 3x3:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> matriks[i][j];
        }
    }

    int jumDiagUtama = 0, jumDiagSekunder = 0;
    for (int i = 0; i < N; i++) {
        jumDiagUtama += matriks[i][i];
        jumDiagSekunder += matriks[i][N - 1 - i];
    }

    cout << "\nMatriks:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << matriks[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Jumlah diagonal utama + diagonal sekunder = "
         << (jumDiagUtama + jumDiagSekunder) << endl;

    return 0;
}
