

#ifndef UTILS_H_
#define UTILS_H_

#define READ_BIT(reg,bit_num)    ((reg>>bit_num)&1)
#define SET_BIT(reg,bit_num)     reg=(reg|(1<<bit_num))
#define CLR_BIT(reg,bit_num)     reg=(reg&(~(1<<bit_num)))
#define TOGGLE_BIT(reg,bit_num)  reg=(reg^(1<<bit_num))



#endif /* UTILS_H_ */