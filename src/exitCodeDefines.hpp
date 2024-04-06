#ifndef ERROR_CODE_DEFINES_H
#define ERROR_CODE_DEFINES_H

#define EXIT_CODE_OK 0
#define EXIT_CODE_DISPLAYED_HELP 1      // Returned when --help or -h is provided as an argument. 
                                        // Help was displayed, simulator did not run.
#define EXIT_CODE_LINE_ARGUMENT_ERROR 2 // For incorrect command line arguments.

#endif /* ERROR_CODE_DEFINES_H */