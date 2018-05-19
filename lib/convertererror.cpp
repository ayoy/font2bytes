#include "convertererror.h"

const ConverterError ConverterError::NoError = { "No error" };

ConverterError & ConverterError::operator =(const std::string &summary)
{
    this->summary = summary;
    description = "";
    return *this;
}

bool ConverterError::operator ==(const ConverterError &rhs)
{
    return (summary.compare(rhs.summary) == 0) and (description.compare(rhs.description) == 0);
}

bool ConverterError::operator !=(const ConverterError &rhs)
{
    return !(*this == rhs);
}
