#ifndef CONVERSIONERROR_H
#define CONVERSIONERROR_H

#include <string>

struct ConverterError
{
    static const ConverterError NoError;

    ConverterError(const std::string &summary = "Unknown error",
                    const std::string &description = "") :
        summary(summary),
        description(description)
    {}

    ConverterError & operator=(const std::string &summary);
    bool operator ==(const ConverterError &rhs) const;
    bool operator !=(const ConverterError &rhs) const;


    std::string summary;
    std::string description;
};

#endif // CONVERSIONERROR_H
