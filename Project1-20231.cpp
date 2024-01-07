#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <conio.h>
using namespace std;
map<string, int> id;
set<string> seen;
int n;

struct Data
{
    string symbol;  // tin
    double prob;    // xac suat
    string code;    // tu ma
    Data() : symbol(""), prob(0), code("") {}
};
vector<Data> sto;

bool cmp(Data x, Data y)
{
    return (x.prob > y.prob);
}

void symbolInput()
{
    string s;
    while (true) {
        cout << "Nhap so tin cua nguon: ";
        cin >> n;

        if (n == 0) {
            cout << "So tin khong the bang 0. Vui long nhap lai.\n";
        }
        else break;
    }

    sto = vector<Data>(n);

    for (int i = 0; i < n; i++)
    {
        cout << "Nhap tin thu " << i + 1 << " : ";
        cin >> s;
        if (seen.count(s)) {
            cout << "Loi: da co tin nay truoc do. Vui long nhap lai!\n";
            i--;
        }
        else {
            sto[i].symbol = s;
            seen.insert(s);
        }
    }
}
bool probInput() {
    system("cls");
    double p, sumP = 0;
    for (int i = 0; i < n; i++) {
        cout << "Nhap xac suat cua tin " << sto[i].symbol << " : ";
        cin >> p;

        if (sumP + p > 1)
        {
            cout << "Loi: tong cac xac suat vuot qua 1. Hay nhap lai: \n";
            cout << "[1] Nhap lai xac suat hien tai\n";
            cout << "[2] Nhap lai toan bo xac suat\n";
            char c;
            while (true) {
                c = _getch();
                if (c == '1' || c == '2') break;
            }
            if (c == '1') i--;
            else return true;
        }
        else
        {
            sumP += p;
            sto[i].prob = p;
        }
    }
    return false;
}

void shannon_fano(int l, int r)
{
    if (l >= r - 1)
    {
        if (l + 1 == r)
        {
            sto[l].code += '0';
            sto[r].code += '1';
        }
        return;
    }

    int mid;
    double sum = 0, left = 0;
    for (int i = l; i <= r; i++) sum += sto[i].prob;
    for (int i = l; i <= r; i++)
    {
        left += sto[i].prob;

        if (left * 2 == sum)
        {
            mid = i;
            break;
        }

        // mid = 1: left - (sum - left)
        // mid = -1: (left - sto[i].prob) - (sum - left + sto[i].prob)
        if (left * 2 > sum)
        {
            if (abs(left * 2 - sum) < abs(left * 2 - sum - sto[i].prob * 2))
                mid = i;
            else mid = i - 1;
            break;
        }
    }

    for (int i = l; i <= mid; i++)
        sto[i].code += '0';

    for (int i = mid + 1; i <= r; i++)
        sto[i].code += '1';

    shannon_fano(l, mid);
    shannon_fano(mid + 1, r);
}

void input() {
    sto.clear();
    id.clear();
    seen.clear();

    symbolInput();
    while (probInput());

    sort(sto.begin(), sto.end(), cmp);
    for (int i = 0; i < n; i++)
        id[sto[i].symbol] = i;
    shannon_fano(0, n - 1);
}

bool output()
{
    if (sto.size() == 0) {
        cout << "Chua nhap nguon tin! Nhan phim bat ki de quay lai.";
        _getch();
        return false;
    }
    cout << "Tin\t\t\tXac suat\tTu ma";
    for (int i = 0; i < n; i++)
    {
        cout << '\n' << sto[i].symbol << "\t\t\t" << sto[i].prob << "\t\t" << sto[i].code;
    }
    return true;
}

bool encode()
{
    if (sto.size() == 0) {
        cout << "Chua nhap nguon tin! Nhan phim bat ki de quay lai.";
        _getch();
        return false;
    }
    cout << "Nhap ban tin can ma hoa (dung lai khi nhap tin chua xuat hien hoac '***'): ";
    vector<int> tmp;
    string s;

    while (cin >> s)
    {
        if (s == "***") break;
        if (id.find(s) != id.end()) tmp.push_back(id[s]);
        else break;
    }

    cout << "Ban tin da duoc ma hoa: ";
    for (int i : tmp)
    {
        cout << sto[i].code << ' ';
    }
    return true;
}

bool mainMenu() {
    system("cls");
    cout << "\tChuong trinh ma hoa Shannon-Fano\n";
    cout << (char)218;
    for (int i = 0; i < 50; i++) {
        cout << (char)196;
    }
    cout << (char)191 << '\n';

    cout << (char)179 << '\t' << " [1]  Nhap nguon tin va xac suat           " << char(179) << '\n';
    cout << (char)179 << '\t' << " [2]  In bang ma hoa tin                   " << char(179) << '\n';
    cout << (char)179 << '\t' << " [3]  Ma hoa ban tin                       " << char(179) << '\n';
    cout << (char)179 << '\t' << "[Esc] Thoat chuong trinh                   " << char(179) << '\n';

    std::cout << (char)192;
    for (int i = 0; i < 50; i++) {
        std::cout << char(196);
    }
    std::cout << (char)217 << '\n';

    char c;
    while (true) {
        c = _getch();
        if (c == '1') {
            system("cls");
            input();
            output();
            cout << "\nNhan phim bat ky de tiep tuc...";
            _getch();
            break;
        }
        else if (c == '2') {
            system("cls");
            if (output()) {
                cout << "\nNhan phim bat ky de tiep tuc...";
                _getch();
            }
            break;
        }
        else if (c == '3') {
            system("cls");
            if (encode()) {
                cout << "\nNhan phim bat ky de tiep tuc...";
                _getch();
            }
            break;
        }
        else if (c == 27) {
            return false;
        }
    }
    return true;
}

int main()
{
    while (mainMenu());
    cout << "Chuong trinh ket thuc! Nhan phim bat ky de thoat...";
    _getch();
    return 0;
}