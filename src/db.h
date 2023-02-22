#include <unistd.h>

#ifndef DB_H
#define DB_H
#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255
#define size_of_attribute(Struct, Attribute) sizeof(((Struct *)0)->Attribute)
#define TABLE_MAX_PAGES 100
#endif

typedef struct {
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE];
    char email[COLUMN_EMAIL_SIZE];
} Row;

typedef struct {
    char *buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

typedef enum { META_COMMAND_SUCCESS, META_COMMAND_UNRECOGNIZED_COMMAND } MetaCommandResult;

typedef enum {
    PREPARE_SUCCESS,
    PREPARE_SYNTAX_ERROR,
    PREPARE_UNRECOGNIZED_STATEMENT,
} PrepareResult;

typedef enum { EXECUTE_SUCCESS, EXECUTE_TABLE_FULL } ExecuteResult;

typedef enum { STATEMENT_INSERT, STATEMENT_SELECT } StatementType;

typedef struct {
    StatementType type;
    Row row_to_insert;  // only used by insert statement
} Statement;

typedef struct {
    uint32_t num_rows;
    void *pages[TABLE_MAX_PAGES];
} Table;

InputBuffer *new_input_buffer();
void print_prompt();
void read_input(InputBuffer *input_buffer);
void close_input_buffer(InputBuffer *input_buffer);

MetaCommandResult do_meta_command(InputBuffer *input_buffer);
PrepareResult prepare_statement(InputBuffer *input_buffer, Statement *statement);
ExecuteResult execute_insert(Statement *statement, Table *table);
ExecuteResult execute_select(Statement *statement, Table *table);
ExecuteResult execute_statement(Statement *statement, Table *table);

void print_row(Row *row);
void serialize_row(Row *source, void *destination);
void deseraialze_row(void *source, Row *destination);
void *row_slot(Table *table, uint32_t row_num);
Table *new_table();
void free_table(Table *table);