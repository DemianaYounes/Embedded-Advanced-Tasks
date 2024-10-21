


#ifndef WDT_INTERFACE_H_
#define WDT_INTERFACE_H_

typedef enum{
	TimeOut_16ms=0,
	TimeOut_32ms,
	TimeOut_65ms,
	TimeOut_130ms,
	TimeOut_260ms,
	TimeOut_520ms,
	TimeOut_1000ms,
	TimeOut_2100ms
	}TimeOut_t;

void WDT_Set(TimeOut_t time);
void WDT_Stop(void);




#endif /* WDT_INTERFACE_H_ */