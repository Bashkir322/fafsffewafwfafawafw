#include "rational.h"
#include <iostream>
int GCD(int a, int b) {
  a = a > 0 ? a : -a;
  while (a != 0 && b != 0) {
    if (a > b) {
      a %= b;
    } else {
      b %= a;
    }
    
  }
  return a + b;
}
void Rational::Reduce() {
  int gcd = GCD(p_, q_);
  p_ /= gcd;
  q_ /= gcd;
}
Rational::Rational(int p, int q) {
  p_ = p;
  q_ = q;
  if (q_ < 0) {
    q_ = -q;
    p_ = -p;
  }
  Reduce();
}
Rational::Rational(const Rational& r) {
  p_ = r.p_;
  q_ = r.q_;
}
Rational& Rational::operator+=(const Rational& other) {
  p_ = p_ * other.q_ + q_ * other.p_;
  q_ = q_ * other.q_;
  Reduce();
  return *this;
}
Rational& Rational::operator-=(const Rational& other) {
  p_ = p_ * other.q_ - q_ * other.p_;
  q_ = q_ * other.q_;
  Reduce();
  return *this;
}
Rational& Rational::operator*=(const Rational& other) {
  p_ = p_ * other.p_;
  q_ = q_ * other.q_;
  Reduce();
  return *this;
}
Rational& Rational::operator/=(const Rational& other) {
  if (other.q_ == 0 || other.p_ == 0) {
    throw RationalDivisionByZero{};
  }
  p_ = p_ * other.q_;
  q_ = q_ * other.p_;
  Reduce();
  return *this;
}
bool operator<(const Rational& first, const Rational& second) {
  return first.GetNumerator() * second.GetDenominator() < first.GetDenominator() * second.GetNumerator();
}
bool operator>(const Rational& first, const Rational& second) {
  return first.GetNumerator() * second.GetDenominator() > first.GetDenominator() * second.GetNumerator();
}
bool operator==(const Rational& first, const Rational& second) {
  return first.GetNumerator() * second.GetDenominator() == first.GetDenominator() * second.GetNumerator();
}
bool operator<=(const Rational& first, const Rational& second) {
  return (first < second || first == second);
}
bool operator>=(const Rational& first, const Rational& second) {
  return (first > second || first == second);
}
bool operator!=(const Rational& first, const Rational& second) {
  return !(first == second);
}
Rational& Rational::operator++() {
  *this += 1;
  return *this;
}
Rational Rational::operator++(int) {
  Rational copy = *this;
  ++*this;
  return copy;
}
Rational& Rational::operator--() {
  *this -= 1;
  return *this;
}
Rational Rational::operator--(int) {
  Rational copy = *this;
  --*this;
  return copy;
}
Rational Rational::operator+() const {
  return *this;
}
Rational Rational::operator-() const {
  Rational copy;
  copy.SetNumerator(-GetNumerator());
  copy.SetDenominator(GetDenominator());
  return copy;
}
Rational operator+(const Rational& first, const Rational& other) {
  Rational copy = first;
  copy += other;
  return copy;
}
Rational operator-(const Rational& first, const Rational& other) {
  Rational copy = first;
  copy -= other;
  return copy;
}
Rational operator*(const Rational& first, const Rational& other) {
  Rational copy = first;
  copy *= other;
  return copy;
}
Rational operator/(const Rational& first, const Rational& other) {
  if (other.GetDenominator() == 0 || other.GetNumerator() == 0) {
    throw RationalDivisionByZero{};
  }
  Rational copy = first;
  copy /= other;
  return copy;
}
int Rational::GetNumerator() const {
  return p_;
}
int Rational::GetDenominator() const {
  return q_;
}
void Rational::SetNumerator(int x) {
  p_ = x;
  Reduce();
}
void Rational::SetDenominator(int value) {
  if (value == 0) {
    throw RationalDivisionByZero{};
  }
  q_ = value;
  Reduce();
}
std::istream& operator>>(std::istream& is, Rational& x) {
  char c;
  is >> x.p_ >> c >> x.q_;
  if (x.q_ == 0) {
    throw RationalDivisionByZero{};
  }
  if (x.q_ < 0) {
    x.p_ = -x.p_;
    x.q_ = -x.q_;
  }
  x.Reduce();
  return is;
}
std::ostream& operator<<(std::ostream& os, const Rational& x) {
  os << x.p_ << "/" << x.q_;
  return os;
}