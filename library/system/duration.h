#ifndef system_duration_h_INCLUDED
#define system_duration_h_INCLUDED

#include <ctime>
#include <iostream>

class Duration
{

public:

    explicit Duration(long sec, long usec);
    explicit Duration(long long usec);
    explicit Duration();

    Duration& operator+=(const Duration& rhs);
    Duration& operator-=(const Duration& rhs);
    Duration& operator%=(const Duration& rhs);

    operator long long() const;

    long long microseconds() const;
    time_t seconds() const;

public:

    friend Duration operator+(Duration x, Duration y) {return x += y;}
    friend Duration operator-(Duration x, Duration y) {return x -= y;}
    friend Duration operator%(Duration x, Duration y) {return x %= y;}

    friend bool operator!=(Duration x, Duration y) { return !(x == y); }
    friend bool operator> (Duration x, Duration y) { return y < x; }
    friend bool operator<=(Duration x, Duration y) { return !(y < x); }
    friend bool operator>=(Duration x, Duration y) { return !(x < y); }

    friend std::ostream& operator<<(std::ostream& os, Duration x)
    { return os << '{' << x.sec_ << ',' << x.usec_ << '}'; }

    friend bool operator==(Duration x, Duration y)
    { return x.sec_ == y.sec_ && x.usec_ == y.usec_; }

    friend bool operator<(Duration x, Duration y)
    { return x.sec_ == y.sec_ ? x.usec_ < y.usec_ : x.sec_ < y.sec_; }

private:

    void fixup();

private:

    long sec_;
    long usec_;
};

#endif // system_duration_h_INCLUDED
