#include "WebServ.hpp"

Logger *Logger::info = new Logger(1, GREEN);

Logger::Logger(std::string &filePath, const char *color): fd(-1), color((char *) color) {
    this->fd = open(filePath.c_str(),  O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
}

Logger::Logger(int fd, const char *color): fd(fd), color((char *) color) {

}

Logger::Logger(Logger const &src) {
    this->fd = src.fd;
}

Logger::~Logger() {
    if(this->fd != -1)
        close(this->fd);
}

Logger &Logger::operator=(Logger const &rhs) {
    if ( this != &rhs )
	{
		this->fd = rhs.fd;
	}
	return *this;
}

int Logger::getFd() {
    return (this->fd);
}

void Logger::log(const char *msg, const char *color) {
    if(this->fd == -1)
        return ;
    write(this->fd, color, strlen(color));
    write(this->fd, msg, strlen(msg));
}

void Logger::log(const char *msg) {
    log(msg, this->color);
}