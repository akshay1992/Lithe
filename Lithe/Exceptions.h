#ifndef LITHE_EXCEPTIONS_H
#define LITHE_EXCEPTIONS_H

#include <stdexcept> 
#include <sstream>

namespace lithe{

class InvalidInletException : public std::range_error
{
public:
    InvalidInletException(int index, int nodeID)
        : std::range_error("Inlet not found at Index:  " + std::to_string(index) + " NodeID: " + std::to_string(nodeID)) {}
};

class InvalidOutletException : public std::range_error
{
public:
    InvalidOutletException(int index, int nodeID)
        : std::range_error("Outlet not found at Index:  " + std::to_string(index) +  " NodeID: " + std::to_string(nodeID)) {}
};

class NodeNotFoundException : public std::range_error
{
public:
    NodeNotFoundException(int id)
        : std::range_error("Node not found   ID: " + std::to_string(id)) {}
};

class RangeIsZeroError : public std::range_error
{
public:
    RangeIsZeroError(float max, float min) : 
        std::range_error("RangeT initialization error: Range can't be zero  Provided max: " + std::to_string(max) +  " min: " + std::to_string(min)) {}
};

}; // namespace lithe

#endif // LITHE_EXCEPTIONS_H
