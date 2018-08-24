typedef char* string_t;

typedef struct {
  string_t id, name, sex, age, height, weight, team, noc, games,
  year, season, city, sport, event, medal;
} data_t;

typedef struct node_t {
  data_t data;
  struct node_t *left, *right;
} node_t;

node_t *makedict(data_t data);
node_t *insert(node_t *parent, data_t data);
