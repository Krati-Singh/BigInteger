#ifndef BigInteger_H
#define BigInteger_H

//Function Prototype
struct BigInteger initialize(char *s);
struct BigInteger add(struct BigInteger a ,struct BigInteger b);
struct BigInteger sub(struct BigInteger a,struct BigInteger b);
struct BigInteger mul(struct BigInteger a,struct BigInteger b);
struct BigInteger div1(struct BigInteger a,struct BigInteger b);
struct BigInteger mod(struct BigInteger a,struct BigInteger b);
void display(struct BigInteger a);


#endif