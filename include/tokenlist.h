//
// Created by natha on 6/30/2023.
//

#ifndef IC10_INTERPRETER_TOKENLIST_H
#define IC10_INTERPRETER_TOKENLIST_H
enum type{
    UNOP,
    BINOP,
    TRIOP,
    QUADOP,
    QUINOP,
    SEXOP,
    CMD,
    LABEL,
    TNULL
};
enum TT_token {
    TT_NEWLINE,
    TT_CMD,
    TT_DPARA,
    TT_HASH,
    TT_BINOP,
    TT_SHIFT,
    TT_BITOP,
    TT_SELECT,
    TT_MOVE,
    TT_JUMP,
    TT_DEVICE,
    TT_DEVICE_CON,
    TT_RJUMP,
    TT_NUM,
    TT_STRING,
    TT_LABEL,
    TT_REG,
    TT_DEFINE,
    TT_ALIAS,
    TT_MATH,
    TT_SET,
    TT_LOAD,
    TT_SPARA,
    TT_STACK,
    TT_WAIT,
    TT_LOL,
    TT_MISC
};
enum Commands{
    ABS,
    ACOS,
    ADD,
    AND,
    ASIN,
    ATAN,
    ATAN2,
    BAP,
    BAPAL,
    BAPZ,
    BAPZAL,
    BDNS,
    BDNSAL,
    BDSE,
    BDSEAL,
    BEQ,
    BEQAL,
    BEQZ,
    BEQZAL,
    BGE,
    BGEAL,
    BGEZ,
    BGEZAL,
    BGT,
    BGTAL,
    BGTZ,
    BGTZAL,
    BLE,
    BLEAL,
    BLEZ,
    BLEZAL,
    BLT,
    BLTAL,
    BLTZ,
    BLTZAL,
    BNA,
    BNAAL,
    BNAN,
    BNAZ,
    BNAZAL,
    BNE,
    BNEAL,
    BNEZ,
    BNEZAL,
    BRAP,
    BRAPZ,
    BRDNS,
    BRDSE,
    BREQ,
    BREQZ,
    BRGE,
    BRGEZ,
    BRGT,
    BRGTZ,
    BRLE,
    BRLEZ,
    BRLT,
    BRLTZ,
    BRNA,
    BRNAN,
    BRNAZ,
    BRNE,
    BRNEZ,
    CEIL,
    COS,
    DIV,
    EXP,
    FLOOR,
    J,
    JAL,
    JR,
    L,
    LB,
    LBN,
    LBNS,
    LBS,
    LOG,
    LR,
    LS,
    MAX,
    MIN,
    MOD,
    MOVE,
    MUL,
    NOR,
    NOT,
    OR,
    PEEK,
    POP,
    PUSH,
    RAND,
    ROUND,
    S,
    SAP,
    SAPZ,
    SB,
    SBN,
    SBS,
    SDNS,
    SDSE,
    SELECT,
    SEQ,
    SEQZ,
    SGE,
    SGEZ,
    SGT,
    SGTZ,
    SIN,
    SLA,
    SLE,
    SLEEP,
    SLEZ,
    SLL,
    SLT,
    SLTZ,
    SNA,
    SNAN,
    SNANZ,
    SNAZ,
    SNE,
    SNEZ,
    SQRT,
    SRA,
    SRL,
    SS,
    SUB,
    TAN,
    TRUNC,
    XOR,
    CNULL

};
struct commandToken{
    char *str;
    enum TT_token tokentype;
    enum type OP_type;
    enum Commands command;
};
static struct commandToken commandList[]={
        {"abs",TT_CMD,UNOP,ABS},
        {"acos",TT_CMD,UNOP,ACOS},
        {"add",TT_CMD,BINOP,ADD},
        {"alias",TT_ALIAS,UNOP,CNULL},
        {"and",TT_CMD,BINOP,AND},
        {"asin",TT_CMD,UNOP,ASIN},
        {"atan",TT_CMD,UNOP,ATAN},
        {"atan2",TT_CMD,BINOP,ATAN2},
        {"bap",TT_CMD,TRIOP,BAP},
        {"bapal",TT_CMD,TRIOP,BAPAL},
        {"bapz",TT_CMD,BINOP,BAPZ},
        {"bapzal",TT_CMD,BINOP,BAPZAL},
        {"bdns",TT_CMD,UNOP,BDNS},
        {"bdnsal",TT_CMD,UNOP,BDNSAL},
        {"bdse",TT_CMD,UNOP,BDSE},
        {"bdseal",TT_CMD,UNOP,BDSEAL},
        {"beq",TT_CMD,BINOP,BEQ},
        {"beqal",TT_CMD,BINOP,BEQAL},
        {"beqz",TT_CMD,UNOP,BEQZ},
        {"beqzal",TT_CMD,UNOP,BEQZAL},
        {"bge",TT_CMD,BINOP,BGE},
        {"bgeal",TT_CMD,BINOP,BGEAL},
        {"bgez",TT_CMD,UNOP,BGEZ},
        {"bgezal",TT_CMD,UNOP,BGEZAL},
        {"bgt",TT_CMD,BINOP,BGT},
        {"bgtal",TT_CMD,BINOP,BGTAL},
        {"bgtz",TT_CMD,UNOP,BGTZ},
        {"bgtzal",TT_CMD,UNOP,BGTZAL},
        {"ble",TT_CMD,BINOP,BLE},
        {"bleal",TT_CMD,BINOP,BLEAL},
        {"blez",TT_CMD,UNOP,BLEZ},
        {"blezal",TT_CMD,UNOP,BLEZAL},
        {"blt",TT_CMD,BINOP,BLT},
        {"bltal",TT_CMD,BINOP,BLTAL},
        {"bltz",TT_CMD,UNOP,BLTZ},
        {"bltzal",TT_CMD,UNOP,BLTZAL},
        {"bna",TT_CMD,TRIOP,BNA},
        {"bnaal",TT_CMD,TRIOP,BNAAL},
        {"bnan",TT_CMD,UNOP,BNAN},
        {"bnaz",TT_CMD,BINOP,BNAZ},
        {"bnazal",TT_CMD,BINOP,BNAZAL},
        {"bne",TT_CMD,BINOP,BNE},
        {"bneal",TT_CMD,BINOP,BNEAL},
        {"bnez",TT_CMD,UNOP,BNEZ},
        {"bnezal",TT_CMD,UNOP,BNEZAL},
        {"brap",TT_CMD,TRIOP,BRAP},
        {"brapz",TT_CMD,BINOP,BRAPZ},
        {"brdns",TT_CMD,UNOP,BRDNS},
        {"brdse",TT_CMD,UNOP,BRDSE},
        {"breq",TT_CMD,BINOP,BREQ},
        {"breqz",TT_CMD,UNOP,BREQZ},
        {"brge",TT_CMD,BINOP,BRGE},
        {"brgez",TT_CMD,UNOP,BRGEZ},
        {"brgt",TT_CMD,BINOP,BRGT},
        {"brgtz",TT_CMD,UNOP,BRGTZ},
        {"brle",TT_CMD,BINOP,BRLE},
        {"brlez",TT_CMD,UNOP,BRLEZ},
        {"brlt",TT_CMD,BINOP,BRLT},
        {"brltz",TT_CMD,UNOP,BRLTZ},
        {"brna",TT_CMD,TRIOP,BRNA},
        {"brnan",TT_CMD,UNOP,BRNAN},
        {"brnaz",TT_CMD,BINOP,BRNAZ},
        {"brne",TT_CMD,BINOP,BRNE},
        {"brnez",TT_CMD,UNOP,BRNEZ},
        {"ceil",TT_CMD,UNOP,CEIL},
        {"cos",TT_CMD,UNOP,COS},
        {"define",TT_DEFINE,UNOP,CNULL},
        {"div",TT_CMD,BINOP,DIV},
        {"exp",TT_CMD,UNOP,EXP},
        {"floor",TT_CMD,UNOP,FLOOR},
        {"hcf",TT_LOL,TNULL,CNULL},
        {"j",TT_CMD,CMD,J},
        {"jal",TT_CMD,CMD,JAL},
        {"jr",TT_CMD,CMD,JR},
        {"l",TT_CMD,BINOP,L},
        {"lb",TT_CMD,TRIOP,LB},
        {"lbn",TT_CMD,QUADOP,LBN},
        {"lbns",TT_CMD,QUINOP,LBNS},
        {"lbs",TT_CMD,QUADOP,LBS},
        {"log",TT_CMD,BINOP,LOG},
        {"lr",TT_CMD,TRIOP,LR},
        {"ls",TT_CMD,TRIOP,LS},
        {"max",TT_CMD,BINOP,MAX},
        {"min",TT_CMD,BINOP,MIN},
        {"mod",TT_CMD,BINOP,MOD},
        {"move",TT_CMD,UNOP,MOVE},
        {"mul",TT_CMD,BINOP,MUL},
        {"nor",TT_CMD,BINOP,NOR},
        {"not",TT_CMD,UNOP,NOT},
        {"or",TT_CMD,BINOP,OR},
        {"peek",TT_CMD,CMD,PEEK},
        {"pop",TT_CMD,CMD,POP},
        {"push",TT_CMD,CMD,PUSH},
        {"rand",TT_CMD,CMD,RAND},
        {"round",TT_CMD,UNOP,ROUND},
        {"s",TT_CMD,BINOP,S},
        {"sap",TT_CMD,TRIOP,SAP},
        {"sapz",TT_CMD,BINOP,SAPZ},
        {"sb",TT_CMD,BINOP,SB},
        {"sbn",TT_CMD,TRIOP,SBN},
        {"sbs",TT_CMD,TRIOP,SBS},
        {"sdns",TT_CMD,UNOP,SDNS},
        {"sdse",TT_CMD,UNOP,SDSE},
        {"select",TT_CMD,TRIOP,SELECT},
        {"seq",TT_CMD,BINOP,SEQ},
        {"seqz",TT_CMD,UNOP,SEQZ},
        {"sge",TT_CMD,BINOP,SGE},
        {"sgez",TT_CMD,UNOP,SGEZ},
        {"sgt",TT_CMD,BINOP,SGT},
        {"sgtz",TT_CMD,UNOP,SGTZ},
        {"sin",TT_CMD,UNOP,SIN},
        {"sla",TT_CMD,BINOP,SLA},
        {"sle",TT_CMD,BINOP,SLE},
        {"sleep",TT_CMD,CMD,SLEEP},
        {"slez",TT_CMD,UNOP,SLEZ},
        {"sll",TT_CMD,BINOP,SLL},
        {"slt",TT_CMD,BINOP,SLT},
        {"sltz",TT_CMD,UNOP,SLTZ},
        {"sna",TT_CMD,TRIOP,SNA},
        {"snan",TT_CMD,UNOP,SNAN},
        {"snanz",TT_CMD,UNOP,SNANZ},
        {"snaz",TT_CMD,BINOP,SNAZ},
        {"sne",TT_CMD,BINOP,SNE},
        {"snez",TT_CMD,UNOP,SNEZ},
        {"sqrt",TT_CMD,UNOP,SQRT},
        {"sra",TT_CMD,BINOP,SRA},
        {"srl",TT_CMD,BINOP,SRL},
        {"ss",TT_CMD,TRIOP,SS},
        {"sub",TT_CMD,BINOP,SUB},
        {"tan",TT_CMD,UNOP,TAN},
        {"trunc",TT_CMD,UNOP,TRUNC},
        {"xor",TT_CMD,BINOP,XOR},
        {"yield",TT_WAIT,TNULL,CNULL},
        {"r0",TT_REG,TNULL,CNULL},
        {"r1",TT_REG,TNULL,CNULL},
        {"r2",TT_REG,TNULL,CNULL},
        {"r3",TT_REG,TNULL,CNULL},
        {"r4",TT_REG,TNULL,CNULL},
        {"r5",TT_REG,TNULL,CNULL},
        {"r6",TT_REG,TNULL,CNULL},
        {"r7",TT_REG,TNULL,CNULL},
        {"r8",TT_REG,TNULL,CNULL},
        {"r9",TT_REG,TNULL,CNULL},
        {"r10",TT_REG,TNULL,CNULL},
        {"r11",TT_REG,TNULL,CNULL},
        {"r12",TT_REG,TNULL,CNULL},
        {"r13",TT_REG,TNULL,CNULL},
        {"r14",TT_REG,TNULL,CNULL},
        {"r15",TT_REG,TNULL,CNULL},
        {"r16",TT_REG,TNULL,CNULL},
        {"r17",TT_REG,TNULL,CNULL},
        {"db",TT_DEVICE,TNULL,CNULL},
        {"d0",TT_DEVICE,TNULL,CNULL},
        {"d1",TT_DEVICE,TNULL,CNULL},
        {"d2",TT_DEVICE,TNULL,CNULL},
        {"d3",TT_DEVICE,TNULL,CNULL},
        {"d4",TT_DEVICE,TNULL,CNULL},
        {"d5",TT_DEVICE,TNULL,CNULL},
        {"occupied",TT_SPARA,TNULL,CNULL},
        {"occupanthash",TT_SPARA,TNULL,CNULL},
        {"quantity",TT_SPARA,TNULL,CNULL},
        {"damage",TT_SPARA,TNULL,CNULL},
        {"efficiency",TT_SPARA,TNULL,CNULL},
        {"health",TT_SPARA,TNULL,CNULL},
        {"growth",TT_SPARA,TNULL,CNULL},
        {"pressure",TT_SPARA,TNULL,CNULL},
        {"temperature",TT_SPARA,TNULL,CNULL},
        {"charge",TT_SPARA,TNULL,CNULL},
        {"chargeratio",TT_SPARA,TNULL,CNULL},
        {"class",TT_SPARA,TNULL,CNULL},
        {"pressurewaste",TT_SPARA,TNULL,CNULL},
        {"pressureair",TT_SPARA,TNULL,CNULL},
        {"maxquantity",TT_SPARA,TNULL,CNULL},
        {"mature",TT_SPARA,TNULL,CNULL},
        {"prefabhash",TT_SPARA,TNULL,CNULL},
        {"seeding",TT_SPARA,TNULL,CNULL},
        {"linenumber",TT_SPARA,TNULL,CNULL},
        {"volume",TT_SPARA,TNULL,CNULL},
        {"open",TT_SPARA,TNULL,CNULL},
        {"on",TT_SPARA,TNULL,CNULL},
        {"lock",TT_SPARA,TNULL,CNULL},
        {"sortingclass",TT_SPARA,TNULL,CNULL},
        {"filtertype",TT_SPARA,TNULL,CNULL},
        {"power",TT_DPARA,TNULL,CNULL},
        {"open",TT_DPARA,TNULL,CNULL},
        {"mode",TT_DPARA,TNULL,CNULL},
        {"error",TT_DPARA,TNULL,CNULL},
        {"lock",TT_DPARA,TNULL,CNULL},
        {"pressure",TT_DPARA,TNULL,CNULL},
        {"temperature",TT_DPARA,TNULL,CNULL},
        {"pressureexternal",TT_DPARA,TNULL,CNULL},
        {"pressureinternal",TT_DPARA,TNULL,CNULL},
        {"activate",TT_DPARA,TNULL,CNULL},
        {"charge",TT_DPARA,TNULL,CNULL},
        {"setting",TT_DPARA,TNULL,CNULL},
        {"reagents",TT_DPARA,TNULL,CNULL},
        {"ratiooxygen",TT_DPARA,TNULL,CNULL},
        {"ratiocarbondioxide",TT_DPARA,TNULL,CNULL},
        {"rationitrogen",TT_DPARA,TNULL,CNULL},
        {"ratiopollutant",TT_DPARA,TNULL,CNULL},
        {"ratiovolatiles",TT_DPARA,TNULL,CNULL},
        {"ratiowater",TT_DPARA,TNULL,CNULL},
        {"horizontal",TT_DPARA,TNULL,CNULL},
        {"vertical",TT_DPARA,TNULL,CNULL},
        {"solarangle",TT_DPARA,TNULL,CNULL},
        {"maximum",TT_DPARA,TNULL,CNULL},
        {"ratio",TT_DPARA,TNULL,CNULL},
        {"powerpotential",TT_DPARA,TNULL,CNULL},
        {"poweractual",TT_DPARA,TNULL,CNULL},
        {"quantity",TT_DPARA,TNULL,CNULL},
        {"on",TT_DPARA,TNULL,CNULL},
        {"importquantity",TT_DPARA,TNULL,CNULL},
        {"importslotoccupant",TT_DPARA,TNULL,CNULL},
        {"exportquantity",TT_DPARA,TNULL,CNULL},
        {"exportslotoccupant",TT_DPARA,TNULL,CNULL},
        {"requiredpower",TT_DPARA,TNULL,CNULL},
        {"horizontalratio",TT_DPARA,TNULL,CNULL},
        {"verticalratio",TT_DPARA,TNULL,CNULL},
        {"powerrequired",TT_DPARA,TNULL,CNULL},
        {"idle",TT_DPARA,TNULL,CNULL},
        {"color",TT_DPARA,TNULL,CNULL},
        {"elevatorspeed",TT_DPARA,TNULL,CNULL},
        {"elevatorlevel",TT_DPARA,TNULL,CNULL},
        {"recipehash",TT_DPARA,TNULL,CNULL},
        {"exportslothash",TT_DPARA,TNULL,CNULL},
        {"importslothash",TT_DPARA,TNULL,CNULL},
        {"planthealth1",TT_DPARA,TNULL,CNULL},
        {"planthealth2",TT_DPARA,TNULL,CNULL},
        {"planthealth3",TT_DPARA,TNULL,CNULL},
        {"planthealth4",TT_DPARA,TNULL,CNULL},
        {"plantgrowth1",TT_DPARA,TNULL,CNULL},
        {"plantgrowth2",TT_DPARA,TNULL,CNULL},
        {"plantgrowth3",TT_DPARA,TNULL,CNULL},
        {"plantgrowth4",TT_DPARA,TNULL,CNULL},
        {"plantefficiency1",TT_DPARA,TNULL,CNULL},
        {"plantefficiency2",TT_DPARA,TNULL,CNULL},
        {"plantefficiency3",TT_DPARA,TNULL,CNULL},
        {"plantefficiency4",TT_DPARA,TNULL,CNULL},
        {"planthash1",TT_DPARA,TNULL,CNULL},
        {"planthash2",TT_DPARA,TNULL,CNULL},
        {"planthash3",TT_DPARA,TNULL,CNULL},
        {"planthash4",TT_DPARA,TNULL,CNULL},
        {"requesthash",TT_DPARA,TNULL,CNULL},
        {"completionratio",TT_DPARA,TNULL,CNULL},
        {"clearmemory",TT_DPARA,TNULL,CNULL},
        {"exportcount",TT_DPARA,TNULL,CNULL},
        {"importcount",TT_DPARA,TNULL,CNULL},
        {"powergeneration",TT_DPARA,TNULL,CNULL},
        {"totalmoles",TT_DPARA,TNULL,CNULL},
        {"volume",TT_DPARA,TNULL,CNULL},
        {"plant",TT_DPARA,TNULL,CNULL},
        {"harvest",TT_DPARA,TNULL,CNULL},
        {"output",TT_DPARA,TNULL,CNULL},
        {"pressuresetting",TT_DPARA,TNULL,CNULL},
        {"temperaturesetting",TT_DPARA,TNULL,CNULL},
        {"temperatureexternal",TT_DPARA,TNULL,CNULL},
        {"filtration",TT_DPARA,TNULL,CNULL},
        {"airrelease",TT_DPARA,TNULL,CNULL},
        {"positionx",TT_DPARA,TNULL,CNULL},
        {"positiony",TT_DPARA,TNULL,CNULL},
        {"positionz",TT_DPARA,TNULL,CNULL},
        {"velocitymagnitude",TT_DPARA,TNULL,CNULL},
        {"velocityrelativex",TT_DPARA,TNULL,CNULL},
        {"velocityrelativey",TT_DPARA,TNULL,CNULL},
        {"velocityrelativez",TT_DPARA,TNULL,CNULL},
        {"rationitrousoxide",TT_DPARA,TNULL,CNULL},
        {"prefabhash",TT_DPARA,TNULL,CNULL},
        {"forcewrite",TT_DPARA,TNULL,CNULL},
        {"signalstrength",TT_DPARA,TNULL,CNULL},
        {"signalid",TT_DPARA,TNULL,CNULL},
        {"targetx",TT_DPARA,TNULL,CNULL},
        {"targety",TT_DPARA,TNULL,CNULL},
        {"targetz",TT_DPARA,TNULL,CNULL},
        {"settinginput",TT_DPARA,TNULL,CNULL},
        {"settingoutput",TT_DPARA,TNULL,CNULL},
        {"currentresearchpodtype",TT_DPARA,TNULL,CNULL},
        {"manualresearchrequiredpod",TT_DPARA,TNULL,CNULL},
        {"mineablesinvicinity",TT_DPARA,TNULL,CNULL},
        {"mineablesinqueue",TT_DPARA,TNULL,CNULL},
        {"nextweathereventtime",TT_DPARA,TNULL,CNULL},
        {"combustion",TT_DPARA,TNULL,CNULL},
        {"fuel",TT_DPARA,TNULL,CNULL},
        {"returnfuelcost",TT_DPARA,TNULL,CNULL},
        {"collectablegoods",TT_DPARA,TNULL,CNULL},
        {"time",TT_DPARA,TNULL,CNULL},
        {"bpm",TT_DPARA,TNULL,CNULL},
        {"environmentefficiency",TT_DPARA,TNULL,CNULL},
        {"workinggasefficiency",TT_DPARA,TNULL,CNULL},
        {"pressureinput",TT_DPARA,TNULL,CNULL},
        {"temperatureinput",TT_DPARA,TNULL,CNULL},
        {"ratiooxygeninput",TT_DPARA,TNULL,CNULL},
        {"ratiocarbondioxideinput",TT_DPARA,TNULL,CNULL},
        {"rationitrogeninput",TT_DPARA,TNULL,CNULL},
        {"ratiopollutantinput",TT_DPARA,TNULL,CNULL},
        {"ratiovolatilesinput",TT_DPARA,TNULL,CNULL},
        {"ratiowaterinput",TT_DPARA,TNULL,CNULL},
        {"rationitrousoxideinput",TT_DPARA,TNULL,CNULL},
        {"totalmolesinput",TT_DPARA,TNULL,CNULL},
        {"pressureinput2",TT_DPARA,TNULL,CNULL},
        {"temperatureinput2",TT_DPARA,TNULL,CNULL},
        {"ratiooxygeninput2",TT_DPARA,TNULL,CNULL},
        {"ratiocarbondioxideinput2",TT_DPARA,TNULL,CNULL},
        {"rationitrogeninput2",TT_DPARA,TNULL,CNULL},
        {"ratiopollutantinput2",TT_DPARA,TNULL,CNULL},
        {"ratiovolatilesinput2",TT_DPARA,TNULL,CNULL},
        {"ratiowaterinput2",TT_DPARA,TNULL,CNULL},
        {"rationitrousoxideinput2",TT_DPARA,TNULL,CNULL},
        {"totalmolesinput2",TT_DPARA,TNULL,CNULL},
        {"pressureoutput",TT_DPARA,TNULL,CNULL},
        {"temperatureoutput",TT_DPARA,TNULL,CNULL},
        {"ratiooxygenoutput",TT_DPARA,TNULL,CNULL},
        {"ratiocarbondioxideoutput",TT_DPARA,TNULL,CNULL},
        {"rationitrogenoutput",TT_DPARA,TNULL,CNULL},
        {"ratiopollutantoutput",TT_DPARA,TNULL,CNULL},
        {"ratiovolatilesoutput",TT_DPARA,TNULL,CNULL},
        {"ratiowateroutput",TT_DPARA,TNULL,CNULL},
        {"rationitrousoxideoutput",TT_DPARA,TNULL,CNULL},
        {"totalmolesoutput",TT_DPARA,TNULL,CNULL},
        {"pressureoutput2",TT_DPARA,TNULL,CNULL},
        {"temperatureoutput2",TT_DPARA,TNULL,CNULL},
        {"ratiooxygenoutput2",TT_DPARA,TNULL,CNULL},
        {"ratiocarbondioxideoutput2",TT_DPARA,TNULL,CNULL},
        {"rationitrogenoutput2",TT_DPARA,TNULL,CNULL},
        {"ratiopollutantoutput2",TT_DPARA,TNULL,CNULL},
        {"ratiovolatilesoutput2",TT_DPARA,TNULL,CNULL},
        {"ratiowateroutput2",TT_DPARA,TNULL,CNULL},
        {"rationitrousoxideoutput2",TT_DPARA,TNULL,CNULL},
        {"totalmolesoutput2",TT_DPARA,TNULL,CNULL},
        {"combustioninput",TT_DPARA,TNULL,CNULL},
        {"combustioninput2",TT_DPARA,TNULL,CNULL},
        {"combustionoutput",TT_DPARA,TNULL,CNULL},
        {"combustionoutput2",TT_DPARA,TNULL,CNULL},
        {"operationaltemperatureefficiency",TT_DPARA,TNULL,CNULL},
        {"temperaturedifferentialefficiency",TT_DPARA,TNULL,CNULL},
        {"pressureefficiency",TT_DPARA,TNULL,CNULL},
        {"combustionlimiter",TT_DPARA,TNULL,CNULL},
        {"throttle",TT_DPARA,TNULL,CNULL},
        {"rpm",TT_DPARA,TNULL,CNULL},
        {"stress",TT_DPARA,TNULL,CNULL},
        {"interrogationprogress",TT_DPARA,TNULL,CNULL},
        {"targetpadindex",TT_DPARA,TNULL,CNULL},
        {"sizex",TT_DPARA,TNULL,CNULL},
        {"sizey",TT_DPARA,TNULL,CNULL},
        {"sizez",TT_DPARA,TNULL,CNULL},
        {"minimumwattstocontact",TT_DPARA,TNULL,CNULL},
        {"wattsreachingcontact",TT_DPARA,TNULL,CNULL},
        {"channel0",TT_DPARA,TNULL,CNULL},
        {"channel1",TT_DPARA,TNULL,CNULL},
        {"channel2",TT_DPARA,TNULL,CNULL},
        {"channel3",TT_DPARA,TNULL,CNULL},
        {"channel4",TT_DPARA,TNULL,CNULL},
        {"channel5",TT_DPARA,TNULL,CNULL},
        {"channel6",TT_DPARA,TNULL,CNULL},
        {"channel7",TT_DPARA,TNULL,CNULL},
        {"linenumber",TT_DPARA,TNULL,CNULL},
        {"flush",TT_DPARA,TNULL,CNULL},
        {"soundalert",TT_DPARA,TNULL,CNULL},
        {"solarirradiance",TT_DPARA,TNULL,CNULL},
        {"ratioliquidnitrogen",TT_DPARA,TNULL,CNULL},
        {"ratioliquidnitrogeninput",TT_DPARA,TNULL,CNULL},
        {"ratioliquidnitrogeninput2",TT_DPARA,TNULL,CNULL},
        {"ratioliquidnitrogenoutput",TT_DPARA,TNULL,CNULL},
        {"ratioliquidnitrogenoutput2",TT_DPARA,TNULL,CNULL},
        {"volumeofliquid",TT_DPARA,TNULL,CNULL},
        {"ratioliquidoxygen",TT_DPARA,TNULL,CNULL},
        {"ratioliquidoxygeninput",TT_DPARA,TNULL,CNULL},
        {"ratioliquidoxygeninput2",TT_DPARA,TNULL,CNULL},
        {"ratioliquidoxygenoutput",TT_DPARA,TNULL,CNULL},
        {"ratioliquidoxygenoutput2",TT_DPARA,TNULL,CNULL},
        {"ratioliquidvolatiles",TT_DPARA,TNULL,CNULL},
        {"ratioliquidvolatilesinput",TT_DPARA,TNULL,CNULL},
        {"ratioliquidvolatilesinput2",TT_DPARA,TNULL,CNULL},
        {"ratioliquidvolatilesoutput",TT_DPARA,TNULL,CNULL},
        {"ratioliquidvolatilesoutput2",TT_DPARA,TNULL,CNULL},
        {"ratiosteam",TT_DPARA,TNULL,CNULL},
        {"ratiosteaminput",TT_DPARA,TNULL,CNULL},
        {"ratiosteaminput2",TT_DPARA,TNULL,CNULL},
        {"ratiosteamoutput",TT_DPARA,TNULL,CNULL},
        {"ratiosteamoutput2",TT_DPARA,TNULL,CNULL},
        {"contacttypeid",TT_DPARA,TNULL,CNULL},
        {"ratioliquidcarbondioxide",TT_DPARA,TNULL,CNULL},
        {"ratioliquidcarbondioxideinput",TT_DPARA,TNULL,CNULL},
        {"ratioliquidcarbondioxideinput2",TT_DPARA,TNULL,CNULL},
        {"ratioliquidcarbondioxideoutput",TT_DPARA,TNULL,CNULL},
        {"ratioliquidcarbondioxideoutput2",TT_DPARA,TNULL,CNULL},
        {"ratioliquidpollutant",TT_DPARA,TNULL,CNULL},
        {"ratioliquidpollutantinput",TT_DPARA,TNULL,CNULL},
        {"ratioliquidpollutantinput2",TT_DPARA,TNULL,CNULL},
        {"ratioliquidpollutantoutput",TT_DPARA,TNULL,CNULL},
        {"ratioliquidpollutantoutput2",TT_DPARA,TNULL,CNULL},
        {"ratioliquidnitrousoxide",TT_DPARA,TNULL,CNULL},
        {"ratioliquidnitrousoxideinput",TT_DPARA,TNULL,CNULL},
        {"ratioliquidnitrousoxideinput2",TT_DPARA,TNULL,CNULL},
        {"ratioliquidnitrousoxideoutput",TT_DPARA,TNULL,CNULL},
        {"ratioliquidnitrousoxideoutput2",TT_DPARA,TNULL,CNULL},
        {"average",TT_MISC,TNULL,CNULL},
        {"sum",TT_MISC,TNULL,CNULL},
        {"minimum",TT_MISC,TNULL,CNULL},
        {"maximum",TT_MISC,TNULL,CNULL},
        {"contents",TT_MISC,TNULL,CNULL},
        {"required",TT_MISC,TNULL,CNULL},
        {"recipe",TT_MISC,TNULL,CNULL}
};
#endif //IC10_INTERPRETER_TOKENLIST_H
