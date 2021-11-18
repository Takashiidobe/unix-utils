#include <stdio.h>

// `cffa edfe` = Mach-O 64-bit executable x86_64.
// `cefa edfe` = Mach-O 32-bit executable x86_32.
// `cafe babe` = java file.
// `5351 4c69 7465 2066 6f72 6d61 7420 3300` = sqlite 3.
// `1F 8B 08` = gzip
// hashtable of [1F, 8B, 08] -> Gzip?
enum FileType {
	FT_EMPTY = 0,
	FT_ASCII = 1,
	FT_CLASS = 2,
	FT_C_SOURCE = 3,
	FT_EXE = 4,
};

static const struct {
	enum FileType code;
	const char* short_key;
	const char* long_key;
} headers[] = {
	{FT_EMPTY, "Empty", ".txt"},
	{FT_ASCII, "ASCII", ".txt"},
	{FT_CLASS, "Java Class File", ".class"},
	{FT_C_SOURCE, "C Source File", ".c"},
	{FT_EXE, "Executable File", ".exe"},
};

static const struct {
	unsigned length;
	unsigned long long decimal;
} Map[] = {
	{4, 0},
	{0, 0},
	{0, 0},
};


int main(int argc, char* argv[]) {
  FILE* f = fopen(argv[1], "r");
  char c;
	int len = 0;

	int curr[16];

  while ((c = fgetc(f)) != EOF && len < 16) {
		curr[len++] = c;
  }
  fclose(f);
}

