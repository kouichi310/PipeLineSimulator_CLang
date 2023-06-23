# PipeLineSimulator_CLang

## 概要
パイプラインシミュレーターです

### How To Use
`main.c`の`main()`の初期データを変更することで任意のプログラムを実行できます。

## OPCode_Debugger
memの1ワードを入力することで、簡単なニーモニックに変換できます。
コンパイルして、使ってください。

### How To Use
```
-> % ./opcode_debuger                      
メモリの内容を入力してください。(int,65535まで)
12576
opcode : Add
rs : 1
rt : 2
rd : 0
ニーモニック : mem[rd(0)] = Reg[rs(1)] + Reg[rt(2)]
```
