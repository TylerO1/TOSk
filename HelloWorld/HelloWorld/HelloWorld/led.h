#define sbi(var, mask)   ((var) |= (uint8_t)(1 << mask))  // This are nice functions to let you control 1 pin; Makes High
#define cbi(var, mask)   ((var) &= (uint8_t)~(1 << mask)) // This are nice functions to let you control 1 pin; Makes Low

using namespace std;

class LED
{
	int PIN;
	unsigned char PORT;
	public:
		LED(unsigned char,int);
		void on(void);
		void off(void);	
};
