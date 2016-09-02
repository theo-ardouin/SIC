#ifndef SIC_H_
#define SIC_H_

#include "consumer.h"

#define SIC_ERR        "SIC Fatal Error"
#define SIC_ENTRY      "_main_"
#define SIC_SYMBOLS    "\'\"`[$*+~"

typedef enum sc_e_rules
{
  SC_RL_INTERNAL = 0,
  SC_RL_STRING,
  SC_RL_COUNT
} sc_rules;

typedef struct s_sic
{
  sc_consumer_t* input;
  sc_hashmp_t* rules[SC_RL_COUNT];
  sc_hashmp_t* save;
  char _err;
} sic_t;

struct sc_s_rl;
struct sc_s_rlint;
typedef int (*sc_rlintfunc)(sic_t*, sc_consumer_t*, struct sc_s_rlint*);
typedef int (*sc_rlfunc)(sic_t*, sc_consumer_t*, struct sc_s_rl*);

typedef struct sc_s_rlint
{
  const char* rule;
  const char* name;
  sc_rlintfunc func;
} sc_rlint_t; //Internal rule

typedef struct sc_s_rl
{
  char* name;
  char* save;
} sc_rl_t;

sic_t* sc_create();
int sc_load_file(sic_t*, const char*);
void sc_add_srule(sic_t*, const char*, const char*);
//int sbnf_add_frule(sic_t*, const char*, );

int sc_parse(sic_t*, const char*, unsigned);

//destroy()
// -> free save = *VALUES + KEYS*

///Internal logic

int _sc_setrl(sic_t*, sc_consumer_t*, sc_rl_t*);

int _sc_eval_rl(sic_t*, sc_consumer_t*, sc_rl_t*);
int _sc_eval_intrl(sic_t*, sc_consumer_t*, sc_rl_t*);
int _sc_eval_strrl(sic_t*, sc_consumer_t*, sc_rl_t*);
int _sc_eval_simplist_rl(sic_t*, sc_consumer_t*);

sic_t* _sc_set_intrl(sic_t*);

int _sc_char(sic_t*, sc_consumer_t*, sc_rlint_t*);
int _sc_string(sic_t*, sc_consumer_t*, sc_rlint_t*);
int _sc_ncstring(sic_t*, sc_consumer_t*, sc_rlint_t*);
int _sc_optional(sic_t*, sc_consumer_t*, sc_rlint_t*);
int _sc_whitespaces(sic_t*, sc_consumer_t*, sc_rlint_t*);

int _sc_digit(sic_t*, sc_consumer_t*, sc_rlint_t*);
int _sc_num(sic_t*, sc_consumer_t*, sc_rlint_t*);
int _sc_alpha(sic_t*, sc_consumer_t*, sc_rlint_t*);
int _sc_word(sic_t*, sc_consumer_t*, sc_rlint_t*);
int _sc_alnum(sic_t*, sc_consumer_t*, sc_rlint_t*);
int _sc_eol(sic_t*, sc_consumer_t*, sc_rlint_t*);

int _sc_internal_err(sic_t*, sc_consumer_t*, sc_rlint_t*);

int _sc_tkn_cntnt(sic_t*, sc_consumer_t*, sc_rlint_t* rlint, const char*, char**);

#endif