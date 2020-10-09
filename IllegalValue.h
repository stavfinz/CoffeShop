#ifndef __ILLEGAL_VALUE_H__
#define __ILLEGAL_VALUE_H__

using namespace std;
#include <iostream>

class IllegalValue : public exception
{
private:
	const char* attr;
public:
	IllegalValue(const char* attr) :attr(attr)
	{
	}

	virtual const char* what() const throw()
	{
		return attr;
	}
};

#endif // !__ILLEGAL_VALUE_H__