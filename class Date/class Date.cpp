#include <iostream>
#include <assert.h>
using namespace std;

class Date
{
friend ostream& operator<<(ostream& _cout, const Date& d);
public:
	//构造函数，默认日期为1990-1-1
	Date(int year = 1990, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
		if (!IsInvalid(_year, _month, _day))//判断日期是否非法，若非法则重置为默认日期
		{
			cout << "非法日期，已重置为默认日期！" << endl;
			_year = 1990;
			_month = 1;
			_day = 1;
		}
	}

	//拷贝构造函数
	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	//赋值操作符重载
	Date& operator=(const Date& d)
	{
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		return *this;
	}

	//加法操作符重载
	Date operator+(int days)
	{
		if (days<0)
		{
			return operator-(-days);
		}
		Date ret = *this;
		int sum_days = ret._day + days;
		while (sum_days > GetMonthDays(ret._year, ret._month))
		{
			sum_days -= GetMonthDays(ret._year, ret._month);
			ret._month++;
			if (ret._month > 12)
			{
				ret._year++;
				ret._month %= 12;
			}
			ret._day = sum_days;
		}
		return ret;
	}

	//加上天数后再赋值
	Date& operator+=(int days)
	{
		*this = operator+(days);
		return *this;
	}

	//减法操作符重载
	Date operator-(int days)
	{
		if (days < 0)
		{
			return operator+(-days);
		}
		Date ret = *this;
		while (days>=ret._day)
		{
			days -= ret._day;
			if (1 == ret._month)
			{
				ret._year--;
				ret._month = 12;
			}
			else
			{
				ret._month--;
			}
			ret._day = GetMonthDays(ret._year, ret._month);
		}
		ret._day -= days;
		if (!IsInvalid(ret._year, ret._month, ret._day))
		{
			cout << "结果日期非法，结果重置为默认日期！" << endl;
			ret._year = 1990;
			ret._month = 1;
			ret._day = 1;
		}
		return ret;
	}

	//减去天数后再赋值
	Date& operator-=(int days)
	{
		*this = operator-(days);
		return *this;
	}

	//获取两日期间相差的天数
	int operator-(const Date& d)
	{
		int flag = 1;
		Date maxDate(*this);
		Date minDate(d);
		if (*this < d)
		{
			maxDate = d;
			minDate = *this;
			flag = -1;
		}
		int days = 0;
		while (minDate != maxDate)
		{
			++minDate;
			++days;
		}
		return days*flag;
	}

	//获取当前日期是本年的第多少天
	int GetYearDays()
	{
		int days = 0;
		for (int month = 1; month < _month; ++month)
		{
			days += GetMonthDays(_year, month);
		}
		days += _day;
		return days;
	}

	//前置++
	Date& operator++()
	{
		++_day;
		if (_day > GetMonthDays(_year, _month))
		{
			_day -= GetMonthDays(_year, _month);
			if (12 == _month)
			{
				++_year;
				_month = 1;
			}
			else
			{
				++_month;
			}
		}
		return *this;
	}

	//后置++
	Date operator++(int)
	{
		Date temp(*this);
		*this += 1;
		return temp;
	}

	//前置--
	Date& operator--()
	{
		if ( _day>1)
		{
			--_day;
		}
		else if (1 == _month)
		{
			--_year;
			_month = 12;
			_day = GetMonthDays(_year, _month);
		}
		else
		{
			--_month;
			_day = GetMonthDays(_year, _month);
		}
		return *this;
	}

	//后置--
	Date operator--(int)
	{
		Date temp(*this);
		*this -= 1;
		return temp;
	}

	//判断本日期是否大于日期d
	bool operator>(const Date& d)const
	{
		return _year > d._year || (_year == d._year && _month > d._month) || (_year == d._year && _month == d._month && _day > d._day);
	}

	//判断本日期是否大于等于日期d
	bool operator>=(const Date& d)const
	{
		return (*this>d)||(*this==d);
	}

	//判断本日期是否小于日期d
	bool operator<(const Date& d)const
	{
		return !(*this >= d);
	}

	//判断本日期是否小于等于日期d
	bool operator<=(const Date& d)const
	{
		return !(*this>d);
	}

	//判断本日期与日期d是否相等
	bool operator==(const Date& d)const
	{
		return _year == d._year && _month == d._month && _day == d._day;
	}

	//判断日期是否不相等
	bool operator!=(const Date& d)const
	{
		return !(*this == d);
	}

	//取地址操作符重载
	Date* operator&()
	{
		return this;
	}

	//const取地址操作符重载
	const Date* operator&()const
	{
		return this;
	}
	/*
	//打印日期
	void PrintDate()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}
	*/
private:
	//判断是否为闰年
	bool IsLeapYear(int year)
	{
		if ((year % 400 == 0) || (year % 4 == 0) && (year % 100 != 0))
		{
			return true;
		}
		return false;
	}

	//获取当前月份的总天数
	int GetMonthDays(int year, int month)
	{
		int month_array[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		int day = month_array[month];
		if (IsLeapYear(year) && (2 == month))
		{
			day += 1;
		}
		return day;
	}

	//判断日期是否非法
	bool IsInvalid(int year, int month, int day)
	{
		if ((year > 0) && ((month > 0) && (month<13)) && ((day>0) && (day <= GetMonthDays(year, month))))
		{
			return true;
		}
		return false;
	}

	int _year;
	int _month;
	int _day;
};

ostream& operator<<(ostream& _cout, const Date& d)
{
	_cout << d._year << "-" << d._month << "-" << d._day;
	return _cout;
}

void TestFunc()
{
	Date d1(2018, 1, 1);
	cout << d1 << endl;
	cout << d1.GetYearDays() << endl;
	Date d2=d1--;
	cout << d2 << endl;
	d2 = d1 -100;
	cout << d2 << endl;
}

int main()
{
	TestFunc();
	return 0;
}