//
// Created by nathan_pc on 11/14/2023.
//

#ifndef IC10_INTERPRETER_INTERP_MATH_H
#define IC10_INTERPRETER_INTERP_MATH_H
double CADD(double a,double b){return a+b;}
double CSUB(double a,double b){return a-b;}
double CMUL(double a,double b){return a*b;}
double CDIV(double a,double b){return a/b;}
double CAND(double a,double b){return (int)a&(int)b;}
double CXOR(double a,double b){return (int)a^(int)b;}
double CBLS(double a,double b){return (int)a<<(int)b;}
double CBRS(double a,double b){return (int)a>>(int)b;}
double max(double a,double b){return a>b?a:b;};
#endif //IC10_INTERPRETER_INTERP_MATH_H
