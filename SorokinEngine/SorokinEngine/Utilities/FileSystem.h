#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <cstdlib>

class FileSystem
{
private:
	typedef std::string(*Builder) (const std::string& path);

public:
	static std::string getPath(const std::string& path)
	{
		static std::string(*pathBuilder)(std::string const &) = getPathBuilder();
		return (*pathBuilder)(path);
	}

private:
	static std::string const & getRoot()
	{
		static char const * envRoot = getenv("LOGL_ROOT_PATH");
		static std::string root = (envRoot != nullptr ? envRoot : "");
		return root;
	}

	//static std::string(*foo (std::string const &)) getPathBuilder()
	static Builder getPathBuilder()
	{
		if (getRoot() != "")
			return &FileSystem::getPathRelativeRoot;
		else
			return &FileSystem::getPathRelativeBinary;
	}

	static std::string getPathRelativeRoot(const std::string& path)
	{
		return getRoot() + std::string("/") + path;
	}

	static std::string getPathRelativeBinary(const std::string& path)
	{
		return "../../../" + path;
	}

	//Important, print with .c_str()
	std::string reverseString(std::string s) {
		char* reversedPointer = &s[0];

		int counter = 0;
		while (reversedPointer[counter] != '\0') {
			counter++;
		}

		counter--;

		std::string reversedString;
		while (counter >= 0) {
			reversedString += reversedPointer[counter];
			counter--;
		}

		return reversedString;
	}




};

// FILESYSTEM_H
#endif