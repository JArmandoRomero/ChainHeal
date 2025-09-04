#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct node
{
  char *name;
  int x, y;
  int cur_PP, max_PP;
  int adj_size;
  bool visited;
  struct node **adj_list;
};

struct params
{
  int initial_range;
  int jump_range;
  int num_jumps;
  int initial_power;
  double power_reduction;
};

struct answer
{
  int best_path_length;
  int current_path_length;
  struct node **best;
  struct node **current;
  int best_healing;
};

struct node **create_nodes_array(size_t *n)
{
}

bool adjacent(int jump_range, struct node *a, struct node *b)
{
}

void setup_graph(int jump_range, size_t num_nodes, struct node **nodes)
{
}

void print_adjacency(size_t num_nodes, struct node **nodes)
{
}

void check_best(struct params *p, struct answer *a)
{
}

void print_best(struct params *p, struct answer *a)
{
}

void dfs(struct params *p, struct answer *a, int depth, struct node *n)
{
}

int main(int argc, char **argv)
{
  if (argc < 6)
  {
    fprintf(stderr, "usage: %s initial_range jump_range num_jumps initial_power power_reduction < input_file\n", argv[0]);
    return 0;
  }

  struct params p;
  struct answer a = {0};
  // Buffer for standard input

  char buffer[1024];

  // parse command line parameters on to the params struct
  p.initial_range = atoi(argv[1]);
  p.jump_range = atoi(argv[2]);
  p.num_jumps = atoi(argv[3]);
  p.initial_power = atoi(argv[4]);
  p.power_reduction = atof(argv[5]);

  struct node n;

  while (fgets(buffer, sizeof(buffer), stdin))
  {
    // Strip trailing \r\n
    buffer[strcspn(buffer, "\r\n")] = '\0';

    int count = sscanf(buffer, "%d %d %d %d %127[^\n]",
                       &n.x, &n.y, &n.cur_PP, &n.max_PP, n.name);

    if (count == 5)
    {
      printf("x: %d\n", n.x);
      printf("y: %d\n", n.y);
      printf("curr_PP: %d\n", n.cur_PP);
      printf("max_PP: %d\n", n.max_PP);
      printf("name: %s\n", n.name);
      printf("----\n");
    }
    else
    {
      fprintf(stderr, "Line didn't match format: %s\n", buffer);
    }
  }

  /*
    Parse Debugfing
  printf("%d\n", p.initial_range);
  printf("%d\n", p.jump_range);
  printf("%d\n", p.num_jumps);
  printf("%d\n", p.initial_power);
  printf("%.2f\n", p.power_reduction);

  */

  // cleanup:

  return 0;
}
