/* Copyright (c) 2020, 2022, Oracle and/or its affiliates.

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

#include <mysql/components/component_implementation.h>
#include <mysql/components/service.h>
#include <mysql/components/service_implementation.h>
#include <mysql/components/services/mysql_psi_system_service.h>
#include <mysql/components/services/psi_memory_service.h>

void impl_min_chassis_psi_system(const char *) { return; }

extern SERVICE_TYPE(mysql_psi_system_v1)
    SERVICE_IMPLEMENTATION(mysql_minimal_chassis, mysql_psi_system_v1);

SERVICE_TYPE(mysql_psi_system_v1)
SERVICE_IMPLEMENTATION(mysql_minimal_chassis,
                       mysql_psi_system_v1) = {impl_min_chassis_psi_system};

//////////////////////////////////////////////

static void register_memory_noop(const char *, PSI_memory_info *, int) {
  return;
}

static PSI_memory_key memory_alloc_noop(PSI_memory_key, size_t,
                                        struct PSI_thread **owner) {
  *owner = nullptr;
  return PSI_NOT_INSTRUMENTED;
}

static PSI_memory_key memory_realloc_noop(PSI_memory_key, size_t, size_t,
                                          struct PSI_thread **owner) {
  *owner = nullptr;
  return PSI_NOT_INSTRUMENTED;
}

static PSI_memory_key memory_claim_noop(PSI_memory_key, size_t,
                                        struct PSI_thread **owner, bool) {
  *owner = nullptr;
  return PSI_NOT_INSTRUMENTED;
}

static void memory_free_noop(PSI_memory_key, size_t, struct PSI_thread *) {
  return;
}

extern SERVICE_TYPE(psi_memory_v2)
    SERVICE_IMPLEMENTATION(mysql_minimal_chassis, psi_memory_v2);

SERVICE_TYPE(psi_memory_v2)
SERVICE_IMPLEMENTATION(mysql_minimal_chassis, psi_memory_v2) = {
    register_memory_noop, memory_alloc_noop, memory_realloc_noop,
    memory_claim_noop, memory_free_noop};
