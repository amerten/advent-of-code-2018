#include <array>
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

typedef array<int, 6> Regs;

enum OpCode {
    addr, addi,
    mulr, muli,
    banr, bani,
    borr, bori,
    setr, seti,
    gtir, gtri, gtrr,
    eqir, eqri, eqrr,
};

unordered_map<string, OpCode> OP_CODES = {
    {"addr", addr}, {"addi", addi},
    {"mulr", mulr}, {"muli", muli},
    {"banr", banr}, {"bani", bani},
    {"borr", borr}, {"bori", bori},
    {"setr", setr}, {"seti", seti},
    {"gtir", gtir}, {"gtri", gtri}, {"gtrr", gtrr},
    {"eqir", eqir}, {"eqri", eqri}, {"eqrr", eqrr},
};

struct Instruction {
    OpCode op;
    int a, b, c;
};

int runOp(const Regs& registers, Instruction x) {
    int rega = registers[x.a], regb = registers[x.b];
    switch (x.op) {
        case addr:  return rega + regb;
        case addi:  return rega + x.b;
        case mulr:  return rega * regb;
        case muli:  return rega * x.b;
        case banr:  return rega & regb;
        case bani:  return rega & x.b;
        case borr:  return rega | regb;
        case bori:  return rega | x.b;
        case setr:  return rega;
        case seti:  return x.a;
        case gtir:  return x.a > regb;
        case gtri:  return rega > x.b;
        case gtrr:  return rega > regb;
        case eqir:  return x.a == regb;
        case eqri:  return rega == x.b;
        case eqrr:  return rega == regb;
        default: return 0;
    }
}

struct Program {
    vector<Instruction> instructions;
    Regs registers = {{0}};
    int ip = 0;
    int ip_register = 0;

    void runNextInstruction() {
        registers[ip_register] = ip;
        Instruction& i = instructions[ip];
        registers[i.c] = runOp(registers, i);
        ip = registers[ip_register];
        ip++;
    }
};

Program readProgram(const string& in) {
    istringstream iss(in);
    Program p;
    string line;

    getline(iss, line);
    sscanf(line.c_str(), "#ip %d", &p.ip_register);

    while (getline(iss, line)) {
        Instruction i;
        i.op = OP_CODES[line.substr(0, 4)];
        sscanf(line.c_str(), "%*s %d %d %d",
            &i.a, &i.b, &i.c);
        p.instructions.push_back(i);
    }
    return p;
}

int run(const string& in) {
    auto program = readProgram(in);

    while (program.ip < program.instructions.size()) {
        program.runNextInstruction();
    }

    return program.registers[0];
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Missing one argument" << endl;
        exit(1);
    }

    clock_t start = clock();
    auto answer = run(string(argv[1]));
    
    cout << "_duration:" << float( clock () - start ) * 1000.0 /  CLOCKS_PER_SEC << "\n";
    cout << answer << "\n";
    return 0;
}
