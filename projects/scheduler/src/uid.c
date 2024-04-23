
#include <string.h> /*memcpy*/
#include <ifaddrs.h> /*getifaddrs*/
#include <netinet/in.h> /*inet_ntoa*/
#include <arpa/inet.h> /*inet_ntoa*/
#include "uid.h"

static size_t static_counter = 1;

my_uid_t UIDCreate(void)

{
	my_uid_t uid = {0};
	
	struct ifaddrs *ifap = NULL;
	struct ifaddrs *ifa = NULL;
	void *addr = NULL;
	char addressBuffer[14] = {0};
	
	getifaddrs(&ifap);
	
	for (ifa = ifap; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (!ifa->ifa_addr) 
        {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) 
        {
            addr = &((struct sockaddr_in*)ifa->ifa_addr)->sin_addr;
            
            inet_ntop(AF_INET, addr, addressBuffer, LINUX_IP_SIZE);
            if (strcmp(ifa->ifa_name, "lo") != 0) 
            { 
                memcpy(uid.ip, addressBuffer,LINUX_IP_SIZE);
            }
        }
    }
    
	if (NULL == ifap)
	{
		return UIDGetBad();
	}
	
	uid.time_stamp = time(NULL);
	uid.pid = getpid();
	uid.counter = static_counter;
	++static_counter;	
	
	freeifaddrs(ifap);
	return uid;
}

my_uid_t UIDGetBad(void)
{
	my_uid_t uid_bad = {0};
	return uid_bad;	
}

int UIDIsSame(my_uid_t lhs, my_uid_t rhs)
{
	int status = 0;
	/*comper time stemps use function from time library*/
	if (lhs.time_stamp == rhs.time_stamp && lhs.counter == rhs.counter && lhs.pid == rhs.pid && 0 == memcmp(lhs.ip, rhs.ip, LINUX_IP_SIZE))
	{
		status = 1;
	}
	
	return status;
}
