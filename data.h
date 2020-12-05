#ifndef DATA_H
#define DATA_H


class Data
{
public:
    Data() = default;
    Data(int nDay, int nMonth, int nYear) {
        day = nDay;
        month = nMonth;
        year = nYear;
    }

    int getDay() const {return day;}
    int getMonth() const {return month;}
    int getYear() const {return year;}

    bool operator>(Data& secondData){
        int val1, val2;
        val1 = day + month*100 + year*10000;
        val2 = secondData.getDay() + secondData.getMonth()*100 + secondData.getYear()*10000;
        return val1 > val2;
    }

    bool operator<(Data& secondData){
        int val1, val2;
        val1 = day + month*100 + year*10000;
        val2 = secondData.getDay() + secondData.getMonth()*100 + secondData.getYear()*10000;
        return val1 < val2;
    }

    bool operator==(Data& secondData){
        int val1, val2;
        val1 = day + month*100 + year*10000;
        val2 = secondData.getDay() + secondData.getMonth()*100 + secondData.getYear()*10000;
        return val1 == val2;
    }

    bool operator!=(Data& secondData){
        int val1, val2;
        val1 = day + month*100 + year*10000;
        val2 = secondData.getDay() + secondData.getMonth()*100 + secondData.getYear()*10000;
        return val1 != val2;
    }

private:
    int day{0};
    int month{0};
    int year{0};
};


#endif // DATA_H
