#define NODE_1 0
#define NODE_2 1
#define NODE_3 2
#define NODE_4 3
#define NODE_A 4
#define NODE_B 5
#define NODE_C 6
#define NODE_D 7
#define NODE_END 100
#define NODE_START NODE_1


struct fsm_trans {
    int node; /* current state */
    int yes; /* next state for YES */
    int no; /* next state for NO */
    char message[100]; /* Question text */
};


struct fsm_trans fsmtable[] = {
    /* Node, Yes, No */
    { NODE_1, NODE_2, NODE_3, "You like cow (y/n)" },
    { NODE_2, NODE_A, NODE_4, "You like whale (y/n)" },
    { NODE_3, NODE_4, NODE_C, "You like mouse (y/n)" },
    { NODE_4, NODE_B, NODE_D, "You like rabbit (y/n)" },
    { NODE_A, NODE_END, NODE_END, "You are type A" },
    { NODE_B, NODE_END, NODE_END, "You are type B" },
    { NODE_C, NODE_END, NODE_END, "You are type C" },
    { NODE_D, NODE_END, NODE_END, "You are type D"}
};