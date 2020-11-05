#include <stdio.h>
#include <string.h>
#define STDIN 0
void jmptarget ();
void calltarget ();
struct data {
    char buf [1024];
    int arg1;
    int arg2;
    int arg3;
    void (* jmpPtr )();
    void (* callPtr )(int ,int ,int);
};
void overflow () {
    struct data our_data;
    our_data.jmpPtr = && label;
    our_data.callPtr = &calltarget;
    printf("%x\n", (unsigned int)& our_data.buf);
    printf("\ndata >");
    read(STDIN , our_data.buf , 1044);
    printf("\n");
    asm("push%0; push%1; push%2; call*%3; add$12 ,%% esp;"
    : : "r"(our_data.arg3),
    "r"(our_data.arg2),
    "r"(our_data.arg1),
    "r"(our_data.callPtr ));
    asm("jmp*%0" : : "r"(our_data.jmpPtr ));
    printf("?\n");
    label:
    printf("labelreached\n");
}
void jmptarget () {
	printf("jmptarget ()called\n");
}
void calltarget(int arg1 , int arg2 , int arg3) {
    printf("calltarget ()called(args:%x,%x,%x)\n",
    arg1 , arg2 , arg3 );
}
int main(int argc , char* argv []) {
    setbuf(stdout , NULL );
    overflow ();
    printf("\ndone .\n");
    return 0;
}
