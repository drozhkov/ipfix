/**
 * This file is part of nvIPFIX
 * Copyright (C) 2015 Denis Rozhkov <denis@rozhkoff.com>
 *
 * nvIPFIX is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 */

#ifndef __NVIPFIX_ERROR_H
#define __NVIPFIX_ERROR_H


#include "log.h"


#define NVIPFIX_ERROR_INIT( a_errorVar ) nvIPFIX_error_t a_errorVar = { .code = NV_IPFIX_ERROR_CODE_NONE, .data = NULL }

#define NVIPFIX_ERROR_INIT_WITH_CODE( a_code ) { .code = a_code, .data = NULL }
#define NVIPFIX_ERROR_RETURN( a_error, a_code ) a_error.code = a_code; return a_error;
#define NVIPFIX_ERROR_HANDLER( a_name ) error ## a_name:
#define NVIPFIX_ERROR_RAISE( a_error, a_code, a_name ) a_error.code = a_code; goto error ## a_name;
#define NVIPFIX_ERROR_RAISE_IF( a_condition, a_error, a_code, a_name, a_fmt, ... ) \
		if ((a_condition)) { a_error.code = a_code; \
			if (a_fmt != NULL && a_fmt[0] != '\0') { nvipfix_tlog_error( NVIPFIX_T( "%s: " a_fmt ), __func__, __VA_ARGS__ ); } \
			goto error ## a_name; }


typedef enum {
	NV_IPFIX_ERROR_CODE_UNKNOWN = -1,
	NV_IPFIX_ERROR_CODE_NONE = 0,
	NV_IPFIX_ERROR_CODE_INVALID_ARGUMENTS,
	NV_IPFIX_ERROR_CODE_MALLOC,
	NV_IPFIX_ERROR_CODE_HASHTABLE_ADD,
	NV_IPFIX_ERROR_CODE_ALLOCATE_INFO_MODEL,
	NV_IPFIX_ERROR_CODE_ALLOCATE_SESSION,
	NV_IPFIX_ERROR_CODE_ALLOCATE_EXPORTER,
	NV_IPFIX_ERROR_CODE_ALLOCATE_TEMPLATE,
	NV_IPFIX_ERROR_CODE_NVC_CONNECT,
	NV_IPFIX_ERROR_CODE_NVC_AUTH,
	NV_IPFIX_ERROR_CODE_NVC_CONN_STAT,
	NV_IPFIX_ERROR_CODE_EXPORT_INIT,
	NV_IPFIX_ERROR_CODE_EXPORT_GET_COLLECTOR,
	NV_IPFIX_ERROR_CODE_EXPORT_TEMPLATE_APPEND_SPEC,
	NV_IPFIX_ERROR_CODE_EXPORT_SESSION_ADD_TEMPLATE,
	NV_IPFIX_ERROR_CODE_EXPORT_BUF_ALLOC,
	NV_IPFIX_ERROR_CODE_EXPORT_SESSION_EXPORT_TEMPLATES,
	NV_IPFIX_ERROR_CODE_EXPORT_SET_INTERNAL_TEMPLATE,
	NV_IPFIX_ERROR_CODE_EXPORT_SET_EXPORT_TEMPLATE,
} nvIPFIX_ERROR_CODE;

typedef struct {
	nvIPFIX_ERROR_CODE code;
	void * data;
} nvIPFIX_error_t;


#endif /* __NVIPFIX_ERROR_H */
