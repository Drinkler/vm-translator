// function SimpleFunction.test 2
(SimpleFunction.test)
@SP
A=M
M=0
@SP
M=M+1
@SP
A=M
M=0
@SP
M=M+1

// 	push local 0
@0
D=A
@LCL
A=D+M
D=M
@SP
A=M
M=D
@SP
M=M+1

// 	push local 1
@1
D=A
@LCL
A=D+M
D=M
@SP
A=M
M=D
@SP
M=M+1

// 	add
@SP
AM=M-1
D=M
A=A-1
M=D+M

// 	not
@SP
A=M-1
M=!M

// 	push argument 0
@0
D=A
@ARG
A=D+M
D=M
@SP
A=M
M=D
@SP
M=M+1

// 	add
@SP
AM=M-1
D=M
A=A-1
M=D+M

// 	push argument 1
@1
D=A
@ARG
A=D+M
D=M
@SP
A=M
M=D
@SP
M=M+1

// 	sub
@SP
AM=M-1
D=M
A=A-1
M=M-D

// 	return
@LCL
D=M
@SimpleFunction.test$FRAME.0
M=D
@5
A=D-A
D=M
@SimpleFunction.test$RETADDR.0
M=D
@SP
AM=M-1
D=M
@ARG
A=M
M=D
@ARG
D=M+1
@SP
M=D
@SimpleFunction.test$FRAME.0
AM=M-1
D=M
@THAT
M=D
@SimpleFunction.test$FRAME.0
AM=M-1
D=M
@THIS
M=D
@SimpleFunction.test$FRAME.0
AM=M-1
D=M
@ARG
M=D
@SimpleFunction.test$FRAME.0
AM=M-1
D=M
@LCL
M=D
@SimpleFunction.test$RETADDR.0
A=M
0;JMP

