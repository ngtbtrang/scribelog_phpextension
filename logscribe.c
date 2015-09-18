#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "php_logscribe.h"
#include "time.h"

enum stateScribe {
	SCRIBE_OK = 0,
	SCRIBE_PARAM_WRONG,
	SCRIBE_OPEN_FAIL,
	SCRIBE_WRITE_FAIL,
	SCRIBE_CLOSE_FAIL
};

const zend_function_entry logscribe_functions[] = {
    PHP_FE(scribelog, NULL)
    {NULL, NULL, NULL}
};

zend_module_entry logscribe_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_LOGSCRIBE_WORLD_EXTNAME,
    logscribe_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
#if ZEND_MODULE_API_NO >= 20010901
    PHP_LOGSCRIBE_WORLD_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_LOGSCRIBE
ZEND_GET_MODULE(logscribe)
#endif

PHP_FUNCTION(scribelog)
{	
	char* host = NULL;
	int port = 1463;
	char* category = NULL;
	char* log = NULL;
	int stringlen1, stringlen2, stringlen3;
	scribe_t *slog = malloc(sizeof(scribe_t));
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|ssl", &log, &stringlen1, &category, &stringlen2, &host, &stringlen3, &port) == FAILURE)
	{
		php_log_err("Parameters of scribe: type of variable is wrong\n");
		RETURN_LONG(SCRIBE_PARAM_WRONG);
	}
	
	if (host == NULL)
	{
		host = "localhost";
	}
	if (category == NULL)
	{
		category = "default";
	}
	
	if (scribe_open(slog, host, port))
	{
		php_log_err("Can't open scribe\n");
		free(slog);
		RETURN_LONG(SCRIBE_OPEN_FAIL);
	} 
	
	if (scribe_write(slog, category, log))
	{
		php_log_err("Can't write log to scribe\n");
		free(slog);
		RETURN_LONG(SCRIBE_WRITE_FAIL);
	}
	if (scribe_close(slog))
	{
		php_log_err("Can't close scribe\n");
		free(slog);
		RETURN_LONG(SCRIBE_CLOSE_FAIL);
	}

	free(slog);
	RETURN_LONG(SCRIBE_OK);
}
