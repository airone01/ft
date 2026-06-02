
#ifndef __FIXED_HPP__
#define __FIXED_HPP__

class Fixed {

public:
  Fixed();
  Fixed(const Fixed &);
  Fixed(const int &);
  Fixed(const float &);
  ~Fixed();

  Fixed &operator=(const Fixed &);

  int getRawBits(void) const;

  void setRawBits(int const);

private:
  int _val;
  static const int _bits; // Number of fractional bits.
};

#endif // !__FIXED_HPP__
