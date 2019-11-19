#include "IGException.h"
#include <sstream>
IGException::IGException(int line, const char* file, const char* what) noexcept
	:
	 _line(line)
	,_file(file)
	,_what(what)
{}

const char* IGException::what() const noexcept
{
	std::ostringstream ss;
	ss << "       " << getType() << std::endl
		<< getOriginString();
	_whatBuffer = ss.str();
	return _whatBuffer.c_str();
}

const char* IGException::getType() const noexcept
{
	return "IG Exception";
}

const std::string IGException::getFile() const noexcept
{
	return _file;
}

const int IGException::getLine() const noexcept
{
	return _line;
}

std::string IGException::getOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << _file << std::endl
		<< "[Line] " << _line << std::endl
		<< "[What] " << _what << std::endl;
	return oss.str();
}
