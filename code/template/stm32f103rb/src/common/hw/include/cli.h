/*
 * cli.h
 *
 *  Created on: May 9, 2025
 *      Author: DAWIT
 */
#ifndef SRC_COMMON_HW_INCLUDE_CLI_H_
#define SRC_COMMON_HW_INCLUDE_CLI_H_


#include "hw_def.h"


#ifdef _USE_HW_CLI

#define CLI_CMD_LIST_MAX      HW_CLI_CMD_LIST_MAX
#define CLI_CMD_NAME_MAX      HW_CLI_CMD_NAME_MAX

#define CLI_LINE_HIS_MAX      HW_CLI_LINE_HIS_MAX
#define CLI_LINE_BUF_MAX      HW_CLI_LINE_BUF_MAX




typedef struct
{
  uint16_t   argc;
  char     **argv;

  int32_t  (*getData)(uint8_t index);
  float    (*getFloat)(uint8_t index);
  char    *(*getStr)(uint8_t index);
  bool     (*isStr)(uint8_t index, char *p_str);
} cli_args_t;


bool cli_init(void);
bool cli_open(uint8_t ch, uint32_t baud);
bool cli_open_log(uint8_t ch, uint32_t baud);
bool cli_main(void);
void cli_printf(const char *fmt, ...);
bool cli_add(const char *cmd_str, void (*p_func)(cli_args_t *));
bool cli_keep_loop(void);


#endif

#endif /* SRC_COMMON_HW_INCLUDE_CLI_H_ */
