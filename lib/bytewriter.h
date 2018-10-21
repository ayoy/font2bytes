#ifndef BYTEWRITER_H
#define BYTEWRITER_H

#include <cstdint>
#include <string>

/**
 * @brief The byte writer for the conversion algorithm to send the result to.
 */
class ByteWriter
{
public:
    /**
     * @brief Start a new file
     *
     * Call this method once at the begin, before any data is written.
     */
    virtual void begin() = 0;

    /**
     * @brief Start a new array of bytes
     * @param name The name of the array.
     */
    virtual void beginArray(std::string name) = 0;

    /**
     * @brief Start a new row of array of bytes
     */
    virtual void beginArrayRow() = 0;

    /**
     * @brief Write a single byte to the output array
     * @param byte
     */
    virtual void writeByte(uint8_t byte) = 0;

    /**
     * @brief Add a comment to the output
     * @param comment
     */
    virtual void addComment(std::string comment) = 0;

    /**
    * @brief Add a linebreak to the output
    */
    virtual void addLineBreak() = 0;

    /**
     * @brief End an array of bytes
     */
    virtual void endArray() = 0;

    /**
     * @brief End a file
     *
     * Call this method once at the end, after all data was written.
     */
    virtual void end() = 0;
};

#endif // BYTEWRITER_H
