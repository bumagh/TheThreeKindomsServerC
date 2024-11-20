#ifndef user_mgr_h
#define user_mgr_h

#include <stdio.h>
#include <stdlib.h>
#include <lwan/lwan.h>

LWAN_HANDLER(user_mgr)
{
    response->mime_type = "text/html;charset=utf-8";
   const char *action = (char *)malloc(64 * sizeof(char));
    if (!action)
    {
        return HTTP_OK;
    }
    action = lwan_request_get_post_param(request, "action");
    char data_buf_fmt[256] = "{\"%s\":\"%s\"}";
    char response_buf_fmt[256] = "{\"code\":%s,\"data\":%s,\"msg\":\"%s\"}";
    if (strcmp(action, "addUser") == 0)
    {
        const char *account = lwan_request_get_post_param(request, "account");
        const char *pwd = lwan_request_get_post_param(request, "pwd");

        if (account == NULL || pwd == NULL)
        {
            static const char noarg[] = "2";
            lwan_strbuf_set_static(response->buffer, noarg, sizeof(noarg) - 1);
            return HTTP_OK;
        }

        if (model_user_add(account, strlen(account), pwd, strlen(pwd)) == 0)
        {

            char code[] = "200";
            char msg[] = "";
            char data_buf[128];
            char response_buf_fmt_buf[256];

            sprintf(data_buf, "\"\"");
            sprintf(response_buf_fmt_buf, response_buf_fmt, code, data_buf, msg);
            lwan_strbuf_append_printf(response->buffer, response_buf_fmt_buf);
        }
        else
        {
            char code[] = "201";
            char msg[] = "account exist";

            char data_buf[128];
            char response_buf_fmt_buf[256];

            sprintf(data_buf, "\"\"");
            sprintf(response_buf_fmt_buf, response_buf_fmt, code, data_buf, msg);

            lwan_strbuf_append_printf(response->buffer, response_buf_fmt_buf);
        }
    }
    else if (strcmp(action, "loginUser") == 0)
    {
        const char *account = lwan_request_get_post_param(request, "account");
        const char *pwd = lwan_request_get_post_param(request, "pwd");

        if (account == NULL || pwd == NULL)
        {
            static const char noarg[] = "2";
            lwan_strbuf_set_static(response->buffer, noarg, sizeof(noarg) - 1);
            return HTTP_OK;
        }

        int loginRet = model_user_login(account, strlen(account), pwd, strlen(pwd));
        if (loginRet > 0)
        {

            char code[] = "200";
            char msg[] = "";
            char data_key[64];
            char data_val[64];
            char data_buf[128];
            char response_buf_fmt_buf[256];

            sprintf(data_key, "%s", "user_id");
            sprintf(data_val, "%d", loginRet);
            sprintf(data_buf, data_buf_fmt, data_key, data_val);
            sprintf(response_buf_fmt_buf, response_buf_fmt, code, data_buf, msg);

            lwan_strbuf_append_printf(response->buffer, response_buf_fmt_buf);
        }
        else
        {
            char code[] = "201";
            char msg[] = "err or not exist";

            char data_buf[128];
            char response_buf_fmt_buf[256];

            sprintf(data_buf, "\"\"");
            sprintf(response_buf_fmt_buf, response_buf_fmt, code, data_buf, msg);

            lwan_strbuf_append_printf(response->buffer, response_buf_fmt_buf);
        }
    }
    else if (strcmp(action, "addUserGoods") == 0)
    {
        const char *goods_idc = lwan_request_get_post_param(request, "goods_id");
        const char *user_idc = lwan_request_get_post_param(request, "user_id");
        const char *countsc = lwan_request_get_post_param(request, "counts");
        if (goods_idc == NULL || user_idc == NULL || countsc == NULL)
        {
            static const char noarg[] = "2";
            lwan_strbuf_set_static(response->buffer, noarg, sizeof(noarg) - 1);
            return HTTP_OK;
        }
        int goods_id = atoi(goods_idc);
        int user_id = atoi(user_idc);
        int counts = atoi(countsc);

        int addret = model_user_goods_add_bygid(user_id, goods_id, counts);
        fprintf(stderr, "addret = %d", addret);
        if (addret == 0)
        {

            static const char success[] = "0";
            lwan_strbuf_set_static(response->buffer, success, sizeof(success) - 1);
        }
        else
        {
            static const char fail[] = "1";
            lwan_strbuf_set_static(response->buffer, fail, sizeof(fail) - 1);
        }
    }
    else if (strcmp(action, "getUserGoodsList") == 0)
    {
        const char *user_idc = lwan_request_get_post_param(request, "user_id");
        int user_id = atoi(user_idc);
        char buf[1024];
        model_user_goods_list(user_id, buf);
        printf(" getUserGoodsList buf:%s", buf);

        //  fprintf(stderr, "jsonbuf = %s", model_user_goods_list(user_id) );
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
            static const char fail[] = "1";
            lwan_strbuf_set_static(response->buffer, fail, sizeof(fail) - 1);
        }
    }
    else if (strcmp(action, "getUserInfoAll") == 0)
    {
        const char *user_idc = lwan_request_get_post_param(request, "user_id");
        int user_id = atoi(user_idc);
        char buf[2048];
        model_user_info_all("id", strlen("id"), user_idc, strlen(user_idc), buf);
        fprintf(stderr, "buf = %s", buf);
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
            static const char fail[] = "1";
            lwan_strbuf_set_static(response->buffer, fail, sizeof(fail) - 1);
        }
    }
    else if (strcmp(action, "updateUserKvByid") == 0)
    {
        const char *user_idc = lwan_request_get_post_param(request, "user_id");
        const char *keyc = lwan_request_get_post_param(request, "key");
        const char *valc = lwan_request_get_post_param(request, "val");
        const char *val_typec = lwan_request_get_post_param(request, "val_type");
        int user_id = atoi(user_idc);
        int val_type = atoi(val_typec);
        if (val_type == 0)
        {

            int val = atoi(valc);
            model_user_update_kv_byid(user_id, keyc, strlen(keyc), val, strlen(valc), 0);
            static const char fail[] = "0";
            lwan_strbuf_set_static(response->buffer, fail, sizeof(fail) - 1);
        }
        else
        {

            model_user_update_kv_byid(user_id, keyc, strlen(keyc), valc, strlen(valc), 1);
            static const char fail[] = "1";
            lwan_strbuf_set_static(response->buffer, fail, sizeof(fail) - 1);
        }
    }
    return HTTP_OK;
}

#endif