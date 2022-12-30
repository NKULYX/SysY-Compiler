#include "MachineCode.h"
extern FILE* yyout;

MachineOperand::MachineOperand(int tp, int val)
{
    this->type = tp;
    if(tp == MachineOperand::IMM)
        this->val = val;
    else 
        this->reg_no = val;
}

MachineOperand::MachineOperand(std::string label, bool is_func)
{
    this->type = MachineOperand::LABEL;
    this->label = label;
    is_funct = is_func;
}

bool MachineOperand::operator==(const MachineOperand&a) const
{
    if (this->type != a.type)
        return false;
    if (this->type == IMM)
        return this->val == a.val;
    return this->reg_no == a.reg_no;
}

bool MachineOperand::operator<(const MachineOperand&a) const
{
    if(this->type == a.type)
    {
        if(this->type == IMM)
            return this->val < a.val;
        return this->reg_no < a.reg_no;
    }
    return this->type < a.type;

    if (this->type != a.type)
        return false;
    if (this->type == IMM)
        return this->val == a.val;
    return this->reg_no == a.reg_no;
}

void MachineOperand::PrintReg()
{
    switch (reg_no)
    {
    case 11:
        fprintf(yyout, "fp");
        break;
    case 13:
        fprintf(yyout, "sp");
        break;
    case 14:
        fprintf(yyout, "lr");
        break;
    case 15:
        fprintf(yyout, "pc");
        break;
    default:
        fprintf(yyout, "r%d", reg_no);
        break;
    }
}

void MachineOperand::output() 
{
    /* HINT：print operand
    * Example:
    * immediate num 1 -> print #1;
    * register 1 -> print r1;
    * lable addr_a -> print addr_a; */
    switch (this->type)
    {
    case IMM:
        fprintf(yyout, "#%d", this->val);
        break;
    case VREG:
        fprintf(yyout, "v%d", this->reg_no);
        break;
    case REG:
        PrintReg();
        break;
    case LABEL:
        if (this->label.substr(0, 2) == ".L" || is_funct)
            fprintf(yyout, "%s", this->label.c_str());
        else
            fprintf(yyout, "addr_%s", this->label.c_str());
    default:
        break;
    }
}

void MachineInstruction::PrintCond()
{
    switch (cond)
    {
    case EQ:
        fprintf(yyout, "eq");
        break;
    case NE:
        fprintf(yyout, "ne");
        break;
    case LT:
        fprintf(yyout, "lt");
        break;
    case LE:
        fprintf(yyout, "le");
        break;
    case GT:
        fprintf(yyout, "gt");
        break;
    case GE:
        fprintf(yyout, "ge");
        break;
    default:
        break;
    }
}

BinaryMInstruction::BinaryMInstruction(
    MachineBlock* p, int op, 
    MachineOperand* dst, MachineOperand* src1, MachineOperand* src2, 
    int cond)
{
    this->parent = p;
    this->type = MachineInstruction::BINARY;
    this->op = op;
    this->cond = cond;
    this->def_list.push_back(dst);
    this->use_list.push_back(src1);
    this->use_list.push_back(src2);
    dst->setParent(this);
    src1->setParent(this);
    src2->setParent(this);
}

void BinaryMInstruction::output() 
{
    switch (this->op)
    {
    case BinaryMInstruction::ADD:
        fprintf(yyout, "\tadd ");
        break;
    case BinaryMInstruction::SUB:
        fprintf(yyout, "\tsub ");
        break;
    case BinaryMInstruction::MUL:
        fprintf(yyout, "\tmul ");
        break;
    case BinaryMInstruction::DIV:
        fprintf(yyout, "\tsdiv ");
        break;
    case BinaryMInstruction::AND:
        fprintf(yyout, "\tand ");
        break;
    case BinaryMInstruction::OR:
        fprintf(yyout, "\tor ");
        break;
    default:
        break;
    }
    this->PrintCond();
    this->def_list[0]->output();
    fprintf(yyout, ", ");
    this->use_list[0]->output();
    fprintf(yyout, ", ");
    this->use_list[1]->output();
    fprintf(yyout, "\n");
}

LoadMInstruction::LoadMInstruction(MachineBlock* p,
    MachineOperand* dst, MachineOperand* src1, MachineOperand* src2,
    int cond)
{
    this->parent = p;
    this->type = MachineInstruction::LOAD;
    this->op = -1;
    this->cond = cond;
    this->def_list.push_back(dst);
    this->use_list.push_back(src1);
    if (src2)
        this->use_list.push_back(src2);
    dst->setParent(this);
    src1->setParent(this);
    if (src2)
        src2->setParent(this);
}

void LoadMInstruction::output()
{
    fprintf(yyout, "\tldr ");
    this->def_list[0]->output();
    fprintf(yyout, ", ");

    // Load immediate num, eg: ldr r1, =8
    if(this->use_list[0]->isImm())
    {
        fprintf(yyout, "=%d\n", this->use_list[0]->getVal());
        return;
    }

    // Load address
    if(this->use_list[0]->isReg()||this->use_list[0]->isVReg())
        fprintf(yyout, "[");

    this->use_list[0]->output();
    if( this->use_list.size() > 1 )
    {
        fprintf(yyout, ", ");
        this->use_list[1]->output();
    }

    if(this->use_list[0]->isReg()||this->use_list[0]->isVReg())
        fprintf(yyout, "]");
    fprintf(yyout, "\n");
}

StoreMInstruction::StoreMInstruction(MachineBlock* p,
    MachineOperand* src1, MachineOperand* src2, MachineOperand* src3, 
    int cond)
{
    this->parent = p;
    this->type = MachineInstruction::STORE;
    this->op = -1;
    this->cond = cond;
    this->use_list.push_back(src1);
    this->use_list.push_back(src2);
    if (src3)
        this->use_list.push_back(src3);
    src1->setParent(this);
    src2->setParent(this);
    if (src3)
        src3->setParent(this);
}

void StoreMInstruction::output()
{
    fprintf(yyout, "\tstr ");
    this->use_list[0]->output();
    fprintf(yyout, ", ");

    // Load address
    if(this->use_list[1]->isReg()||this->use_list[1]->isVReg())
        fprintf(yyout, "[");

    this->use_list[1]->output();
    if( this->use_list.size() > 2 )
    {
        fprintf(yyout, ", ");
        this->use_list[2]->output();
    }

    if(this->use_list[1]->isReg()||this->use_list[1]->isVReg())
        fprintf(yyout, "]");
    fprintf(yyout, "\n");
}

MovMInstruction::MovMInstruction(MachineBlock* p, int op, 
    MachineOperand* dst, MachineOperand* src,
    int cond)
{
    this->parent = p;
    this->type = MachineInstruction::MOV;
    this->op = op;
    this->cond = cond;
    this->def_list.push_back(dst);
    this->use_list.push_back(src);
    dst->setParent(this);
    src->setParent(this);
}

void MovMInstruction::output() 
{
    fprintf(yyout, "\tmov");
    PrintCond();
    fprintf(yyout, " ");
    this->def_list[0]->output();
    fprintf(yyout, ", ");
    this->use_list[0]->output();
    fprintf(yyout, "\n");
}

BranchMInstruction::BranchMInstruction(MachineBlock* p, int op, 
    MachineOperand* dst, 
    int cond)
{
    this->parent = p;
    this->type = MachineInstruction::BRANCH;
    this->op = op;
    this->cond = cond;
    this->def_list.push_back(dst);
    dst->setParent(this);
}

void BranchMInstruction::output()
{
    switch(op){
    case B:
        fprintf(yyout, "\tb");
        PrintCond();
        fprintf(yyout, " ");
        break;
    case BL:
        fprintf(yyout, "\tbl ");
        break;
    case BX://弃用
        fprintf(yyout, "\tbx ");
        break;
    }
    this->def_list[0]->output();
    fprintf(yyout, "\n");
}

CmpMInstruction::CmpMInstruction(MachineBlock* p, 
    MachineOperand* src1, MachineOperand* src2, 
    int cond)
{
    this->parent = p;
    this->type = MachineInstruction::CMP;
    this->cond = cond;
    this->use_list.push_back(src1);
    this->use_list.push_back(src2);
    src1->setParent(this);
    src2->setParent(this);
}

void CmpMInstruction::output()
{
    fprintf(yyout, "\tcmp ");
    this->use_list[0]->output();
    fprintf(yyout, ", ");
    this->use_list[1]->output();
    fprintf(yyout, "\n");
}

StackMInstruction::StackMInstruction(MachineBlock* p, int op, 
    std::vector<MachineOperand*> src,
    int cond)
{
    this->parent = p;
    this->type = MachineInstruction::STACK;
    this->op = op;
    this->cond = cond;
    this->use_list = src;
    for(auto reg : use_list){
        reg->setParent(this);
    }
}

void StackMInstruction::output()
{
    switch(op){
    case PUSH:
        fprintf(yyout, "\tpush {");
        break;
    case POP:
        fprintf(yyout, "\tpop {");
        break;
    }
    for(auto reg : use_list){
        reg->output();
    }
    fprintf(yyout, "}\n");
}

MachineFunction::MachineFunction(MachineUnit* p, SymbolEntry* sym_ptr) 
{ 
    this->parent = p; 
    this->sym_ptr = sym_ptr; 
    this->stack_size = 0;
};

std::vector<MachineOperand*> MachineFunction::getSavedRegs() 
{
    std::vector<MachineOperand*> ret;
    for(auto no : saved_regs){
        ret.push_back(new MachineOperand(MachineOperand::REG, no));
    }
    return ret;
};

void MachineBlock::output()
{
    // 如果是一个空块则直接返回
    if(this->inst_list.size() == 0)
        return;
    fprintf(yyout, ".L%d:\n", this->no);
    for(auto iter : inst_list)
        iter->output();
}

void MachineBlock::insertBefore(MachineInstruction* at, MachineInstruction* src)
{
    std::vector<MachineInstruction*>::iterator pos = find(inst_list.begin(), inst_list.end(), at);
    inst_list.insert(pos, src);
}

void MachineBlock::insertAfter(MachineInstruction* at, MachineInstruction* src)
{
    std::vector<MachineInstruction*>::iterator pos = find(inst_list.begin(), inst_list.end(), at);
    ++pos;
    inst_list.insert(pos, src);
}

void MachineFunction::output()
{
    const char *func_name = this->sym_ptr->toStr().c_str() + 1;
    fprintf(yyout, "\t.global %s\n", func_name);
    fprintf(yyout, "\t.type %s , %%function\n", func_name);
    fprintf(yyout, "%s:\n", func_name);
    //3. Save callee saved register
    fprintf(yyout, "\tpush {");
    for(auto reg : getSavedRegs()){
        reg->output();
        fprintf(yyout, ", ");
    }
    //1. Save fp
    fprintf(yyout, "fp, lr}\n");
    //2. fp = sp
    fprintf(yyout, "\tmov fp, sp\n");
    //4. Allocate stack space for local variable
    if(stack_size!=0){
        fprintf(yyout, "\tsub sp, sp, #%d\n", stack_size);
    }
    // Traverse all the block in block_list to print assembly code.
//    for(auto iter : block_list)
//        iter->output();
    std::queue<MachineBlock*> q;
    std::set<MachineBlock*> v;
    q.push(block_list[0]);
    v.insert(block_list[0]);
    while(!q.empty()) {
        MachineBlock* cur = q.front();
        q.pop();
        cur->output();
        for(auto iter : cur->getSuccs()) {
            if(v.find(iter) == v.end()) {
                q.push(iter);
                v.insert(iter);
            }
        }
    }
    // output label .LEND
    fprintf(yyout, ".L%s_END:\n", this->sym_ptr->toStr().erase(0,1).c_str());
    //2. Restore callee saved registers and sp, fp
    if(stack_size!=0){
        fprintf(yyout, "\tadd sp, sp, #%d\n", stack_size);
    }
    //恢复saved registers和fp
    fprintf(yyout, "\tpop {");
    for(auto reg : getSavedRegs()){
        reg->output();
        fprintf(yyout, ", ");
    }
    fprintf(yyout, "fp, lr}\n");
    // 3. Generate bx instruction
    fprintf(yyout, "\tbx lr\n\n");
}

void MachineUnit::PrintGlobalDecl()
{
    // TODO:
    // You need to print global variable/const declarition code;
}

void MachineUnit::output()
{
    // TODO
    /* Hint:
    * 1. You need to print global variable/const declarition code;
    * 2. Traverse all the function in func_list to print assembly code;
    * 3. Don't forget print bridge label at the end of assembly code!! */
    fprintf(yyout, "\t.arch armv8-a\n");
    fprintf(yyout, "\t.arch_extension crc\n");
    fprintf(yyout, "\t.arm\n");
    PrintGlobalDecl();
    for(auto iter : func_list)
        iter->output();
}

ZextMInstruction::ZextMInstruction(MachineBlock *p, MachineOperand *dst, MachineOperand *src, int cond) {
    this->parent = p;
    this->type = MachineInstruction::ZEXT;
    this->cond = cond;
    this->def_list.push_back(dst);
    this->use_list.push_back(src);
    dst->setParent(this);
    src->setParent(this);
}

void ZextMInstruction::output() {
    fprintf(yyout, "\tuxtb ");
    def_list[0]->output();
    fprintf(yyout, ", ");
    use_list[0]->output();
    fprintf(yyout, "\n");
}
