#include "fnv1a.h"

static const uint32_t Prime = 0x01000193; //   16777619
static const uint32_t Seed = 0x811C9DC5; // 2166136261
/// hash a single byte
inline uint32_t fnv1ab(unsigned char oneByte, uint32_t hash = Seed) {
	return (oneByte ^ hash) * Prime;
}

uint32_t fnv1a(const void* data, size_t numBytes) {
	uint32_t hash = Seed;
	const unsigned char* ptr = (const unsigned char*)data;
	while (numBytes--)
		hash = fnv1ab(*ptr++, hash);
	return hash;
}