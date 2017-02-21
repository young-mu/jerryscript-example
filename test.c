#include <string.h>
#include "jerryscript.h"
#include "jerry-port.h"
#include "jerry-port-default.h"

int main (int argc, char *argv[])
{
    const jerry_char_t script[] = "print ('Hello, World!');";
    size_t script_size = strlen((const char *)script);

    jerry_init(JERRY_INIT_MEM_STATS);
    jerry_port_default_set_log_level(JERRY_LOG_LEVEL_DEBUG);

    jerry_value_t parsed_code = jerry_parse(script, script_size, false);

    if (jerry_value_has_error_flag(parsed_code)) {
        printf("jerry_parse failed\n");
        goto CLEANUP;
    }

    jerry_value_t ret_value = jerry_run(parsed_code);
    jerry_release_value(ret_value);

CLEANUP:
    jerry_release_value(parsed_code);
    jerry_cleanup();

    return 0;
}
