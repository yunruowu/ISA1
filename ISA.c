/*************************************************************************
    > File Name: 2.c
    > Author: Yunruowu
    > Mail: xuyunyang12345@163.com
    > Created Time: 2018年09月12日 星期三 15时05分00秒
 ************************************************************************/
#ifndef ISA
#define ISA 
#include<stdio.h>
#include<stdlib.h>

enum opcodes{
	//	R-Type
	//	OP_JR = 0,
		OP_SPECIAL = 0,
//I-Type
	//	I-Type ALU Insns
		OP_ADDI,OP_ADDUI,
	//	I-Type Branch and Jump Insns
		OP_BNEZ,OP_BRE,
	//	I-Type Load and Store Insns
		OP_STORED,OP_LOADI,OP_LOADIMM,OP_LOADD,
	//	J-Type Insns
		OP_NOP,OP_JR,
	//	MOV
		OP_MOVI,OP_MOVD,

		NUM_OPCODES
};
enum functions{
	OP_ADD = 0,OP_ADDU,OP_ADDDOU,

	NUM_FUNCS
};




char* mem;
long mem_size = 0x080000;
int ireg_size = 0x1000;
int *r;
int dreg_size = 0x8;
double *rrd;

unsigned char read_mem_ubyte(long addr)
{
	return *((unsigned char *)(mem + addr));
}

void write_mem_ubyte(long addr, unsigned char val)
{
	*((unsigned char *)(mem + addr)) = val;
}


char read_mem_byte(long addr)
{
	return *((char*)(mem + addr));
}
void write_mem_byte(long addr, char val)
{
	*((char *)(mem + addr)) = val;
}



//unsigned short
unsigned short read_mem_uhalfword(long addr)
{
	return *((unsigned short*)(mem + addr));
}
void write_mem_uhalfword(long addr, unsigned short val)
{
	*((unsigned short*)(mem + addr)) = val;
}


//short
short read_mem_halfword(long addr)
{
	return *((short*)(mem + addr));
}
void write_mem_halfword(long addr, short val)
{
	*((short*)(mem + addr)) = val;
}

//unsigned int
unsigned int read_mem_uword(long addr)
{
	return *((unsigned int*)(mem + addr));
}
void write_mem_uword(long addr,unsigned int val)
{
	*((unsigned int*)(mem + addr)) = val;
}

//int
int read_mem_word(long addr)
{
	return *((int*)(mem + addr));
}


void write_mem_word(long addr, int val)
{
	*((int*)(mem + addr)) = val;
}



float read_mem_float(long addr)
{
	return *((float*)(mem + addr));
}
void write_mem_float(long addr, float val)
{
	*((float*)(mem + addr)) = val;
}



double read_mem_double(long addr)
{
	return *((double*)(mem + addr));
}
void write_mem_double(long addr, double val)
{
	*((double*)(mem + addr)) = val;
}


//functions for register file
int get_int(long addr)
{
	return *((int*)(r+addr));
}

void put_int(long addr,int val)
{
	*((int*)(r+addr))= val;
}

int get_uint(long addr)
{
	return *((unsigned int*)(r+addr));
}

void put_uint(long addr,int val)
{
	*((unsigned int *)(r+addr)) = val;
}

float get_flo(long addr)
{
	return *((float*)(r+addr));
}

void put_flo(long addr,float val)
{
	*((float *)(r+addr))=val;
}

short get_shor(long addr)
{
	return *((short*)(r+addr));
}

void put_shor(long addr, short val)
{
	*((short*)(r+addr))=val;
}

unsigned short get_ushor(long addr)
{
	return *((unsigned short*)(r+addr));
}

void put_ushor(long addr,unsigned short val)
{
	*((unsigned short*)(r+addr))=val;
}

char get_char(long addr){
	return *((char*)(r+addr));
}

void put_char(long addr,char val){
	*((char*)(r+addr)) = val;
}

//double register
double get_double(long addr){
	return *(double*)(rrd + addr);
}

void put_double(long addr,double val){
	*((double*)(rrd+addr)) = val;
}












long INSA_ADD(long pc){
	unsigned int insn = read_mem_uword(pc);//读第一条指令
	int RS1	= (insn>>21) & 0x1f;
	int RS2 = (insn>>16) & 0x1f;
	int RD = (insn>>11) & 0x1f;
	int *rd = r + RD;
	int rs1 = get_int(RS1);
	int rs2 = get_int(RS2);
	*rd = rs1 + rs2;
	return pc + 4;
}

long INSA_ADDU(long pc){
	unsigned int insn = read_mem_uword(pc);//读第一条指令
	int RS1	= (insn>>21) & 0x1f;
	int RS2 = (insn>>16) & 0x1f;
	int RD = (insn>>11) & 0x1f;
	unsigned int rs1 = get_uint(RS1);
	unsigned int rs2 = get_uint(RS2);
	return pc + 4;
}


long INSN_ADDI(long pc){
	unsigned int insn = read_mem_uword(pc);//读第一条指令
	int RS1	= (insn>>21) & 0x1f;
	int RS2 = (insn>>16) & 0x1f;
	int IMM = (int)(short)(insn & 0x1fffff);//符号扩展
//	printf("IMM:%d\n",IMM);
//	printf("%d",get_int(RS1));
	put_int(RS1,get_int(RS1)+IMM);
	return pc + 4;

}
/*long INSN_ADDUI(long pc){
	unsigned int *rd = r + RS2;
	unsigned int rs = get_int(RS1);
	unsigned int UIMM= (unsigned int)(insn & 0xffff);
	*rd = rd + UIMM;
	return pc + 4;
}*/

long INSA_ADDUI(long pc){
	unsigned int insn = read_mem_uword(pc);//读第一条指令
	int RS1	= (insn>>21) & 0x1f;
	int RS2 = (insn>>16) & 0x1f;
	int IMM = (int)(short)(insn & 0xffff);//符号扩展
	int *rd = r + RS2;
	int rs = get_int(RS1);
	*rd = rs + IMM;
	return pc + 4;
}

long INSN_ADDDOU(long pc){//double的寄存器加
	unsigned int insn = read_mem_uword(pc);//读第一条指令
		//指令译码
	int OPCODE = (insn>>26) & 0x3f;
	int RS1	= (insn>>21) & 0x1f;
	int RS2 = (insn>>16) & 0x1f;
	int RD = (insn>>11) & 0x1f;
	//printf("%d\n",get_int(RS1)+get_int(RS2));
	//printf("%f\n",read_mem_double(get_int(RS1))+get_int(RS2));
	
	put_double(RD,get_double(RD) + read_mem_double(get_int(RS1)+get_int(RS2)));
	return pc + 4;
}

/*long INSN_ADDDOUI(pc){//double的立即数加（感觉没有用）
	unsigned int insn = read_mem_uword(pc);//读第一条指令
	int RS1	= (insn>>21) & 0x1f;
	int RS2 = (insn>>16) & 0x1f;
	double *rd = rrd + RS2;
	double rs = get_double(RS1);
	*rd = rs + IMM;
	return pc + 4;
}*/

long INSN_MOVI(long pc){
//	printf("MOVI\n");
	unsigned int insn = read_mem_uword(pc);

	int RS1 = (insn>>21) & 0x1f;//寄存器号
	int RS2 = (insn>>16) & 0x1f;
	put_int(RS2,get_int(RS1));
	return pc + 4;
}

long INSN_MOVD(long pc){
//	printf("MOVD\n");
	unsigned int insn = read_mem_uword(pc);
	int RS1 = (insn>>21) & 0x1f;//寄存器号
	int RS2 = (insn>>16) & 0x1f;
	put_double(RS2,get_double(RS1));
	return pc + 4;
}


long INSN_LOADI(long pc){
	unsigned int insn = read_mem_uword(pc);
	int RS1 = (insn>>21) & 0x1f;//寄存器号
	int RS2 = (insn>>16) & 0x1f;
	int IMM = (int)(short)(insn & 0xffff);
//	printf("%d",get_int(RS2));
	int val=read_mem_word(long(IMM + get_int(RS1)));
	put_int(RS2,val);
	return pc+4;

}

long INSN_LOADIMM(long pc){
//	printf("LO\n");
	unsigned int insn = read_mem_uword(pc);
	int RS1 = (insn>>21) & 0x1f;
	int IMM = (int)(short)(insn & 0xfffff);
	put_int(RS1,IMM);
	return pc+4;
}
long INSN_LOADD(long pc){
	unsigned int insn = read_mem_uword(pc);
	int RS1 = (insn>>21) & 0x1f;
	int RS2 = (insn>>16) & 0x1f;
	int IMM = (int)(short)(insn & 0xffff);
	put_double(RS2,read_mem_double(long(IMM + get_int(RS1))));
	return pc + 4;
}

long INSN_STORED(long pc){
	unsigned int insn = read_mem_uword(pc);
	int RS1 = (insn>>21) & 0x1f;
	int RS2 = (insn>>16) & 0x1f;
	int IMM = (int)(short)(insn & 0xffff);
	double rt = get_int(RS2);
	double rs = get_double(RS1);
	write_mem_double(rt+IMM,rs);
	return pc + 4;

}


long INSN_BRE(long pc){//分支指令
	unsigned int insn = read_mem_uword(pc);
	int RS1 = (insn>>21) & 0x1f;//存放i
	int RS2 = (insn>>16) & 0x1f;//存放N
	int IMM = (int)(short)(insn & 0xffff);
	int rt = get_int(RS2);
	int rs = get_int(RS1)/8;
 	if(rs < rt){
		return pc - 8;
	}
	else{
		return pc + 4;
	}


}

long INSN_NOP(long pc){
	return pc + 4;
}

long INSN_JR(long pc)
{
	unsigned int insn = read_mem_uword(pc);//读第一条指令
	int RS1	= (insn>>21) & 0x1f;
	return 0;
}


void Execution(void)
{
	long pc;
	pc = 0x1000;
	for(;pc;)
	{	
	//	printf("%d\n",pc);
		unsigned int insn = read_mem_uword(pc);//读第一条指令
		//指令译码
		int OPCODE = (insn>>26) & 0x3f;
		int RS1	= (insn>>21) & 0x1f;
		int RS2 = (insn>>16) & 0x1f;
		int RD = (insn>>11) & 0x1f;
		int IMM = (int)(short)(insn & 0xffff);//符号扩展
		unsigned int UIMM = (unsigned int)(short)(insn & 0xffff);//0扩展
		int FUNC = insn & 0x7ff;
		int OFFSET = insn & 0x3fffff;
		if(OPCODE)
		{
			switch(OPCODE){
				case OP_ADDI:	pc = INSN_ADDI(pc);
								break;
		//		case OP_ADDUI:	pc = INSN_ADDUI(pc);
		//						break;
				case OP_NOP:	pc = INSN_NOP(pc);
								break;
				case OP_LOADI:  pc = INSN_LOADI(pc);
							//	printf("%d\n",get_int(1));					
								break;
				case OP_LOADIMM:pc = INSN_LOADIMM(pc);
							//	printf("%f\n",1.1);
								break;
				case OP_LOADD:	pc = INSN_LOADD(pc);
								break;
				case OP_STORED:	pc = INSN_STORED(pc);
								break;
				case OP_JR:		pc = INSN_JR(pc);
								break;
				case OP_BRE:	pc = INSN_BRE(pc);
								break;
				case OP_MOVI:	pc = INSN_MOVI(pc);
								break;
				case OP_MOVD:	pc = INSN_MOVD(pc);
								break;
				default:		printf("error1:unimplemented instruction\n");
								exit(-1);
			}//end switch(OPCODE)
		}//end if(OPCODE)
		else
		{
			switch(FUNC){
			/*	case OP_ADD:	pc = INSN_ADD(pc);
								break;
				case OP_ADDU:	pc = INSN_ADDU(pc);
								break;*/
				case OP_ADDDOU: pc = INSN_ADDDOU(pc);
								break;
				default:		printf("error2:unimplemented instruction\n");
								exit(-1);
			}//end switch(FUNC)
		}//end else
	}//end for
}//end Execution()







int main()
{
	unsigned char uch1,uch2;
	char cha1,cha2;
	unsigned short uns1,uns2;
	short sho1,sho2;
	int in1,in2;
	unsigned int uni1,uni2;
	float fl1,fl2;
	double dou1,dou2;
	unsigned long addr = 256;
	mem = (char*)malloc(sizeof(char)* mem_size);
	r = (int*)malloc(sizeof(int)*ireg_size);
	rrd = (double*)malloc(sizeof(double)*8);
	if(mem==NULL)
	{
		printf("error:main memory allocation\n");
		exit(-1);
	}
	if(r==NULL)
	{
		printf("error:main Register file allocation\n");
		exit(-1);
	}
	
	put_int(0,0);
	put_double(0,0.0);
	put_int(1,1);
	for(long i = 0x1100;(i/8-0x1100)<512; i=i+8 ){
		write_mem_double(i,2.0);
	}
	write_mem_uword(1,512);
	//write_mem_uword(0x100,0x18030001);

	write_mem_uword(0x1000,0x2c010000);//MOVI R1=0	i
///	printf("%d\n",get_int(1));
	write_mem_uword(0x1004,0x30010000);//MOVD D1=0.0	sum
//	printf("%f\n",get_double(1));
	//printf("%d\n",(0x1c400200>>26)&0x3f);
	write_mem_uword(0x1008,0x1c400200);//LOADII R2 = 512	N
//	write_mem_uword(0x1008,0x1c400003);//LOADII R2 = 3	N
	write_mem_uword(0x100c,0x1c601108);//A->R3



	write_mem_uword(0x1010,0x00610802);//sum = sum + A[i];
	write_mem_uword(0x1014,0x04200008);//i+8
	write_mem_uword(0x1018,0x10220000);//bre
	write_mem_uword(0x101c,0x14200008);//store sum->mem[8]; 
	write_mem_uword(0x1020,0x28000000);
	Execution();
	printf("%f\n",get_double(1));
	printf("%f\n",read_mem_double(8));
	
	
	
	
	
	
/*	uch1 ='1';
	cha1 = 'a';
	uns1 = 123;
	sho1 = -123;
	in1 = -1234567;
	uni1 = 1234567;
	fl1 = 123.6;
	dou1 = 123.456789;
	write_mem_ubyte(0,uch1);
	uch2 = read_mem_ubyte (0);

	write_mem_byte(10,cha1);
	cha2 = read_mem_byte (10);

	write_mem_uhalfword (20,uns1);
	uns2 = read_mem_uhalfword (20);

	write_mem_halfword (30, sho1);
	sho2 = read_mem_halfword(30);
	
	write_mem_uword (40,uni1);
	uni2 = read_mem_uword(40);
	
	write_mem_word(50,in1);
	in2 = read_mem_word (50);
	
	write_mem_float(70,fl1);
	fl2 = read_mem_float(70);
	
	write_mem_double (70,dou1);
	dou2 = read_mem_double (70);
	
	printf("uchar:%c\n",uch2);
	printf("char:%c\n",cha2);
	printf("uword:%d\n",uni2);
	printf("float:%f\n",fl2);
	printf("double:%f\n",dou2);
	

	printf("\n\n\n\n\n");

	put_int(1,in2);
	printf("int:%d\n",get_int(1));
	put_uint(2,uni2);

	printf("unsigned short:%d\n",get_ushor(3));
	put_flo(4,fl2);
	printf("float:%f\n",get_flo(4));
	put_shor(5,sho2);
	printf("short:%d\n",get_shor(5));
	put_ushor(6,uns2);
	printf("unsigned short:%d\n",get_ushor(6));
	put_char(7,cha2);
	printf("char:%c\n",get_char(7));*/

	
	
	

	free (mem);
	free (r);

return 0;
}

#endif
/*wdwdwddas
 * das
 * dasdasdas
 * dasd
 * asdas
 * da
 * dsadadasda
 * */
