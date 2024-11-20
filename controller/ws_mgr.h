#ifndef ws_mgr_h
#define ws_mgr_h

#include <stdio.h>
#include <stdlib.h>
#include <lwan/lwan.h>
#include <lwan/lwan-mod-serve-files.h>
#include <lwan/lwan-strbuf.h>
#include <errno.h>
LWAN_HANDLER(ws)
{
    enum lwan_http_status status = lwan_request_websocket_upgrade(request);
    if (status != HTTP_SWITCHING_PROTOCOLS)
        return status;

    while (true) {
        lwan_strbuf_printf(response->buffer, "Some random integer: %d", rand());
        lwan_response_websocket_write_text(request);
        lwan_request_sleep(request, 1000);
    }

    __builtin_unreachable();
}

#endif