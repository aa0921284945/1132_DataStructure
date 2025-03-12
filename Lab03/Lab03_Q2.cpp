#include <iostream>
#include <cmath>
using namespace std;

class Polynomial {
private:
    float *coef; // 初始化係數指標
    int degree; // 最高次數

public:
    //構造函數初始化一個動態長度d的陣列並將所有值設為0，以及初始化degree為d
    Polynomial(int d = 0) : degree(d) {
        coef = new float[degree + 1];
        for (int i = 0; i <= degree; i++) {
            coef[i] = 0;
        }
    }
    //解構函數釋放動態陣列
    ~Polynomial() {
        delete[] coef;
        coef = nullptr;
    }
    //輸入函數
    void input() {
        float value; //輸入的係數
        int deg;//輸入的次數
        cout << "Enter the coefficient and degree of the polynomial: (0 0 to quit)\n";//輸入提示
        //無窮迴圈，直到輸入0 0跳出
        while (true) {
            cin >> value >> deg;//一次讀取兩個值分別是係數和次數
            if (value == 0 && deg == 0) {
                break; // 遇到 0 0 結束輸入
            }
            if (deg > degree) {//如果輸入的次數大於最高次數
                // 重新分配陣列大小
                float* tmp = new float[deg + 1];//初始化一個新的陣列
                //將原陣列的值複製到新陣列
                for (int i = 0; i <= degree; i++) {
                    tmp[i] = coef[i];
                }
                //將新陣列的剩餘部分設為0
                for (int i = degree + 1; i <= deg; i++) {
                    tmp[i] = 0;
                }
                delete[] coef;//釋放原陣列
                coef = tmp;//將新陣列指定給原陣列
                degree = deg;//更新最高次數
            }
            coef[deg] = value; // 在係數陣列存入對應次數的係數
        }
    }
    //通用輸出函數(假設都是+號)
    void PolyInfo() {
        bool first = true;//初始化第一次為true
        // 由最高次數degree開始遍歷
        for (int i = degree; i >= 0; i--) {
            if (coef[i] != 0) {//如果係數不是0
                if (!first) {//如果不是第一次
                    cout << " + ";//印出+號
                }
                if (coef[i] != 0 || i == 0) {//如果係數不是0或是常數項
                    cout << coef[i];//印出係數
                }
                if (i > 1) {
                    cout << "x^" << i;//印出次數
                }
                else if (i == 1) {
                    cout << "x";//印出x
                }
                first = false;//第一次印出後設為false
            }
        }
    }
    //多項式輸出函數
    void Info(int n = 0) {
        //替換n從1~2從1~2
        cout << "Polynomial " << n << " p(x) = ";
        PolyInfo();
        cout << endl << endl;
    }
    //加法函數
    void add(Polynomial* p) {
        Polynomial tmp(max(degree, p->degree));//初始化一個多項式暫存結果
        //遍歷最高次數，附值給暫存多項式
        for (int i = 0; i <= tmp.degree; i++) {
            float a = (i <= degree) ? coef[i] : 0;//如果i小於等於多項式1最高次數，則取係數，否則為0
            float b = (i <= p->degree) ? p->coef[i] : 0;//如果i小於等於多項式2最高次數，則取係數，否則為0
            tmp.coef[i] = a + b;
        }        
        //輸出暫存多項式結果
        cout << "Add : Polynomial 1 + Polynomial 2 = ";
        tmp.PolyInfo();
        cout << endl << endl;
    }
    //乘法函數
    void Mult(Polynomial* p) {
        Polynomial tmp(degree + p->degree);//初始化一個多項式暫存結果
        //遍歷多項式1的最高次數
        for (int i = 0; i <= degree; i++) {
            //遍歷多項式2的最高次數
            for (int j = 0; j <= p->degree; j++) {
                tmp.coef[i + j] += coef[i] * p->coef[j];//會有重複次數，所以用+=，並附值給暫存多項式
            }
        }
        //輸出暫存多項式結果
        cout << "Mult: Polynomial 1 * Polynomial 2 = ";
        tmp.PolyInfo();
        cout << endl << endl;
    }
    //評估函數(輸入一個x，返回多項式在x的值)
    void Eval(float x) {
        float result = 0;//初始化結果
        //遍歷多項式的最高次數
        for (int i = 0; i <= degree; i++) {
            //結果 = i位置的係數乘上x的i次方
            result += coef[i] * pow(x, i);//累加每一項的值
        }
        //輸出結果
        cout << "Eval: Polynomial = p(" << x << ") = ";
        PolyInfo();
        cout << " = " << result << endl << endl;
    }
    void Eval2(float x) {
        float result = 0;//初始化結果
        //遍歷多項式的最高次數
        for (int i = 0; i <= degree; i++) {
            //結果 = i位置的係數乘上x的i次方
            result += coef[i] * pow(x, i);//累加每一項的值
        }
        //輸出結果不重複列印Eval: 
        cout << "      Polynomial = p(" << x << ") = ";
        PolyInfo();
        cout << " = " << result << endl;
    }
};

int main() {
    Polynomial p1, p2;//初始化多項式1、2
    p1.input();//輸入多項式1
    p2.input();//輸入多項式2

    float x;//初始化x
    cout << "Eval num = ";
    cin >> x;//輸入x

    p1.Info(1);//輸出多項式1
    p2.Info(2);//輸出多項式2
    

    // 加法結果
    p1.add(&p2);//多項式相加

    // 乘法結果
    p1.Mult(&p2);//多項式相乘

    // 帶入x結果
    p1.Eval(x);//多項式1在x的值
    p2.Eval2(x);//多項式2在x的值
    return 0;
}
