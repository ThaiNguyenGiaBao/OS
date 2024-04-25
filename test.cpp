#include <bits/stdc++.h>
using namespace std;

#define OPT_CALC	"calc"
#define OPT_ALLOC	"alloc"
#define OPT_FREE	"free"
#define OPT_READ	"read"
#define OPT_WRITE	"write"

enum ins_opcode_t {
	CALC,	// Just perform calculation, only use CPU
	ALLOC,	// Allocate memory
	FREE,	// Deallocated a memory block
	READ,	// Write data to a byte on memory
	WRITE	// Read data from a byte on memory
};

static enum ins_opcode_t get_opcode(char * opt) {
	if (!strcmp(opt, OPT_CALC)) {
		return CALC;
	}else if (!strcmp(opt, OPT_ALLOC)) {
		return ALLOC;
	}else if (!strcmp(opt, OPT_FREE)) {
		return FREE;
	}else if (!strcmp(opt, OPT_READ)) {
		return READ;
	}else if (!strcmp(opt, OPT_WRITE)) {
		return WRITE;
	}else{
		printf("Opcode: %s\n", opt);
		exit(1);
	}
}



int main() {
    const char *opt = "ca2lc";
    cout<<strcmp(opt, OPT_CALC);
    
}