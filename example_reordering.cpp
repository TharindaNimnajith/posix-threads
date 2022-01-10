#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

#include <iostream>

struct S {
    long l[3];
    int i[3];
    float f[3];
    double d[3];
};

void addLD(S &s) {
    s.l[0] = s.l[1] + s.l[2];
    // asm volatile("" ::: "memory");
    s.d[0] = s.d[1] + s.d[2];
}

void addDL(S &s) {
    s.d[0] = s.d[1] + s.d[2];
    // asm volatile("" ::: "memory");
    s.l[0] = s.l[1] + s.l[2];
}

void addLdep(S &s) {
    s.l[0] = s.l[1] + s.l[2];
    s.l[1] = 5 + 2 * 10;
    s.l[0] = s.l[1] + s.l[2];
}

void addLDIF(S &s) {
    s.l[0] = s.l[1] + s.l[2];
    s.i[0] = s.i[1] + s.i[2];
    s.d[0] = s.d[1] + s.d[2];
    s.f[0] = s.f[1] + s.f[2];
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

#pragma clang diagnostic pop
