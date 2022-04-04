/*************************************************************************
  > File Name: cc.c
  > Author: SuWeishuai
  > Mail: suwsl@foxmail.com
  > Created Time: Mon 04 Apr 2022 06:13:25 PM CST
 ************************************************************************/

void cc_c_argc_0_return_0(void){
    return ;
}

void cc_c_argc_1_return_0(int a){
    return ;
}

void cc_c_argc_2_return_0(int a,int b){
    return ;
}

int cc_c_argc_0_return_1(void){
    return 0x12345678;
}

int cc_c_embedded_assembly(void){
    int input  = 0x12345678;
    int result = 0;

    __asm__ __volatile__(
            "mov %1,%0":
            "=r"(result):
            "r"(input)   );
    return result;
}
