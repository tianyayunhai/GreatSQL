/* Copyright (c) 2016, 2022, Oracle and/or its affiliates. All rights reserved.
   Copyright (c) 2023, 2024, GreatDB Software Co., Ltd.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License, version 2.0,
   as published by the Free Software Foundation.

   This program is also distributed with certain software (including
   but not limited to OpenSSL) that is licensed under separate terms,
   as designated in a particular file or component or in included license
   documentation.  The authors of MySQL hereby grant you an additional
   permission to link the program and your derivative works with the
   separately licensed software that they have included with MySQL.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License, version 2.0, for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA */

#ifndef XCOM_CFG_H
#define XCOM_CFG_H

#include <stdint.h>
#include <stdlib.h>
#include "xcom/network/include/network_provider.h"
#include "xdr_gen/xcom_vp.h"

#define DEFAULT_EXPEL_TIMEOUT 5
#define MAX_IP_PORT_LEN 64

typedef struct cfg_app_xcom {
  /*
   The number of spin loops the XCom thread does before
   blocking on the poll system call.
  */
  unsigned int m_poll_spin_loops;

  /*
   cache size limit and interval
  */
  uint64_t m_cache_limit;

  uint64_t m_flp_timeout;

  char ip_port[MAX_IP_PORT_LEN];
  /*
   The (address, incarnation) pair that uniquely identifies this XCom instance.
  */
  node_address *identity;

  /**
   This is a network namespace manager to deal with network namespace
   operations
   */
  Network_namespace_manager *network_ns_manager;
} cfg_app_xcom_st;

/*
 The application will set this pointer before engaging
 xcom
*/
extern cfg_app_xcom_st *the_app_xcom_cfg;

void init_cfg_app_xcom();
void deinit_cfg_app_xcom();

node_address *cfg_app_xcom_get_identity();

Network_namespace_manager *cfg_app_get_network_namespace_manager();

/*
 Takes ownership of @c identity.

 @param identity The unique identity of this XCom instance. Must not be null.
*/
void cfg_app_xcom_set_identity(node_address *identity);

#endif
