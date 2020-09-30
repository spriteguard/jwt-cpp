#define ENABLE_PKCS11_OPENSC
#include <jwt-cpp/jwt.h>
#include <iostream>
#include <string>

int main(int argc, char **argv)
{
	if (argc < 3 || !strcmp(argv[1], "--help")) {
		std::cout << std::endl << "Usage: " << argv[0] << " <pkcs11 shared library path/filename> <object label> [user pin]" << std::endl << std::endl;
		return -1;
	}

        auto jwtExpiryTime = std::chrono::system_clock::now() + std::chrono::seconds(120);
        auto jwtpass = jwt::create()
            .set_issued_at(std::chrono::system_clock::now())
            .set_expires_at(jwtExpiryTime)
            .set_audience("test")
	    .sign(jwt::algorithm::rs256_pkcs11(argv[1], argv[2], argc==3 ? "" : argv[3]));
	std::cout << jwtpass << std::endl;
	return 0;
}

