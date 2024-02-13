#include <stdio.h> /*printf*/

#include "fsm.h"

static void DrawSuccess(void);
static void DrawFailure(void);
static void TestIsAcceptable(void);

int main(void)
{
	TestIsAcceptable();
	return 0;
}

static void TestIsAcceptable(void)
{
	char *str = "0111010";
	char *str2 = "00";
	char *str3 = "100";
	char *str4 = "01111";
	char *str5 = "0";
	char *str6 = "0101010";
	char *str7 = "0101011";
	
	(IsAcceptable(str)) ? DrawSuccess() : DrawFailure();
	(IsAcceptable(str2)) ? DrawSuccess() : DrawFailure();
	(!IsAcceptable(str3)) ? DrawSuccess() : DrawFailure();
	(!IsAcceptable(str4)) ? DrawSuccess() : DrawFailure();
	(!IsAcceptable(str5)) ? DrawSuccess() : DrawFailure();
	(!IsAcceptable(str5)) ? DrawSuccess() : DrawFailure();
	(IsAcceptable(str6)) ? DrawSuccess() : DrawFailure();
	(!IsAcceptable(str7)) ? DrawSuccess() : DrawFailure();
}

static void DrawSuccess(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;42mSUCCESS\033[0m\n\n");
}

static void DrawFailure(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;41mFailed, You should be ashamed of yourself!\033[0m\n\n");
}



