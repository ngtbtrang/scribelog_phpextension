#ifndef PHP_LOGSCRIBE_H
#define PHP_LOGSCRIBE_H 1

#ifdef ZTS
#include "TSRM.h"
#endif

#include "scribe_c.h"

#define PHP_LOGSCRIBE_WORLD_VERSION "1.0"
#define PHP_LOGSCRIBE_WORLD_EXTNAME "logscribe"

PHP_FUNCTION(scribelog);

extern zend_module_entry logscribe_module_entry;
#define phpext_logscribe_ptr &logscribe_module_entry

#endif
