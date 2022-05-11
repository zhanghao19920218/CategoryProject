//
// Created by Mason on 2022/5/4.
//

#ifndef QQ_API_SCRIPT_HTTP_ERROR_H
#define QQ_API_SCRIPT_HTTP_ERROR_H

/**
 * SUCCESS: 请求成功
 * PARAM_ERROR: 传参错误
 * NODE_ERROR: Node.js报错
 * COOKIE_ERROR: Cookie用户登录值不对
 * OTHER
 */
enum HTTP_STATUS: int {
    SUCCESS = 200,
    PARAM_ERROR = 500,
    NODE_ERROR = 400,
    COOKIE_ERROR = 301,
    OTHER_ERROR = 500
};

#endif //QQ_API_SCRIPT_HTTP_ERROR_H
