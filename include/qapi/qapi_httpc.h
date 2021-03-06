
/*===========================================================================

  Copyright (c) 2017 Qualcomm Technologies, Inc. All Rights Reserved

  Qualcomm Technologies Proprietary

  Export of this technology or software is regulated by the U.S. Government.
  Diversion contrary to U.S. law prohibited.

  All ideas, data and information contained in or disclosed by
  this document are confidential and proprietary information of
  Qualcomm Technologies, Inc. and all rights therein are expressly reserved.
  By accepting this material the recipient agrees that this material
  and the information contained therein are held in confidence and in
  trust and will not be used, copied, reproduced in whole or in part,
  nor its contents revealed in any manner to others without the express
  written permission of Qualcomm Technologies, Inc.

===========================================================================*/

/* Copyright (c) 2015 Qualcomm Atheros, Inc.
   All rights reserved.
   Qualcomm Atheros Confidential and Proprietary.
*/ 
/*!
  @file
  qapi_httpc.h

  @brief
  HTTP client service provides a collection of API functions that allow the 
  application to enable and configure HTTP client services. The HTTP client 
  can be configured to support IPv4, IPv6, as well as HTTP mode, HTTPS 
  mode (secure) or both. 
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

$Header: 

when       who     what, where, why
--------   ---     ----------------------------------------------------------
25Jan2017 vpulimi  Created the module. First version of the file.
===========================================================================*/
#ifndef _QAPI_HTTPC_H_
#define _QAPI_HTTPC_H_

#include <stdint.h>
#include "qapi/qapi_status.h"   /* qapi_Status_t */
#include "qapi/qapi_ssl.h"

#include "qapi_data_txm_base.h"
#include "qapi_status.h"

/* HTTP client request IDs */
#define  TXM_QAPI_HTTPC_START                      TXM_QAPI_NET_HTTP_BASE + 1
#define  TXM_QAPI_HTTPC_STOP                       TXM_QAPI_NET_HTTP_BASE + 2
#define  TXM_QAPI_HTTPC_NEW_SESSION                TXM_QAPI_NET_HTTP_BASE + 3
#define  TXM_QAPI_HTTPC_FREE_SESSION               TXM_QAPI_NET_HTTP_BASE + 4
#define  TXM_QAPI_HTTPC_CONNECT                    TXM_QAPI_NET_HTTP_BASE + 5
#define  TXM_QAPI_HTTPC_DISCONNECT                 TXM_QAPI_NET_HTTP_BASE + 6
#define  TXM_QAPI_HTTPC_REQUEST                    TXM_QAPI_NET_HTTP_BASE + 7
#define  TXM_QAPI_HTTPC_SET_BODY                   TXM_QAPI_NET_HTTP_BASE + 8
#define  TXM_QAPI_HTTPC_SET_PARAM                  TXM_QAPI_NET_HTTP_BASE + 9
#define  TXM_QAPI_HTTPC_ADD_HEADER_FIELD           TXM_QAPI_NET_HTTP_BASE + 10
#define  TXM_QAPI_HTTPC_CLEAR_HEADER               TXM_QAPI_NET_HTTP_BASE + 11
#define  TXM_QAPI_HTTPC_SSL_CONFIG                 TXM_QAPI_NET_HTTP_BASE + 12
#define  TXM_QAPI_HTTPC_PROXY_CONNECT              TXM_QAPI_NET_HTTP_BASE + 13


/** @addtogroup qapi_networking_httpc
@{ */

/**
 * @brief HTTP request types supported by qapi_Net_HTTPc_Request()
 */
typedef enum 
{
  /* Supported http client methods */
  QAPI_NET_HTTP_CLIENT_GET_E = 1,
  /**< HTTP Get request */
  QAPI_NET_HTTP_CLIENT_POST_E,
  /**< HTTP Post request */
  QAPI_NET_HTTP_CLIENT_PUT_E,
  /**< HTTP Put request */
  QAPI_NET_HTTP_CLIENT_PATCH_E,
  /**< HTTP Patch request */
  QAPI_NET_HTTP_CLIENT_HEAD_E,
  /**< HTTP Head request */
  QAPI_NET_HTTP_CLIENT_CONNECT_E
  /**< HTTP Connect request */
} qapi_Net_HTTPc_Method_e;

/**
 * @brief HTTP callback state returned by qapi_HTTPc_CB_t()
 */
typedef enum
{
  QAPI_NET_HTTPC_RX_ERROR_SERVER_CLOSED = -8, 
  /**< HTTP response error - server closed connection */
  QAPI_NET_HTTPC_RX_ERROR_RX_PROCESS = -7,
  /**< HTTP response error - response processing */
  QAPI_NET_HTTPC_RX_ERROR_RX_HTTP_HEADER = -6,
  /**< HTTP response error - header processing */
  QAPI_NET_HTTPC_RX_ERROR_INVALID_RESPONSECODE = -5,
  /**< HTTP response error - invalid response code */
  QAPI_NET_HTTPC_RX_ERROR_CLIENT_TIMEOUT = -4,
  /**< HTTP response error - timeout waiting for response */
  QAPI_NET_HTTPC_RX_ERROR_NO_BUFFER = -3,
  /**< HTTP response error - memory unavailable */
  QAPI_NET_HTTPC_RX_CONNECTION_CLOSED = -2,
  /**< HTTP response - connection closed */
  QAPI_NET_HTTPC_RX_ERROR_CONNECTION_CLOSED = -1,
  /**< HTTP response error - connection closed */
  QAPI_NET_HTTPC_RX_FINISHED = 0,
  /**< HTTP response - response received completely */
  QAPI_NET_HTTPC_RX_MORE_DATA = 1,	
  /**< HTTP response - response data to be further received */
}qapi_Net_HTTPc_CB_State_e;

/**
 * @brief HTTP response data returned by qapi_HTTPc_CB_t()
 */
typedef struct 
{
  uint32_t      length;
  /**< HTTP response data buffer length */
  uint32_t      resp_Code;
  /**< HTTP response code */
  const void   *data;
  /**< HTTP response data */
} qapi_Net_HTTPc_Response_t;

/**
 * @brief HTTP response user callback registered during qapi_Net_HTTPc_New_sess()
 */
typedef void (*qapi_HTTPc_CB_t)
(
  void* arg,
  /**< User payload information */
  int32_t state,
  /**< HTTP response state */
  void* value
  /**< HTTP response information */
);

/**
 * @brief HTTP client handle used by most of qapi_Net_HTTPc_xxxx()
 */
typedef void* qapi_Net_HTTPc_handle_t;

/* HTTP client QAPIs */
#ifdef  QAPI_TXM_MODULE     // USER_MODE_DEFS
#define qapi_Net_HTTPc_Start()                    ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_HTTPC_START, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_HTTPc_Stop()                     ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_HTTPC_STOP, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_HTTPc_New_sess(a,b,c,d,e,f)      ((qapi_Net_HTTPc_handle_t) (_txm_module_system_call12)(TXM_QAPI_HTTPC_NEW_SESSION, (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) d, (ULONG) e, (ULONG) f, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_HTTPc_Free_sess(a)               ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_HTTPC_FREE_SESSION, (ULONG) a, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_HTTPc_Connect(a,b,c)             ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_HTTPC_CONNECT, (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_HTTPc_Disconnect(a)              ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_HTTPC_DISCONNECT, (ULONG) a, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_HTTPc_Request(a,b,c)             ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_HTTPC_REQUEST, (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_HTTPc_Set_Body(a,b,c)            ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_HTTPC_SET_BODY, (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_HTTPc_Set_Param(a,b,c)           ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_HTTPC_SET_PARAM, (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_HTTPc_Add_Header_Field(a,b,c)    ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_HTTPC_ADD_HEADER_FIELD, (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_HTTPc_Clear_Header(a)            ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_HTTPC_CLEAR_HEADER, (ULONG) a, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_HTTPc_Configure_SSL(a,b)         ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_HTTPC_SSL_CONFIG, (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_HTTPc_Proxy_Connect(a,b,c,d)     ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_HTTPC_PROXY_CONNECT, (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) d, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))

#else

qapi_Status_t qapi_HTTPc_Handler(UINT id, UINT a1, UINT a2, UINT a3, UINT a4, UINT a5, UINT a6, UINT a7, UINT a8, UINT a9, UINT a10, UINT a11, UINT a12);

/**
 * @brief Start/Re-start HTTP client module
 *
 * @details Function is invoked to start or restart the HTTP client after it is
 *          stopped via call to qapi_Net_HTTPc_Stop().
 *
 * @return On success, 0 is returned. Other value on error.
 */
qapi_Status_t qapi_Net_HTTPc_Start(void);

/**
 * @brief Stop HTTP client module
 *
 * @details Function is invoked to stop the HTTP client after it was started via 
            call to qapi_Net_HTTPc_Start().
 *
 * @return On success, 0 is returned. Other value on error.
 */
qapi_Status_t qapi_Net_HTTPc_Stop(void);

/**
 * @brief Creates new HTTP client session 
 *
 * @details In order to create a client session the caller needs to invoke this function 
 *          and the handle to the newly created context is returned if success. As part 
 *          of the function call, an user callback function is registered with the HTTP 
 *          client module that gets invoked for that particular session if there is some
 *          response data from the HTTP server. Passing in the SSL context information
 *          would ensure that a secure session would get created.           
 *
 * @param[in] timeout   Timeout(ms) on session method (zero is not recommended)
 * @param[in] ssl_Object_Handle   SSL context for HTTPs connect (zero for no HTTPs session support)
 * @param[in] callback  Register callback function, NULL for not support callback
 * @param[in] arg       User data payload to be returned by the callback function
 * @param[in] httpc_Max_Body_Length    Max body length on this session
 * @param[in] httpc_Max_Header_Length  Max header length on this session
 *
 * @return On success, qapi_Net_HTTPc_handle_t is returned. NULL otherwise.
 */
qapi_Net_HTTPc_handle_t qapi_Net_HTTPc_New_sess(
        uint32_t timeout,
        qapi_Net_SSL_Obj_Hdl_t ssl_Object_Handle,
        qapi_HTTPc_CB_t callback,
        void *arg,
        uint32_t httpc_Max_Body_Length,
        uint32_t httpc_Max_Header_Length);

/**
 * @brief Release HTTP client session
 *
 * @details HTTP client session that is connected to the HTTP server is disconnected prior 
            to releasing the resources associated with that session. 
 *
 * @param[in] handle  Handle to the HTTP client session
 *
 * @return On success, 0 is returned. Other value on error.
 */
qapi_Status_t qapi_Net_HTTPc_Free_sess(qapi_Net_HTTPc_handle_t handle);

/**
 * @brief Connect HTTP client session to the HTTP server
 *
 * @details HTTP client session is connected to the HTTP server in blocking mode. 
 *
 * @param[in] handle  Handle to the HTTP client session
 * @param[in] URL     Server URL informtion  
 * @param[in] port    Server port information 
 *
 * @return On success, 0 is returned. Other value on error.
 */
qapi_Status_t qapi_Net_HTTPc_Connect(qapi_Net_HTTPc_handle_t handle, const char *URL, uint16_t port);

/**
 * @brief Connect HTTP client session to the HTTP proxy server
 *
 * @details HTTP client session is connected to the HTTP server in blocking mode. 
 *
 * @param[in] handle        Handle to the HTTP client session
 * @param[in] URL           Server URL informtion  
 * @param[in] port          Server port information 
 * @param[in] secure_proxy  Secure proxy connection
 *
 * @return On success, 0 is returned. Other value on error.
 */
qapi_Status_t qapi_Net_HTTPc_Proxy_Connect(qapi_Net_HTTPc_handle_t handle, const char *URL, uint16_t port, uint8_t secure_proxy);

/**
 * @brief Disconnect HTTP client session from the HTTP server
 *
 * @details HTTP client session that is connected to the HTTP server is disconnected 
            from the HTTP server. 
 *
 * @param[in] handle  Handle to the HTTP client session
 *
 * @return On success, 0 is returned. Other value on error.
 */
qapi_Status_t qapi_Net_HTTPc_Disconnect(qapi_Net_HTTPc_handle_t handle);

/**
 * @brief Process the HTTP client session requests
 *
 * @details HTTP client session requests are processed and sent to the HTTP server. 
 *
 * @param[in] handle   Handle to the HTTP client session
 * @param[in] cmd      HTTP request method information 
 * @param[in] URL      Server URL information
 *
 * @return On success, 0 is returned. Other value on error.
 */
qapi_Status_t qapi_Net_HTTPc_Request(qapi_Net_HTTPc_handle_t handle, qapi_Net_HTTPc_Method_e cmd, const char *URL);

/**
 * @brief Set HTTP client session body
 *
 * @details Multiple invocations of this function would result in overwriting the 
            internal data buffer with content of the last call.  
 *
 * @param[in] handle        Handle to the HTTP client session
 * @param[in] body          HTTP body related information buffer
 * @param[in] body_Length   HTTP body buffer length
 *
 * @return On success, 0 is returned. Other value on error.
 */
qapi_Status_t qapi_Net_HTTPc_Set_Body(qapi_Net_HTTPc_handle_t handle, const char *body, uint32_t body_Length);

/**
 * @brief Set HTTP client session parameter
 *
 * @details Multiple invocations of this function would result in appending the 
            parameter key-value pair information to the internal data buffer. 
 *
 * @param[in] handle    Handle to the HTTP client session
 * @param[in] key       HTTP key related inforamtion 
 * @param[in] value     HTTP value associated with the key 
 *
 * @return On success, 0 is returned. Other value on error.
 */
qapi_Status_t qapi_Net_HTTPc_Set_Param(qapi_Net_HTTPc_handle_t handle, const char *key, const char *value);

/**
 * @brief Add HTTP client session header field
 *
 * @details Multiple invocations of this function would result in appending the 
            header type-value pair information to the internal header buffer. 
 *
 * @param[in] handle    Handle to the HTTP client session
 * @param[in] type      HTTP header type related inforamtion 
 * @param[in] value     HTTP value associated with the header type 
 *
 * @return On success, 0 is returned. Other value on error.
 */
qapi_Status_t qapi_Net_HTTPc_Add_Header_Field(qapi_Net_HTTPc_handle_t handle, const char *type, const char *value);

/**
 * @brief Clear HTTP client session header
 *
 * @details Invocation to this function would clear the entire content associated 
            with the internal header buffer. 
 *
 * @param[in] handle    Handle to the HTTP client session
 *
 * @return On success, 0 is returned. Other value on error.
 */
 /** @} */
qapi_Status_t qapi_Net_HTTPc_Clear_Header(qapi_Net_HTTPc_handle_t handle);

/**
 * @brief Configure HTTP client session
 *
 * @details Invocation to this function would configure the HTTP client SSL session. 
 *
 * @param[in] handle    Handle to the HTTP client session
 * @param[in] ssl_cfg   SSL configuration information 
 *
 * @return On success, 0 is returned. Other value on error.
 */
qapi_Status_t qapi_Net_HTTPc_Configure_SSL(qapi_Net_HTTPc_handle_t handle, qapi_Net_SSL_Config_t *ssl_Cfg);

#endif /* QAPI_TXM_MODULE  */
#endif /* _QAPI_HTTPC_H_ */
