#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include "standart_converts.h"

#define TITLE \
" _ .-') _  _  .-')     ('-.  _   .-')      ('-.                                          .-') _      (`-.      ('-.  _  .-')   .-') _     ('-.  _  .-')\n" \
"( (  OO) )( \\( -O )  _(  OO)( '.( OO )_   ( OO ).-.                                     ( OO ) )   _(OO  )_  _(  OO)( \\( -O ) (  OO) )  _(  OO)( \\( -O )  \n" \
" \\     .'_ ,------. (,------.,--.   ,--.) / . --. /            .-----.  .-'),-----. ,--./ ,--,',--(_/   ,. \\(,------.,------. /     '._(,------.,------.  \n" \
" ,`'--..._)|   /`. ' |  .---'|   `.'   |  | \\-.  \\            '  .--./ ( OO'  .-.  '|   \\ |  |\\\\   \\   /(__/ |  .---'|   /`. '|'--...__)|  .---'|   /`. ' \n" \
" |  |  \\  '|  /  | | |  |    |         |.-'-'  |  |           |  |('-. /   |  | |  ||    \\|  | )\\   \\ /   /  |  |    |  /  | |'--.  .--'|  |    |  /  | | \n" \
" |  |   ' ||  |_.' |(|  '--. |  |'.'|  | \\| |_.'  |  (`-.    /_) |OO  )\\_) |  |\\|  ||  .     |/  \\   '   /, (|  '--. |  |_.' |   |  |  (|  '--. |  |_.' | \n" \
" |  |   / :|  .  '.' |  .--' |  |   |  |  |  .-.  | (OO  )_  ||  |`-'|   \\ |  | |  ||  |\\    |    \\     /__) |  .--' |  .  '.'   |  |   |  .--' |  .  '.' \n" \
" |  '--'  /|  |\\  \\  |  `---.|  |   |  |  |  | |  |,------.)(_'  '--'\\    `'  '-'  '|  | \\   |     \\   /     |  `---.|  |\\  \\    |  |   |  `---.|  |\\  \\  \n" \
" `-------' `--' '--' `------'`--'   `--'  `--' `--'`------'    `-----'      `-----' `--'  `--'      `-'      `------'`--' '--'   `--'   `------'`--' '--'\n"

#define HELP_MSG \
"Converts text files to binary and vise versa, according to specified C types\n" \
"You should specify way of converting with -t (text to binary) or -b (binary to text)\n" \
"To specify used C type use -T TYPE, allowed types are listed below\n" \
"Then you may specify output file with -o OUT_FILE, or convert.out will be used as default\n" \
"The last passed argument will be considered as input FILE"\
"Flags:\n" \
"    -h              Outputs help message\n" \
"    -t              Sets convert way to T2B (text to binary)\n" \
"    -b              Sets convert way to B2T (binary to text)\n" \
"                    You always have to use either -t or -b!\n" \
"    -T TYPE         Sets C type used for convertion\n" \
"    -o OUT_FILE    Sets output file, convert.out will be used as default\n" \
"Allowed C types: int, long, int64_t, int32_t, float, double, char"

#define EMPTY_ARGS {0, 0, 0, 0, 0, 0, NULL, NULL}

#define OK 0
#define ERR_ARGS 1
#define ERR_FILES 2
#define ERR_TYPE 3
#define ERR_UNEXPECTED 4

#define UNSET 0
#define SET 1
#define SETTING 2

#define TYPE_COUNT 7
static char *TypeNames[TYPE_COUNT] = {
    "int",
    "long",
    "int64_t",
    "int32_t",
    "float",
    "double",
    "char"
};

typedef enum Types {
    INT,
    LONG,
    INT64_T,
    INT32_T,
    FLOAT,
    DOUBLE,
    CHAR,
    NOT_A_TYPE
} Types;

#define FLAG_COUNT 5
static char *FlagNames[FLAG_COUNT] = {
    "-h",
    "-t",
    "-b",
    "-T",
    "-o"
};

typedef enum Flags {
    HELP,
    T2B,
    B2T,
    TYPE,
    OUTPUT,
    NOT_A_FLAG
} Flags;

typedef struct arguments {
    unsigned help: 1;
    unsigned t2b: 1;
    unsigned b2t: 1;
    unsigned type: 2;
    unsigned output: 2;
    unsigned errors: 1;
    const char *c_type;
    const char *out_file;
    const char *target_file;
} Arguments;

Flags parse_flag(const char *str);
Types parse_type(const char *str);
void print_help(char *file_name);
void print_usage(char *file_name);
void parse_args(Arguments *args, int argc, char *argv[]);
int run_convert_t2b(Types type, FILE *in, FILE *out);
int run_convert_b2t(Types type, FILE *in, FILE *out, char *delimeter, char *end);
int run(Arguments *args, char *file_name);

#ifdef DEBUG
void print_args(Arguments *args)
{
    printf("Help: %d\n", args->help);
    printf("T2B: %d\n", args->t2b);
    printf("B2T: %d\n", args->b2t);
    printf("Type: %d\n", args->type);
    printf("Output: %d\n", args->output);
    printf("C type: %s\n", args->c_type);
    printf("Out file: %s\n", args->out_file);
    printf("Target file: %s\n", args->target_file);
    printf("Errors: %d\n", args->errors);
}
#endif

int main(int argc, char *argv[])
{
    Arguments args = EMPTY_ARGS;

    parse_args(&args, argc, argv);

    return run(&args, argv[0]);
}

int run(Arguments *args, char *file_name)
{
    int return_code = OK;

    if (args->errors)
    {
        return_code = ERR_ARGS;
        printf("Program syntax error, use -h key to get help message!\n");
        print_usage(file_name);
    }
    else if (args->help)
    {
        print_help(file_name);
    }
    else
    {
        Types type = parse_type(args->c_type);

        if (type == NOT_A_TYPE)
        {
            printf("Wrong C type: %s", args->c_type);
            return_code = ERR_TYPE;
        }

        const char *out_path = args->out_file == NULL ? "convert.out" : args->out_file;
        FILE *in, *out;

        if (args->t2b)
        {
            in = fopen(args->target_file, "r");
            out = fopen(out_path, "wb");
        }
        else if (args->b2t)
        {
            in = fopen(args->target_file, "rb");
            out = fopen(out_path, "w");
        }
        else
        {
            puts("Unexpected error occured!");
            return_code = ERR_UNEXPECTED;
        }

        if (in == NULL)
        {
            printf("Error when opening input file: %s\n", args->target_file);
            return_code = ERR_FILES;
        }

        if (out == NULL)
        {
            printf("Error when opening output file: %s\n", out_path);
            return_code = ERR_FILES;
        }

        if (return_code == OK)
        {
            if (args->t2b)
            {
                return_code = run_convert_t2b(type, in, out);
            }
            else if (args->b2t)
            {
                return_code = run_convert_b2t(type, in, out, " ", "\n");
            }
            else
            {
                puts("Unexpected error occured!");
                return_code = ERR_UNEXPECTED;
            }
        }
    }

    if (return_code == OK)
        puts("Succesfully converted file!");

    return return_code;
}

int run_convert_t2b(Types type, FILE *in, FILE *out)
{
    int return_code = OK;
    switch (type)
    {
        case INT:
            return_code = CONVERT_T2B(int, in, out);
            break;
        case LONG:
            return_code = CONVERT_T2B(long, in, out);
            break;
        case INT64_T:
            return_code = CONVERT_T2B(int64_t, in, out);
            break;
        case INT32_T:
            return_code = CONVERT_T2B(int32_t, in, out);
            break;
        case FLOAT:
            return_code = CONVERT_T2B(float, in, out);
            break;
        case DOUBLE:
            return_code = CONVERT_T2B(double, in, out);
            break;
        case CHAR:
            return_code = CONVERT_T2B(char, in, out);
            break;
        default:
            puts("Unexpected error occured!");
            return_code = ERR_UNEXPECTED;
    }

    if (return_code == ERR_READ)
        puts("Error when reading file occured!");

    return return_code;
}

int run_convert_b2t(Types type, FILE *in, FILE *out, char *delimeter, char *end)
{
    int return_code = OK;
    switch (type)
    {
        case INT:
            return_code = CONVERT_B2T(int, in, out, delimeter, end);
            break;
        case LONG:
            return_code = CONVERT_B2T(long, in, out, delimeter, end);
            break;
        case INT64_T:
            return_code = CONVERT_B2T(int64_t, in, out, delimeter, end);
            break;
        case INT32_T:
            return_code = CONVERT_B2T(int32_t, in, out, delimeter, end);
            break;
        case FLOAT:
            return_code = CONVERT_B2T(float, in, out, delimeter, end);
            break;
        case DOUBLE:
            return_code = CONVERT_B2T(double, in, out, delimeter, end);
            break;
        case CHAR:
            return_code = CONVERT_B2T(char, in, out, delimeter, end);
            break;
        default:
            puts("Unexpected error occured!");
            return_code = ERR_UNEXPECTED;
    }

    if (return_code == ERR_READ)
        puts("Error when reading file occured!");

    return return_code;
}

void print_usage(char *file_name)
{
    printf("Usage: %s [PARAM...] [FILE]\n", file_name);
}

void parse_args(Arguments *args, int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        char *cur_arg = argv[i];
        if (args->type == SETTING)
        {
            args->c_type = cur_arg;
            args->type = SET;
        }
        else if (args->output == SETTING)
        {
            args->out_file = cur_arg;
            args->output = SET;
        }
        else
        {
            Flags flag = parse_flag(cur_arg);
            switch (flag)
            {
                case HELP:
                    if (args->help & SET)
                        args->errors = SET;
                    args->help = SET;
                    break;
                case T2B:
                    if (args->t2b & SET)
                        args->errors = SET;
                    args->t2b = SET;
                    break;
                case B2T:
                    if (args->b2t & SET)
                        args->errors = SET;
                    args->b2t = SET;
                    break;
                case TYPE:
                    if (args->type & SET | args->type & SETTING)
                        args->errors = SET;
                    else
                        args->type = SETTING;
                    break;
                case OUTPUT:
                    if (args->output & SET | args->output & SETTING)
                        args->errors = SET;
                    else
                        args->output = SETTING;
                    break;
                default:
                    if (i == argc - 1)
                        args->target_file = argv[i];
                    else
                        args->errors = SET;
                    break;
            }
        }
    }

    args->errors = (args->errors) |
                   (args->type == SETTING) |
                   (args->output == SETTING) |
                   (args->help & (args->type | args->output | args->t2b | args->b2t)) |
                   (~args->help & ((args->c_type == NULL) | ((args->output & SET) & args->out_file == NULL) | ~(args->t2b ^ args->b2t) | (args->target_file == NULL)));
}

Flags parse_flag(const char *str)
{
    Flags flag = NOT_A_FLAG;
    for (int i = 0; i < FLAG_COUNT; i++)
        if (strcmp(str, FlagNames[i]) == 0)
        {
            flag = i;
            break;
        }

    return flag;
}

Types parse_type(const char *str)
{
    Types type = NOT_A_TYPE;
    for (int i = 0; i < TYPE_COUNT; i++)
        if (strcmp(str, TypeNames[i]) == 0)
        {
            type = i;
            break;
        }

    return type;
}

void print_help(char *file_name)
{
    puts(TITLE);
    print_usage(file_name);
    puts(HELP_MSG);
}
