#include <stdio.h>

enum Opcode {
    None,
    Load,
    Store,
    Add,
    Sub,
    Mul,
    Div,
};

int main(){
    int mem=0,opcode=0,rs=0,rt=0,rd=0;

    puts("メモリの内容を入力してください。(int,65535まで)");
    scanf("%d", &mem);

    opcode = (mem >> 12) & 0xF;
    rs = (mem >> 8) & 0xF;
    rt = (mem >> 4) & 0xF;
    rd = mem & 0xF; //constantの可能性もあり

    switch (opcode)
    {
    case None:
        puts("opcode : None");
        printf("rs : %d\n",rs);
        printf("rs : %d\n",rt);
        printf("rs : %d\n",rd);
        printf("ニーモニック : none\n");
        break;
    case Load:
        puts("opcode : Load");
        printf("rs : %d\n",rs);
        printf("rt : %d\n",rt);
        printf("constant : %d\n",rd);
        printf("ニーモニック : Reg[%d] = mem[const(%d) + Reg[rs(%d)]]\n",rt,rd,rs);
        break;
    case Store:
        puts("opcode : Store");
        printf("rs : %d\n",rs);
        printf("rt : %d\n",rt);
        printf("constant : %d\n",rd);
        printf("ニーモニック : mem[const(%d) + Reg[rs(%d)]] = Reg[rt(%d)]\n",rd,rs,rt);
        break;
    case Add:
        puts("opcode : Add");
        printf("rs : %d\n",rs);
        printf("rt : %d\n",rt);
        printf("rd : %d\n",rd);
        printf("ニーモニック : Reg[rd(%d)] = Reg[rs(%d)] + Reg[rt(%d)]\n",rd,rs,rt);
        break;
    case Sub:
        puts("opcode : Sub");
        printf("rs : %d\n",rs);
        printf("rt : %d\n",rt);
        printf("rd : %d\n",rd);
        printf("ニーモニック : Reg[rd(%d)] = Reg[rs(%d)] - Reg[rt(%d)]\n",rd,rs,rt);
        break;
    case Mul:
        puts("opcode : Mul");
        printf("rs : %d\n",rs);
        printf("rt : %d\n",rt);
        printf("rd : %d\n",rd);
        printf("ニーモニック : Reg[rd(%d)] = Reg[rs(%d)] * Reg[rt(%d)]\n",rd,rs,rt);
        break;
    case Div:
        puts("opcode : Div");
        printf("rs : %d\n",rs);
        printf("rt : %d\n",rt);
        printf("rd : %d\n",rd);
        printf("ニーモニック : Reg[rd(%d)] = Reg[rs(%d)] / Reg[rt(%d)]\n",rd,rs,rt);
        break;
    default:
        puts("opcodeが不正な形式です。");
        break;
    }
}
