@256
D=A
@SP
M=D
@Sys.init$ret.bootstrap
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@5
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Sys.init
0;JMP
(Sys.init$ret.bootstrap)
// function Main.fibonacci 0
(Main.fibonacci)

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

// 	push constant 2
@2
D=A
@SP
A=M
M=D
@SP
M=M+1

// 	lt
@SP
AM=M-1
D=M
A=A-1
D=M-D
@TRUE0
D;JLT
@SP
A=M-1
M=0
@CONTINUE0
0;JMP
(TRUE0)
@SP
A=M-1
M=-1
(CONTINUE0)

// 	if-goto N_LT_2
@SP
AM=M-1
D=M
@N_LT_2
D;JNE

// 	goto N_GE_2
@N_GE_2
0;JMP

// label N_LT_2
(N_LT_2)

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

// 	return
@LCL
D=M
@Main.fibonacci$FRAME.0
M=D
@5
A=D-A
D=M
@Main.fibonacci$RETADDR.0
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
@Main.fibonacci$FRAME.0
AM=M-1
D=M
@THAT
M=D
@Main.fibonacci$FRAME.0
AM=M-1
D=M
@THIS
M=D
@Main.fibonacci$FRAME.0
AM=M-1
D=M
@ARG
M=D
@Main.fibonacci$FRAME.0
AM=M-1
D=M
@LCL
M=D
@Main.fibonacci$RETADDR.0
A=M
0;JMP

// label N_GE_2
(N_GE_2)

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

// 	push constant 2
@2
D=A
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

// 	call Main.fibonacci 1
@Main.fibonacci$ret.0
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@6
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Main.fibonacci
0;JMP
(Main.fibonacci$ret.0)

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

// 	push constant 1
@1
D=A
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

// 	call Main.fibonacci 1
@Main.fibonacci$ret.1
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@6
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Main.fibonacci
0;JMP
(Main.fibonacci$ret.1)

// 	add
@SP
AM=M-1
D=M
A=A-1
M=D+M

// 	return
@LCL
D=M
@Main.fibonacci$FRAME.1
M=D
@5
A=D-A
D=M
@Main.fibonacci$RETADDR.1
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
@Main.fibonacci$FRAME.1
AM=M-1
D=M
@THAT
M=D
@Main.fibonacci$FRAME.1
AM=M-1
D=M
@THIS
M=D
@Main.fibonacci$FRAME.1
AM=M-1
D=M
@ARG
M=D
@Main.fibonacci$FRAME.1
AM=M-1
D=M
@LCL
M=D
@Main.fibonacci$RETADDR.1
A=M
0;JMP

// function Sys.init 0
(Sys.init)

// 	push constant 4
@4
D=A
@SP
A=M
M=D
@SP
M=M+1

// 	call Main.fibonacci 1
@Sys.init$ret.0
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@6
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Main.fibonacci
0;JMP
(Sys.init$ret.0)

// label END
(END)

// 	goto END
@END
0;JMP

