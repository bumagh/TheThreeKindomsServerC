#include <lwan/lwan.h>
#include "controller/user_mgr.h"
// #include "controller/msg_mgr.h"
#include "controller/ws_mgr.h"

int main(void)
{
    const struct lwan_url_map default_map[] = {
        {.prefix = "/ws", .handler = LWAN_HANDLER_REF(ws)},
        {.prefix = "/hxsg/api/user_mgr", .handler = LWAN_HANDLER_REF(user_mgr)},
        // {.prefix = "/hxsg/api/msg_mgr", .handler = LWAN_HANDLER_REF(msg_mgr)},
        {.prefix = NULL}};
    struct lwan l;
    lwan_init(&l);
    lwan_set_url_map(&l, default_map);
    lwan_main_loop(&l);
    lwan_shutdown(&l);
    return 0;
}
