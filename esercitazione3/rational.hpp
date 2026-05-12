#include <iostream>
#include <concepts>
#include <numeric> // Necessario per calcolate mcd usando std::gcd(..., ...)

template<typename I> requires std::integral<I>
class rational
{
    I num_;
    I den_;

    public:

        /* DEFAULT CONSTRUCTOR */
        // Se non vengono specificati num_ e den_, vengono inizializzati come num_ = 0, den = 1, ovvero 0/1 = 0
        rational()
            : num_(I{0}), den_(I{1})
            {}
            
        /* USER-DEFINED CONSTRUCTOR */
        rational (const I& num, const I& den)
        {
            // Per semplicità nella definizione degli operatori, Inf non ha segno, qualsiasi num != 0 con den = 0 risulta Inf
            if ( den == 0 && num != 0 ) 
            {
                num_ = 1;
                den_ = 0;

            }
            else if ( den == 0 && num == 0 )
            {
                num_ = 0;
                den_ = 0;
            }
            else
            {
                num_ = num;
                den_ = den;
                semplifica();
            }
        }

        /* RESTITUZIONE DEI VALORI INSERITI */
        I num() const { return num_; }
        I den() const { return den_; }

        /* OPERATOR OVERLOADING */

        // Operatore +=
        rational& operator+=(const rational& other)
        {
            // Casi NaN, Inf
            if ( is_NaN() || other.is_NaN() )
            {
                den_ = 0;
                num_ = 0;
                return *this;
            }
            else if ( is_Inf() || other.is_Inf() )
            {
                den_ = 0;
                num_ = 1;
                return *this;
            }
            // Caso normale
            else
            {
                num_ = ( num_ * other.den() ) + ( den_ * other.num() );
                den_ = den_ * other.den();
                semplifica();
                return *this;
            }
        }

        // Operatore +
        rational operator+(const rational& other) const
        {
            rational ret = *this;
            ret += other;
            return ret;
        }

        // Operatore -=
        rational& operator-=(const rational& other)
        {
            // Casi NaN, Inf
            if ( is_NaN() || other.is_NaN() )
            {
                den_ = 0;
                num_ = 0;
                return *this;
            }
            else if ( is_Inf() || other.is_Inf() )
            {
                den_ = 0;
                num_ = 1;
                return *this;
            }
            // Caso normale
            else
            {
                num_ = ( num_ * other.den() ) - ( den_ * other.num() );
                den_ = den_ * other.den();
                semplifica();
                return *this;
            }
        }

        // Operatore -
        rational operator-(const rational& other) const
        {
            rational ret = *this;
            ret -= other;
            return ret;
        }

        // Operatore *=
        rational& operator*=(const rational& other)
        {
            // Casi NaN, Inf
            if ( is_NaN() || other.is_NaN() )
            {
                den_ = 0;
                num_ = 0;
                return *this;
            }
            else if ( (is_zero() && other.is_Inf()) || (is_Inf() && other.is_zero()) )
            {
                den_ = 0;
                num_ = 0;
                return *this;
            }
            else if ( is_Inf() || other.is_Inf() )
            {
                den_ = 0;
                num_ = 1;
                return *this;
            }
            else
            {
                num_ = num_ * other.num();
                den_ = den_ * other.den();
                semplifica();
                return *this;
            }
        }

        // Operatore *
        rational operator*(const rational& other) const
        {
            rational ret = *this;
            ret *= other;
            return ret;
        }

        // Operatore /=
        rational& operator/=(const rational& other)
        {
            rational reciproco(other.den(), other.num());
            *this *= reciproco;
            return *this;
        }

        // Operatore /
        rational operator/(const rational& other) const
        {
            rational ret = *this;
            ret /= other;
            return ret;
        }

    private:

        /* SEMPLIFICAZIONE */
        void semplifica()
        {
            if ( den_ == 0 ) 
                return; // Se rientra tra i casi speciali non faccio nulla perché vengono trattati separatamente

            I mcd = std::gcd(num_, den_);
            num_ /= mcd;
            den_ /= mcd;

            if ( den_ < 0 ) // È meglio avere il segno negativo al numeratore
            {
                num_ = -num_;
                den_ = -den_;
            }
        }

        /* VERIFICA NaN, Inf, zero */
        // Funzionano andando a verificare se la condizione è vera e restituiscono T o F
        bool is_NaN() const { return den_ == 0 && num_ == 0; }
        bool is_Inf() const { return den_ == 0 && num_ == 1; }
        bool is_zero() const { return num_ == 0 && den_ != 0; }
};

template<typename I> requires std::integral<I>
std::ostream&
operator<<(std::ostream& os, const rational<I>& r)
{
    if ( r.den() == 0 && r.num() == 0 )
        os << "NaN";
    else if ( r.den() == 0 && r.num() == 1 )
        os << "Inf";
    else
        os << r.num() << "/" << r.den();

    return os;
}