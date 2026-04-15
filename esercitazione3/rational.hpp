#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <concepts>
#include <iostream>

template<typename I>
requires std::integral<I>
class rational
{
    I num_;
    I den_;

    bool is_nan() const
    {
        return num_ == I{0} && den_ == I{0};
    }

    bool is_inf() const
    {
        return den_ == I{0} && num_ != I{0};
    }

    bool is_pos_inf() const
    {
        return den_ == I{0} && num_ > I{0};
    }

    bool is_neg_inf() const
    {
        return den_ == I{0} && num_ < I{0};
    }

    void make_nan()
    {
        num_ = I{0};
        den_ = I{0};
    }

    void make_pos_inf()
    {
        num_ = I{1};
        den_ = I{0};
    }

    void make_neg_inf()
    {
        num_ = I{-1};
        den_ = I{0};
    }

    void simplify()
    {
        if (den_ == I{0})
            return;

        if (num_ == I{0})
        {
            den_ = I{1};
            return;
        }

        if (den_ < I{0})
        {
            num_ = -num_;
            den_ = -den_;
        }

        I a = num_;
        if (a < I{0})
            a = -a;

        I b = den_;
        if (b < I{0})
            b = -b;

        while (b != I{0})
        {
            I r = a % b;
            a = b;
            b = r;
        }

        num_ /= a;
        den_ /= a;
    }

public:
    //  ** Costruttore default **
    rational()
        : num_(I{0}), den_(I{1})
    {}

    // ** Costruttore user-defined **
    rational(const I& num, const I& den)
        : num_(num), den_(den)
    {
        if (den_ == I{0})
        {
            if (num_ == I{0})
            {
                make_nan();
            }
            else if (num_ > I{0})
            {
                make_pos_inf();
            }
            else
            {
                make_neg_inf();
            }

            return;
        }

        simplify();
    }

    // ** Restituiscono numeratore e denominatore **
    I num() const { return num_; }
    I den() const { return den_; }

    // ** Operazione += **
    rational& operator+=(const rational& other)
    {
        if (is_nan() || other.is_nan())
        {
            make_nan();
            return *this;
        }

        if (is_inf() && other.is_inf())
        {
            if ((is_pos_inf() && other.is_neg_inf()) ||
                (is_neg_inf() && other.is_pos_inf()))
            {
                make_nan();
                return *this;
            }

            return *this;
        }

        if (is_inf())
            return *this;

        if (other.is_inf())
        {
            if (other.is_pos_inf())
                make_pos_inf();
            else
                make_neg_inf();

            return *this;
        }

        num_ = num_ * other.den_ + other.num_ * den_;
        den_ = den_ * other.den_;

        simplify();
        return *this;
    }

    // ** Operazione + **
    rational operator+(const rational& other) const
    {
        rational ret = *this;
        ret += other;
        return ret;
    }

    // ** Operazione -= **
    rational& operator-=(const rational& other)
    {
        if (is_nan() || other.is_nan())
        {
            make_nan();
            return *this;
        }

        if (is_inf() && other.is_inf())
        {
            if ((is_pos_inf() && other.is_pos_inf()) ||
                (is_neg_inf() && other.is_neg_inf()))
            {
                make_nan();
                return *this;
            }

            return *this;
        }

        if (is_inf())
            return *this;

        if (other.is_inf())
        {
            if (other.is_pos_inf())
                make_neg_inf();
            else
                make_pos_inf();

            return *this;
        }

        num_ = num_ * other.den_ - other.num_ * den_;
        den_ = den_ * other.den_;

        simplify();
        return *this;
    }

    // ** Operazione - **
    rational operator-(const rational& other) const
    {
        rational ret = *this;
        ret -= other;
        return ret;
    }

    // ** Operazione *= **
    rational& operator*=(const rational& other)
    {
        if (is_nan() || other.is_nan())
        {
            make_nan();
            return *this;
        }

        if ((is_inf() && other.num_ == I{0} && other.den_ != I{0}) ||
            (other.is_inf() && num_ == I{0} && den_ != I{0}))
        {
            make_nan();
            return *this;
        }

        if (is_inf() && other.is_inf())
        {
            if ((is_pos_inf() && other.is_pos_inf()) ||
                (is_neg_inf() && other.is_neg_inf()))
            {
                make_pos_inf();
            }
            else
            {
                make_neg_inf();
            }

            return *this;
        }

        if (is_inf())
        {
            if (other.num_ > I{0})
                return *this;

            if (other.num_ < I{0})
            {
                if (is_pos_inf())
                    make_neg_inf();
                else
                    make_pos_inf();
            }

            return *this;
        }

        if (other.is_inf())
        {
            if (num_ > I{0})
            {
                if (other.is_pos_inf())
                    make_pos_inf();
                else
                    make_neg_inf();
            }
            else if (num_ < I{0})
            {
                if (other.is_pos_inf())
                    make_neg_inf();
                else
                    make_pos_inf();
            }
            else
            {
                make_nan();
            }

            return *this;
        }

        num_ = num_ * other.num_;
        den_ = den_ * other.den_;

        simplify();
        return *this;
    }

    // ** Operazione * **
    rational operator*(const rational& other) const
    {
        rational ret = *this;
        ret *= other;
        return ret;
    }

    // ** Operazione /= **
    rational& operator/=(const rational& other)
    {
        if (is_nan() || other.is_nan())
        {
            make_nan();
            return *this;
        }

        if (other.num_ == I{0} && other.den_ != I{0})
        {
            if (num_ == I{0} && den_ != I{0})
            {
                make_nan();
            }
            else if (num_ > I{0})
            {
                make_pos_inf();
            }
            else if (num_ < I{0})
            {
                make_neg_inf();
            }
            else
            {
                make_nan();
            }

            return *this;
        }

        if (is_inf() && other.is_inf())
        {
            make_nan();
            return *this;
        }

        if (other.is_inf())
        {
            num_ = I{0};
            den_ = I{1};
            return *this;
        }

        if (is_inf())
        {
            if (other.num_ > I{0})
                return *this;

            if (other.num_ < I{0})
            {
                if (is_pos_inf())
                    make_neg_inf();
                else
                    make_pos_inf();
            }

            return *this;
        }

        num_ = num_ * other.den_;
        den_ = den_ * other.num_;

        if (den_ == I{0})
        {
            if (num_ == I{0})
                make_nan();
            else if (num_ > I{0})
                make_pos_inf();
            else
                make_neg_inf();

            return *this;
        }

        simplify();
        return *this;
    }

    // ** Operazione / **
    rational operator/(const rational& other) const
    {
        rational ret = *this;
        ret /= other;
        return ret;
    }
};

template<typename I>
requires std::integral<I>
std::ostream&
operator<<(std::ostream& os, const rational<I>& r)
{
    if (r.den() == I{0} && r.num() == I{0})
    {
        os << "NaN";
        return os;
    }

    if (r.den() == I{0})
    {
        if (r.num() > I{0})
            os << "Inf";
        else
            os << "-Inf";

        return os;
    }

    os << r.num() << "/" << r.den();
    return os;
}

#endif