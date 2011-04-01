/*
 * $Id$
 *
 * Copyright (C) 2010 The Paparazzi Team
 *
 * This file is part of paparazzi.
 *
 * paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with paparazzi; see the file COPYING.  If not, write to
 * the Free Software Foundation, 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <event.h>

#include "fms/overo_gps_test.h"

#include "std.h"
#include "fms_debug.h"
#include "fms_network.h"

/* stuff for io processor link */
#include "fms_spi_link.h"
#include "fms_autopilot_msg.h"

static void main_init(void);

#define BUFLEN 512
struct FmsNetwork *net;
char buf[BUFLEN];

struct iphone_msg
{
  double lat;
  double lon;
};

int main(int argc, char *argv[]) {

  main_init();

  return 0;

}

static void network_init()
{
  net = network_new("192.168.1.1", 5900, 56789, 0);
}

static void send_message(double lat, double lon) {

  struct AutopilotMessageCRCFrame msg_in;
  struct AutopilotMessageCRCFrame msg_out;
  uint8_t crc_valid;

  msg_out.payload.msg_down.lat = lat;
  msg_out.payload.msg_down.lon = lon;

  spi_link_send(&msg_out, sizeof(struct AutopilotMessageCRCFrame), &msg_in, &crc_valid);

}

static void main_init(void) {

  /* Initalize our SPI link to IO processor */
  if (spi_link_init()) {
    TRACE(TRACE_ERROR, "%s", "failed to open SPI link \n");
    return;
  }

  network_init();
  size_t len;
  struct iphone_msg *msg;

  while(1) {
    len = recvfrom(net->socket_in, buf, BUFLEN, 0, NULL, NULL);
    if (len == -1) {
      perror("recvfrom()\n");
    } else if (len == 16) {
      msg = (struct iphone_msg *) buf;
      printf("recv: %f %f.\n", msg->lat, msg->lon);
      send_message(msg->lat, msg->lon);
    }
  }

}
