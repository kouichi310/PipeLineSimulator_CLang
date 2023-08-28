#include <stdio.h>

typedef unsigned short u16;

// ステージ間レジスタ
u16 IF_ID = 0;
u16 ID_EX[4] = {0};
u16 EX_MEM[4] = {0};
u16 MEM_WB[4] = {0};

// メモリ
u16 Mem[100] = {0};

// レジスタ
u16 Reg[16] = {0};

// PC
u16 pc = 0;

enum Opcode
{
    None,
    Load,
    Store,
    Add,
    Sub,
    Mul,
    Div,
};

// IFステージ
int if_stage()
{
    // 命令フェッチ
    IF_ID = Mem[pc];
    pc++;

    // フェッチした命令が終了を示す場合（None命令の場合）は1を返す
    if (IF_ID == 0)
        return 1;

    return 0;
}

// IDステージ
void id_stage()
{
    // 命令デコード
    int opcode = (IF_ID >> 12) & 0xF; // オペコードの上位4bit
    int rs = (IF_ID >> 8) & 0xF;      // オペランドの上位4bitから上位8bit
    int rt = (IF_ID >> 4) & 0xF;      // オペランドの下位8bitから下位4bit
    int rd = IF_ID & 0xF;             // オペランドの下位4bit

    if (opcode == Load)
    {
        // レジスタの値を取得
        int rs_value = Reg[rs];
        // ID/EXレジスタに値を設定
        ID_EX[0] = opcode;
        ID_EX[1] = rs_value;
        ID_EX[2] = rt;
        ID_EX[3] = rd;
    }
    else if (opcode == Store)
    {
        // レジスタの値を取得
        int rs_value = Reg[rs];
        int rt_value = Reg[rt];
        // ID/EXレジスタに値を設定
        ID_EX[0] = opcode;
        ID_EX[1] = rs_value;
        ID_EX[2] = rt_value;
        ID_EX[3] = rd;
    }
    else
    {
        // レジスタの値を取得
        int rs_value = Reg[rs];
        int rt_value = Reg[rt];
        // ID/EXレジスタに値を設定
        ID_EX[0] = opcode;
        ID_EX[1] = rs_value;
        ID_EX[2] = rt_value;
        ID_EX[3] = rd;
    }
}

// EXステージ
void ex_stage()
{
    // 演算実行
    int opcode = ID_EX[0];
    int rs = ID_EX[1];
    int rt = ID_EX[2];
    int rd = ID_EX[3];
    int result = 0;

    if (opcode == Load)
    {
        // Load命令
        result = rd + rs; // メモリからデータをロード
        EX_MEM[2] = rt;
    }
    else if (opcode == Store)
    {
        // Store命令
        result = rd + rs; // メモリからデータをロード
        EX_MEM[2] = rt;
    }
    else if (opcode == Add)
    {
        // Add命令
        result = rs + rt;
    }
    else if (opcode == Sub)
    {
        // Sub命令
        result = rs - rt;
    }
    else if (opcode == Mul)
    {
        // Mul命令
        result = rs * rt;
    }
    else if (opcode == Div)
    {
        // Div命令
        result = rs / rt;
    }

    // EX/MEMレジスタに値を設定
    EX_MEM[0] = opcode;
    EX_MEM[1] = result;
    EX_MEM[3] = rd;
}

// MEMステージ
void mem_stage()
{
    // メモリアクセス
    int opcode = EX_MEM[0];
    int result = EX_MEM[1];
    int rt = EX_MEM[2];
    int memoryResult = 0;

    if (opcode == Load)
    {
        // Load命令
        memoryResult = Mem[result]; // メモリからデータをロード
        MEM_WB[1] = memoryResult;
    }
    else if (opcode == Store)
    {
        // Store命令
        Mem[result] = Reg[rt]; // レジスタ0の値をメモリにストア
        MEM_WB[1] = EX_MEM[1];
    }
    else
    {
        MEM_WB[1] = EX_MEM[1];
    }

    // MEM/WBレジスタに値を設定
    MEM_WB[0] = EX_MEM[0];
    MEM_WB[2] = EX_MEM[2];
    MEM_WB[3] = EX_MEM[3];
}

// WBステージ
void wb_stage()
{
    // レジスタ書き込み
    int opcode = MEM_WB[0];
    int result = MEM_WB[1];
    int rt = MEM_WB[2];
    int rd = MEM_WB[3];

    if (opcode == Load)
    {
        // Load命令
        Reg[rt] = result; // レジスタ0に結果を書き込み
    }
    else if (opcode != Store)
    {
        Reg[rd] = result;
    }
}

void print_registory()
{
    // Reg[0]~Reg[15]の値を表示
    for (int i = 0; i < 16; i++)
    {
        printf("Reg[%d] = %d\n", i, Reg[i]);
    }
}

int main(void)
{
    // 初期データの設定
    Mem[0] = 12801;
    Reg[0] = 1;
    Reg[1] = 2;

    // パイプラインの実行
    while (1)
    {
        if (if_stage() == 1)
            break;

        id_stage();
        ex_stage();
        mem_stage();
        wb_stage();

        print_registory();
    }

    return 0;
}
