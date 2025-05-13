/*
 * cli.c
 *
 *  Created on: May 9, 2025
 *      Author: DAWIT
 */



#include "cli.h"
#include "uart.h"



#define CLI_KEY_BACK              0x08
#define CLI_KEY_DEL               0x7F
#define CLI_KEY_ENTER             0x0D
#define CLI_KEY_ESC               0x1B
#define CLI_KEY_LEFT              0x44
#define CLI_KEY_RIGHT             0x43
#define CLI_KEY_UP                0x41
#define CLI_KEY_DOWN              0x42
#define CLI_KEY_HOME              0x31
#define CLI_KEY_END               0x34

#define CLI_PROMPT_STR            "cli# "

#define CLI_ARGS_MAX              32
#define CLI_PRINT_BUF_MAX         256


enum
{
  CLI_RX_IDLE,
  CLI_RX_SP1,
  CLI_RX_SP2,
  CLI_RX_SP3,
  CLI_RX_SP4,
};


typedef struct
{
  char   cmd_str[CLI_CMD_NAME_MAX];
  void (*cmd_func)(cli_args_t *);
} cli_cmd_t;


typedef struct
{
  uint8_t buf[CLI_LINE_BUF_MAX];
  uint8_t buf_len;
  uint8_t cursor;
  uint8_t count;
} cli_line_t;


typedef struct
{
  uint8_t  ch;
  uint32_t baud;
  bool     is_open;
  bool     is_log;
  uint8_t  log_ch;
  uint32_t log_baud;
  uint8_t  state;
  char     print_buffer[CLI_PRINT_BUF_MAX];
  uint16_t  argc;
  char     *argv[CLI_ARGS_MAX];


  bool        hist_line_new;
  int8_t      hist_line_i;
  uint8_t     hist_line_last;
  uint8_t     hist_line_count;

  cli_line_t  line_buf[CLI_LINE_HIS_MAX];
  cli_line_t  line;

  uint16_t    cmd_count;
  cli_cmd_t   cmd_list[CLI_CMD_LIST_MAX];
  cli_args_t  cmd_args;
} cli_t;



cli_t   cli_node;



static bool cli_update(cli_t *p_cli, uint8_t rx_data);
static void cli_line_clean(cli_t *p_cli);
static void cli_line_add(cli_t *p_cli);
static void cli_line_change(cli_t *p_cli, int8_t key_up);
static void cli_show_prompt(cli_t *p_cli);
static void cli_to_upper(char *str);
static bool cli_run_cmd(cli_t *p_cli);
static bool cli_parse_args(cli_t *p_cli);

static int32_t  cli_args_get_data(uint8_t index);
static float    cli_args_get_float(uint8_t index);
static char    *cli_args_get_str(uint8_t index);
static bool     cli_args_is_str(uint8_t index, char *p_str);


void cli_show_list(cli_args_t *args);
void cli_memory_dump(cli_args_t *args);


bool cli_init(void)
{
  cli_node.is_open = false;
  cli_node.is_log  = false;
  cli_node.state   = CLI_RX_IDLE;

  cli_node.hist_line_i     = 0;
  cli_node.hist_line_last  = 0;
  cli_node.hist_line_count = 0;
  cli_node.hist_line_new   = false;

  cli_node.cmd_args.getData  = cli_args_get_data;
  cli_node.cmd_args.getFloat = cli_args_get_float;
  cli_node.cmd_args.getStr   = cli_args_get_str;
  cli_node.cmd_args.isStr    = cli_args_is_str;

  cli_line_clean(&cli_node);


  cli_add("help", cli_show_list);
  cli_add("md"  , cli_memory_dump);

  return true;
}

bool cli_open(uint8_t ch, uint32_t baud)
{
  cli_node.ch = ch;
  cli_node.baud = baud;

  cli_node.is_open = uart_open(ch, baud);

  return cli_node.is_open;
}

bool cli_open_log(uint8_t ch, uint32_t baud)
{
  bool ret;

  cli_node.log_ch = ch;
  cli_node.log_baud = baud;

  ret = uart_open(ch, baud);

  if (ret == true)
  {
    cli_node.is_log = true;
  }
  return ret;
}

bool cli_log_close(void)
{
  cli_node.is_log = false;
  return true;
}

void cli_show_log(cli_t *p_cli)
{
  if (cli_node.is_log == true)
  {
    uart_printf(p_cli->log_ch, "Cursor  : %d\n", p_cli->line.cursor);
    uart_printf(p_cli->log_ch, "Count   : %d\n", p_cli->line.count);
    uart_printf(p_cli->log_ch, "buf_len : %d\n", p_cli->line.buf_len);
    uart_printf(p_cli->log_ch, "buf     : %s\n", p_cli->line.buf);
    uart_printf(p_cli->log_ch, "line_i  : %d\n", p_cli->hist_line_i);
    uart_printf(p_cli->log_ch, "line_lt : %d\n", p_cli->hist_line_last);
    uart_printf(p_cli->log_ch, "line_c  : %d\n", p_cli->hist_line_count);

    for (int i=0; i<p_cli->hist_line_count; i++)
    {
      uart_printf(p_cli->log_ch, "buf %d   : %s\n", i, p_cli->line_buf[i].buf);
    }
    uart_printf(p_cli->log_ch, "\n");
  }
}

void cli_show_prompt(cli_t *p_cli)
{
  uart_printf(p_cli->ch, "\n\r");
  uart_printf(p_cli->ch, CLI_PROMPT_STR);
}

bool cli_main(void)
{
  if (cli_node.is_open != true)
  {
    return false;
  }

  if (uart_available(cli_node.ch) > 0)
  {
    cli_update(&cli_node, uart_read(cli_node.ch));
  }

  return true;
}

bool cli_update(cli_t *p_cli, uint8_t rx_data)
{
  bool ret = false;
  uint8_t tx_buf[8];
  cli_line_t *line;

  line = &p_cli->line;


  if (p_cli->state == CLI_RX_IDLE)
  {
    switch(rx_data)
    {
      // 엔터
      //
      case CLI_KEY_ENTER:
        if (line->count > 0)
        {
          cli_line_add(p_cli);
          cli_run_cmd(p_cli);
        }

        line->count = 0;
        line->cursor = 0;
        line->buf[0] = 0;
        cli_show_prompt(p_cli);
        break;


      case CLI_KEY_ESC:
        p_cli->state = CLI_RX_SP1;
        break;


      // DEL
      //
      case CLI_KEY_DEL:
        if (line->cursor < line->count)
        {
          uint8_t mov_len;

          mov_len = line->count - line->cursor;
          for (int i=1; i<mov_len; i++)
          {
            line->buf[line->cursor + i - 1] = line->buf[line->cursor + i];
          }

          line->count--;
          line->buf[line->count] = 0;

          uart_printf(p_cli->ch, "\x1B[1P");
        }
        break;


      // 백스페이스
      //
      case CLI_KEY_BACK:
        if (line->count > 0 && line->cursor > 0)
        {
          if (line->cursor == line->count)
          {
            line->count--;
            line->buf[line->count] = 0;
          }

          if (line->cursor < line->count)
          {
            uint8_t mov_len;

            mov_len = line->count - line->cursor;

            for (int i=0; i<mov_len; i++)
            {
              line->buf[line->cursor + i - 1] = line->buf[line->cursor + i];
            }

            line->count--;
            line->buf[line->count] = 0;
          }
        }

        if (line->cursor > 0)
        {
          line->cursor--;
          uart_printf(p_cli->ch, "\b \b\x1B[1P");
        }
        break;


      default:
        if ((line->count + 1) < line->buf_len)
        {
          if (line->cursor == line->count)
          {
            uart_write(p_cli->ch, &rx_data, 1);

            line->buf[line->cursor] = rx_data;
            line->count++;
            line->cursor++;
            line->buf[line->count] = 0;
          }
          if (line->cursor < line->count)
          {
            uint8_t mov_len;

            mov_len = line->count - line->cursor;
            for (int i=0; i<mov_len; i++)
            {
              line->buf[line->count - i] = line->buf[line->count - i - 1];
            }
            line->buf[line->cursor] = rx_data;
            line->count++;
            line->cursor++;
            line->buf[line->count] = 0;

            uart_printf(p_cli->ch, "\x1B[4h%c\x1B[4l", rx_data);
          }
        }
        break;
    }
  }

  switch(p_cli->state)
  {
    case CLI_RX_SP1:
      p_cli->state = CLI_RX_SP2;
      break;

    case CLI_RX_SP2:
      p_cli->state = CLI_RX_SP3;
      break;

    case CLI_RX_SP3:
      p_cli->state = CLI_RX_IDLE;

      if (rx_data == CLI_KEY_LEFT)
      {
        if (line->cursor > 0)
        {
          line->cursor--;
          tx_buf[0] = 0x1B;
          tx_buf[1] = 0x5B;
          tx_buf[2] = rx_data;
          uart_write(p_cli->ch, tx_buf, 3);
        }
      }

      if (rx_data == CLI_KEY_RIGHT)
      {
        if (line->cursor < line->buf_len)
        {
          line->cursor++;
        }
        tx_buf[0] = 0x1B;
        tx_buf[1] = 0x5B;
        tx_buf[2] = rx_data;
        uart_write(p_cli->ch, tx_buf, 3);
      }

      if (rx_data == CLI_KEY_UP)
      {
        cli_line_change(p_cli, true);
        uart_printf(p_cli->ch, (char *)p_cli->line.buf);
      }

      if (rx_data == CLI_KEY_DOWN)
      {
        cli_line_change(p_cli, false);
        uart_printf(p_cli->ch, (char *)p_cli->line.buf);
      }

      if (rx_data == CLI_KEY_HOME)
      {
        uart_printf(p_cli->ch, "\x1B[%dD", line->cursor);
        line->cursor = 0;

        p_cli->state = CLI_RX_SP4;
      }

      if (rx_data == CLI_KEY_END)
      {
        uint16_t mov_len;

        if (line->cursor < line->count)
        {
          mov_len = line->count - line->cursor;
          uart_printf(p_cli->ch, "\x1B[%dC", mov_len);
        }
        if (line->cursor > line->count)
        {
          mov_len = line->cursor - line->count;
          uart_printf(p_cli->ch, "\x1B[%dD", mov_len);
        }
        line->cursor = line->count;
        p_cli->state = CLI_RX_SP4;
      }
      break;

    case CLI_RX_SP4:
      p_cli->state = CLI_RX_IDLE;
      break;
  }



  cli_show_log(p_cli);

  return ret;
}

void cli_line_clean(cli_t *p_cli)
{
  p_cli->line.count   = 0;
  p_cli->line.cursor  = 0;
  p_cli->line.buf_len = CLI_LINE_BUF_MAX - 1;
  p_cli->line.buf[0]  = 0;
}

void cli_line_add(cli_t *p_cli)
{

  p_cli->line_buf[p_cli->hist_line_last] = p_cli->line;

  if (p_cli->hist_line_count < CLI_LINE_HIS_MAX)
  {
    p_cli->hist_line_count++;
  }

  p_cli->hist_line_i    = p_cli->hist_line_last;
  p_cli->hist_line_last = (p_cli->hist_line_last + 1) % CLI_LINE_HIS_MAX;
  p_cli->hist_line_new  = true;
}

void cli_line_change(cli_t *p_cli, int8_t key_up)
{
  uint8_t change_i;


  if (p_cli->hist_line_count == 0)
  {
    return;
  }


  if (p_cli->line.cursor > 0)
  {
    uart_printf(p_cli->ch, "\x1B[%dD", p_cli->line.cursor);
  }
  if (p_cli->line.count > 0)
  {
    uart_printf(p_cli->ch, "\x1B[%dP", p_cli->line.count);
  }


  if (key_up == true)
  {
    if (p_cli->hist_line_new == true)
    {
      p_cli->hist_line_i = p_cli->hist_line_last;
    }
    p_cli->hist_line_i = (p_cli->hist_line_i + p_cli->hist_line_count - 1) % p_cli->hist_line_count;
    change_i = p_cli->hist_line_i;
  }
  else
  {
    p_cli->hist_line_i = (p_cli->hist_line_i + 1) % p_cli->hist_line_count;
    change_i = p_cli->hist_line_i;
  }

  p_cli->line = p_cli->line_buf[change_i];
  p_cli->line.cursor = p_cli->line.count;

  p_cli->hist_line_new = false;
}

bool cli_run_cmd(cli_t *p_cli)
{
  bool ret = false;


  if (cli_parse_args(p_cli) == true)
  {
    cli_printf("\r\n");

    cli_to_upper(p_cli->argv[0]);

    for (int i=0; i<p_cli->cmd_count; i++)
    {
      if (strcmp(p_cli->argv[0], p_cli->cmd_list[i].cmd_str) == 0)
      {
        p_cli->cmd_args.argc =  p_cli->argc - 1;
        p_cli->cmd_args.argv = &p_cli->argv[1];
        p_cli->cmd_list[i].cmd_func(&p_cli->cmd_args);
        break;
      }
    }
  }

  return ret;
}

bool cli_parse_args(cli_t *p_cli)
{
  bool ret = false;
  char *tok;
  char *next_ptr;
  uint16_t argc = 0;
  static const char *delim = " \f\n\r\t\v";
  char *cmdline;
  char **argv;

  p_cli->argc = 0;

  cmdline = (char *)p_cli->line.buf;
  argv    = p_cli->argv;

  argv[argc] = NULL;

  for (tok = strtok_r(cmdline, delim, &next_ptr); tok; tok = strtok_r(NULL, delim, &next_ptr))
  {
    argv[argc++] = tok;
  }

  p_cli->argc = argc;

  if (argc > 0)
  {
    ret = true;
  }

  return ret;
}

void cli_printf(const char *fmt, ...)
{
  va_list arg;
  va_start (arg, fmt);
  int32_t len;
  cli_t *p_cli = &cli_node;


  len = vsnprintf(p_cli->print_buffer, 256, fmt, arg);
  va_end (arg);

  uart_write(p_cli->ch, (uint8_t *)p_cli->print_buffer, len);
}

void cli_to_upper(char *str)
{
  uint16_t i;
  uint8_t  str_ch;

  for (i=0; i<CLI_CMD_NAME_MAX; i++)
  {
    str_ch = str[i];

    if (str_ch == 0)
    {
      break;
    }

    if ((str_ch >= 'a') && (str_ch <= 'z'))
    {
      str_ch = str_ch - 'a' + 'A';
    }
    str[i] = str_ch;
  }

  if (i == CLI_CMD_NAME_MAX)
  {
    str[i-1] = 0;
  }
}

int32_t cli_args_get_data(uint8_t index)
{
  int32_t ret = 0;
  cli_t *p_cli = &cli_node;


  if (index >= p_cli->cmd_args.argc)
  {
    return 0;
  }

  ret = (int32_t)strtoul((const char * ) p_cli->cmd_args.argv[index], (char **)NULL, (int) 0);

  return ret;
}

float cli_args_get_float(uint8_t index)
{
  float ret = 0.0;
  cli_t *p_cli = &cli_node;


  if (index >= p_cli->cmd_args.argc)
  {
    return 0;
  }

  ret = (float)strtof((const char * ) p_cli->cmd_args.argv[index], (char **)NULL);

  return ret;
}

char *cli_args_get_str(uint8_t index)
{
  char *ret = NULL;
  cli_t *p_cli = &cli_node;


  if (index >= p_cli->cmd_args.argc)
  {
    return 0;
  }

  ret = p_cli->cmd_args.argv[index];

  return ret;
}

bool cli_args_is_str(uint8_t index, char *p_str)
{
  bool ret = false;
  cli_t *p_cli = &cli_node;


  if (index >= p_cli->cmd_args.argc)
  {
    return 0;
  }

  if(strcmp(p_str, p_cli->cmd_args.argv[index]) == 0)
  {
    ret = true;
  }

  return ret;
}

bool cli_keep_loop(void)
{
  cli_t *p_cli = &cli_node;


  if (uart_available(p_cli->ch) == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool cli_add(const char *cmd_str, void (*p_func)(cli_args_t *))
{
  bool ret = true;
  cli_t *p_cli = &cli_node;
  uint16_t index;

  if (p_cli->cmd_count >= CLI_CMD_LIST_MAX)
  {
    return false;
  }

  index = p_cli->cmd_count;

  strcpy(p_cli->cmd_list[index].cmd_str, cmd_str);
  p_cli->cmd_list[index].cmd_func = p_func;

  cli_to_upper(p_cli->cmd_list[index].cmd_str);

  p_cli->cmd_count++;

  return ret;
}

void cli_show_list(cli_args_t *args)
{
  cli_t *p_cli = &cli_node;


  cli_printf("\r\n");
  cli_printf("---------- cmd list ---------\r\n");

  for (int i=0; i<p_cli->cmd_count; i++)
  {
    cli_printf(p_cli->cmd_list[i].cmd_str);
    cli_printf("\r\n");
  }

  cli_printf("-----------------------------\r\n");
}

void cli_memory_dump(cli_args_t *args)
{
  int idx, size = 16;
  unsigned int *addr;
  int idx1, i;
  unsigned int *ascptr;
  unsigned char asc[4];

  int    argc = args->argc;
  char **argv = args->argv;


  if(args->argc < 1)
  {
    cli_printf(">> md addr [size] \n");
    return;
  }

  if(argc > 1)
  {
    size = (int)strtoul((const char * ) argv[1], (char **)NULL, (int) 0);
  }
  addr   = (unsigned int *)strtoul((const char * ) argv[0], (char **)NULL, (int) 0);
  ascptr = (unsigned int *)addr;

  cli_printf("\n   ");
  for (idx = 0; idx<size; idx++)
  {
    if((idx%4) == 0)
    {
      cli_printf(" 0x%08X: ", (unsigned int)addr);
    }
    cli_printf(" 0x%08X", *(addr));

    if ((idx%4) == 3)
    {
      cli_printf ("  |");
      for (idx1= 0; idx1< 4; idx1++)
      {
        memcpy((char *)asc, (char *)ascptr, 4);
        for (i=0;i<4;i++)
        {
          if (asc[i] > 0x1f && asc[i] < 0x7f)
          {
            cli_printf("%c", asc[i]);
          }
          else
          {
            cli_printf(".");
          }
        }
        ascptr+=1;
      }
      cli_printf("|\n   ");
    }
    addr++;
  }
}

