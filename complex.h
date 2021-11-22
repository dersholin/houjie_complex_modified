// 防衛式聲明
#ifndef COMPLEX_H_
#define COMPLEX_H_

// 因為要調用ostream做cout,所以引入頭文件
#include <iostream>

#pragma region complex物件宣告
class complex
{
	// 公用function
public:
	// constructor,如果初始時有數據則帶入數據,若無數據則設出值為0
	// (double r = 0, double i = 0)表示建構值初始值
	// :後為帶入數據欄位
	complex(double r = 0, double i = 0) :re(r), im(i) {}
	// operator overwrite +=、-=、*=、/= 均為加到左值所以使用參考,右值不改變所以使用const
	complex& operator +=(const complex& x);
	complex& operator -=(const complex& x);
	complex& operator *=(const complex& x);
	complex& operator /=(const complex& x);
	// 外部取用成員函數用
	double real() const { return re; }
	double imag() const { return im; }
	// cout function
	friend std::ostream& operator << (std::ostream& os, const complex& x);

private:
	// 成員函數re為實部,im為虛部
	double re, im;
	// 以下為課程中有出現但事實上連老師都說不清楚的雞肋函式事實上根本用不到
	//	complex& __doapl(complex* ths, const complex& r);
	//	complex& __doami(complex* ths, const complex& r);
	//	complex& __doaml(complex* ths, const complex& r);

};
#pragma endregion

#pragma region 輸出至COUT
//取用cout的參考位址,直接把數據傳到cout,這是標準C++的寫法
std::ostream& operator <<(std::ostream& os, const complex& x)
{
	os << "(" << x.re << "," << x.im << ")";
	return os;
}
#pragma endregion

#pragma region 複數加法
// 能不能inline為編譯器決定,可以增加程序速度?未必
inline complex& complex::operator +=(const complex& x)
{
	// this代表本體物件,實部加實部虛部加虛部,return本體指針
	this->re += x.re;
	this->im += x.im;
	return *this;
}

// 以下含式不需要在class內宣告,但是還是要把各種狀況考慮進去寫出來
inline complex operator + (const complex& x, const complex& y)
{
	return complex(x.real() + y.real(), x.imag() - y.imag());
}

inline complex operator + (const complex& x, double y)
{
	return complex(x.real() + y, x.imag());
}

inline complex operator + (double x, complex& y)
{
	return complex(x + y.real(), y.imag());
}
#pragma endregion

#pragma region 複數減法
// 能不能inline為編譯器決定,可以增加程序速度?未必
inline complex& complex::operator -=(const complex& x)
{
	// this代表本體物件,實部減實部虛部減虛部
	this->re -= x.re;
	this->im -= x.im;
	return *this;
}

// 以下含式不需要在class內宣告,但是還是要把各種狀況考慮進去寫出來
inline complex operator - (const complex& x, complex& y)
{
	return complex(x.real() - y.real(), x.imag() - y.imag());
}

inline complex operator - (const complex& x, double y)
{
	return complex(x.real() - y, x.imag());
}

//以下含式編譯會出錯
//inline complex operator - (double x, const complex& y)
//{
//	return complex(x - y.real(), -y.imag());
//}
#pragma endregion

#pragma region 複數乘法
// 能不能inline為編譯器決定,可以增加程序速度?未必
inline complex& complex::operator *=(const complex& x)
{
	// this代表本體物件,使用複數相乘公式(a, bi) * (c, di) = (ac - bidi, adi + bic)
	double buff = this->re * x.re - this->im * x.im;
	this->im = this->re * x.im + x.re * this->im;
	this->re = buff;
	return *this;
}

// 以下含式不需要在class內宣告,但是還是要把各種狀況考慮進去寫出來
inline complex operator * (const complex& x, const complex& y)
{
	return complex(x.real() * y.real() - x.imag() * y.imag(), x.real() * y.imag() + x.imag() * y.real());
}

inline complex operator * (const complex& x, double y)
{
	return complex(x.real() * y, x.imag() * y);
}

inline complex operator * (double x, const complex& y)
{
	return complex(y.real() * x, y.imag() * x);
}

#pragma endregion

#pragma region 複數除法
// 能不能inline為編譯器決定,可以增加程序速度?未必
inline complex& complex::operator /=(const complex& x)
{
	// 複數除法要求(c或di不等於0),必須先排除
	if (x.re == 0 && x.im == 0)
	{
		std::cout << "Can't divide by zero..." << std::endl;
		return *this;
	}
	else
	{
		// this代表本體物件,使用複數除法公式(a, bi) / (c, di) = (((a * c + bi * di) / (c^2 + di^2)) , ((bi * c − a * di) / (c^2 +di^2)))
		double buff1;
		buff1 = (this->re * x.re + this->im * x.im) / ((x.re * x.re) + (x.im * x.im));
		this->im = (this->im * x.re + this->re * x.im) / ((x.re * x.re) + (x.im * x.im));
		this->re = buff1;
		return *this;
	}
}

// 以下含式不需要在class內宣告,但是還是要把各種狀況考慮進去寫出來
inline complex operator / (const complex& x, double y)
{
	return complex(x.real() / y, x.imag() / y);
}

#pragma endregion

#pragma region 改變正負
inline complex operator + (const complex& x)
{
	// 正正得正,正負得負,所以狀態不改變,直接回傳即可
	return x;
}

inline complex operator - (const complex& x)
{
	// 各加上一負號回傳
	return complex(-x.real(), -x.imag());
}
#pragma endregion

#pragma region 邏輯
// 判斷式true或false直接回傳,但是還是要把各種組合狀況考慮進去
inline bool operator ==(const complex& x, const complex& y)
{
	return x.real() == y.real() && x.imag() == y.imag();
}

inline bool operator ==(double x, const complex& y)
{
	return y.real() == x && y.imag() == 0;
}

inline bool operator ==(const complex& x, double y)
{
	return x.real() == y && x.imag() == 0;
}

inline bool operator !=(const complex& x, const complex& y)
{
	return x.real() != y.real() || x.imag() != y.imag();
}

inline bool operator !=(const complex& x, double y)
{
	return x.real() != y || x.imag() != 0;
}

inline bool operator !=(double x, const complex& y)
{
	return x != y.real() || y.imag() != 0;
}
#pragma endregion

#pragma region 數學計算
// 事實上標準庫中有更多函式成員可以調用
// 傳回以笛卡兒座標形式表示的複數，其對應到指定的模和幅角。(這是標準庫所使用的名稱與說明)
inline complex polar(double r, double t)
{
	return complex(r * cos(t), r * sin(t));
}

// 傳回複數的共軛複數。(這是標準庫所使用的名稱與說明)
inline complex conj(const complex& x)
{
	return complex(x.real(), -(x.imag()));
}

// 擷取複數的範數。(這是標準庫所使用的名稱與說明)
inline double norm(const complex& x)
{
	return x.real() * x.real() + x.imag() * x.imag();
}
#pragma endregion

#pragma region 數值取得
// 不說明,就是直接回傳數值
inline double image(const complex& x)
{
	return x.imag();
}

inline double real(const complex& x)
{
	return x.real();
}
#pragma endregion
#endif // !COMPLEX_H_
