#ifndef LITHE_EXCEPTIONS_H
#define LITHE_EXCEPTIONS_H

#include <stdexcept> 
#include <sstream>

namespace lithe{

class InvalidInletException : public std::range_error
{
public:
    InvalidInletException(int index, int nodeID) : std::range_error("Inlet not found"), inletIndex(index), nodeID(nodeID) {}
    virtual const char* what() const throw()
    {
        message.str( "" );
        message << std::range_error::what() << "at Index:  " << std::to_string(inletIndex) <<  " NodeID: " << std::to_string(nodeID);
        return message.str().c_str();
    }

private:
	int nodeID;
    int inletIndex;
    static std::ostringstream message;
};

class InvalidOutletException : public std::range_error
{
public:
    InvalidOutletException(int index, int nodeID) : std::range_error("Outlet not found"), outletIndex(index), nodeID(nodeID) {}
    virtual const char* what() const throw()
    {
        message.str( "" );
        message << std::range_error::what() << "at Index:  " << std::to_string(outletIndex) <<  " NodeID: " << std::to_string(nodeID);
        return message.str().c_str();
    }

private:
	int nodeID;
    int outletIndex;
    static std::ostringstream message;
};

class NodeNotFoundException : public std::range_error
{
public:
    NodeNotFoundException(int id) : std::range_error("Node not found"), nodeID(id) {}
    virtual const char* what() const throw()
    {
        message.str( "" );
        message << std::range_error::what() << "   ID: " << std::to_string(nodeID);
        return message.str().c_str();
    }

private:
    int nodeID;
    static std::ostringstream message;
};

class RangeIsZeroError : public std::range_error
{
public:
    RangeIsZeroError(float max, float min) : 
        std::range_error("RangeT initialization error: Range can't be zero "), 
        max(max), 
        min(min) 
    {}

    virtual const char* what() const throw()
    {
        message.str( "" );
        message << std::range_error::what() << " Provided max: " << max <<  " min: " << min;
        return message.str().c_str();
    }

private:
    float max, min;
    static std::ostringstream message;
};

}; // namespace lithe

#endif // LITHE_EXCEPTIONS_H