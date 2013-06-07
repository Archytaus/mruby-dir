#include "mrb_dir.h"
#include "tinydir.h"

#include <mruby/array.h>
#include <mruby/string.h>

static struct RClass* mrb_dir_class = NULL;

mrb_value 
mrb_dir_entries(mrb_state* mrb, mrb_value self)
{
  mrb_value entries = mrb_ary_new(mrb);
  mrb_value dirname;
  mrb_get_args(mrb, "S", &dirname);
  const char* name = mrb_string_value_ptr(mrb, dirname);

  tinydir_dir dir;  
  if (tinydir_open(&dir, name) == -1)
  {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "Error opening file: %s", name);
  }

  while (dir.has_next) {
    tinydir_file file;
    tinydir_readfile(&dir, &file);
    
    mrb_ary_push(mrb, entries, mrb_str_new_cstr(mrb, file.name));
      
    tinydir_next(&dir);
  } 
  tinydir_close(&dir);

  

  return entries;
}


void
mrb_mruby_dir_gem_init(mrb_state* mrb) {
  mrb_dir_class = mrb_define_module(mrb, "Dir");
  mrb_define_module_function(mrb, mrb_dir_class, "entries", mrb_dir_entries, MRB_ARGS_REQ(1));
}

void
mrb_mruby_dir_gem_final(mrb_state* mrb) {
  // finalizer
}
