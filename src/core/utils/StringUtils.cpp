#include "WebServ.hpp"

bool StringUtils::endsWith(const std::string& fullString, const std::string& ending) {
    if (fullString.length() >= ending.length()) {
        return (fullString.compare(fullString.length() - ending.length(), ending.length(), ending) == 0);
    } else {
        return (false);
    }
}

std::string StringUtils::parse(const char* format, ...) {
    // Definir un tamaño máximo para el buffer
    const int bufferSize = 256;
    char buffer[bufferSize];

    // Usar va_list y vsprintf para formatear la cadena en el buffer
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, bufferSize, format, args);
    va_end(args);

    // Convertir el buffer a std::string
    return std::string(buffer) + RED;
}