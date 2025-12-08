#ifndef DATE_H
#define DATE_H

using namespace std;

#pragma pack(push, 1)

class Date {
private:
    int day;
    int month;
    int year;
public:
    Date() : day(0), month(0), year(0) {}
    Date(int d, int m, int y) : day(d), month(m), year(y) {}
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    void setDay(int d) { day = d; }
    void setMonth(int m) { month = m; }
    void setYear(int y) { year = y; }
};

#pragma pack(pop)

#endif
