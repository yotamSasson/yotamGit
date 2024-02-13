#include <stdlib.h> /* malloc */
#include <assert.h> /*assert*/
#include <string.h> /*memcpy*/
#include <limits.h> /*CHAR_BIT*/

#include "trie.h"
#include "dhcp.h"

#define BITS_IN_IP (CHAR_BIT * BYTES_IN_IP)
#define HOST_BITS(bits_in_subnet) (BITS_IN_IP - bits_in_subnet)
#define SERVER (0xFFFFFFFE)
#define BROADCAST (0xFFFFFFFF)
#define NETWORK (0x00000000)

struct dhcp
{
    unsigned int net_id;
    unsigned int subnet_mask;
    size_t bits_in_subnet;
    trie_t *trie;
};

/************************ Static Functions ************************/
static void BitsInSubnetToMask(size_t bits_in_subnet, unsigned int *subnet_mask);
static unsigned int ExtractHostId(unsigned char *ip_address, unsigned int subnet_mask);
static unsigned int ExtractNetId( unsigned char *ip_address, unsigned int subnet_mask);
static unsigned int IpToInt(unsigned char *ip_address);
static void IntToIP(unsigned int new_ip, unsigned char *result_ip);
static int CreateInit(dhcp_t *dhcp);

/************************ Functions ************************/
dhcp_t *DHCPCreateDHCP(unsigned char *subnet_ip, size_t bits_in_subnet)
{
    dhcp_t *dhcp = malloc(sizeof(dhcp_t));
    
    assert(NULL != subnet_ip);
    assert(2 < BITS_IN_IP - bits_in_subnet);

    if (NULL == dhcp)
    {
        return NULL;
    }

    BitsInSubnetToMask(bits_in_subnet, &dhcp->subnet_mask);
    dhcp->bits_in_subnet = bits_in_subnet;
    dhcp->net_id = ExtractNetId(subnet_ip, dhcp->subnet_mask);
    dhcp->trie = TrieCreate();
    if (NULL == dhcp->trie)
    {
        free(dhcp);
        return NULL;
    }

    if (SUCCESS != CreateInit(dhcp))
    {
        free(dhcp);
        TrieDestroy(dhcp->trie);
        return NULL;
    }
    return dhcp;
}

void DHCPDestroy(dhcp_t *dhcp)
{
    assert(NULL != dhcp);

    TrieDestroy(dhcp->trie);
    free(dhcp);
}

dhcp_status_t DHCPAllocateIp(dhcp_t *dhcp, unsigned char *requested_ip, unsigned char *result_ip)
{
    unsigned int host_id = 0;
    unsigned int new_host_id = 0;
    unsigned int new_ip = 0;
    int status = 0;

    assert(NULL != dhcp);
    assert(NULL != result_ip);

    host_id = ExtractHostId(requested_ip, dhcp->subnet_mask);

    if (TrieIsFULL(dhcp->trie))
    {
        return FULL;
    }

    status = TrieSearchAndInsert(dhcp->trie,  host_id, &new_host_id, HOST_BITS(dhcp->bits_in_subnet));

    new_ip = dhcp->net_id | new_host_id;

    IntToIP(new_ip, result_ip);

    return SUCCESS == status ? status : DS_FAILURE;
}

dhcp_status_t DHCPFreeIp(dhcp_t *dhcp, unsigned char *ip_to_free)
{   
    unsigned int host_id = 0;
    unsigned int server_mask = (1 << (HOST_BITS(dhcp->bits_in_subnet))) - 2;
    unsigned int broadcast_mask = (1 << (HOST_BITS(dhcp->bits_in_subnet))) - 1;
    unsigned int to_free_net_id = 0;

    assert(NULL != dhcp);
    assert(NULL != ip_to_free);

    host_id = ExtractHostId(ip_to_free, dhcp->subnet_mask);
    to_free_net_id = ExtractNetId(ip_to_free, dhcp->subnet_mask);

    if (SUCCESS == Search(dhcp->trie, host_id, dhcp->bits_in_subnet))
    {
        return DOUBLE_FREE;
    }

    if ((NETWORK == host_id) || (server_mask == host_id) || (broadcast_mask == host_id) || (dhcp->net_id != to_free_net_id))
    {
        return INVALID_FREE;
    }

    return TrieFree(dhcp->trie, host_id, HOST_BITS(dhcp->bits_in_subnet));
}

size_t DHCPCountFree(const dhcp_t *dhcp)
{
    assert(NULL != dhcp);

    return (1 << (BITS_IN_IP - dhcp->bits_in_subnet)) - TrieCount(dhcp->trie);
}

/************************ Static Functions ************************/
static int CreateInit(dhcp_t *dhcp)
{
    unsigned int address = 0;
    int status = 0;

    status += TrieInsert(dhcp->trie, NETWORK, &address, HOST_BITS(dhcp->bits_in_subnet));
    status += TrieInsert(dhcp->trie, SERVER, &address, HOST_BITS(dhcp->bits_in_subnet));
    status += TrieInsert(dhcp->trie, BROADCAST, &address, HOST_BITS(dhcp->bits_in_subnet));
   
    return status;
}

static unsigned int ExtractHostId(unsigned char* ip_address, unsigned int subnet_mask) 
{
    unsigned int ip = IpToInt(ip_address);
    return ip & ~subnet_mask;
}

static unsigned int ExtractNetId(unsigned char* ip_address, unsigned int subnet_mask)
{
    unsigned int ip = IpToInt(ip_address);
    return ip & subnet_mask;
}

static unsigned int IpToInt(unsigned char *ip_address)
{
    unsigned int result = 0;
    unsigned char *p = ip_address;
    size_t i = 0;

    for (i = 0; i < BYTES_IN_IP; ++i)
    {
        result <<= 8;
        result |= *p++;
    }
    return result;
}

static void BitsInSubnetToMask(size_t bits_in_subnet, unsigned int *subnet_mask)
{
    unsigned int mask = 0xFFFFFFFF;
    mask <<= (HOST_BITS(bits_in_subnet));
    *subnet_mask = mask;
}

static void IntToIP(unsigned int new_ip, unsigned char *result_ip)
{
    result_ip[0] = (new_ip >> 24) & 0xFF;
    result_ip[1] = (new_ip >> 16) & 0xFF;
    result_ip[2] = (new_ip >> 8) & 0xFF;
    result_ip[3] = new_ip & 0xFF;
}
