#include "matt_daemon.h"

Tintin_reporter::Tintin_reporter() {
	mkdir(LOG_DIR, 0755);
	log.open(LOG_FILE, std::ios_base::app | std::ios_base::out);
	if (!log.is_open()) {
		std::cerr << "can't open " <<  LOG_FILE << std::endl;
		exit(1);
	}
}

Tintin_reporter::~Tintin_reporter() {
	log.close();
}

void Tintin_reporter::print_log(const std::string level, const std::string message) {
	char buff[100];
	std::time_t now = std::time(NULL);
	strftime(buff, sizeof(buff), "[%d/%m/%Y-%H:%M:%S]", localtime(&now));
	log <<  buff << " " << level << " - Matt_daemon: " << message << std::endl;
}

void Tintin_reporter::print_pid(const std::string level) {
	std::stringstream ss;
	ss << "started. PID: " << getpid() << ".";
	print_log(level, ss.str());
}
