#pragma once
#include <exception>
#include <string>
class IGException : public std::exception
{
public:
	IGException(int line, const char* file, const char* what) noexcept;
	const char* what() const noexcept;
	virtual const char* getType() const noexcept;
	const std::string getFile()const noexcept;
	const int getLine() const noexcept;
	std::string getOriginString()const noexcept;
private:
	int _line;
	std::string _file;
	std::string _what;
protected:
	mutable std::string _whatBuffer;
};

#define IGEXCEPTION( hr ) IGException( __LINE__,__FILE__,hr )

class IOException : public IGException
{
public:
	IOException(int line, const char* file, const char* what) noexcept;
private:
	const char* getType()const noexcept override;
};

#define IGEXCEPTIONIO( hr ) IOException( __LINE__,__FILE__,hr )