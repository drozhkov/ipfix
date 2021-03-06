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

#ifndef __NVIPFIX_CONFIG_H
#define __NVIPFIX_CONFIG_H


#include "types.h"


#define	CONFIG_BASE_DIR	"/var/nvOS/etc/Local"

/**
 *
 */
typedef enum {
	NV_IPFIX_TRANSPORT_UNDEFINED = 0,  //!< TCP
	NV_IPFIX_TRANSPORT_TCP,	           //!< TCP
	NV_IPFIX_TRANSPORT_UDP,	           //!< UDP
	NV_IPFIX_TRANSPORT_SCTP	           //!< SCTP
} nvIPFIX_TRANSPORT;

/**
 *
 */
typedef struct {
	const nvIPFIX_CHAR * name;		//!< switch name
	const nvIPFIX_CHAR * host;		//!< switch host
	const nvIPFIX_CHAR * login;		//!< switch login
	const nvIPFIX_CHAR * password;	//!< switch password
} nvIPFIX_switch_info_t;

/**
 *
 */
typedef struct {
	const nvIPFIX_CHAR * name;		//!< collector's name
	const nvIPFIX_CHAR * host;		//!< collector's host
	const nvIPFIX_CHAR * port;		//!< collector's port
	nvIPFIX_ip_address_t ipAddress;	//!< collector's IP address
	nvIPFIX_OCTET dscp;
	nvIPFIX_TRANSPORT transport;	//!< collector's transport
	nvIPFIX_hashtable_key_t key;
	void *ctx;
} nvIPFIX_collector_info_t;

typedef struct _nvIPFIX_collector_info_list_item_t {
        struct _nvIPFIX_collector_info_list_item_t * next;
        nvIPFIX_collector_info_t * current;
} nvIPFIX_collector_info_list_item_t;


/**
 *
 * @return
 */
nvIPFIX_switch_info_t * nvipfix_config_switch_info_get();

/**
 *
 * @param a_switchInfo
 */
void nvipfix_config_switch_info_free( nvIPFIX_switch_info_t * a_switchInfo );

/**
 *
 * @return
 */
nvIPFIX_timespan_t nvipfix_config_get_export_interval( void );

/**
 * get linked list of collectors
 * @return pointer to list
 */
nvIPFIX_collector_info_list_item_t * nvipfix_config_collectors_get( );

void nvipfix_config_collectors_free( nvIPFIX_collector_info_t * a_collectors );


#endif /* __NVIPFIX_CONFIG_H */
