#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

class WADNotFoundException : public std::exception {
public:
    ~WADNotFoundException() override {};
    const char *what() const noexcept override {
        return "Unable to open WAD file!";
    }
};

class PortNotFoundException : public std::exception {
public:
    ~PortNotFoundException() override {};
    const char *what() const noexcept override {
        return "Unable to open source port!";
    }
};

class PortNotExecutableException : public std::exception {
public:
    ~PortNotExecutableException() override {};
    const char *what() const noexcept override {
        return "Source port must be an executable!";
    }
};

#endif // EXCEPTIONS_H