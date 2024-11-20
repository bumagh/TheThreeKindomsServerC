#ifndef msg_mgr_h
#define msg_mgr_h

#include <stdio.h>
#include <stdlib.h>
#include <lwan/lwan.h>
#include <lwan/lwan-mod-serve-files.h>

LWAN_HANDLER(msg_mgr)
{
    response->mime_type = "text/html;charset=utf-8";
    const char *action = lwan_request_get_post_param(request, "action");
    char data_buf_fmt[256] = "{\"%s\":\"%s\"}";
    char response_buf_fmt[256] = "{\"code\":%s,\"data\":%s,\"msg\":\"%s\"}";

   if (strcmp(action, "msg_add") == 0)
    {
        const char *content = lwan_request_get_post_param(request, "content");
        const char *user_name = lwan_request_get_post_param(request, "user_name");
        const char *user_idc = lwan_request_get_post_param(request, "user_id");
        const char *typec = lwan_request_get_post_param(request, "type");
        if (content == NULL || user_idc == NULL || typec == NULL ||user_name == NULL)
        {
             char code[] = "202";
            char msg[] = "err: params can not be null";

            char data_buf[16];
            char response_buf_fmt_buf[256];

            sprintf(data_buf, "\"\"");
            sprintf(response_buf_fmt_buf, response_buf_fmt, code, data_buf, msg);

            lwan_strbuf_append_printf(response->buffer, response_buf_fmt_buf);
        }
        int type = atoi(typec);
        int user_id = atoi(user_idc);
        int addret = model_msg_add(user_id, user_name, content, type);
        fprintf(stderr, "addret = %d", addret);
        if (addret == 0)
        {
           char code[] = "200";
            char msg[] = "ok";

            char data_buf[16];
            char response_buf_fmt_buf[256];

            sprintf(data_buf, "\"\"");
            sprintf(response_buf_fmt_buf, response_buf_fmt, code, data_buf, msg);

            lwan_strbuf_append_printf(response->buffer, response_buf_fmt_buf);
        }
        else
        {
            char code[] = "201";
            char msg[] = "add err";

            char data_buf[16];
            char response_buf_fmt_buf[256];

            sprintf(data_buf, "\"\"");
            sprintf(response_buf_fmt_buf, response_buf_fmt, code, data_buf, msg);

            lwan_strbuf_append_printf(response->buffer, response_buf_fmt_buf);
        }
    }
    else if (strcmp(action, "msg_get_by_type") == 0)
    {
        const char *typec = lwan_request_get_post_param(request, "type");
        int type = atoi(typec);
        char buf[1024];
        model_msg_get_by_type(type, buf);
        if (strlen(buf) != 0)
        {
            char code[] = "200";
            char msg[] = "";
            char data_key[64];
            char data_val[64];
            char data_buf[128];
            char response_buf_fmt_buf[256];

            sprintf(response_buf_fmt_buf, response_buf_fmt, code, buf, msg);

            lwan_strbuf_append_printf(response->buffer, response_buf_fmt_buf);
        }
        else
        {
            char code[] = "201";
            char msg[] = "get err";

            char data_buf[16];
            char response_buf_fmt_buf[256];

            sprintf(data_buf, "\"\"");
            sprintf(response_buf_fmt_buf, response_buf_fmt, code, data_buf, msg);

            lwan_strbuf_append_printf(response->buffer, response_buf_fmt_buf);
        }
    }
    return HTTP_OK;
}

#endif