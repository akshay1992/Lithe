#include "Lithe/Exceptions.h"

namespace lithe {

std::ostringstream NodeNotFoundException::message = std::ostringstream(); 
std::ostringstream InvalidOutletException::message = std::ostringstream(); 
std::ostringstream InvalidInletException::message = std::ostringstream(); 
std::ostringstream RangeIsZeroError::message = std::ostringstream(); 

}; // namespace lithe

