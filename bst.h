
#define MAX_LINE_LEN 513
#define MAX_STR_LEN 129
#define OUTPUT_FIELDS 13
#define FIELD_STR_LEN 7
#define TRUE 1
#define FALSE 0

// Counter definitions
#define INCREMENT 0
#define RESET 1
#define RETURN 2

typedef char* string_t;

typedef struct {
  string_t id, name, sex, age, height, weight, team, noc, games,
  year, season, city, sport, event, medal;
} data_t;

typedef struct node_t{
  data_t data;
  struct node_t *left, *right, *next;
} node_t;

// Dictionary functions
node_t *make_dict(data_t data);
node_t *insert_dict(node_t *parent, data_t data);
void search_dict(node_t *parent, string_t name, FILE *out, int *found_match);
void free_dict(node_t *parent);
void output_data(data_t *data, FILE *out);

// I/O and counter functions
void read_data(data_t *data, string_t input);
void strip_trailing_newline(string_t string);
int counter(int delta, int key);
