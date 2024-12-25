#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <limits>

using namespace std;

void nhapBang(vector<vector<double>>& bang, vector<int>& fx, vector<double>& phuongAn, int an, int soHe);
void inBang(const vector<vector<double>>& bang, const vector<int>& fx, const vector<double>& phuongAn);
vector<int> timCotMaTranDonVi(const vector<vector<double>>& bang);
double tinhPhuongAn(const vector<vector<double>>& bang, const vector<double>& phuongAn, const vector<int>& fx);
vector<double> tinhDelta(const vector<vector<double>>& bang, const vector<int>& fx);
int kiemTraDinhLy(const vector<double>& deltas, const vector<int>& fx, const vector<vector<double>>& bang);
int kiemTraDeltaMax(const vector<double>& deltas, const vector<int>& fx, const vector<vector<double>>& bang);
pair<int, pair<int, double>> timCotHangQuay(const vector<double>& deltas, const vector<vector<double>>& bang, const vector<double>& phuongAn);
vector<vector<double>> taoHinh2(const vector<vector<double>>& bang, int hangQuay, int cotQuay, double tamQuay, vector<double>& phuongAn);
vector<double> timNghiem(const vector<vector<double>>& bang, const vector<double>& phuongAn, int heSo);
void inNghiem(const vector<double>& x);


int main() {
    vector<int> fx;
    vector<vector<double>> bang;
    vector<double> phuongAn;
    cout << "Nhap so luong an: ";
    int an; cin >> an;
    cout << "Nhap so he: ";
    int he; cin >> he;

    nhapBang(bang, fx, phuongAn, an, he);


    inBang(bang, fx, phuongAn);
    while (true) {
        vector<double> deltas = tinhDelta(bang, fx);
        int kq = kiemTraDinhLy(deltas, fx, bang);
        
        if (kq == 1) {
            cout << "\nPhuong an toi uu: " << tinhPhuongAn(bang, phuongAn, fx) << endl;
            vector<double> x = timNghiem(bang, phuongAn, fx.size());
            inNghiem(x);
            break;
        } 
        else if (kq == 2) {
            cout << "\nPhuong trinh vo nghiem" << endl;
            break;
        } 
        else {
            pair<int, pair<int, double>> hangCotQuay = timCotHangQuay(deltas, bang, phuongAn);
            if (hangCotQuay.first == -1) {
                cout << "Phuong an khong co gioi han" << endl;
                return 2;
            } else {
                cout << "Hang quay: " << hangCotQuay.second.first + 1 << endl;
                cout << "Cot quay: " << hangCotQuay.first + 1 << endl;
                cout << "Tam quay: " << hangCotQuay.second.second << endl;
                vector<vector<double>> bang2 = taoHinh2(bang, hangCotQuay.second.first, hangCotQuay.first, hangCotQuay.second.second, phuongAn);
    
                inBang(bang2, fx, phuongAn);

                bang = bang2;
            }
        }
    }

    system("pause");
    return 13;
}

void nhapBang(vector<vector<double>>& bang, vector<int>& fx, vector<double>& phuongAn, int an, int soHe) {
    cout << "Nhap he so: ";
    for (int i = 0; i < an; i++) {
        int heSo; cin >> heSo;
        fx.push_back(heSo);
    }

    cout << "Nhap he phuong trinh: \n";
    for (int i = 0; i < soHe; i++) {
        vector<double> temp;
        cout << " - Nhap phuong trinh so " << i + 1 << ": \n";
        for (int a = 0; a < an; a++) {
            double heSo; cin >> heSo;
            temp.push_back(heSo);
        }
        bang.push_back(temp);
    }

    cout << "Nhap phuong an: \n";
    for (int i = 0; i < soHe; i++) {
        double p; cin >> p;
        phuongAn.push_back(p);
    }
}

void inBang(const vector<vector<double>>& bang, const vector<int>& fx, const vector<double>& phuongAn) {
    int hang = bang.size();
    int cot = bang[0].size();
    
    // Mục đề
    cout << "___________________________________________________________________________";
    cout << left << setw(10) << "\n\nHeSo" << setw(8) << "AnCB" << setw(8) << "P/An";
    for (int i = 0; i < fx.size(); i++) {
        cout << setw(8) << ("X" + to_string(i + 1) + "(" + to_string(fx[i]) + ")");
    }
    cout << "\n";

    // Dữ liệu các hàng
    vector<int> identityCols = timCotMaTranDonVi(bang);
    vector<double> deltas = tinhDelta(bang, fx);
    for (int i = 0; i < hang; i++) {
        //HeSo
        if (i < identityCols.size()) {
            cout << setw(8) << fx[identityCols[i]];
        } else {
            cout << setw(8) << "-";
        }

        //AnCB
        if (i < identityCols.size()) {
            cout << setw(8) << ("X" + to_string(identityCols[i] + 1));
        } else {
            cout << setw(8) << "-";
        }

        //P/An
        cout << fixed << setprecision(2) << setw(8) << phuongAn[i];

        // Các cột của bảng
        for (int j = 0; j < cot; j++) {
            cout << fixed << setprecision(2) << setw(8) << bang[i][j];
        }
        cout << endl;
    }

    // Dòng cuối cùng
    cout << " " << right << setw(20) << fixed << setprecision(2) << tinhPhuongAn(bang, phuongAn, fx);
    for (double delta : deltas) {
         cout << fixed << setprecision(2) << setw(7) << delta << " ";
    }
    cout << endl;
}



vector<int> timCotMaTranDonVi(const vector<vector<double>>& bang) {
    vector<pair<int, int>> identityCols;
    int m = bang.size();
    int n = bang[0].size();

    for (int j = 0; j < n; ++j) {
        int countOne = 0;
        int onePosition = -1;
        bool hasNonZero = false;
        for (int i = 0; i < m; ++i) {
            if (bang[i][j] == 1) {
                countOne++;
                onePosition = i;
            } else if (bang[i][j] != 0) {
                hasNonZero = true;
            }
        }
        if (countOne == 1 && !hasNonZero) {
            identityCols.push_back({onePosition, j});
        }
    }

    sort(identityCols.begin(), identityCols.end());

    vector<int> result;
    for (const auto& col : identityCols) {
        result.push_back(col.second);
    }

    return result;
}


double tinhPhuongAn(const vector<vector<double>>& bang, const vector<double>& phuongAn, const vector<int>& fx) {
    double kq = 0;
    vector<int> identityCols = timCotMaTranDonVi(bang);
    int i = 0;
    for (int col : identityCols) {
        double heSo = fx[col];
        double phuongan = phuongAn[i];
        i++;
        kq += heSo * phuongan;
    }
    return kq;
}

vector<double> tinhDelta(const vector<vector<double>>& bang, const vector<int>& fx) {
    vector<double> deltas; 
    vector<int> identityCols = timCotMaTranDonVi(bang);

    for (int j = 0; j < bang[0].size(); ++j) {
        if (find(identityCols.begin(), identityCols.end(), j) != identityCols.end()) {
            deltas.push_back(0);
            continue;
        }

        double tongTich = 0;
        int m = 0;
        for (int i = 0; i < bang.size(); ++i) {
            tongTich += bang[i][j] * fx[identityCols[m]];
            m++;
        }
        double delta = tongTich - fx[j];
        deltas.push_back(delta);
    }

    return deltas;
}

int kiemTraDinhLy(const vector<double>& deltas, const vector<int>& fx, const vector<vector<double>>& bang) {
    bool dinhLy1 = true;
    bool dinhLy2 = false;
    bool dinhLy3 = true;

    for (int j = 0; j < deltas.size(); j++) {
        if (deltas[j] > 0) {
            dinhLy1 = false;

            bool tatCaCotAm = true;
            bool tonTaiDuongTrongCot = false;
            
            for (int i = 0; i < bang.size(); i++) {
                if (bang[i][j] > 0) {
                    tatCaCotAm = false;
                    tonTaiDuongTrongCot = true;
                }
            }

            if (tatCaCotAm) {
                dinhLy2 = true;
            }
            
            if (!tonTaiDuongTrongCot) {
                dinhLy3 = false;
            }
        }
    }

    if (dinhLy1) {
        return 1;
    } else if (dinhLy2) {
        return 2;
    } else if (dinhLy3) {
        return 3;
    }

    return 4;
}


pair<int, pair<int, double>> timCotHangQuay(const vector<double>& deltas, const vector<vector<double>>& bang, const vector<double>& phuongAn) {
    int cotQuay = -1;
    double maxDelta = -1; //delta dương lớn nhứt

    for (int j = 0; j < deltas.size(); ++j) {
        if (deltas[j] > maxDelta) {
            maxDelta = deltas[j];
            cotQuay = j;
        }
    } 

    if (cotQuay == -1) {
        return {-1, {-1, 0}};
    }


    int hangQuay = -1;
    double tamQuay = 0;
    double minTiLe = numeric_limits<double>::max(); //ti le nhonhat

    for (int i = 0; i < bang.size(); ++i) {
        if (bang[i][cotQuay] <= 0) {
            continue;
        }

        double TiLe = phuongAn[i] / bang[i][cotQuay];
        if (TiLe < minTiLe) {
            minTiLe = TiLe;
            hangQuay = i;
            tamQuay = bang[i][cotQuay];
        }
    }

    return {cotQuay, {hangQuay, tamQuay}};
}

vector<vector<double>> taoHinh2(const vector<vector<double>>& bang, int hangQuay, int cotQuay, double tamQuay, vector<double>& phuongAn) {
    int soHang = bang.size();
    int soCot = bang[0].size();
    
    vector<vector<double>> bang2(soHang, vector<double>(soCot));

    for (int j = 0; j < soCot; j++) {
        //chuan hoa hang quay, ở dưới không cần chia cho tamQuay vì đã chia ở đây
        bang2[hangQuay][j] = bang[hangQuay][j] / tamQuay;
    }

    for (int i = 0; i < soHang; i++) {
        if (i != hangQuay) {
            bang2[i][cotQuay] = 0; // các hàng của cột quay bằng 0
        }
    }
    bang2[hangQuay][cotQuay] = 1;

    // úpdate các hàng khác
    for (int i = 0; i < soHang; i++) {
        if (i != hangQuay) {
            double hesonhan = bang[i][cotQuay];
            for (int j = 0; j < soCot; j++) {
                bang2[i][j] = bang[i][j] - hesonhan * bang2[hangQuay][j];
            }
        }
    }

    // úpdate phuong an
    double hesonhan = phuongAn[hangQuay] / tamQuay;
    for (int i = 0; i < soHang; i++) {
        if (i != hangQuay) {
            phuongAn[i] = phuongAn[i] - hesonhan * bang[i][cotQuay];
        } else {
            phuongAn[i] = hesonhan;
        }
    }
    return bang2;
}

vector<double> timNghiem(const vector<vector<double>>& bang, const vector<double>& phuongAn, int heSo) {
    vector<double> x(heSo, 0.0);
    vector<int> giaTri = timCotMaTranDonVi(bang);
    
    for (int i = 0; i < giaTri.size(); i++) {
        x[giaTri[i]] = phuongAn[i];
    }
    
    return x;
}

void inNghiem(const vector<double>& x) {
    cout << "x = (";
    for (int i = 0; i < x.size(); i++) {
        cout << fixed << setprecision(2) << x[i];
        if (i < x.size() - 1) {
            cout << ", ";
        }
    }
    cout << ")" << endl;
}
