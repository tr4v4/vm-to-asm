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
                "@%d\nD=A\n@LCL\nA=M\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n",
                index);
            fputs(code, fout);
        } else if (strncmp(segment, "argument", MAX_SEGMENT_LENGTH) == 0) {
            char code[MAX_CODE_LENGTH];
            sprintf(
                code,
                "@%d\nD=A\n@ARG\nA=M\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n",
                index);
            fputs(code, fout);
        } else if (strncmp(segment, "static", MAX_SEGMENT_LENGTH) == 0) {
            char code[MAX_CODE_LENGTH];
            sprintf(code,
                    "@%d\nD=A\n@16\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n",
                    index);
            fputs(code, fout);
        }
    } else if (cType == C_POP) {
        if (strncmp(segment, "local", MAX_SEGMENT_LENGTH) == 0) {
            char code[MAX_CODE_LENGTH];
            sprintf(code,
                    "@SP\nM=M-1\n@%d\nD=A\n@LCL\nA=M\nD=D+A\n@R13\nM=D\n@SP\nA="
                    "M\nD=M\n@R13\nA=M\nM=D\n",
                    index);
            fputs(code, fout);
        } else if (strncmp(segment, "argument", MAX_SEGMENT_LENGTH) == 0) {
            char code[MAX_CODE_LENGTH];
            sprintf(code,
                    "@SP\nM=M-1\n@%d\nD=A\n@ARG\nA=M\nD=D+A\n@R13\nM=D\n@SP\nA="
                    "M\nD=M\n@R13\nA=M\nM=D\n",
                    index);
            fputs(code, fout);
        } else if (strncmp(segment, "static", MAX_SEGMENT_LENGTH) == 0) {
            char code[MAX_CODE_LENGTH];
            sprintf(code,
                    "@SP\nM=M-1\n@%d\nD=A\n@16\nD=D+A\n@R13\nM=D\n@SP\nA="
                    "M\nD=M\n@R13\nA=M\nM=D\n",
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

void writeFunction(FILE *fout, command cType, char function[], int vars) {
    if (cType == C_FUNCTION) {
        writeFlow(fout, C_LABEL, function);
        for (int i = 0; i < vars; i++)
            writePushPop(fout, C_PUSH, (char *)"constant", 0);
    } else if (cType == C_CALL) {
        // FIXME: usare ftell potrebbe non essere adatto a programmi lunghi
        long int index = ftell(fout);
        char ret[MAX_COMMAND_LENGTH];
        sprintf(ret, "RET_%ld", index);
        char code[MAX_CODE_LENGTH];
        sprintf(code,
                "@%s\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n"
                "@LCL\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n"
                "@ARG\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n"
                "@THIS\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n"
                "@THAT\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n"
                "@SP\nD=M\n@%d\nD=D-A\n@5\nD=D-A\n@ARG\nM=D\n"
                "@SP\nD=M\n@LCL\nM=D\n",
                ret, vars);
        fputs(code, fout);
        writeFlow(fout, C_GOTO, function);
        writeFlow(fout, C_LABEL, ret);
    } else if (cType == C_RETURN) {
        // NOTE: R15 = FRAME, R14 = RET
        char code[MAX_CODE_LENGTH] =
            "@LCL\nD=M\n@R15\nM=D\n"
            "@R15\nD=M\n@5\nD=D-A\nA=D\nD=M\n@R14\nM=D\n"
            "@SP\nM=M-1\nA=M\nD=M\n@ARG\nA=M\nM=D\n"
            "@ARG\nD=M+1\n@SP\nM=D\n"
            "@R15\nD=M\n@1\nD=D-A\nA=D\nD=M\n@THAT\nM=D\n"
            "@R15\nD=M\n@2\nD=D-A\nA=D\nD=M\n@THIS\nM=D\n"
            "@R15\nD=M\n@3\nD=D-A\nA=D\nD=M\n@ARG\nM=D\n"
            "@R15\nD=M\n@4\nD=D-A\nA=D\nD=M\n@LCL\nM=D\n";
        fputs(code, fout);
        writeFlow(fout, C_GOTO, (char *)"R14\nA=M");  // !! ASM Injection !!
    }
}