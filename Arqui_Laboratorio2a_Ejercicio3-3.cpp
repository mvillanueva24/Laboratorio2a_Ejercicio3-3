#include <iostream>
#include <string>

using namespace std;

void mostrar_binario(int arr[], int n) {
    for (int i = n - 1; i >= 0; i--) {
        cout << arr[i];
    }
    cout << endl;
}

void sumar(int A[], int M[], int n) {
    int carry = 0;
    for (int i = 0; i < n; i++) {
        int sum = A[i] + M[i] + carry;
        A[i] = sum % 2;
        carry = sum / 2;
    }
}

void restar(int A[], int M[], int n) {
    int M_complemento[8], carry = 1;
    for (int i = 0; i < n; i++) {
        M_complemento[i] = M[i] ^ 1;
    }
    for (int i = 0; i < n; i++) {
        int sum = M_complemento[i] + carry;
        M_complemento[i] = sum % 2;
        carry = sum / 2;
        if (carry == 0) break;
    }
    sumar(A, M_complemento, n);
}

void carry(int A[], int Q[], int& Q_1, int n) {
    int A_MSB = A[n - 1];
    Q_1 = Q[0];
    for (int i = 0; i < n - 1; i++) {
        Q[i] = Q[i + 1];
    }
    Q[n - 1] = A[0];
    for (int i = 0; i < n - 1; i++) {
        A[i] = A[i + 1];
    }
    A[n - 1] = A_MSB;
}

void multiplicar(int M[], int Q[], int n) {
    int A[8] = { 0 }, Q_1 = 0, count = n;
    cout << "Estado inicial:\n";
    cout << "A: "; mostrar_binario(A, n);
    cout << "Q: "; mostrar_binario(Q, n); cout << "Q-1: " << Q_1 << "\n";
    cout << "-----------------------------------------\n";
    cout << "-----------------------------------------\n";
    while (count--) {
        if (Q[0] == 1 && Q_1 == 0) { restar(A, M, n); cout << "Restar A = A - M: A = "; mostrar_binario(A, n); }
        if (Q[0] == 0 && Q_1 == 1) { sumar(A, M, n); cout << "Sumar A = A + M: A = "; mostrar_binario(A, n); }
        carry(A, Q, Q_1, n);
        cout << "Corrimiento: A = "; mostrar_binario(A, n);
        cout << "Q = "; mostrar_binario(Q, n);
        cout << "Q-1: " << Q_1 << "\n";
        cout << "-----------------------------------------\n";
    }
    cout << "Producto de los dos valores:\n";
    cout << "A: "; mostrar_binario(A, n);
    cout << "Q: "; mostrar_binario(Q, n);
}

int main() {
    int num;
    string multiplicando, multiplicador;
    int len;
    cout << "Ingrese el numero de bits: "; cin >> num;
    cout << "Ingrese el primer valor en binario: "; cin >> multiplicando;
    cout << "Ingrese el segundo valor en binario: "; cin >> multiplicador;
    int M[8], Q[8];

    len = multiplicando.length();
    for (int i = 0; i < num; i++) {
        if (i < len) {
            M[i] = multiplicando[len - 1 - i] - '0';
        }
        else {
            M[i] = 0;
        }
    }

    len = multiplicador.length();
    for (int i = 0; i < num; i++) {
        if (i < len) {
            Q[i] = multiplicador[len - 1 - i] - '0';
        }
        else {
            Q[i] = 0;
        }
    }

    multiplicar(M, Q, num);
    return 0;
}
