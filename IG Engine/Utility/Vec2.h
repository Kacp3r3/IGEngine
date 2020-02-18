#ifndef VEC2_H
#define VEC2_H
template <typename T>
class Vec2
{
public:
	Vec2<T>();
	Vec2<T>(T x, T y);
	Vec2<T>(const Vec2<T>& src);
	~Vec2<T>();


public:
	T getX();
	T getY();
	Vec2<T> getVector();
	Vec2<T> getNormalized();
	T getLength();


public:
	void setX(T x);
	void setY(T y);


public:
	void Normalize();


public:
	Vec2<T>& operator /= (T number);
	Vec2<T> operator/(T number);
	Vec2<T> operator*(T number);
	Vec2<T> operator*(Vec2<T> rhs);
	Vec2<T> operator*=(Vec2<T> rhs);
	Vec2<T> operator+(Vec2<T> rhs);
	Vec2<T>& operator+=(Vec2<T> rhs);
	Vec2<T> operator -(Vec2<T> rhs);
	Vec2<T>& operator -=(Vec2<T> rhs);
	bool operator != (Vec2<T> rhs);


public:
	T _x;
	T _y;
};


typedef Vec2<double> Vec2d;
typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;
typedef const Vec2<double> Vec2dc;
typedef const Vec2<float> Vec2fc;
typedef const Vec2<int> Vec2ic;


template<typename T>
inline Vec2<T>::Vec2()
	:
	_x(0)
	, _y(0)
{};

template<typename T>
inline Vec2<T>::Vec2(T x, T y)
	:
	_x(x)
	, _y(y)
{};


template<typename T>
inline Vec2<T>::Vec2(const Vec2<T>& src)
	:
	_x(src._x)
	, _y(src._y)
{};

template<typename T>
inline Vec2<T>::~Vec2()
{};

template<typename T>
inline T Vec2<T>::getX()
{
	return _x;
};

template<typename T>
inline T Vec2<T>::getY()
{
	return _y;
};

template<typename T>
inline Vec2<T> Vec2<T>::getVector()
{
	return this;
};

template<typename T>
inline Vec2<T> Vec2<T>::getNormalized()
{
	T len = sqrt(_x*_x + _y * _y);
	return Vec2<T>(_x/len,_y/len);
};

template<typename T>
inline T Vec2<T>::getLength()
{
	return sqrt(_x*_x+_y*_y);
};

template<typename T>
inline void Vec2<T>::setX(T x)
{
	_x = x;
};

template<typename T>
inline void Vec2<T>::setY(T y)
{
	_y = y;
};
template<typename T>
inline void Vec2<T>::Normalize()
{
	*this/= sqrt(_x*_x +_y*_y);
};
template<typename T>
inline Vec2<T> & Vec2<T>::operator/=(T number)
{
	*this->_x /= number;
	*this->_y /= number;
}
template<typename T>
inline Vec2<T> Vec2<T>::operator/(T number)
{
	return { this->_x / number,this->_y / number };
}
template<typename T>
inline Vec2<T> Vec2<T>::operator*(T number)
{
	return Vec2<T>(this->_x*number,this->_y*number);
}

template<typename T>
inline Vec2<T> Vec2<T>::operator*(Vec2<T> rhs)
{
	return Vec2<T>(this->_x * rhs._x, this->_y * rhs._y);
}

template<typename T>
inline Vec2<T> Vec2<T>::operator*=(Vec2<T> rhs)
{
	*this = *this * rhs;
	return *this;
}
template<typename T>
inline Vec2<T> Vec2<T>::operator+(Vec2<T> rhs)
{
	return { this->_x + rhs._x, this->_y + rhs._y };
}
template<typename T>
inline Vec2<T>& Vec2<T>::operator+=(Vec2<T> rhs)
{
	*this = *this + rhs;
	return *this;
}
template<typename T>
inline Vec2<T> Vec2<T>::operator-(Vec2<T> rhs)
{
	return {this->_x - rhs._x, this->_y- rhs._y};
}
template<typename T>
inline Vec2<T>& Vec2<T>::operator-=(Vec2<T> rhs)
{
	*this = *this - rhs;
	return *this;
}

template<typename T>
inline bool Vec2<T>::operator!=(Vec2<T> rhs)
{
	return _x != rhs._x || _y != rhs._y;
}

#endif