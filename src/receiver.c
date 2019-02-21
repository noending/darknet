#include <stdio.h>
#include <inttypes.h>
#include <lcm/lcm.h>
#include "tpa_obu_lcm_obstacle_v.h"
    
static void my_handler(const lcm_recv_buf_t *rbuf, const char * channel, 
        const tpa_obu_lcm_obstacle_v * msg, void * user)
{
    int i;
    printf("timestamp = %"PRId64"\n", msg->timestamp);
    printf("num of obstacle = %d\n",msg->nums);

    printf("distance:\n");
    for(i =0;  i< msg->nums ; i++)
    {
    printf("%.3fm\n",msg->distance[i]);
    }
    printf("world-x:\n");
    for(i =0; i < msg->nums ; i++)
    {
    printf("%f\n", msg->worldx[i]);
    }
}

int main(int argc, char ** argv)
{
    lcm_t * lcm = lcm_create("udpm://239.255.76.63:17667?ttl=1");
    if(!lcm)
        return 1;

    tpa_obu_lcm_obstacle_v_subscribe(lcm, "obstacle_v", &my_handler, NULL);

    while(1)
    {
        lcm_handle(lcm);
    }

    lcm_destroy(lcm);
    return 0;
}