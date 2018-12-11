#pragma once

#include <string>

namespace OpenGMP
{
    /**
     * @brief Bin2HexString creates a hex representation of a unsigned char byte array.
     * @param in the input bytes.
     * @param length the length of the byte array.
     * @param optional delimiter, which is placed between the bytes.
     * @return a string containing the hex output representation.
     */
    inline std::string Bin2HexString(const unsigned char *in, size_t length, const std::string &delim = "", bool upper=false)
    {
        std::string out;
        char part[3];   //Buffer to create hex output.
        part[2] = 0;    //Zero terminate
        const char *format; //Format string.
        if(upper)
            format = "%02X";
        else
            format = "%02x";

        for(size_t i = 0; i < length; i++)
        {
            snprintf(part, 3, format, in[i]);
            out.append(part);
            if(i < length - 1) //Add delimiter to all but the least part.
                out.append(delim);
        }
        return out;
    }

    /**
     * @brief Bin2HexString creates a hex representation of a unsigned char byte array.
     * @param in the input bytes (will be casted to const unsigned char *).
     * @param length the length of the byte array.
     * @param optional delimiter, which is placed between the bytes.
     * @return a string containing the hex output representation.
     */
    inline std::string Bin2HexString(const char *in, size_t length, const std::string &delim = "", bool upper=false)
    {
        return Bin2HexString(reinterpret_cast<const unsigned char*>(in), length, delim, upper);
    }
} //namespace
