// Copyright (c) 2025, London Sheard
// Licensed under the 3-Clause Sheard License
// See the LICENSE file in project root for details.

#include <random>

static char GetRandomChar() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::string charset =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz"
	"1234567890"
	"`~!@#$%^&*()-=_+[]\{}|;':\",./<>?";
    std::uniform_int_distribution<> distrib(0, charset.size() - 1);

    return charset[distrib(gen)];
}

/**
 * Generates a string of random characters of size _len.
 *
 * Usage:
 * size_t len = 20;
 * std::string password = GenPassword(len);
 * @param _len length of password
 * @return std::string password
 */
std::string GenPassword(size_t _len) {
    std::string password;
    for (size_t i = 0; i < _len; i++) {
	password += GetRandomChar();
    }

    return password;
}

