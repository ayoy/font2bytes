#include "sourcecodegenerator.h"
#include <ctime>

//template <class T>
//SourceCodeGenerator<T>::SourceCodeGenerator(SourceCodeOptions options):
//    options(std::move(options)),
//    m_bytewriter(std::make_unique<T>()),
//    m_stream(std::make_unique<std::ostringstream>())
//{
//}

//template <class T>
//std::string SourceCodeGenerator<T>::getCurrentTimestamp() const
//{
//    time_t     now = time(0);
//    struct tm  tstruct;
//    char       buf[22];
//    tstruct = *localtime(&now);
//    strftime(buf, sizeof(buf), "%d/%m/%Y at %H:%M:%S", &tstruct);
//
//    return buf;
//}
//
//template <class T>
//uint8_t SourceCodeGenerator<T>::formatByte(uint8_t byte) const
//{
//    if (options.bitNumbering == SourceCodeOptions::MSB) {
//        uint8_t reversedByte = 0;
//        for (uint8_t i = 0; i < 8; i++) {
//            if ((byte & (1<<i)) != 0) {
//                uint8_t setBit = 1<<(7-i);
//                reversedByte |= setBit;
//            }
//        }
//        byte = reversedByte;
//    }
//    if (options.shouldInvertBits) {
//        byte = ~byte;
//    }
//    return byte;
//}
//
//template <class T>
//void SourceCodeGenerator<T>::begin()
//{
//    m_stream->flush();
//    m_stream << m_bytewriter.begin(std::move(getCurrentTimestamp()));
//}
//
//template <class T>
//void SourceCodeGenerator<T>::beginArray(const std::string &name)
//{
//    m_stream << m_bytewriter.beginArray(name);
//}
//
//template <class T>
//void SourceCodeGenerator<T>::beginArrayRow()
//{
//    m_stream << m_bytewriter.beginArrayRow();
//}
//
//template <class T>
//void SourceCodeGenerator<T>::writeByte(uint8_t byte)
//{
//    m_stream << m_bytewriter.byte(formatByte(byte));
//}
//
//template <class T>
//void SourceCodeGenerator<T>::addComment(const std::string &comment)
//{
//    m_stream << m_bytewriter.comment(comment);
//}
//
//template <class T>
//void SourceCodeGenerator<T>::addLineBreak()
//{
//    m_stream << m_bytewriter.lineBreak();
//}
//
//template <class T>
//void SourceCodeGenerator<T>::endArray()
//{
//    m_stream << m_bytewriter.endArray();
//}
//
//template <class T>
//void SourceCodeGenerator<T>::end()
//{
//    m_stream << m_bytewriter.end();
//}
