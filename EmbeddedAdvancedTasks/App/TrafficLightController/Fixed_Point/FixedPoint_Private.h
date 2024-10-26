/*
 * FixedPoint_Private.h
 *
 * Created: 10/27/2024 12:11:17 AM
 *  Author: Demiana Younes
 */ 


#ifndef FIXEDPOINT_PRIVATE_H_
#define FIXEDPOINT_PRIVATE_H_

#define FP_SHIFT    16
#define FP_SCALE    ((u32)1<<16)



/*Convert an integer number to fixed point*/
#define INTEGER_TO_FIXED_POINT(num)     (num<<FP_SHIFT)
/*Convert Floating point number to fixed point number*/
#define FLOAT_TO_FIXED_POINT(num)       ((FixedPoint)(num*FP_SCALE))
/*Macro to get the integral portion in the upper 16 bits*/
#define FIXED_POINT_INTEGER_PART(num)   (num>>16)  
/*Get the decimal portion in the lower 16 bits*/
#define FIXED_POINT_DECIMAL_PART(num)   (num&0x0000ffff)      

#endif /* FIXEDPOINT_PRIVATE_H_ */