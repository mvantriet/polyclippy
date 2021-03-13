#ifndef _POINT_H_
#define _POINT_H_

#ifdef __cplusplus

template <class T> class Point
{
private:
	T x;
	T y;

public:
	Point() {}

	Point(T x, T y)
	{
		this->x = x;
		this->y = y;
	}

	~Point() {}

	T getX()
	{
		return this->x;
	}

	T getY()
	{
		return this->y;
	}

	void setX(T x)
	{
		this->x = x;
	}

	void setY(T y)
	{
		this->y = y;
	}

	Point* clone()
	{
		return new Point<T>(this->getX(), this->getY());
	}
};

#endif

#endif
