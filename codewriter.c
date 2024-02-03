#include "codewriter.h"

void bootstrap(FILE *fout) {
    char code[MAX_CODE_LENGTH] = "@256\nD=A\n@SP\nM=D\n";
    fputs(code, fout);
}

void writeArithmetic(FILE *fout, char cString[]) {
    if (strncmp(cString, "add", MAX_COMMAND_LENGTH) == 0) {
        char code[MAX_CODE_LENGTH] =
            "@SP\nD=M\n@2\nD=D-A\nA=D\nD=M\nA=A+1\nD=D+M\nA=A-1\nM=D\n@SP\nM=M-"
            "1\n";
        fputs(code, fout);
    } else if (strncmp(cString, "sub", MAX_COMMAND_LENGTH) == 0) {
        char code[MAX_CODE_LENGTH] =
            "@SP\nD=M\n@2\nD=D-A\nA=D\nD=M\nA=A+1\nD=D-M\nA=A-1\nM=D\n@SP\nM=M-"
            "1\n";
        fputs(code, fout);
    } else if (strncmp(cString, "neg", MAX_COMMAND_LENGTH) == 0) {
        char code[MAX_CODE_LENGTH] = "@SP\nD=M-1\nA=D\nM=-M\n";
        fputs(code, fout);
    } else if (strncmp(cString, "eq", MAX_COMMAND_LENGTH) == 0) {
        // FIXME: usare ftell potrebbe non essere adatto a programmi lunghi
        long int index = ftell(fout);
        char code[MAX_CODE_LENGTH];
        sprintf(code,
                "@SP\nD=M\n@2\nD=D-A\nA=D\nD=M\nA=A+1\nD=D-M\n@EQ_%ld\nD;JEQ\n@"
                "SP\nD=M\n@2\nD=D-A\nA=D\nM=0\n@END_EQ_%ld\n0;JMP\n(EQ_%ld)\n@"
                "SP\nD=M\n@2\nD=D-A\nA=D\nM=-1\n(END_EQ_%ld)\n@SP\nM=M-1\n",
                index, index, index, index);
        fputs(code, fout);
    } else if (strncmp(cString, "gt", MAX_COMMAND_LENGTH) == 0) {
        // FIXME: usare ftell potrebbe non essere adatto a programmi lunghi
        long int index = ftell(fout);
        char code[MAX_CODE_LENGTH];
        sprintf(code,
                "@SP\nD=M\n@2\nD=D-A\nA=D\nD=M\nA=A+1\nD=D-M\n@GT_%ld\nD;JGT\n@"
                "SP\nD=M\n@2\nD=D-A\nA=D\nM=0\n@END_GT_%ld\n0;JMP\n(GT_%ld)\n@"
                "SP\nD=M\n@2\nD=D-A\nA=D\nM=-1\n(END_GT_%ld)\n@SP\nM=M-1\n",
                index, index, index, index);
        fputs(code, fout);
    } else if (strncmp(cString, "lt", MAX_COMMAND_LENGTH) == 0) {
        // FIXME: usare ftell potrebbe non essere adatto a programmi lunghi
        long int index = ftell(fout);
        char code[MAX_CODE_LENGTH];
        sprintf(code,
                "@SP\nD=M\n@2\nD=D-A\nA=D\nD=M\nA=A+1\nD=D-M\n@LT_%ld\nD;JLT\n@"
                "SP\nD=M\n@2\nD=D-A\nA=D\nM=0\n@END_LT_%ld\n0;JMP\n(LT_%ld)\n@"
                "SP\nD=M\n@2\nD=D-A\nA=D\nM=-1\n(END_LT_%ld)\n@SP\nM=M-1\n",
                index, index, index, index);
        fputs(code, fout);
    } else if (strncmp(cString, "and", MAX_COMMAND_LENGTH) == 0) {
        char code[MAX_CODE_LENGTH] =
            "@SP\nD=M-1\nA=D\nD=M\nA=A-1\nM=D&M\n@SP\nM=M-1\n";
        fputs(code, fout);
    } else if (strncmp(cString, "or", MAX_COMMAND_LENGTH) == 0) {
        char code[MAX_CODE_LENGTH] =
            "@SP\nD=M-1\nA=D\nD=M\nA=A-1\nM=D|M\n@SP\nM=M-1\n";
        fputs(code, fout);
    } else if (strncmp(cString, "not", MAX_COMMAND_LENGTH) == 0) {
        char code[MAX_CODE_LENGTH] = "@SP\nD=M-1\nA=D\nM=!M\n";
        fputs(code, fout);
    }
}

void writePushPop(FILE *fout, command cType, char segment[], int index) {
    if (cType == C_PUSH) {
        if (strncmp(segment, "constant", MAX_SEGMENT_LENGTH) == 0) {
            char code[MAX_CODE_LENGTH];
            sprintf(code, "@%d\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n", index);
            fputs(code, fout);
        } else if (strncmp(segment, "local", MAX_SEGMENT_LENGTH) == 0) {
            char code[MAX_CODE_LENGTH];
            sprintf(
                code,
                "@%d\nD=A\n@LCL\nA=M\nA=A+D\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n",
                index);
            fputs(code, fout);
        } else if (strncmp(segment, "argument", MAX_SEGMENT_LENGTH) == 0) {
            char code[MAX_CODE_LENGTH];
            sprintf(
                code,
                "@%d\nD=A\n@ARG\nA=M\nA=A+D\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n",
                index);
            fputs(code, fout);
        } else if (strncmp(segment, "static", MAX_SEGMENT_LENGTH) == 0) {
            char code[MAX_CODE_LENGTH];
            sprintf(code,
                    "@%d\nD=A\n@16\nA=A+D\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n",
                    index);
            fputs(code, fout);
        }
    } else if (cType == C_POP) {
        if (strncmp(segment, "local", MAX_SEGMENT_LENGTH) == 0) {
            char code[MAX_CODE_LENGTH];
            sprintf(code,
                    "@SP\nM=M-1\n@%d\nD=A\n@LCL\nA=M\nD=A+D\n@R15\nM=D\n@SP\nA="
                    "M\nD=M\n@R15\nA=M\nM=D\n",
                    index);
            fputs(code, fout);
        } else if (strncmp(segment, "argument", MAX_SEGMENT_LENGTH) == 0) {
            char code[MAX_CODE_LENGTH];
            sprintf(code,
                    "@SP\nM=M-1\n@%d\nD=A\n@ARG\nA=M\nD=A+D\n@R15\nM=D\n@SP\nA="
                    "M\nD=M\n@R15\nA=M\nM=D\n",
                    index);
            fputs(code, fout);
        } else if (strncmp(segment, "static", MAX_SEGMENT_LENGTH) == 0) {
            char code[MAX_CODE_LENGTH];
            sprintf(code,
                    "@SP\nM=M-1\n@%d\nD=A\n@16\nD=A+D\n@R15\nM=D\n@SP\nA="
                    "M\nD=M\n@R15\nA=M\nM=D\n",
                    index);
            fputs(code, fout);
        }
    }
}

void writeFlow(FILE *fout, command cType, char label[]) {
    if (cType == C_LABEL) {
        char code[MAX_CODE_LENGTH];
        sprintf(code, "(%s)\n", label);
        fputs(code, fout);
    } else if (cType == C_GOTO) {
        char code[MAX_CODE_LENGTH];
        sprintf(code, "@%s\n0;JMP\n", label);
        fputs(code, fout);
    } else if (cType == C_IF) {
        char code[MAX_CODE_LENGTH];
        sprintf(code, "@SP\nM=M-1\nA=M\nD=M\n@%s\nD;JNE\n", label);
        fputs(code, fout);
    }
}